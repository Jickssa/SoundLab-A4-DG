#include "a4of/sim_bus.h"
#include <string.h>

static int width_ok(uint8_t w){return w==1u||w==2u||w==4u;}
static int overlap(uint32_t a,uint32_t as,uint32_t b,uint32_t bs){
 uint64_t ae=(uint64_t)a+as,be=(uint64_t)b+bs;
 return (uint64_t)a<be&&(uint64_t)b<ae;
}
static a4of_sim_status_t map_region(a4of_sim_bus_t *b,uint32_t base,uint32_t size,uint8_t perm,
 uint8_t *mem,a4of_sim_device_read_fn rd,a4of_sim_device_write_fn wr,void *ctx,const char *name){
 if(!b)return A4OF_SIM_ERR_NULL;
 if(!size||!perm||(perm&~(uint8_t)7u))return A4OF_SIM_ERR_ARGUMENT;
 if((uint64_t)base+size>(uint64_t)UINT32_MAX+1u)return A4OF_SIM_ERR_RANGE;
 if(b->region_count>=A4OF_SIM_MAX_REGIONS)return A4OF_SIM_ERR_FULL;
 for(size_t i=0;i<b->region_count;i++)if(overlap(base,size,b->regions[i].base,b->regions[i].size))return A4OF_SIM_ERR_OVERLAP;
 a4of_sim_region_t *r=&b->regions[b->region_count++];
 r->base=base;r->size=size;r->permissions=perm;r->memory=mem;r->read=rd;r->write=wr;r->context=ctx;r->name=name;
 return A4OF_SIM_OK;
}
void a4of_sim_bus_init(a4of_sim_bus_t *b){if(b)memset(b,0,sizeof(*b));}
a4of_sim_status_t a4of_sim_bus_map_memory(a4of_sim_bus_t*b,uint32_t base,uint32_t size,uint8_t p,uint8_t*m,const char*n){
 if(!m)return A4OF_SIM_ERR_NULL;return map_region(b,base,size,p,m,NULL,NULL,NULL,n);
}
a4of_sim_status_t a4of_sim_bus_map_device(a4of_sim_bus_t*b,uint32_t base,uint32_t size,uint8_t p,a4of_sim_device_read_fn rd,a4of_sim_device_write_fn wr,void*c,const char*n){
 if(!rd&&!wr)return A4OF_SIM_ERR_NULL;return map_region(b,base,size,p,NULL,rd,wr,c,n);
}
static a4of_sim_region_t *find_region(a4of_sim_bus_t*b,uint32_t a,uint8_t w){
 uint64_t end=(uint64_t)a+w;
 for(size_t i=0;i<b->region_count;i++){a4of_sim_region_t*r=&b->regions[i];uint64_t re=(uint64_t)r->base+r->size;
  if((uint64_t)a>=r->base&&end<=re)return r;}return NULL;
}
static a4of_sim_status_t fail(a4of_sim_bus_t*b,uint32_t a,a4of_sim_status_t s){b->last_fault_address=a;b->last_fault=s;return s;}
static a4of_sim_status_t read_access(a4of_sim_bus_t*b,uint32_t a,uint8_t w,uint32_t*v){
 if(!b||!v)return A4OF_SIM_ERR_NULL;if(!width_ok(w))return A4OF_SIM_ERR_ARGUMENT;
 if(w>1u&&a%w)return fail(b,a,A4OF_SIM_ERR_ALIGNMENT);
 a4of_sim_region_t*r=find_region(b,a,w);if(!r)return fail(b,a,A4OF_SIM_ERR_UNMAPPED);
 if(!(r->permissions&A4OF_SIM_MEM_READ))return fail(b,a,A4OF_SIM_ERR_PERMISSION);
 uint32_t off=a-r->base;a4of_sim_status_t s=A4OF_SIM_OK;
 if(r->memory){const uint8_t*p=r->memory+off;
  *v=w==1u?p[0]:w==2u?((uint32_t)p[0]<<8)|p[1]:((uint32_t)p[0]<<24)|((uint32_t)p[1]<<16)|((uint32_t)p[2]<<8)|p[3];
 }else if(r->read){s=r->read(r->context,off,w,v);if(s!=A4OF_SIM_OK)s=A4OF_SIM_ERR_DEVICE;}else s=A4OF_SIM_ERR_DEVICE;
 if(s==A4OF_SIM_OK){b->reads++;b->cycles+=w;}else fail(b,a,s);return s;
}
static a4of_sim_status_t write_access(a4of_sim_bus_t*b,uint32_t a,uint8_t w,uint32_t v){
 if(!b)return A4OF_SIM_ERR_NULL;if(!width_ok(w))return A4OF_SIM_ERR_ARGUMENT;
 if(w>1u&&a%w)return fail(b,a,A4OF_SIM_ERR_ALIGNMENT);
 a4of_sim_region_t*r=find_region(b,a,w);if(!r)return fail(b,a,A4OF_SIM_ERR_UNMAPPED);
 if(!(r->permissions&A4OF_SIM_MEM_WRITE))return fail(b,a,A4OF_SIM_ERR_PERMISSION);
 uint32_t off=a-r->base;a4of_sim_status_t s=A4OF_SIM_OK;
 if(r->memory){uint8_t*p=r->memory+off;
  if(w==1u)p[0]=(uint8_t)v;else if(w==2u){p[0]=(uint8_t)(v>>8);p[1]=(uint8_t)v;}
  else{p[0]=(uint8_t)(v>>24);p[1]=(uint8_t)(v>>16);p[2]=(uint8_t)(v>>8);p[3]=(uint8_t)v;}
 }else if(r->write){s=r->write(r->context,off,w,v);if(s!=A4OF_SIM_OK)s=A4OF_SIM_ERR_DEVICE;}else s=A4OF_SIM_ERR_DEVICE;
 if(s==A4OF_SIM_OK){b->writes++;b->cycles+=w;}else fail(b,a,s);return s;
}
a4of_sim_status_t a4of_sim_bus_read8(a4of_sim_bus_t*b,uint32_t a,uint8_t*v){if(!v)return A4OF_SIM_ERR_NULL;uint32_t x=0;a4of_sim_status_t s=read_access(b,a,1,&x);if(s==A4OF_SIM_OK)*v=(uint8_t)x;return s;}
a4of_sim_status_t a4of_sim_bus_read16(a4of_sim_bus_t*b,uint32_t a,uint16_t*v){if(!v)return A4OF_SIM_ERR_NULL;uint32_t x=0;a4of_sim_status_t s=read_access(b,a,2,&x);if(s==A4OF_SIM_OK)*v=(uint16_t)x;return s;}
a4of_sim_status_t a4of_sim_bus_read32(a4of_sim_bus_t*b,uint32_t a,uint32_t*v){return read_access(b,a,4,v);}
a4of_sim_status_t a4of_sim_bus_write8(a4of_sim_bus_t*b,uint32_t a,uint8_t v){return write_access(b,a,1,v);}
a4of_sim_status_t a4of_sim_bus_write16(a4of_sim_bus_t*b,uint32_t a,uint16_t v){return write_access(b,a,2,v);}
a4of_sim_status_t a4of_sim_bus_write32(a4of_sim_bus_t*b,uint32_t a,uint32_t v){return write_access(b,a,4,v);}
const char*a4of_sim_status_string(a4of_sim_status_t s){switch(s){
 case A4OF_SIM_OK:return "ok";case A4OF_SIM_ERR_NULL:return "null argument";case A4OF_SIM_ERR_ARGUMENT:return "invalid argument";
 case A4OF_SIM_ERR_FULL:return "region table full";case A4OF_SIM_ERR_OVERLAP:return "region overlap";case A4OF_SIM_ERR_UNMAPPED:return "unmapped address";
 case A4OF_SIM_ERR_RANGE:return "address range error";case A4OF_SIM_ERR_PERMISSION:return "permission denied";case A4OF_SIM_ERR_ALIGNMENT:return "alignment fault";
 case A4OF_SIM_ERR_DEVICE:return "device access failed";default:return "unknown status";}}
