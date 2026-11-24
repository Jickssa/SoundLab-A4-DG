#include "a4of/param.h"
#include <string.h>
void a4of_param_registry_init(a4of_param_registry_t*r){if(r)memset(r,0,sizeof(*r));}
static size_t index_of(const a4of_param_registry_t*r,uint16_t id){for(size_t i=0;i<r->count;i++)if(r->entries[i].descriptor.id==id)return i;return r->count;}
a4of_param_status_t a4of_param_register(a4of_param_registry_t*r,const a4of_param_descriptor_t*d){
 if(!r||!d)return A4OF_PARAM_ERR_NULL;
 if(!d->name||!d->name[0]||d->minimum>d->maximum||d->default_value<d->minimum||d->default_value>d->maximum||d->curve>A4OF_PARAM_DISCRETE||(d->flags&~(uint8_t)7u))return A4OF_PARAM_ERR_ARGUMENT;
 if(index_of(r,d->id)!=r->count)return A4OF_PARAM_ERR_DUPLICATE;if(r->count>=A4OF_PARAM_MAX)return A4OF_PARAM_ERR_FULL;
 r->entries[r->count].descriptor=*d;r->entries[r->count].value=d->default_value;r->count++;return A4OF_PARAM_OK;
}
const a4of_param_descriptor_t*a4of_param_find(const a4of_param_registry_t*r,uint16_t id){if(!r)return NULL;size_t i=index_of(r,id);return i==r->count?NULL:&r->entries[i].descriptor;}
a4of_param_status_t a4of_param_get(const a4of_param_registry_t*r,uint16_t id,int32_t*v){if(!r||!v)return A4OF_PARAM_ERR_NULL;size_t i=index_of(r,id);if(i==r->count)return A4OF_PARAM_ERR_NOT_FOUND;*v=r->entries[i].value;return A4OF_PARAM_OK;}
a4of_param_status_t a4of_param_set(a4of_param_registry_t*r,uint16_t id,int32_t v,int32_t*out){
 if(!r)return A4OF_PARAM_ERR_NULL;size_t i=index_of(r,id);if(i==r->count)return A4OF_PARAM_ERR_NOT_FOUND;
 a4of_param_entry_t*e=&r->entries[i];if(e->descriptor.flags&A4OF_PARAM_READ_ONLY)return A4OF_PARAM_ERR_READ_ONLY;
 if(v<e->descriptor.minimum)v=e->descriptor.minimum;if(v>e->descriptor.maximum)v=e->descriptor.maximum;e->value=v;if(out)*out=v;return A4OF_PARAM_OK;
}
