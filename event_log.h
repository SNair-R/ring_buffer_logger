#ifndef EVENT_LOG_H
#define EVENT_LOG_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    uint8_t *data;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
} RingBuffer;

// API function declarations
bool rb_init(RingBuffer *rb, uint8_t *storage, size_t capacity);
bool rb_push(RingBuffer *rb, uint8_t byte);
bool rb_pop(RingBuffer *rb, uint8_t *out);

bool rb_is_full(const RingBuffer *rb);
bool rb_is_empty(const RingBuffer *rb);

#endif // EVENT_LOG_H
