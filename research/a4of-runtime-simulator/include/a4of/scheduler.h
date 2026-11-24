#ifndef A4OF_SCHEDULER_H
#define A4OF_SCHEDULER_H
#include <stddef.h>
#include <stdint.h>
#include "a4of/event.h"
#define A4OF_SCHEDULER_CAPACITY 128u
typedef enum {A4OF_SCHED_OK=0,A4OF_SCHED_ERR_NULL=-1,A4OF_SCHED_ERR_FULL=-2,A4OF_SCHED_ERR_PAST=-3,A4OF_SCHED_ERR_EMPTY=-4,A4OF_SCHED_ERR_TIME_REVERSED=-5,A4OF_SCHED_ERR_ARGUMENT=-6} a4of_sched_status_t;
typedef struct {a4of_event_t event;uint8_t priority;uint32_t order;} a4of_scheduled_event_t;
typedef struct {a4of_scheduled_event_t items[A4OF_SCHEDULER_CAPACITY];size_t count;uint64_t now;uint32_t next_order;uint64_t dropped;} a4of_scheduler_t;
void a4of_scheduler_init(a4of_scheduler_t*,uint64_t);
a4of_sched_status_t a4of_scheduler_schedule(a4of_scheduler_t*,const a4of_event_t*,uint8_t);
a4of_sched_status_t a4of_scheduler_advance(a4of_scheduler_t*,uint64_t);
a4of_sched_status_t a4of_scheduler_pop_due(a4of_scheduler_t*,a4of_event_t*,uint8_t*);
size_t a4of_scheduler_count(const a4of_scheduler_t*);
#endif
