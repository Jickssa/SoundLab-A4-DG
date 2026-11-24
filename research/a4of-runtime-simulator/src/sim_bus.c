#include "a4of/sim_bus.h"

#include <string.h>

static int width_ok(uint8_t width) {
    return width == 1u || width == 2u || width == 4u;
}

static int ranges_overlap(uint32_t a_base, uint32_t a_size,
                          uint32_t b_base, uint32_t b_size) {
    const uint64_t a_end = (uint64_t)a_base + a_size;
    const uint64_t b_end = (uint64_t)b_base + b_size;
    return (uint64_t)a_base < b_end && (uint64_t)b_base < a_end;
}

static a4of_sim_status_t map_region(
    a4of_sim_bus_t *bus, uint32_t base, uint32_t size, uint8_t permissions,
    uint8_t *memory, a4of_sim_device_read_fn read_fn,
    a4of_sim_device_write_fn write_fn, void *context, const char *name) {
    if (bus == NULL) return A4OF_SIM_ERR_NULL;
    if (size == 0u || permissions == 0u ||
        (permissions & (uint8_t)~7u) != 0u) return A4OF_SIM_ERR_ARGUMENT;
    if ((uint64_t)base + size > (uint64_t)UINT32_MAX + 1u)
        return A4OF_SIM_ERR_RANGE;
    if (bus->region_count >= A4OF_SIM_MAX_REGIONS) return A4OF_SIM_ERR_FULL;
    for (size_t i = 0; i < bus->region_count; ++i) {
        if (ranges_overlap(base, size, bus->regions[i].base, bus->regions[i].size))
            return A4OF_SIM_ERR_OVERLAP;
    }
    a4of_sim_region_t *region = &bus->regions[bus->region_count++];
    region->base = base;
    region->size = size;
    region->permissions = permissions;
    region->memory = memory;
    region->read = read_fn;
    region->write = write_fn;
    region->context = context;
    region->name = name;
    return A4OF_SIM_OK;
}

void a4of_sim_bus_init(a4of_sim_bus_t *bus) {
    if (bus != NULL) memset(bus, 0, sizeof(*bus));
}

a4of_sim_status_t a4of_sim_bus_map_memory(
    a4of_sim_bus_t *bus, uint32_t base, uint32_t size,
    uint8_t permissions, uint8_t *memory, const char *name) {
    if (memory == NULL) return A4OF_SIM_ERR_NULL;
    return map_region(bus, base, size, permissions, memory, NULL, NULL, NULL, name);
}

a4of_sim_status_t a4of_sim_bus_map_device(
    a4of_sim_bus_t *bus, uint32_t base, uint32_t size, uint8_t permissions,
    a4of_sim_device_read_fn read_fn, a4of_sim_device_write_fn write_fn,
    void *context, const char *name) {
    if (read_fn == NULL && write_fn == NULL) return A4OF_SIM_ERR_NULL;
    return map_region(bus, base, size, permissions, NULL, read_fn, write_fn, context, name);
}

static a4of_sim_region_t *find_region(a4of_sim_bus_t *bus, uint32_t address,
                                      uint8_t width) {
    const uint64_t end = (uint64_t)address + width;
    for (size_t i = 0; i < bus->region_count; ++i) {
        a4of_sim_region_t *region = &bus->regions[i];
        const uint64_t region_end = (uint64_t)region->base + region->size;
        if ((uint64_t)address >= region->base && end <= region_end) return region;
    }
    return NULL;
}

static a4of_sim_status_t record_fault(a4of_sim_bus_t *bus, uint32_t address,
                                      a4of_sim_status_t status) {
    bus->last_fault_address = address;
    bus->last_fault = status;
    return status;
}

static a4of_sim_status_t read_access(a4of_sim_bus_t *bus, uint32_t address,
                                     uint8_t width, uint32_t *value) {
    if (bus == NULL || value == NULL) return A4OF_SIM_ERR_NULL;
    if (!width_ok(width)) return A4OF_SIM_ERR_ARGUMENT;
    if (width > 1u && address % width != 0u)
        return record_fault(bus, address, A4OF_SIM_ERR_ALIGNMENT);

    a4of_sim_region_t *region = find_region(bus, address, width);
    if (region == NULL) return record_fault(bus, address, A4OF_SIM_ERR_UNMAPPED);
    if ((region->permissions & A4OF_SIM_MEM_READ) == 0u)
        return record_fault(bus, address, A4OF_SIM_ERR_PERMISSION);

    const uint32_t offset = address - region->base;
    a4of_sim_status_t status = A4OF_SIM_OK;
    if (region->memory != NULL) {
        const uint8_t *p = region->memory + offset;
        if (width == 1u) *value = p[0];
        else if (width == 2u) *value = ((uint32_t)p[0] << 8) | p[1];
        else *value = ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
                      ((uint32_t)p[2] << 8) | p[3];
    } else if (region->read != NULL) {
        status = region->read(region->context, offset, width, value);
        if (status != A4OF_SIM_OK) status = A4OF_SIM_ERR_DEVICE;
    } else {
        status = A4OF_SIM_ERR_DEVICE;
    }

    if (status == A4OF_SIM_OK) {
        ++bus->reads;
        bus->cycles += width;
    } else {
        record_fault(bus, address, status);
    }
    return status;
}

