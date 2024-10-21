#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "ringbuf.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void ringbuffer_init(RingBuffer_t *r, int size) {

    if(size > MAX_SIZE){
    size = MAX_SIZE;
    }
    r->head = 0;
    r->tail = 0;
    r->size = size;
}

int ringbuffer_add(RingBuffer_t *r, int value) {
    pthread_mutex_lock(&lock);
    if ((r->tail + 1) % r->size == r->head) { // Buffer đầy khi tail chỉ còn 1 vị trí là gặp head
        return -1;
    }
    r->buffer[r->tail] = value;
    r->tail = (r->tail + 1) % r->size; // nếu quá max sẽ quay lại 0;
    pthread_mutex_unlock(&lock);
    return 0;
}

int ringbuffer_remove(RingBuffer_t *r, int *value) {
    pthread_mutex_lock(&lock);
    if (r->head == r->tail) {
        pthread_mutex_unlock(&lock);
        return -1;
    }
    *value = r->buffer[r->head];
    r->head = (r->head + 1) % (r->size); // nếu vượt quá sẽ quay lại 0
    pthread_mutex_unlock(&lock);
    return 0;
}

int ringbuffer_is_full(RingBuffer_t *r) {  
    return ((r->tail + 1) % r->size == r->head) ? 1 : 0; 
}

int ringbuffer_is_empty(RingBuffer_t *r) {
    return (r->head == r->tail) ? 1 : 0;
}

int ringbuffer_size(RingBuffer_t *r) {
    // pthread_mutex_lock(&lock);
    return (r->tail - r->head + r->size) % r->size; // Tính số phần tử hiện tại
    // pthread_mutex_unlock(&lock);
}

// Hàm để in trạng thái của buffer
void ringbuffer_print(RingBuffer_t *r) {
    printf("Trạng thái của buffer: ");
    for (int i = 0; i < r->size; i++) {
        int index = (r->head + i) % r->size;
        if (i < ringbuffer_size(r)) {
            printf("%d ", r->buffer[index]); 
        } else {
            printf("N/A "); // In N/A cho ô trống
        }
    }
    printf("\n");
}
