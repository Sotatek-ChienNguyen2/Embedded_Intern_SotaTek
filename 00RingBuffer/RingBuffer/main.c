#include <stdio.h>
#include "ringbuf.h"



int main()
{
    RingBuffer_t ringbuffer;
    int value;

    ringbuffer_init(&ringbuffer, 5);

    ringbuffer_add(&ringbuffer, 10);
    ringbuffer_add(&ringbuffer, 20);
    ringbuffer_add(&ringbuffer, 30);
    ringbuffer_add(&ringbuffer, 40);
    ringbuffer_add(&ringbuffer, 50);


    printf("Bộ đệm đầy: %d\n", ringbuffer_is_full(&ringbuffer));

    ringbuffer_add(&ringbuffer, 60);

    printf("Số lượng phần tử hiện tại: %d\n", ringbuffer_size(&ringbuffer));



    return 0;
}