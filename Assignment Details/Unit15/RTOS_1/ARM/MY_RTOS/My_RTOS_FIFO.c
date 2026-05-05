/*
 * My_RTOS_FIFO.c
 *
 *  Created on: May 5, 2026
 *      Author: mahmo
 */
#include "My_RTOS_FIFO.h"

Queue_Status_t Queue_Init(Queue_t* queue, Element_Type * buffer, uint32_t length)
{
    if (!queue || !buffer || length == 0)
        return QUEUE_NULL;

    queue->base  = buffer;
    queue->front = buffer;
    queue->rear  = buffer;
    queue->length = length;
    queue->count = 0;

    return QUEUE_OK;
}
Queue_Status_t Queue_Enqueue(Queue_t* queue,const Element_Type* item)
{
    if (!queue || !item)
        return QUEUE_NULL;

    if (Queue_Is_Full(queue))
        return QUEUE_FULL;

    *(queue->rear) = *item;
    queue->count++;

    if (queue->rear == queue->base + (queue->length - 1))
        queue->rear = queue->base;
    else
        queue->rear++;

    return QUEUE_OK;
}

Queue_Status_t Queue_Dequeue(Queue_t* queue, Element_Type * item)
{
    if (!queue || !item)
        return QUEUE_NULL;

    if (Queue_Is_Empty(queue))
        return QUEUE_EMPTY;

    *item = *(queue->front);

    if (queue->front == queue->base + (queue->length - 1))
        queue->front = queue->base;
    else
        queue->front++;

    queue->count--;

    return QUEUE_OK;
}

uint8_t Queue_Is_Full(const Queue_t* queue)
{
    if (!queue)
        return 0;
    return (queue->count == queue->length) ? 1 : 0;
}

uint8_t Queue_Is_Empty(const Queue_t* queue)
{
    if (!queue)
        return 1;
    return (queue->count == 0) ? 1 : 0;
}