static a4of_sim_status_t write_access(a4of_sim_bus_t *bus, uint32_t address,
                                      uint8_t width, uint32_t value) {
    if (bus == NULL) return A4OF_SIM_ERR_NULL;
    if (!width_ok(width)) return A4OF_SIM_ERR_ARGUMENT;
    if (width > 1u && address % width != 0u)
        return record_fault(bus, address, A4OF_SIM_ERR_ALIGNMENT);

    a4of_sim_region_t *region = find_region(bus, address, width);
    if (region == NULL) return record_fault(bus, address, A4OF_SIM_ERR_UNMAPPED);
    if ((region->permissions & A4OF_SIM_MEM_WRITE) == 0u)
        return record_fault(bus, address, A4OF_SIM_ERR_PERMISSION);

    const uint32_t offset = address - region->base;
    a4of_sim_status_t status = A4OF_SIM_OK;
    if (region->memory != NULL) {
        uint8_t *p = region->memory + offset;
        if (width == 1u) p[0] = (uint8_t)value;
        else if (width == 2u) {
            p[0] = (uint8_t)(value >> 8);
            p[1] = (uint8_t)value;
        } else {
            p[0] = (uint8_t)(value >> 24);
            p[1] = (uint8_t)(value >> 16);
            p[2] = (uint8_t)(value >> 8);
            p[3] = (uint8_t)value;
        }
    } else if (region->write != NULL) {
        status = region->write(region->context, offset, width, value);
        if (status != A4OF_SIM_OK) status = A4OF_SIM_ERR_DEVICE;
    } else {
        status = A4OF_SIM_ERR_DEVICE;
    }

    if (status == A4OF_SIM_OK) {
        ++bus->writes;
        bus->cycles += width;
    } else {
        record_fault(bus, address, status);
    }
    return status;
}

a4of_sim_status_t a4of_sim_bus_read8(a4of_sim_bus_t *bus, uint32_t address,
                                     uint8_t *value) {
    if (value == NULL) return A4OF_SIM_ERR_NULL;
    uint32_t raw = 0u;
    const a4of_sim_status_t status = read_access(bus, address, 1u, &raw);
    if (status == A4OF_SIM_OK) *value = (uint8_t)raw;
    return status;
}

a4of_sim_status_t a4of_sim_bus_read16(a4of_sim_bus_t *bus, uint32_t address,
                                      uint16_t *value) {
    if (value == NULL) return A4OF_SIM_ERR_NULL;
    uint32_t raw = 0u;
    const a4of_sim_status_t status = read_access(bus, address, 2u, &raw);
    if (status == A4OF_SIM_OK) *value = (uint16_t)raw;
    return status;
}

a4of_sim_status_t a4of_sim_bus_read32(a4of_sim_bus_t *bus, uint32_t address,
                                      uint32_t *value) {
    return read_access(bus, address, 4u, value);
}

a4of_sim_status_t a4of_sim_bus_write8(a4of_sim_bus_t *bus, uint32_t address,
                                      uint8_t value) {
    return write_access(bus, address, 1u, value);
}

a4of_sim_status_t a4of_sim_bus_write16(a4of_sim_bus_t *bus, uint32_t address,
                                       uint16_t value) {
    return write_access(bus, address, 2u, value);
}

a4of_sim_status_t a4of_sim_bus_write32(a4of_sim_bus_t *bus, uint32_t address,
                                       uint32_t value) {
    return write_access(bus, address, 4u, value);
}

const char *a4of_sim_status_string(a4of_sim_status_t status) {
    switch (status) {
    case A4OF_SIM_OK: return "ok";
    case A4OF_SIM_ERR_NULL: return "null argument";
    case A4OF_SIM_ERR_ARGUMENT: return "invalid argument";
    case A4OF_SIM_ERR_FULL: return "region table full";
    case A4OF_SIM_ERR_OVERLAP: return "region overlap";
    case A4OF_SIM_ERR_UNMAPPED: return "unmapped address";
    case A4OF_SIM_ERR_RANGE: return "address range error";
    case A4OF_SIM_ERR_PERMISSION: return "permission denied";
    case A4OF_SIM_ERR_ALIGNMENT: return "alignment fault";
    case A4OF_SIM_ERR_DEVICE: return "device access failed";
    default: return "unknown status";
    }
}
