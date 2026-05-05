/*
 * My_RTOS_FIFO.h
 *
 *  Created on: May 5, 2026
 *      Author: mahmo
 */

#ifndef INC_MY_RTOS_FIFO_H_
#define INC_MY_RTOS_FIFO_H_
#include "scheduler.h"

typedef Task_Ref* Element_Type;
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
	Element_Type* base;          /* Pointer to first byte of buffer */
	Element_Type* front;         /* Pointer to front element */
	Element_Type* rear;          /* Pointer to next free position */
    uint32_t length;        /* Maximum number of elements */
    uint32_t count;         /* Current number of elements */
} Queue_t;


Queue_Status_t Queue_Init(Queue_t* queue,Element_Type * buffer,uint32_t length);
Queue_Status_t Queue_Enqueue(Queue_t* queue,const Element_Type * item);
Queue_Status_t Queue_Dequeue(Queue_t* queue,Element_Type * item);
uint8_t Queue_Is_Full(const Queue_t* queue);
uint8_t Queue_Is_Empty(const Queue_t* queue);
void Queue_Print(const Queue_t * queue);



#endif /* INC_MY_RTOS_FIFO_H_ */
