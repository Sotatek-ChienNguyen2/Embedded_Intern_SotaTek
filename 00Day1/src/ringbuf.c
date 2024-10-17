#include <stdio.h>
#include <stdlib.h>
#include "ringbuf.h"
#include <stdint.h>


RINGBUF ring_buff;


void ringbuffer_init(int size)
{
    printf("Init ring buffer \n");
    ring_buff.size = size;
    ring_buff.buf  = (uint8_t*)malloc(size * sizeof(uint8_t));

    if (ring_buff.buf != NULL)
    {
        printf("malloc sucessesfully \n");
    }
    ring_buff.head = 0;
    ring_buff.tail = 0;
    
}

int ringbuffer_add(int value)
{



}

int ringbuffer_is_empty()
{
    return (ring_buff.head == ring_buff.tail) ? 1 : 0;

}

int ringbuffer_is_full()
{
    return (ring_buff.head + 1 == ring_buff.tail) ? 1 : 0;
}

int ringbuffer_size()
{
    return ring_buff.tail - ring_buff.head;
}

