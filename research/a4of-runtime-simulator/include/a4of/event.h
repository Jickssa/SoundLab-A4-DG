#ifndef A4OF_EVENT_H
#define A4OF_EVENT_H
#include <stddef.h>
#include <stdint.h>
#define A4OF_EVENT_CAPACITY 128u
typedef enum { A4OF_EVENT_NONE=0,A4OF_EVENT_NOTE_ON,A4OF_EVENT_NOTE_OFF,A4OF_EVENT_TRIG,A4OF_EVENT_PARAMETER,A4OF_EVENT_TRANSPORT,A4OF_EVENT_UI,A4OF_EVENT_MIDI_RX,A4OF_EVENT_STORAGE } a4of_event_type_t;
typedef struct {uint64_t tick;uint32_t sequence,id;int32_t value;uint16_t source;uint8_t type,flags;} a4of_event_t;
typedef enum {A4OF_EVENT_OK=0,A4OF_EVENT_ERR_NULL=-1,A4OF_EVENT_ERR_FULL=-2,A4OF_EVENT_ERR_EMPTY=-3,A4OF_EVENT_ERR_ARGUMENT=-4} a4of_event_status_t;
typedef struct {a4of_event_t events[A4OF_EVENT_CAPACITY];size_t head,count;uint32_t next_sequence;uint64_t dropped;} a4of_event_queue_t;
void a4of_event_queue_init(a4of_event_queue_t*);
a4of_event_status_t a4of_event_push(a4of_event_queue_t*,const a4of_event_t*);
a4of_event_status_t a4of_event_peek(const a4of_event_queue_t*,a4of_event_t*);
a4of_event_status_t a4of_event_pop(a4of_event_queue_t*,a4of_event_t*);
size_t a4of_event_count(const a4of_event_queue_t*);
#endif
