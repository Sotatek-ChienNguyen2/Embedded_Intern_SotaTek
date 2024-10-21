#ifndef _RING_BUF_H_
#define _RING_BUF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define MAX_SIZE 10

typedef struct{

    int buffer[MAX_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t size;
} RingBuffer_t;

void ringbuffer_init(RingBuffer_t *r, int size);
int ringbuffer_add(RingBuffer_t *r, int value);
int ringbuffer_remove(RingBuffer_t *r, int *value);
int ringbuffer_is_full(RingBuffer_t *r);
int ringbuffer_is_empty(RingBuffer_t *r);
int ringbuffer_size(RingBuffer_t *r);
void ringbuffer_print(RingBuffer_t *r);

#ifdef __cplusplus
}
#endif
#endif
