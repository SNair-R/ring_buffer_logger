#ifndef EVENT_LOG_H
#define EVENT_LOG_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// added log level structure to event log
typedef enum { LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL } LogLevel;

// log even structure with timestamp, level, id, and value
typedef struct
{
    uint32_t ts;
    LogLevel level;
    uint16_t id;
    int32_t value;
} LogEvent;

// ring buffer structure
typedef struct
{
    LogEvent *data;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
} RingBuffer;

// API function declarations
bool rb_init(RingBuffer *rb, LogEvent *storage, size_t capacity);
bool rb_push(RingBuffer *rb, LogEvent event);
bool rb_pop(RingBuffer *rb, LogEvent *out);

bool rb_is_full(const RingBuffer *rb);
bool rb_is_empty(const RingBuffer *rb);

#endif // EVENT_LOG_H
