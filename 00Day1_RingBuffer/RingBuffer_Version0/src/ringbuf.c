#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "ringbuf.h"


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;



void ringbuffer_init(RingBuffer_t *r, int size)
{
    if(size > MAX_SIZE){
        size = MAX_SIZE;
    }
    r->max_size = size;
    r->head = 0;
    r->tail = 0;
    r->size = 0;
}

int ringbuffer_add(RingBuffer_t *r, int value)
{
    pthread_mutex_lock(&lock);
    if(r->size == r->max_size){
        return -1;
    }
    
    r->buffer[r->tail] = value;
    r->tail = (r->tail +1) % r->max_size; // nếu quá max sẽ quay lại 0;
    r->size++;
    pthread_mutex_unlock(&lock);
    return 0;
}

int ringbuffer_remove(RingBuffer_t *r, int *value)
{
    pthread_mutex_lock(&lock);
    if(r->size == 0){
        return -1;
    }
    *value = r->buffer[r->head];
    
    r->head = (r->head + 1) % (r->max_size); //nếu vượt quá sẽ quay lại 0
    r->size --;
    pthread_mutex_unlock(&lock);
    
    return 0;

}


int ringbuffer_is_full(RingBuffer_t *r)
{
   return (r->size == r->max_size) ? 1 : 0;
   
}

int ringbuffer_is_empty(RingBuffer_t *r)
{
    return (r->size == 0) ? 1 : 0;

}

int ringbuffer_size(RingBuffer_t *r)
{
    return r->size;
}


void ringbuffer_print(RingBuffer_t *r) {
    printf("Trạng thái của buffer: ");
    for (int i = 0; i < r->max_size; i++) {
        int index = (r->head + i) % r->max_size;  
        if (i < r->size) {
            printf("%d ", r->buffer[index]); 
        } else {
            printf("N/A "); // In N/A cho ô trống
        }
    }
    printf("\n");
}

