#include "a4of/event.h"
#include <string.h>
void a4of_event_queue_init(a4of_event_queue_t*q){if(q)memset(q,0,sizeof(*q));}
a4of_event_status_t a4of_event_push(a4of_event_queue_t*q,const a4of_event_t*e){
 if(!q||!e)return A4OF_EVENT_ERR_NULL;if(e->type==A4OF_EVENT_NONE||e->type>A4OF_EVENT_STORAGE)return A4OF_EVENT_ERR_ARGUMENT;
 if(q->count==A4OF_EVENT_CAPACITY){q->dropped++;return A4OF_EVENT_ERR_FULL;}
 size_t t=(q->head+q->count)%A4OF_EVENT_CAPACITY;q->events[t]=*e;q->events[t].sequence=q->next_sequence++;q->count++;return A4OF_EVENT_OK;
}
a4of_event_status_t a4of_event_peek(const a4of_event_queue_t*q,a4of_event_t*e){if(!q||!e)return A4OF_EVENT_ERR_NULL;if(!q->count)return A4OF_EVENT_ERR_EMPTY;*e=q->events[q->head];return A4OF_EVENT_OK;}
a4of_event_status_t a4of_event_pop(a4of_event_queue_t*q,a4of_event_t*e){if(!q||!e)return A4OF_EVENT_ERR_NULL;if(!q->count)return A4OF_EVENT_ERR_EMPTY;*e=q->events[q->head];q->head=(q->head+1u)%A4OF_EVENT_CAPACITY;q->count--;return A4OF_EVENT_OK;}
size_t a4of_event_count(const a4of_event_queue_t*q){return q?q->count:0u;}
