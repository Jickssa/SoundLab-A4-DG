#include "a4of/scheduler.h"
#include <string.h>
static int before(const a4of_scheduled_event_t*a,const a4of_scheduled_event_t*b){
 if(a->event.tick!=b->event.tick)return a->event.tick<b->event.tick;
 if(a->priority!=b->priority)return a->priority>b->priority;
 return a->order<b->order;
}
void a4of_scheduler_init(a4of_scheduler_t*s,uint64_t now){if(!s)return;memset(s,0,sizeof(*s));s->now=now;}
a4of_sched_status_t a4of_scheduler_schedule(a4of_scheduler_t*s,const a4of_event_t*e,uint8_t p){
 if(!s||!e)return A4OF_SCHED_ERR_NULL;if(e->type==A4OF_EVENT_NONE||e->type>A4OF_EVENT_STORAGE)return A4OF_SCHED_ERR_ARGUMENT;
 if(e->tick<s->now)return A4OF_SCHED_ERR_PAST;if(s->count>=A4OF_SCHEDULER_CAPACITY){s->dropped++;return A4OF_SCHED_ERR_FULL;}
 a4of_scheduled_event_t v;v.event=*e;v.priority=p;v.order=s->next_order++;
 size_t i=s->count;while(i>0u&&before(&v,&s->items[i-1u])){s->items[i]=s->items[i-1u];i--;}s->items[i]=v;s->count++;return A4OF_SCHED_OK;
}
a4of_sched_status_t a4of_scheduler_advance(a4of_scheduler_t*s,uint64_t t){if(!s)return A4OF_SCHED_ERR_NULL;if(t<s->now)return A4OF_SCHED_ERR_TIME_REVERSED;s->now=t;return A4OF_SCHED_OK;}
a4of_sched_status_t a4of_scheduler_pop_due(a4of_scheduler_t*s,a4of_event_t*e,uint8_t*p){
 if(!s||!e)return A4OF_SCHED_ERR_NULL;if(!s->count||s->items[0].event.tick>s->now)return A4OF_SCHED_ERR_EMPTY;
 *e=s->items[0].event;if(p)*p=s->items[0].priority;for(size_t i=1;i<s->count;i++)s->items[i-1u]=s->items[i];s->count--;return A4OF_SCHED_OK;
}
size_t a4of_scheduler_count(const a4of_scheduler_t*s){return s?s->count:0u;}
