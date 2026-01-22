#include "event_log.h"

// function to initialize the ring buffer
bool rb_init(RingBuffer *rb, LogEvent *storage, size_t capacity)
{
    // validates pointers and capacity
    if (rb == NULL || storage == NULL || capacity == 0) {
        return false;
    }

    // initializes ring buffer fields
    rb->data = storage;
    rb->capacity = capacity;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;

    return true;
}

// function to check if the ring buffer is full
bool rb_is_full(const RingBuffer *rb)
{
    if (rb == NULL) return false;
    return rb->count == rb->capacity;
}

// function to check if the ring buffer is empty
bool rb_is_empty(const RingBuffer *rb)
{
    if (rb == NULL) return true;
    return rb->count == 0;
}

// function to push a byte into the ring buffer
bool rb_push(RingBuffer *rb, LogEvent event)
{
    // validates buffer
    if (rb == NULL)
    {
        return false;
    }

    if (rb_is_full(rb))
    {
        rb->tail = (rb->tail + 1) % rb->capacity;
        rb->count--;
    }
    // adds byte and updates head w/ ability to wrap around with % capacity
    rb->data[rb->head] = event;
    rb->head = (rb->head + 1) % rb->capacity;

    // increments count of elements
    rb->count++;

    return true;
}

// function to remove a byte from the ring buffer
bool rb_pop(RingBuffer *rb, LogEvent *out)
{
    // validates buffer, output pointer, and checks if empty
    if (rb == NULL || out == NULL || rb_is_empty(rb)) {
        return false;
    }

    // stores unwanted byte into out and updates tail w/ ability to wrap around with % capacity
    *out = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;

    // decrements count of elements
    rb->count--;

    return true;
}
