#ifndef _LIFO_H_
#define _LIFO_H_

#include"String.h"

/* ===================== LIFO Object ===================== */
typedef struct {
    uint8_t* base;          /* Pointer to first byte of buffer */
    uint8_t* top;           /* Pointer to next free position */
    uint32_t  length;        /* Maximum number of elements */
    uint32_t  count;         /* Current number of elements */
    uint32_t  element_size;  /* Size of one element in bytes */
} LIFO_t;

/* ===================== Status Enum ===================== */
typedef enum {
    LIFO_OK = 0,         /* Operation succeeded */
    LIFO_FULL,           /* Stack is full */
    LIFO_EMPTY,          /* Stack is empty */
    LIFO_NULL,           /* Null pointer provided */
    INDEX_OUT_OF_RANGE,  /*INDEX_OUT_OF_RANGE*/

} LIFO_Status_t;

/* =====================  LIFO API ===================== */

/**
 * @brief Initialize the LIFO stack
 * @param lifo         Pointer to LIFO object
 * @param buffer       Pointer to pre-allocated memory buffer
 * @param length       Maximum number of elements
 * @param element_size Size of each element in bytes
 * @return Status of operation
 */
LIFO_Status_t LIFO_Init(LIFO_t* lifo, void* buffer, uint32_t length, uint32_t element_size);

/**
 * @brief Push an element onto the stack
 * @param lifo LIFO object
 * @param item Pointer to element to push
 * @return Status of operation
 */
LIFO_Status_t LIFO_Push(LIFO_t* lifo, const void* item);

/**
 * @brief Pop the top element from the stack
 * @param lifo LIFO object
 * @param item Pointer where popped element will be stored
 * @return Status of operation
 */
LIFO_Status_t LIFO_Pop(LIFO_t* lifo, void* item);

/**
 * @brief Peek at the top element without removing it
 * @param lifo LIFO object
 * @param item Pointer where the element will be copied
 * @return Status of operation
 */
LIFO_Status_t LIFO_Peek(const LIFO_t* lifo, void* item);

/**
 * @brief Peek at element by index from start (0 = bottom)
 * @param lifo LIFO object
 * @param index Index from start (bottom)
 * @param item Pointer to store the element
 * @return Status of operation
 */
LIFO_Status_t LIFO_Peek_From_Start(const LIFO_t* lifo, uint32_t index, void* item);

/**
 * @brief Peek at element by index from end (0 = top)
 * @param lifo LIFO object
 * @param index Index from top
 * @param item Pointer to store the element
 * @return Status of operation
 */
LIFO_Status_t LIFO_Peek_From_End(const LIFO_t* lifo, uint32_t index, void* item);

/**
 * @brief Get the middle element of the stack
 * @param lifo LIFO object
 * @param item Pointer to store middle element
 * @return Status of operation
 */
LIFO_Status_t LIFO_Get_Middle(const LIFO_t* lifo, void* item);

/**
 * @brief Reverse the stack elements in-place
 * @param lifo LIFO object
 * @return Status of operation
 */
LIFO_Status_t LIFO_Reverse(LIFO_t* lifo);

/**
 * @brief Clear all elements from stack
 * @param lifo LIFO object
 * @return Status of operation
 */
LIFO_Status_t LIFO_Clear(LIFO_t* lifo);

/*===================================================================*/
/*====================== Utilities Functions ========================*/
/*===================================================================*/

/**
 * @brief Get current number of elements
 * @param lifo LIFO object
 * @return Number of elements
 */
uint32_t LIFO_Count(const LIFO_t* lifo);

/**
 * @brief Get maximum capacity of stack
 * @param lifo LIFO object
 * @return Maximum number of elements
 */
uint32_t LIFO_Capacity(const LIFO_t* lifo);

#endif /* _LIFO_H_ */
