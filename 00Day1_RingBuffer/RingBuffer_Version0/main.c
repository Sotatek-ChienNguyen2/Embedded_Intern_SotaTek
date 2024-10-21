#include <stdio.h>
#include "ringbuf.h"



int main()
{
    RingBuffer_t ringbuffer;
    int value;

    ringbuffer_init(&ringbuffer, 5);

    ringbuffer_add(&ringbuffer, 10);
    ringbuffer_add(&ringbuffer, 20);

    ringbuffer_remove(&ringbuffer, &value);

    ringbuffer_add(&ringbuffer, 30);
    ringbuffer_add(&ringbuffer, 40);
    ringbuffer_add(&ringbuffer, 50);
    ringbuffer_add(&ringbuffer, 60);
    ringbuffer_add(&ringbuffer, 70);

    printf("Bộ đệm đầy: %d\n", ringbuffer_is_full(&ringbuffer));
    ringbuffer_print(&ringbuffer);

    printf("Số lượng phần tử hiện tại: %d\n", ringbuffer_size(&ringbuffer));



    return 0;
}