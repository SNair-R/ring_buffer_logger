# Ring Buffer Logger (C)

This project implements a fixed-size circular (ring) buffer in C, designed as the foundation for a lightweight event logger.

## Current Features
- FIFO ring buffer implementation
- Fixed capacity with head/tail indexing
- Clean separation into `.h` / `.c` files
- Safe push and pop operations
- No dynamic memory allocation (embedded-friendly)

## Planned Features
- Structured event logging
- Overwrite-on-full behavior (drop oldest events)
- Event-based log entries instead of raw bytes

## Build Instructions

Using gcc:

```bash
gcc -Wall -Wextra -std=c11 -o event_log main.c event_log.c
