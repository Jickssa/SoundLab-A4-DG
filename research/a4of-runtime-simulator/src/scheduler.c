#include "a4of/scheduler.h"

#include <string.h>

static int comes_before(const a4of_scheduled_event_t *left,
                        const a4of_scheduled_event_t *right) {
    if (left->event.tick != right->event.tick)
        return left->event.tick < right->event.tick;
    if (left->priority != right->priority)
        return left->priority > right->priority;
    return left->order < right->order;
}

void a4of_scheduler_init(a4of_scheduler_t *scheduler, uint64_t now) {
    if (scheduler == NULL) return;
    memset(scheduler, 0, sizeof(*scheduler));
    scheduler->now = now;
}

a4of_sched_status_t a4of_scheduler_schedule(a4of_scheduler_t *scheduler,
                                             const a4of_event_t *event,
                                             uint8_t priority) {
    if (scheduler == NULL || event == NULL) return A4OF_SCHED_ERR_NULL;
    if (event->type == A4OF_EVENT_NONE || event->type > A4OF_EVENT_STORAGE)
        return A4OF_SCHED_ERR_ARGUMENT;
    if (event->tick < scheduler->now) return A4OF_SCHED_ERR_PAST;
    if (scheduler->count >= A4OF_SCHEDULER_CAPACITY) {
        ++scheduler->dropped;
        return A4OF_SCHED_ERR_FULL;
    }

    a4of_scheduled_event_t item;
    item.event = *event;
    item.priority = priority;
    item.order = scheduler->next_order++;
    size_t index = scheduler->count;
    while (index > 0u && comes_before(&item, &scheduler->items[index - 1u])) {
        scheduler->items[index] = scheduler->items[index - 1u];
        --index;
    }
    scheduler->items[index] = item;
    ++scheduler->count;
    return A4OF_SCHED_OK;
}

a4of_sched_status_t a4of_scheduler_advance(a4of_scheduler_t *scheduler,
                                            uint64_t tick) {
    if (scheduler == NULL) return A4OF_SCHED_ERR_NULL;
    if (tick < scheduler->now) return A4OF_SCHED_ERR_TIME_REVERSED;
    scheduler->now = tick;
    return A4OF_SCHED_OK;
}

a4of_sched_status_t a4of_scheduler_pop_due(a4of_scheduler_t *scheduler,
                                            a4of_event_t *event,
                                            uint8_t *priority) {
    if (scheduler == NULL || event == NULL) return A4OF_SCHED_ERR_NULL;
    if (scheduler->count == 0u ||
        scheduler->items[0].event.tick > scheduler->now) return A4OF_SCHED_ERR_EMPTY;
    *event = scheduler->items[0].event;
    if (priority != NULL) *priority = scheduler->items[0].priority;
    for (size_t i = 1; i < scheduler->count; ++i)
        scheduler->items[i - 1u] = scheduler->items[i];
    --scheduler->count;
    return A4OF_SCHED_OK;
}

size_t a4of_scheduler_count(const a4of_scheduler_t *scheduler) {
    return scheduler == NULL ? 0u : scheduler->count;
}
