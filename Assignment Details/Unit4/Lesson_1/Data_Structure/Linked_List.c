#include "Linked_List.h"


/*==================== Initialize ====================*/
/**
 * @brief Initialize a Linked List
 * @param list Pointer to list
 * @param element_size Size of each element in bytes
 * @return Status
 */
List_Status_t List_Init(LinkedList_t* list, uint32_t element_size)
{
    if (!list || element_size == 0) return LIST_NULL;

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    list->element_size = element_size;

    return LIST_OK;
}

/*==================== Insert ====================*/
/**
 * @brief Insert a new node at head
 */
List_Status_t List_Insert_From_Head(LinkedList_t* list, const void* data)
{
    if (!list || !data || list->element_size == 0) return LIST_NULL;

    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    if (!node) return LIST_NULL;
    node->data = malloc(list->element_size);
    if (!node->data) { free(node); return LIST_NULL; }

    my_memcpy(node->data, data, list->element_size);
    node->next = list->head;
    list->head = node;
    if (list->count == 0) list->tail = node;

    list->count++;
    return LIST_OK;
}

/**
 * @brief Insert a new node at tail
 */
List_Status_t List_Insert_From_Tail(LinkedList_t* list, const void* data)
{
    if (!list || !data || list->element_size == 0) return LIST_NULL;

    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    if (!node) return LIST_NULL;

    node->data = malloc(list->element_size);
    if (!node->data) { free(node); return LIST_NULL; }

    my_memcpy(node->data, data, list->element_size);
    node->next = NULL;

    if (list->count == 0)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    list->count++;
    return LIST_OK;
}

/**
 * @brief Insert a new node at a given index
 */
List_Status_t List_Insert_At_Index(LinkedList_t* list, uint32_t index, const void* data)
{
    if (!list || !data) return LIST_NULL;
    if (index > list->count) return INDEX_OUT_OF_RANGE;

    if (index == 0) return List_Insert_From_Head(list, data);
    if (index == list->count) return List_Insert_From_Tail(list, data);

    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    if (!node) return LIST_NULL;

    node->data = malloc(list->element_size);
    if (!node->data) { free(node); return LIST_NULL; }

    my_memcpy(node->data, data, list->element_size);

    Node_t* current = list->head;
    for (uint32_t i = 0; i < index - 1; i++)
        current = current->next;

    node->next = current->next;
    current->next = node;

    list->count++;
    return LIST_OK;
}

/*==================== Remove ====================*/
List_Status_t List_Remove_From_Head(LinkedList_t* list, void* data)
{
    if (!list || !data) return LIST_NULL;
    if (list->count == 0) return LIST_EMPTY;

    Node_t* temp = list->head;
    my_memcpy(data, temp->data, list->element_size);

    list->head = temp->next;
    if (!list->head) list->tail = NULL;

    free(temp->data);
    free(temp);

    list->count--;
    return LIST_OK;
}

List_Status_t List_Remove_From_Tail(LinkedList_t* list, void* data)
{
    if (!list || !data) return LIST_NULL;
    if (list->count == 0) return LIST_EMPTY;

    Node_t* current = list->head;
    Node_t* prev = NULL;

    while (current->next)
    {
        prev = current;
        current = current->next;
    }

    my_memcpy(data, current->data, list->element_size);

    if (prev) prev->next = NULL;
    else list->head = NULL;

    list->tail = prev;

    free(current->data);
    free(current);

    list->count--;
    return LIST_OK;
}

List_Status_t List_Remove_At_Index(LinkedList_t* list, uint32_t index, void* data)
{
    if (!list || !data) return LIST_NULL;
    if (list->count == 0) return LIST_EMPTY;
    if (index >= list->count) return INDEX_OUT_OF_RANGE;
    if (index == 0) return List_Remove_From_Head(list, data);
    if (index == list->count - 1) return List_Remove_From_Tail(list, data);

    Node_t* prev = list->head;
    for (uint32_t i = 0; i < index - 1; i++)
        prev = prev->next;

    Node_t* temp = prev->next;
    my_memcpy(data, temp->data, list->element_size);

    prev->next = temp->next;

    free(temp->data);
    free(temp);

    list->count--;
    return LIST_OK;
}

/*==================== Get ====================*/
List_Status_t List_Get_From_Head(const LinkedList_t* list, void* data)
{
    if (!list || !data) return LIST_NULL;
    if (list->count == 0) return LIST_EMPTY;

    my_memcpy(data, list->head->data, list->element_size);
    return LIST_OK;
}

List_Status_t List_Get_From_Tail(const LinkedList_t* list, void* data)
{
    if (!list || !data) return LIST_NULL;
    if (list->count == 0) return LIST_EMPTY;

    my_memcpy(data, list->tail->data, list->element_size);
    return LIST_OK;
}

List_Status_t List_Get_At_Index(const LinkedList_t* list, uint32_t index, void* data)
{
    if (!list || !data) return LIST_NULL;
    if (list->count == 0) return LIST_EMPTY;
    if (index >= list->count) return INDEX_OUT_OF_RANGE;

    Node_t* current = list->head;
    for (uint32_t i = 0; i < index; i++)
        current = current->next;

    my_memcpy(data, current->data, list->element_size);
    return LIST_OK;
}

List_Status_t List_Get_From_Middle(const LinkedList_t* list, void* data)
{
    if (!list || !data) return LIST_NULL;
    if (list->count == 0) return LIST_EMPTY;

    uint32_t mid = list->count / 2;
    Node_t* current = list->head;
    for (uint32_t i = 0; i < mid; i++)
        current = current->next;

    my_memcpy(data, current->data, list->element_size);
    return LIST_OK;
}

/*==================== Find ====================*/
List_Status_t List_Find(const LinkedList_t* list, const void* data, uint32_t* index)
{
    if (!list || !data || !index) return LIST_NULL;
    if (list->count == 0) return LIST_EMPTY;

    Node_t* current = list->head;
    for (uint32_t i = 0; current; i++, current = current->next)
    {
        if (my_memcmp(current->data, data, list->element_size) == 0)
        {
            *index = i;
            return LIST_OK;
        }
    }
    return LIST_NOT_FOUND;
}

/*==================== Reverse ====================*/
List_Status_t List_Reverse(LinkedList_t* list)
{
    if (!list) return LIST_NULL;
    if (list->count <= 1) return LIST_OK;

    Node_t* prev = NULL;
    Node_t* curr = list->head;
    Node_t* next = NULL;

    list->tail = list->head;

    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    list->head = prev;
    return LIST_OK;
}

/*==================== Clear ====================*/
List_Status_t List_Clear(LinkedList_t* list)
{
    if (!list) return LIST_NULL;

    Node_t* curr = list->head;
    while (curr)
    {
        Node_t* temp = curr;
        curr = curr->next;
        free(temp->data);
        free(temp);
    }

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

    return LIST_OK;
}

/*==================== Loop Detection ====================*/
uint8_t List_Has_Loop(const LinkedList_t* list)
{
    if (!list || list->count == 0) return 0;

    Node_t* slow = list->head;
    Node_t* fast = list->head;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) return 1;
    }

    return 0;
}

/*==================== Utilities ====================*/
uint32_t List_Count(const LinkedList_t* list)
{
    return list ? list->count : 0;
}

uint8_t List_Is_Empty(const LinkedList_t* list)
{
    return (!list || list->count == 0) ? 1 : 0;
}
