#ifndef A4OF_SIM_BUS_H
#define A4OF_SIM_BUS_H
#include <stddef.h>
#include <stdint.h>
#define A4OF_SIM_MAX_REGIONS 24u

typedef enum {
 A4OF_SIM_OK=0, A4OF_SIM_ERR_NULL=-1, A4OF_SIM_ERR_ARGUMENT=-2,
 A4OF_SIM_ERR_FULL=-3, A4OF_SIM_ERR_OVERLAP=-4, A4OF_SIM_ERR_UNMAPPED=-5,
 A4OF_SIM_ERR_RANGE=-6, A4OF_SIM_ERR_PERMISSION=-7,
 A4OF_SIM_ERR_ALIGNMENT=-8, A4OF_SIM_ERR_DEVICE=-9
} a4of_sim_status_t;
enum { A4OF_SIM_MEM_READ=1u, A4OF_SIM_MEM_WRITE=2u, A4OF_SIM_MEM_EXEC=4u };

typedef a4of_sim_status_t (*a4of_sim_device_read_fn)(void*,uint32_t,uint8_t,uint32_t*);
typedef a4of_sim_status_t (*a4of_sim_device_write_fn)(void*,uint32_t,uint8_t,uint32_t);

typedef struct {
 uint32_t base,size;
 uint8_t permissions;
 uint8_t *memory;
 a4of_sim_device_read_fn read;
 a4of_sim_device_write_fn write;
 void *context;
 const char *name;
} a4of_sim_region_t;

typedef struct {
 a4of_sim_region_t regions[A4OF_SIM_MAX_REGIONS];
 size_t region_count;
 uint64_t cycles,reads,writes;
 uint32_t last_fault_address;
 a4of_sim_status_t last_fault;
} a4of_sim_bus_t;

void a4of_sim_bus_init(a4of_sim_bus_t*);
a4of_sim_status_t a4of_sim_bus_map_memory(a4of_sim_bus_t*,uint32_t,uint32_t,uint8_t,uint8_t*,const char*);
a4of_sim_status_t a4of_sim_bus_map_device(a4of_sim_bus_t*,uint32_t,uint32_t,uint8_t,a4of_sim_device_read_fn,a4of_sim_device_write_fn,void*,const char*);
a4of_sim_status_t a4of_sim_bus_read8(a4of_sim_bus_t*,uint32_t,uint8_t*);
a4of_sim_status_t a4of_sim_bus_read16(a4of_sim_bus_t*,uint32_t,uint16_t*);
a4of_sim_status_t a4of_sim_bus_read32(a4of_sim_bus_t*,uint32_t,uint32_t*);
a4of_sim_status_t a4of_sim_bus_write8(a4of_sim_bus_t*,uint32_t,uint8_t);
a4of_sim_status_t a4of_sim_bus_write16(a4of_sim_bus_t*,uint32_t,uint16_t);
a4of_sim_status_t a4of_sim_bus_write32(a4of_sim_bus_t*,uint32_t,uint32_t);
const char *a4of_sim_status_string(a4of_sim_status_t);
#endif
