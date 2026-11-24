#include "a4of/param.h"

#include <string.h>

void a4of_param_registry_init(a4of_param_registry_t *registry) {
    if (registry != NULL) memset(registry, 0, sizeof(*registry));
}

static size_t index_of(const a4of_param_registry_t *registry, uint16_t id) {
    for (size_t i = 0; i < registry->count; ++i) {
        if (registry->entries[i].descriptor.id == id) return i;
    }
    return registry->count;
}

a4of_param_status_t a4of_param_register(a4of_param_registry_t *registry,
                                         const a4of_param_descriptor_t *descriptor) {
    if (registry == NULL || descriptor == NULL) return A4OF_PARAM_ERR_NULL;
    if (descriptor->name == NULL || descriptor->name[0] == '\0' ||
        descriptor->minimum > descriptor->maximum ||
        descriptor->default_value < descriptor->minimum ||
        descriptor->default_value > descriptor->maximum ||
        descriptor->curve > A4OF_PARAM_DISCRETE ||
        (descriptor->flags & (uint8_t)~7u) != 0u) return A4OF_PARAM_ERR_ARGUMENT;
    if (index_of(registry, descriptor->id) != registry->count)
        return A4OF_PARAM_ERR_DUPLICATE;
    if (registry->count >= A4OF_PARAM_MAX) return A4OF_PARAM_ERR_FULL;
    a4of_param_entry_t *entry = &registry->entries[registry->count++];
    entry->descriptor = *descriptor;
    entry->value = descriptor->default_value;
    return A4OF_PARAM_OK;
}

const a4of_param_descriptor_t *a4of_param_find(
    const a4of_param_registry_t *registry, uint16_t id) {
    if (registry == NULL) return NULL;
    const size_t index = index_of(registry, id);
    return index == registry->count ? NULL : &registry->entries[index].descriptor;
}

a4of_param_status_t a4of_param_get(const a4of_param_registry_t *registry,
                                    uint16_t id, int32_t *value) {
    if (registry == NULL || value == NULL) return A4OF_PARAM_ERR_NULL;
    const size_t index = index_of(registry, id);
    if (index == registry->count) return A4OF_PARAM_ERR_NOT_FOUND;
    *value = registry->entries[index].value;
    return A4OF_PARAM_OK;
}

a4of_param_status_t a4of_param_set(a4of_param_registry_t *registry,
                                    uint16_t id, int32_t value, int32_t *applied) {
    if (registry == NULL) return A4OF_PARAM_ERR_NULL;
    const size_t index = index_of(registry, id);
    if (index == registry->count) return A4OF_PARAM_ERR_NOT_FOUND;
    a4of_param_entry_t *entry = &registry->entries[index];
    if ((entry->descriptor.flags & A4OF_PARAM_READ_ONLY) != 0u)
        return A4OF_PARAM_ERR_READ_ONLY;
    if (value < entry->descriptor.minimum) value = entry->descriptor.minimum;
    if (value > entry->descriptor.maximum) value = entry->descriptor.maximum;
    entry->value = value;
    if (applied != NULL) *applied = value;
    return A4OF_PARAM_OK;
}
