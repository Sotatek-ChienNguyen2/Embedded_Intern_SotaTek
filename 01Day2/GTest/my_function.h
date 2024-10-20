

#ifndef _RING_BUF_H_
#define _RING_BUF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define MAX_SIZE 100

typedef struct{

    uint32_t buffer[MAX_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t max_size;
    uint32_t size;
} RingBuffer_t;

void ringbuffer_init(int size);
int ringbuffer_add(int value);
int ringbuffer_remove(int *value);
int ringbuffer_is_full();
int ringbuffer_is_empty();
int ringbuffer_size();

int ringbuffer_get_head();

void ringbuffer_print();

#ifdef __cplusplus
}
#endif
#endif
