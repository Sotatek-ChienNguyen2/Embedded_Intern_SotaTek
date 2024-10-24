#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "my_function.h"


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * \brief Initializes a RingBuffer object.
 * \param r Pointer to a RingBuffer object.
 * \param size Size of the buffer.
 * \return 0 if successful, -1 if failed.
 */
int ringbuffer_init(RingBuffer_t *r, int size)
{
    if (r == NULL || size < 2 || size > MAX_SIZE)
        return -1;

    r->max_size = size;
    r->head = 0;
    r->tail = 0;
    r->size = 0;

    return 0;
}

/**
 * \brief Adds a character into the ring buffer.
 * \param r Pointer to a RingBuffer object.
 * \param value Character to be added.
 * \return 0 if successful, -1 if failed.
 */
int ringbuffer_add(RingBuffer_t *r, int value)
{
    pthread_mutex_lock(&lock);

    if (r == NULL || ringbuffer_is_full(r) == 1) {
        return -1;
    }

    r->buffer[r->tail] = value;
    r->tail = (r->tail + 1) % r->max_size; // If exceeds max(tail = max_size - 1), wrap around to 0.
    r->size++;
    pthread_mutex_unlock(&lock);

    return 0;
}


/**
 * \brief Removes a character from the ring buffer.
 * \param r Pointer to a RingBuffer object.
 * \param value Pointer to the read value.
 * \return 0 if successful, -1 if failed.
 */

int ringbuffer_remove(RingBuffer_t *r, int *value)
{
    pthread_mutex_lock(&lock);

    if (ringbuffer_is_empty(r) == 1 || r == NULL) {
        return -1;
    }

    *value = r->buffer[r->head];
    r->head = (r->head + 1) % r->max_size; // If exceeds max (head = max_size - 1), wrap around to 0.
    r->size--;
    pthread_mutex_unlock(&lock);
    
    return 0;
}

/**
 * \brief Checks if the ring buffer is full.
 * \param r Pointer to a RingBuffer object.
 * \return 1 if the buffer is full, 0 if not, -1 if the pointer is NULL.
 */
int ringbuffer_is_full(RingBuffer_t *r)
{
    if (r == NULL)
        return -1;
    return (r->size == r->max_size) ? 1 : 0;
}


/**
 * \brief Checks if the ring buffer is empty.
 * \param r Pointer to a RingBuffer object.
 * \return 1 if the buffer is empty, 0 if not, -1 if the pointer is NULL.
 */


int ringbuffer_is_empty(RingBuffer_t *r)
{
    if(r == NULL)
        return -1;
    return (r->size == 0) ? 1 : 0;

}

/**
 * \brief Gets the current size of the ring buffer.
 * \param r Pointer to a RingBuffer object.
 * \return The number of elements in the buffer, or -1 if the pointer is NULL.
 */
int ringbuffer_size(RingBuffer_t *r)
{
    if (r == NULL)
        return -1;
    return r->size;
}

