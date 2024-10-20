#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "my_function.h"


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

RingBuffer_t r;

void ringbuffer_init(int size)
{
    if(size > MAX_SIZE){
        size = MAX_SIZE;
    }
    r.max_size = size;
    r.head = 0;
    r.tail = 0;
    r.size = 0;
}

int ringbuffer_add(int value)
{
    if(r.size == r.max_size){
        return -1;
    }
    pthread_mutex_lock(&lock);
    r.buffer[r.tail] = value;
    r.tail = (r.tail +1) % r.max_size; // nếu quá max sẽ quay lại 0;
    r.size++;
    pthread_mutex_unlock(&lock);
    return 0;
}

int ringbuffer_remove(int *value)
{
    if(r.size == 0){
        return -1;
    }
    *value = r.buffer[r.head];
    pthread_mutex_lock(&lock);
    r.head = (r.head + 1) % (r.max_size); //nếu vượt quá sẽ quay lại 0
    r.size --;
    pthread_mutex_unlock(&lock);
    
    return 0;

}


int ringbuffer_is_full()
{
   return (r.size == r.max_size) ? 1 : 0;
   
}

int ringbuffer_is_empty()
{
    return (r.size == 0) ? 1 : 0;

}

int ringbuffer_size()
{
    return r.size;
}


void ringbuffer_print() {
    printf("Trạng thái của buffer: ");
    for (int i = 0; i < r.max_size; i++) {
        int index = (r.head + i) % r.max_size;  
        if (i < r.size) {
            printf("%d ", r.buffer[index]); 
        } else {
            printf("N/A "); // In N/A cho ô trống
        }
    }
    printf("\n");
}

