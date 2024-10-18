#include <stdio.h>
#include <stdlib.h>
#include "ringbuf.h"
#include <stdint.h>

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
    r.buffer[r.tail] = value;
    r.tail = (r.tail +1) % r.max_size; // nếu quá max sẽ quay lại 0;
    r.size++;
    return 0;
}

int ringbuffer_remove(int *value)
{
    if(r.size == 0){
        return -1;
    }
    *value = r.buffer[r.head];
    r.head = (r.head + 1) % (r.max_size); //nếu vượt quá sẽ quay lại 0
    r.size --;
    
    return 0;

}


int ringbuffer_is_full()
{
   return (r.size == r.max_size) ? 1 : 0;
   // return ((r.tail + 1) % r.max_size == r.head) ? 1 : 0;
}

int ringbuffer_is_empty()
{
    return (r.size == 0) ? 1 : 0;
    //return (head == tail) ? 1 : 0;


}

int ringbuffer_size()
{
    return r.size;


}




int ringbuffer_get_head() {
    return r.head;
}

int ringbuffer_get_tail() {
    return r.tail;
}


// Hàm in trạng thái của buffer
void ringbuffer_print() {
    printf("Trạng thái của buffer: ");
    for (int i = 0; i < r.max_size; i++) {
        int index = (r.head + i) % r.max_size;  // Tính toán chỉ số
        if (i < r.size) {
            printf("%d ", r.buffer[index]); // In giá trị nếu có
        } else {
            printf("N/A "); // In N/A cho ô trống
        }
    }
    printf("\n");
}

