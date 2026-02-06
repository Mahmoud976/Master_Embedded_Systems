#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include"String.h"

/* ===================== Status Enum ===================== */
/**
 * @brief Status codes returned by Linked List operations
 */
typedef enum {
    LIST_OK = 0,        /**< Operation succeeded */
    LIST_NULL,          /**< Null pointer provided */
    LIST_EMPTY,         /**< List is empty */
    LIST_NOT_FOUND,     /**< Node not found */
    INDEX_OUT_OF_RANGE, /**< Index out of range */
    LIST_LOOP_DETECTED  /**< Loop detected in list */
} List_Status_t;

/* ===================== Node Structure ===================== */
/**
 * @brief Node structure for Linked List
 */
typedef struct Node {
    void* data;          /**< Pointer to the node data */
    struct Node* next;   /**< Pointer to the next node in the list */
} Node_t;

/* ===================== Linked List Object ===================== */
/**
 * @brief Linked List structure
 */
typedef struct {
    Node_t* head;         /**< Pointer to first node */
    Node_t* tail;         /**< Pointer to last node */
    uint32_t count;       /**< Number of nodes currently in the list */
    uint32_t element_size;/**< Size of each element in bytes */
} LinkedList_t;

/*===================================================================*/
/*========================= Linked List API =========================*/
/*===================================================================*/

/*================ Initialize =================*/
/**
 * @brief Initialize a linked list object
 *
 * @param list Pointer to linked list object
 * @param element_size Size of each element in bytes
 *
 * @return Status of operation
 */
List_Status_t List_Init(LinkedList_t* list, uint32_t element_size);

/*================ Insert Operations =================*/

/**
 * @brief Insert element at the head of the list
 *
 * @param list Pointer to linked list
 * @param data Pointer to data to insert
 *
 * @return Status of operation
 */
List_Status_t List_Insert_From_Head(LinkedList_t* list, const void* data);

/**
 * @brief Insert element at the tail of the list
 *
 * @param list Pointer to linked list
 * @param data Pointer to data to insert
 *
 * @return Status of operation
 */
List_Status_t List_Insert_From_Tail(LinkedList_t* list, const void* data);

/**
 * @brief Insert element at a specific index (0 = head)
 *
 * @param list Pointer to linked list
 * @param index Index to insert at
 * @param data Pointer to data to insert
 *
 * @return Status of operation
 */
List_Status_t List_Insert_At_Index(LinkedList_t* list, uint32_t index, const void* data);

/*================ Remove Operations =================*/

/**
 * @brief Remove element from the head of the list
 *
 * @param list Pointer to linked list
 * @param data Pointer to store removed data
 *
 * @return Status of operation
 */
List_Status_t List_Remove_From_Head(LinkedList_t* list, void* data);

/**
 * @brief Remove element from the tail of the list
 *
 * @param list Pointer to linked list
 * @param data Pointer to store removed data
 *
 * @return Status of operation
 */
List_Status_t List_Remove_From_Tail(LinkedList_t* list, void* data);

/**
 * @brief Remove element at a specific index
 *
 * @param list Pointer to linked list
 * @param index Index of element to remove
 * @param data Pointer to store removed data
 *
 * @return Status of operation
 */
List_Status_t List_Remove_At_Index(LinkedList_t* list, uint32_t index, void* data);

/*================ Get Operations =================*/

/**
 * @brief Get element from the head of the list without removing
 *
 * @param list Pointer to linked list
 * @param data Pointer to store element
 *
 * @return Status of operation
 */
List_Status_t List_Get_From_Head(const LinkedList_t* list, void* data);

/**
 * @brief Get element from the tail of the list without removing
 *
 * @param list Pointer to linked list
 * @param data Pointer to store element
 *
 * @return Status of operation
 */
List_Status_t List_Get_From_Tail(const LinkedList_t* list, void* data);

/**
 * @brief Get element at a specific index without removing
 *
 * @param list Pointer to linked list
 * @param index Index of element
 * @param data Pointer to store element
 *
 * @return Status of operation
 */
List_Status_t List_Get_At_Index(const LinkedList_t* list, uint32_t index, void* data);


/**
 * @brief Get the middle element from the linked list
 *
 * Middle is defined as count/2 (0-based index).
 * For even number of nodes, it returns the first element of the second half.
 *
 * @param list Pointer to linked list
 * @param data Pointer to store the middle element
 *
 * @return Status of operation
 */
List_Status_t List_Get_From_Middle(const LinkedList_t* list, void* data);





/*================ Other Operations =================*/

/**
 * @brief Find the first node containing the specified data
 *
 * @param list Pointer to linked list
 * @param data Pointer to data to search for
 * @param index Pointer to store index of found node
 *
 * @return Status of operation
 */
List_Status_t List_Find(const LinkedList_t* list, const void* data, uint32_t* index);

/**
 * @brief Reverse the linked list in place
 *
 * @param list Pointer to linked list
 *
 * @return Status of operation
 */
List_Status_t List_Reverse(LinkedList_t* list);

/**
 * @brief Clear the entire list and free memory
 *
 * @param list Pointer to linked list
 *
 * @return Status of operation
 */
List_Status_t List_Clear(LinkedList_t* list);

/**
 * @brief Detect if the linked list contains a loop (cycle)
 *
 * Uses Floyd's cycle detection algorithm (slow and fast pointer)
 *
 * @param list Pointer to linked list
 *
 * @return 1 if loop exists, 0 otherwise
 */
uint8_t List_Has_Loop(const LinkedList_t* list);

/*===================================================================*/
/*====================== Utility Functions ==========================*/
/*===================================================================*/

/**
 * @brief Get the current number of nodes in the list
 *
 * @param list Pointer to linked list
 *
 * @return Number of nodes
 */
uint32_t List_Count(const LinkedList_t* list);

/**
 * @brief Check if the list is empty
 *
 * @param list Pointer to linked list
 *
 * @return 1 if empty, 0 otherwise
 */
uint8_t List_Is_Empty(const LinkedList_t* list);

#endif /* _LINKED_LIST_H_ */
