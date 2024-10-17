#include <stdio.h>
#include "inc/ringbuf.h"



int main()
{
     int value;

    ringbuffer_init(5);

    printf("Bộ đệm rỗng: %d\n", ringbuffer_is_empty());

    ringbuffer_add(10);
    ringbuffer_add(20);

   
    ringbuffer_remove(&value);
    printf("Giá trị đã loại bỏ: %d\n", value); 

    ringbuffer_add(30);
    ringbuffer_add(40);
    ringbuffer_add(50);

    printf("Bộ đệm đầy: %d\n", ringbuffer_is_full());

    ringbuffer_remove(&value);
    printf("Giá trị đã loại bỏ: %d\n", value); 

    printf("Số lượng phần tử hiện tại: %d\n", ringbuffer_size());


    return 0;
}