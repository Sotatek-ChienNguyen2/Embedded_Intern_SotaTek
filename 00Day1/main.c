#include <stdio.h>
#include "inc/ringbuf.h"

int size  = 5;
uint8_t isEmpty;
uint8_t isFull;

int main()
{
   ringbuffer_init(size);
   isFull   =  ringbuffer_is_full();
   isEmpty  =  ringbuffer_is_empty();
   printf("Status code isEmpty: %d\n", isEmpty);
   printf("Status code isFull %d\n", isFull);




    return 0;
}