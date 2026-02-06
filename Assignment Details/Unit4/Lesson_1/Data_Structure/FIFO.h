#ifndef _FIFO_H_
#define _FIFO_H_

#include"String.h"

/* ===================== Status Enum ===================== */
typedef enum {
    QUEUE_OK = 0,        /* Operation succeeded */
    QUEUE_FULL,          /* Queue is full */
    QUEUE_EMPTY,         /* Queue is empty */
    QUEUE_NULL,          /* Null pointer provided */
    INDEX_OUT_OF_RANGE   /* Index out of range */
} Queue_Status_t;

/* ===================== Queue Object ===================== */
typedef struct {
    uint8_t* base;          /* Pointer to first byte of buffer */
    uint8_t* front;         /* Pointer to front element */
    uint8_t* rear;          /* Pointer to next free position */
    uint32_t length;        /* Maximum number of elements */
    uint32_t count;         /* Current number of elements */
    uint32_t element_size;  /* Size of one element in bytes */
} Queue_t;

/*===================================================================*/
/*==========================  Queue API =============================*/
/*===================================================================*/

/**
 * @brief Initialize the Queue object
 *
 * @param queue        Pointer to Queue object
 * @param buffer       Pointer to pre-allocated memory buffer
 * @param length       Maximum number of elements
 * @param element_size Size of each element in bytes
 *
 * @return Status of operation
 */
Queue_Status_t Queue_Init(Queue_t* queue,
    void* buffer,
    uint32_t length,
    uint32_t element_size);

/**
 * @brief Insert an element at the rear of the Queue
 *
 * @param queue Queue object
 * @param item  Pointer to element to enqueue
 *
 * @return Status of operation
 */
Queue_Status_t Queue_Enqueue(Queue_t* queue, const void* item);

/**
 * @brief Remove the front element from the Queue
 *
 * @param queue Queue object
 * @param item  Pointer to store the dequeued element
 *
 * @return Status of operation
 */
Queue_Status_t Queue_Dequeue(Queue_t* queue, void* item);

/**
 * @brief Peek at the front element without removing it
 *
 * @param queue Queue object
 * @param item  Pointer to store the front element
 *
 * @return Status of operation
 */
Queue_Status_t Queue_Peek_Front(const Queue_t* queue, void* item);

/**
 * @brief Peek at the rear element without removing it
 *
 * @param queue Queue object
 * @param item  Pointer to store the rear element
 *
 * @return Status of operation
 */
Queue_Status_t Queue_Peek_Rear(const Queue_t* queue, void* item);

/**
 * @brief Peek element by index from front (0 = front)
 *
 * @param queue Queue object
 * @param index Index from front
 * @param item  Pointer to store the element
 *
 * @return Status of operation
 */
Queue_Status_t Queue_Peek_By_Index(const Queue_t* queue,
    uint32_t index,
    void* item);

/**
 * @brief Reverse Queue elements in-place
 *
 * @note This reverses the physical storage order, not the Queue semantics.
 *
 * @param queue Queue object
 *
 * @return Status of operation
 */
Queue_Status_t Queue_Reverse(Queue_t* queue);

/**
 * @brief Clear all elements from the Queue
 *
 * @param queue Queue object
 *
 * @return Status of operation
 */
Queue_Status_t Queue_Clear(Queue_t* queue);

/*===================================================================*/
/*====================== Utilities Functions ========================*/
/*===================================================================*/

/**
 * @brief Get current number of elements in Queue
 *
 * @param queue Queue object
 *
 * @return Number of elements
 */
uint32_t Queue_Count(const Queue_t* queue);

/**
 * @brief Get maximum Queue capacity
 *
 * @param queue Queue object
 *
 * @return Maximum number of elements
 */
uint32_t Queue_Capacity(const Queue_t* queue);

/**
 * @brief Check if Queue is full
 *
 * @param queue Queue object
 *
 * @return 1 if full, 0 otherwise
 */
uint8_t Queue_Is_Full(const Queue_t* queue);

/**
 * @brief Check if Queue is empty
 *
 * @param queue Queue object
 *
 * @return 1 if empty, 0 otherwise
 */
uint8_t Queue_Is_Empty(const Queue_t* queue);

#endif /* _FIFO_H_ */
