---

# Structured Event Logger with Ring Buffer (C)

A lightweight structured event logger implemented in C using a fixed-size circular (ring) buffer.
Designed for embedded systems and low-level applications where deterministic behavior and memory control are critical.

The logger stores timestamped events with severity levels and automatically overwrites the oldest events when the buffer is full, ensuring the most recent log data is always preserved.

---

## Features

* Fixed-capacity circular (ring) buffer
* Structured log records using a `LogEvent` struct
* Severity levels via `enum LogLevel`
* Overwrite-on-full behavior (oldest event is dropped)
* No dynamic memory allocation (`malloc` / `free`)
* Constant-time push and pop operations
* Simple test harness for verification
* Clean separation of interface and implementation

---

## Project Structure

```
.
├── event_log.h   # Public API, enums, and data structures
├── event_log.c   # Ring buffer implementation
├── main.c        # Example usage / test harness
```

---

## Log Event Format

Each log entry is represented by the following structure:

```
typedef struct
{
    uint32_t ts;     // Timestamp (user-defined units)
    LogLevel level;  // Severity level
    uint16_t id;     // Event identifier
    int32_t value;   // Associated value
} LogEvent;
```

### Log Levels

```
LOG_DEBUG
LOG_INFO
LOG_WARN
LOG_ERROR
LOG_FATAL
```

---

## Ring Buffer Behavior

The ring buffer stores `LogEvent` entries and tracks:

* `head` – next write position
* `tail` – next read position
* `count` – current number of stored events
* `capacity` – maximum number of events

### Overwrite-on-Full Semantics

When the buffer is full and a new event is pushed:

* The oldest event is discarded
* The `tail` index is advanced
* The new event is written at `head`

This guarantees the buffer always contains the most recent events.

---

## Public API

Declared in `event_log.h`:

```
bool rb_init(RingBuffer *rb, LogEvent *storage, size_t capacity);
bool rb_push(RingBuffer *rb, LogEvent event);
bool rb_pop(RingBuffer *rb, LogEvent *out);

bool rb_is_full(const RingBuffer *rb);
bool rb_is_empty(const RingBuffer *rb);
```

### API Semantics

* `rb_init`

  * Initializes a ring buffer using caller-provided storage
  * Returns false if arguments are invalid

* `rb_push`

  * Inserts a `LogEvent` into the buffer
  * Automatically overwrites the oldest event if full

* `rb_pop`

  * Removes the oldest event from the buffer
  * Returns false if the buffer is empty

---

## Example Usage

```
LogEvent storage[10];
RingBuffer rb;

rb_init(&rb, storage, 10);

LogEvent event = {
    .ts = 42,
    .level = LOG_INFO,
    .id = 1,
    .value = 123
};

rb_push(&rb, event);

LogEvent out;
if (rb_pop(&rb, &out)) {
    // process event
}
```

---

## Build Instructions

Compile with GCC:

```
gcc -Wall -Wextra -std=c11 -o event_log main.c event_log.c
```

Run:

```
./event_log
```

---

## Current Status

* Structured event logging implemented
* Overwrite-on-full behavior enabled
* No dynamic memory allocation
* Tested via `main.c`

---

## Intended Use Cases

* Embedded firmware logging
* Event tracing and diagnostics
* Telemetry buffers
* Systems programming practice
* Resume and portfolio projects

---

If you want next, I can:

* Add a **Future Improvements** section
* Add **embedded/ISR safety notes**
* Tighten this into a **one-paragraph resume description**
* Help you tag and version the repo professionally
