#include"LIFO.h"

/* ===================== Initialize LIFO ===================== */
LIFO_Status_t LIFO_Init(LIFO_t* lifo, void* buffer, uint32_t length, uint32_t element_size)
{
    if (NULL == lifo || NULL == buffer || length == 0 || element_size == 0) return LIFO_NULL;
    lifo->base = (uint8_t*)buffer;
    lifo->length = length;
    lifo->element_size = element_size;
    lifo->top = (uint8_t*)buffer;
    lifo->count = 0;
    return LIFO_OK;

}

/* ===================== Push Element ===================== */
LIFO_Status_t LIFO_Push(LIFO_t* lifo, const void* item)
{

    if (NULL == lifo || NULL == item) return LIFO_NULL;

    if (lifo->count == lifo->length)  return LIFO_FULL;

    /* Copy element to stack */
    my_memcpy(lifo->top, item, lifo->element_size);

    /* Update pointer and count */
    lifo->top += lifo->element_size;
    lifo->count++;

    return LIFO_OK;

}

/* ===================== Pop Element ===================== */
LIFO_Status_t LIFO_Pop(LIFO_t* lifo, void* item)
{
    if (NULL == lifo || NULL == item) return LIFO_NULL;

    if (lifo->count == 0) return LIFO_EMPTY;

    /* Move top back to last element */
    lifo->top -= lifo->element_size;

    /* Copy element to output */
    my_memcpy(item, lifo->top, lifo->element_size);

    /* Update count */
    lifo->count--;

    return LIFO_OK;
}

/* ===================== Peek Top Element ===================== */
LIFO_Status_t LIFO_Peek(const LIFO_t* lifo, void* item)
{
    if (NULL == lifo || NULL == item) return LIFO_NULL;

    if (lifo->count == 0) return LIFO_EMPTY;

    /* Copy top element without changing top pointer */
    my_memcpy(item, lifo->top - lifo->element_size, lifo->element_size);

    return LIFO_OK;

}

/* ===================== Peek From Start ===================== */
LIFO_Status_t LIFO_Peek_From_Start(const LIFO_t* lifo, uint32_t index, void* item)
{
    if (NULL == lifo || NULL == item) return LIFO_NULL;

    if (lifo->count == 0) return LIFO_EMPTY;

    if (index >= lifo->count) return INDEX_OUT_OF_RANGE;
    /* Copy element at index from Start without changing top pointer */

    my_memcpy(item, (uint8_t*)(lifo->base + (lifo->element_size * index)), lifo->element_size);

    return LIFO_OK;

}

/* ===================== Peek From End ===================== */
LIFO_Status_t LIFO_Peek_From_End(const LIFO_t* lifo, uint32_t index, void* item)
{
    if (NULL == lifo || NULL == item) return LIFO_NULL;

    if (lifo->count == 0) return LIFO_EMPTY;

    if (index >= lifo->count) return INDEX_OUT_OF_RANGE;

    /* Copy element at index from end without changing top pointer */
    my_memcpy(item, (uint8_t*)(lifo->top - lifo->element_size * (index + 1)), lifo->element_size);
    return LIFO_OK;
}

/* ===================== Get Middle Element ===================== */
LIFO_Status_t LIFO_Get_Middle(const LIFO_t* lifo, void* item)
{
    if (NULL == lifo || NULL == item) return LIFO_NULL;

    if (lifo->count == 0) return LIFO_EMPTY;


    uint32_t middle_index = lifo->count / 2;

    /* Copy middle element without changing top pointer */
    my_memcpy(item, lifo->base + middle_index * lifo->element_size, lifo->element_size);


    return LIFO_OK;

}

/* ===================== Reverse LIFO ===================== */
LIFO_Status_t LIFO_Reverse(LIFO_t* lifo)
{
    if (lifo == NULL) return LIFO_NULL;
    if (lifo->count == 0) return LIFO_EMPTY;

    uint8_t* start = lifo->base;
    uint8_t* end = lifo->top - lifo->element_size;

    while (start < end)
    {
        /* Swap element byte by byte */
        for (uint32_t i = 0; i < lifo->element_size; i++)
        {
            uint8_t temp = start[i];
            start[i] = end[i];
            end[i] = temp;
        }

        start += lifo->element_size;
        end -= lifo->element_size;
    }

    return LIFO_OK;
}


/*===================================================================*/
/*====================== Utilities Functions ========================*/
/*===================================================================*/

/* ===================== Clear Stack ===================== */
LIFO_Status_t LIFO_Clear(LIFO_t* lifo)
{
    if (lifo == NULL) return LIFO_NULL;

    lifo->top = lifo->base;  // reset top to start of buffer
    lifo->count = 0;          // reset count

    return LIFO_OK;
}

/* ===================== Get Count ===================== */
uint32_t LIFO_Count(const LIFO_t* lifo)
{
    if (lifo == NULL) return 0;  // null safe
    return lifo->count;
}

/* ===================== Get Capacity ===================== */
uint32_t LIFO_Capacity(const LIFO_t* lifo)
{
    if (lifo == NULL) return 0;  // null safe
    return lifo->length;          // maximum number of elements
}
