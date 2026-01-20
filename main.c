#include <stdio.h>
#include "event_log.h"

// tester main function
int main(void)
{
    // sets up storage and ring buffer
    uint8_t storage[10];
    RingBuffer rb;

    // initlizes the ring buffer
    if (!rb_init(&rb, storage, sizeof(storage) / sizeof(storage[0]))) {
        printf("rb_init failed\n");
        return 1;
    }

    // pushes some data into the ring buffer
    rb_push(&rb, 'A');
    rb_push(&rb, 'B');
    rb_push(&rb, 'C');

    // pops and prints data from the ring buffer
    uint8_t out;
    while (rb_pop(&rb, &out)) {
        printf("Popped: %c\n", out);
    }

    return 0;
}
