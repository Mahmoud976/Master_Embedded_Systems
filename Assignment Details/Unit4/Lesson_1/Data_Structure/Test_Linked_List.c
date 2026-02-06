
#include"Test_Linked_List.h"


void Test_Linked_List(void)
{
    printf("===== Linked List Test Started =====\n\n");

    LinkedList_t list;
    List_Status_t status;
    uint32_t val;
    uint32_t index;

    /*================ Step 1: Initialize =================*/
    printf("Step 1: Initialize List\n");
    status = List_Init(&list, sizeof(uint32_t));
    printf("Expected Status: LIST_OK, Actual: %d\n", status);
    printf("Expected Count: 0, Actual Count: %u\n", List_Count(&list));
    printf("Expected Is Empty: 1, Actual: %d\n\n", List_Is_Empty(&list));

    /*================ Step 2: Insert From Head =================*/
    printf("Step 2: Insert 1,2 from Head\n");
    for (uint32_t i = 1; i <= 2; i++)
    {
        uint32_t value = i; //A separate variable for each insertion
        status = List_Insert_From_Head(&list, &value);
        printf("Inserted %u from head, Status: %d\n", value, status);
        printf("Count: %u, Is Empty: %d\n", List_Count(&list), List_Is_Empty(&list));

        List_Get_From_Head(&list, &val);
        printf("Head Element Expected: %u, Actual: %u\n", value, val);

        List_Get_From_Tail(&list, &val);
        printf("Tail Element Expected: %d , Actual: %u\n\n", (value == 1 ? 1 : 1), val);
    }

    /*================ Step 3: Insert From Tail =================*/
    printf("Step 3: Insert 3,4 from Tail\n");
    for (uint32_t i = 3; i <= 4; i++)
    {
        uint32_t value = i; // A separate variable for each insertion
        status = List_Insert_From_Tail(&list, &value);
        printf("Inserted %u from tail, Status: %d\n", value, status);
        printf("Count: %u\n", List_Count(&list));

        List_Get_From_Tail(&list, &val);
        printf("Tail Element Expected: %u, Actual: %u\n\n", value, val);
    }

    /*================ Step 4: Insert At Index =================*/
    printf("Step 4: Insert 99 at index 2\n");
    val = 99;
    status = List_Insert_At_Index(&list, 2, &val);
    printf("Inserted %u at index 2, Status: %d\n", val, status);
    printf("Count: %u\n", List_Count(&list));

    List_Get_At_Index(&list, 2, &val);
    printf("Element at index 2 Expected: 99, Actual: %u\n\n", val);

    /*================ Step 5: Get From Middle =================*/
    printf("Step 5: Get From Middle\n");
    status = List_Get_From_Middle(&list, &val);
    printf("Middle element Expected index %u, Actual: %u, Status: %d\n\n", list.count / 2, val, status);

    /*================ Step 6: Find =================*/
    printf("Step 6: Find element 3\n");
    val = 3;
    status = List_Find(&list, &val, &index);
    printf("Expected Index: 3, Actual Index: %u, Status: %d\n\n", index, status);

    /*================ Step 7: Reverse =================*/
    printf("Step 7: Reverse List\n");
    printf("List before reverse (from head to tail):\n");
    for (uint32_t i = 0; i < List_Count(&list); i++)
    {
        List_Get_At_Index(&list, i, &val);
        printf("Index %u -> %u\n", i, val);
    }
    printf("\n");

    status = List_Reverse(&list);
    printf("Reverse Status: %d\n", status);

    printf("List after reverse (from head to tail):\n");
    for (uint32_t i = 0; i < List_Count(&list); i++)
    {
        List_Get_At_Index(&list, i, &val);
        printf("Index %u -> %u\n", i, val);
    }
    printf("\n");

    /*================ Step 8: Remove From Head =================*/
    printf("Step 8: Remove From Head\n");
    status = List_Remove_From_Head(&list, &val);
    printf("Removed element: %u, Status: %d\n", val, status);
    printf("Count: %u\n\n", List_Count(&list));

    /*================ Step 9: Remove From Tail =================*/
    printf("Step 9: Remove From Tail\n");
    status = List_Remove_From_Tail(&list, &val);
    printf("Removed element: %u, Status: %d\n", val, status);
    printf("Count: %u\n\n", List_Count(&list));

    /*================ Step 10: Remove At Index =================*/
    printf("Step 10: Remove element at index 1\n");
    status = List_Remove_At_Index(&list, 1, &val);
    printf("Removed element: %u, Status: %d\n", val, status);
    printf("Count: %u\n\n", List_Count(&list));

    /*================ Step 11: Loop Detection =================*/
    printf("Step 11: Check Loop Detection (should be 0)\n");
    uint8_t loop = List_Has_Loop(&list);
    printf("Expected: 0, Actual: %d\n\n", loop);

    /*================ Step 12: Clear List =================*/
    printf("Step 12: Clear List\n");
    status = List_Clear(&list);
    printf("Clear Status: %d\n", status);
    printf("Expected Count: 0, Actual Count: %u\n", List_Count(&list));
    printf("Expected Is Empty: 1, Actual: %d\n", List_Is_Empty(&list));

    printf("\n===== Linked List Test Finished =====\n");
}
