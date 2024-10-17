#include <stdio.h>
#include <stdint.h>


typedef struct{
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint8_t  *buf;

} RINGBUF;






void ringbuffer_init(int size); 
int ringbuffer_add(int value);
int ringbuffer_remove(int* value);
int ringbuffer_is_full();
int ringbuffer_is_empty();
int ringbuffer_size();

