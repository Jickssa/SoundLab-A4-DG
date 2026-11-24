#ifndef A4OF_PARAM_H
#define A4OF_PARAM_H
#include <stddef.h>
#include <stdint.h>
#define A4OF_PARAM_MAX 192u
typedef enum {A4OF_PARAM_LINEAR=0,A4OF_PARAM_LOGARITHMIC,A4OF_PARAM_DISCRETE} a4of_param_curve_t;
enum {A4OF_PARAM_READ_ONLY=1u,A4OF_PARAM_PERSISTENT=2u,A4OF_PARAM_MODULATABLE=4u};
typedef struct {uint16_t id;const char*name;const char*unit;int32_t minimum,maximum,default_value;uint16_t smoothing_ms;uint8_t curve,flags;} a4of_param_descriptor_t;
typedef struct {a4of_param_descriptor_t descriptor;int32_t value;} a4of_param_entry_t;
typedef enum {A4OF_PARAM_OK=0,A4OF_PARAM_ERR_NULL=-1,A4OF_PARAM_ERR_FULL=-2,A4OF_PARAM_ERR_DUPLICATE=-3,A4OF_PARAM_ERR_RANGE=-4,A4OF_PARAM_ERR_NOT_FOUND=-5,A4OF_PARAM_ERR_READ_ONLY=-6,A4OF_PARAM_ERR_ARGUMENT=-7} a4of_param_status_t;
typedef struct {a4of_param_entry_t entries[A4OF_PARAM_MAX];size_t count;} a4of_param_registry_t;
void a4of_param_registry_init(a4of_param_registry_t*);
a4of_param_status_t a4of_param_register(a4of_param_registry_t*,const a4of_param_descriptor_t*);
a4of_param_status_t a4of_param_get(const a4of_param_registry_t*,uint16_t,int32_t*);
a4of_param_status_t a4of_param_set(a4of_param_registry_t*,uint16_t,int32_t,int32_t*);
const a4of_param_descriptor_t*a4of_param_find(const a4of_param_registry_t*,uint16_t);
#endif
