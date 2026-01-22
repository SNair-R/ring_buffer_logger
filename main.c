#include <stdio.h>
#include "event_log.h"

// log level string representations
static const char *Log_Lvl_Str[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

// tester main function
int main(void)
{
    // sets up storage and ring buffer
    LogEvent storage[10];
    RingBuffer rb;

    // initlizes the ring buffer
    if (!rb_init(&rb, storage, sizeof(storage) / sizeof(storage[0]))) {
        printf("rb_init failed\n");
        return 1;
    }

// example log events to push into the ring buffer
LogEvent e1 = {
    .ts = 1,
    .level = LOG_INFO,
    .id = 1,         
    .value = 0
};
LogEvent e2 = {
    .ts = 42,
    .level = LOG_WARN,
    .id = 2,           
    .value = 78         
};
LogEvent e3 = {
    .ts = 100,
    .level = LOG_FATAL,
    .id = 3,          
    .value = -1
};

// pushes example log events into the ring buffer
rb_push(&rb, e1);
rb_push(&rb, e2);
rb_push(&rb, e3);



    // pops and prints data from the ring buffer
    LogEvent out;
    while (rb_pop(&rb, &out)) {
        printf(
            "Time Stamp: %us\nLevel %s\n Event ID: %u\nValue: %d\n\n",
            out.ts, Log_Lvl_Str[out.level], out.id, out.value
        );
    }

    return 0;
}
