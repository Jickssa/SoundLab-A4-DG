#include "a4of/sim_bus.h"
#include "a4of/panel_latch.h"
#include "a4of/event.h"
#include "a4of/param.h"
#include "a4of/scheduler.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
typedef struct{uint32_t reg;unsigned reads,writes;} mock_t;
static a4of_sim_status_t mock_read(void*c,uint32_t o,uint8_t w,uint32_t*v){mock_t*m=c;if(!m||!v||o||w!=4)return A4OF_SIM_ERR_DEVICE;m->reads++;*v=m->reg;return A4OF_SIM_OK;}
static a4of_sim_status_t mock_write(void*c,uint32_t o,uint8_t w,uint32_t v){mock_t*m=c;if(!m||o||w!=4)return A4OF_SIM_ERR_DEVICE;m->writes++;m->reg=v;return A4OF_SIM_OK;}
static void test_bus(void){
 a4of_sim_bus_t b;uint8_t ram[32]={0},u8=0;uint16_t u16=0;uint32_t u32=0;a4of_sim_bus_init(&b);
 assert(a4of_sim_bus_map_memory(&b,0x1000,32,7,ram,"ram")==A4OF_SIM_OK);
 assert(a4of_sim_bus_write8(&b,0x1000,0xAB)==A4OF_SIM_OK);
 assert(a4of_sim_bus_write16(&b,0x1002,0xCDEF)==A4OF_SIM_OK);
 assert(a4of_sim_bus_write32(&b,0x1004,0x12345678)==A4OF_SIM_OK);
 assert(ram[0]==0xAB&&ram[2]==0xCD&&ram[3]==0xEF&&ram[4]==0x12);
 assert(a4of_sim_bus_read8(&b,0x1000,&u8)==A4OF_SIM_OK&&u8==0xAB);
 assert(a4of_sim_bus_read16(&b,0x1002,&u16)==A4OF_SIM_OK&&u16==0xCDEF);
 assert(a4of_sim_bus_read32(&b,0x1004,&u32)==A4OF_SIM_OK&&u32==0x12345678);
 assert(b.reads==3&&b.writes==3&&b.cycles==14);
 assert(a4of_sim_bus_read16(&b,0x1001,&u16)==A4OF_SIM_ERR_ALIGNMENT);
 assert(a4of_sim_bus_read8(&b,0x2000,&u8)==A4OF_SIM_ERR_UNMAPPED);
 assert(a4of_sim_bus_map_memory(&b,0x1010,8,3,ram,"overlap")==A4OF_SIM_ERR_OVERLAP);
 assert(a4of_sim_bus_map_memory(&b,0xFFFFFFF0u,32,1,ram,"overflow")==A4OF_SIM_ERR_RANGE);
 assert(a4of_sim_bus_write8(&b,0x1000,0)==A4OF_SIM_OK);
 a4of_sim_bus_init(&b);assert(a4of_sim_bus_map_memory(&b,0x3000,8,A4OF_SIM_MEM_READ,ram,"rom")==A4OF_SIM_OK);
 assert(a4of_sim_bus_write8(&b,0x3000,1)==A4OF_SIM_ERR_PERMISSION);
 mock_t m={0xA5A55A5A,0,0};a4of_sim_bus_init(&b);
 assert(a4of_sim_bus_map_device(&b,0x4000,4,3,mock_read,mock_write,&m,"mmio")==A4OF_SIM_OK);
 assert(a4of_sim_bus_read32(&b,0x4000,&u32)==A4OF_SIM_OK&&u32==0xA5A55A5A);
 assert(a4of_sim_bus_write32(&b,0x4000,0x11223344)==A4OF_SIM_OK&&m.reg==0x11223344&&m.writes==1);
}
static void test_latch(void){
 a4of_74hc373_t l;uint8_t v=0;a4of_74hc373_init(&l);assert(!a4of_74hc373_output(&l,&v));
 a4of_74hc373_set_oe_n(&l,false);assert(!a4of_74hc373_output(&l,&v));
 a4of_74hc373_set_le(&l,true);a4of_74hc373_set_data(&l,0x3C);assert(a4of_74hc373_output(&l,&v)&&v==0x3C);
 a4of_74hc373_set_le(&l,false);a4of_74hc373_set_data(&l,0xA5);assert(a4of_74hc373_output(&l,&v)&&v==0x3C);
 a4of_74hc373_set_oe_n(&l,true);assert(!a4of_74hc373_output(&l,&v));
}
static void test_events(void){
 a4of_event_queue_t q;a4of_event_t e={0},o;a4of_event_queue_init(&q);e.type=A4OF_EVENT_NOTE_ON;e.tick=5;e.id=60;
 assert(a4of_event_push(&q,&e)==A4OF_EVENT_OK);assert(a4of_event_pop(&q,&o)==A4OF_EVENT_OK&&o.id==60&&o.sequence==0);
 for(size_t i=0;i<A4OF_EVENT_CAPACITY;i++)assert(a4of_event_push(&q,&e)==A4OF_EVENT_OK);
 assert(a4of_event_push(&q,&e)==A4OF_EVENT_ERR_FULL&&q.dropped==1);
}
static void test_params(void){
 a4of_param_registry_t r;int32_t v=0;a4of_param_registry_init(&r);
 a4of_param_descriptor_t d={100,"Cutoff","Hz",20,20000,1000,10,A4OF_PARAM_LOGARITHMIC,A4OF_PARAM_MODULATABLE};
 assert(a4of_param_register(&r,&d)==A4OF_PARAM_OK);assert(a4of_param_register(&r,&d)==A4OF_PARAM_ERR_DUPLICATE);
 assert(a4of_param_set(&r,100,30000,&v)==A4OF_PARAM_OK&&v==20000);assert(a4of_param_get(&r,100,&v)==A4OF_PARAM_OK&&v==20000);
 d.id=101;d.name="Status";d.minimum=0;d.maximum=1;d.default_value=1;d.flags=A4OF_PARAM_READ_ONLY;
 assert(a4of_param_register(&r,&d)==A4OF_PARAM_OK);assert(a4of_param_set(&r,101,0,&v)==A4OF_PARAM_ERR_READ_ONLY);
}
static void test_scheduler(void){
 a4of_scheduler_t s;a4of_event_t e={0},o;uint8_t p=0;a4of_scheduler_init(&s,100);
 e.type=A4OF_EVENT_NOTE_ON;e.tick=120;e.id=60;assert(a4of_scheduler_schedule(&s,&e,1)==A4OF_SCHED_OK);
 e.type=A4OF_EVENT_PARAMETER;e.id=5;assert(a4of_scheduler_schedule(&s,&e,3)==A4OF_SCHED_OK);
 e.type=A4OF_EVENT_NOTE_OFF;e.tick=110;e.id=60;assert(a4of_scheduler_schedule(&s,&e,9)==A4OF_SCHED_OK);
 assert(a4of_scheduler_pop_due(&s,&o,&p)==A4OF_SCHED_ERR_EMPTY);
 assert(a4of_scheduler_advance(&s,120)==A4OF_SCHED_OK);
 assert(a4of_scheduler_pop_due(&s,&o,&p)==A4OF_SCHED_OK&&o.tick==110&&p==9);
 assert(a4of_scheduler_pop_due(&s,&o,&p)==A4OF_SCHED_OK&&o.id==5&&p==3);
 assert(a4of_scheduler_pop_due(&s,&o,&p)==A4OF_SCHED_OK&&o.id==60&&p==1);
 assert(a4of_scheduler_advance(&s,119)==A4OF_SCHED_ERR_TIME_REVERSED);
 assert(a4of_scheduler_schedule(&s,&e,1)==A4OF_SCHED_ERR_PAST);
 e.tick=121;assert(a4of_scheduler_schedule(&s,&e,1)==A4OF_SCHED_OK);
}
int main(void){test_bus();test_latch();test_events();test_params();test_scheduler();puts("A4OF runtime tests: PASS");return 0;}
