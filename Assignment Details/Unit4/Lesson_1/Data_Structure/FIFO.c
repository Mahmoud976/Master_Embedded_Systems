#include "FIFO.h"

/*==================== Queue API Implementation ====================*/

Queue_Status_t Queue_Init(Queue_t* queue, void* buffer, uint32_t length, uint32_t element_size)
{
    if (!queue || !buffer || length == 0 || element_size == 0)
        return QUEUE_NULL;

    queue->base = (uint8_t*)buffer;
    queue->front = (uint8_t*)buffer;
    queue->rear = (uint8_t*)buffer;
    queue->length = length;
    queue->count = 0;
    queue->element_size = element_size;

    return QUEUE_OK;
}

Queue_Status_t Queue_Enqueue(Queue_t* queue, const void* item)
{
    if (!queue || !item)
        return QUEUE_NULL;

    if (Queue_Is_Full(queue))
        return QUEUE_FULL;

    my_memcpy(queue->rear, item, queue->element_size);

    // Move rear pointer
    queue->rear += queue->element_size;
    if (queue->rear >= queue->base + (queue->length * queue->element_size))
        queue->rear = queue->base;  // Wrap around

    queue->count++;
    return QUEUE_OK;
}

Queue_Status_t Queue_Dequeue(Queue_t* queue, void* item)
{
    if (!queue || !item)
        return QUEUE_NULL;

    if (Queue_Is_Empty(queue))
        return QUEUE_EMPTY;

    my_memcpy(item, queue->front, queue->element_size);

    // Move front pointer
    queue->front += queue->element_size;
    if (queue->front >= queue->base + (queue->length * queue->element_size))
        queue->front = queue->base;  // Wrap around

    queue->count--;
    return QUEUE_OK;
}

Queue_Status_t Queue_Peek_Front(const Queue_t* queue, void* item)
{
    if (!queue || !item)
        return QUEUE_NULL;

    if (Queue_Is_Empty(queue))
        return QUEUE_EMPTY;

    my_memcpy(item, queue->front, queue->element_size);
    return QUEUE_OK;
}

Queue_Status_t Queue_Peek_Rear(const Queue_t* queue, void* item)
{
    if (!queue || !item)
        return QUEUE_NULL;

    if (Queue_Is_Empty(queue))
        return QUEUE_EMPTY;

    uint8_t* rear_pos = queue->rear;
    if (rear_pos == queue->base)
        rear_pos = queue->base + (queue->length - 1) * queue->element_size;
    else
        rear_pos -= queue->element_size;

    my_memcpy(item, rear_pos, queue->element_size);
    return QUEUE_OK;
}

Queue_Status_t Queue_Peek_By_Index(const Queue_t* queue, uint32_t index, void* item)
{
    if (!queue || !item)
        return QUEUE_NULL;

    if (index >= queue->count)
        return INDEX_OUT_OF_RANGE;

    uint8_t* ptr = queue->front + index * queue->element_size;
    if (ptr >= queue->base + (queue->length * queue->element_size))
        ptr -= queue->length * queue->element_size;  // Wrap around

    my_memcpy(item, ptr, queue->element_size);
    return QUEUE_OK;
}

Queue_Status_t Queue_Reverse(Queue_t* queue)
{
    if (!queue)
        return QUEUE_NULL;

    if (Queue_Is_Empty(queue) || queue->count == 1)
        return QUEUE_OK;

    uint32_t i = 0;
    uint32_t j = queue->count - 1;

    while (i < j)
    {
        for (uint32_t k = 0; k < queue->element_size; k++)
        {
            uint8_t* ptr_i = queue->front + ((i * queue->element_size + k) % (queue->length * queue->element_size));
            uint8_t* ptr_j = queue->front + ((j * queue->element_size + k) % (queue->length * queue->element_size));

            // Swap byte by byte
            uint8_t tmp = *ptr_i;
            *ptr_i = *ptr_j;
            *ptr_j = tmp;
        }

        i++;
        j--;
    }

    return QUEUE_OK;
}


Queue_Status_t Queue_Clear(Queue_t* queue)
{
    if (!queue)
        return QUEUE_NULL;

    queue->front = queue->base;
    queue->rear = queue->base;
    queue->count = 0;

    return QUEUE_OK;
}

/*==================== Utility Functions ====================*/

uint32_t Queue_Count(const Queue_t* queue)
{
    if (!queue)
        return 0;
    return queue->count;
}

uint32_t Queue_Capacity(const Queue_t* queue)
{
    if (!queue)
        return 0;
    return queue->length;
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
