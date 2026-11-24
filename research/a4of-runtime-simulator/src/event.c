#include "a4of/event.h"

#include <string.h>

void a4of_event_queue_init(a4of_event_queue_t *queue) {
    if (queue != NULL) memset(queue, 0, sizeof(*queue));
}

a4of_event_status_t a4of_event_push(a4of_event_queue_t *queue,
                                    const a4of_event_t *event) {
    if (queue == NULL || event == NULL) return A4OF_EVENT_ERR_NULL;
    if (event->type == A4OF_EVENT_NONE || event->type > A4OF_EVENT_STORAGE)
        return A4OF_EVENT_ERR_ARGUMENT;
    if (queue->count == A4OF_EVENT_CAPACITY) {
        ++queue->dropped;
        return A4OF_EVENT_ERR_FULL;
    }
    const size_t tail = (queue->head + queue->count) % A4OF_EVENT_CAPACITY;
    queue->events[tail] = *event;
    queue->events[tail].sequence = queue->next_sequence++;
    ++queue->count;
    return A4OF_EVENT_OK;
}

a4of_event_status_t a4of_event_peek(const a4of_event_queue_t *queue,
                                    a4of_event_t *event) {
    if (queue == NULL || event == NULL) return A4OF_EVENT_ERR_NULL;
    if (queue->count == 0u) return A4OF_EVENT_ERR_EMPTY;
    *event = queue->events[queue->head];
    return A4OF_EVENT_OK;
}

a4of_event_status_t a4of_event_pop(a4of_event_queue_t *queue,
                                   a4of_event_t *event) {
    if (queue == NULL || event == NULL) return A4OF_EVENT_ERR_NULL;
    if (queue->count == 0u) return A4OF_EVENT_ERR_EMPTY;
    *event = queue->events[queue->head];
    queue->head = (queue->head + 1u) % A4OF_EVENT_CAPACITY;
    --queue->count;
    return A4OF_EVENT_OK;
}

size_t a4of_event_count(const a4of_event_queue_t *queue) {
    return queue == NULL ? 0u : queue->count;
}
