#include"Test_FIFO.h"

void Test_Queue(void)
{
    printf("===== Queue Test Started =====\n\n");

#define QUEUE_SIZE 5
    uint32_t buffer[QUEUE_SIZE];
    Queue_t queue;
    Queue_Status_t status;
    uint32_t val;

    /*================ Step 1: Initialize Queue ================*/
    printf("Step 1: Initialize Queue\n");
    status = Queue_Init(&queue, buffer, QUEUE_SIZE, sizeof(uint32_t));
    printf("Expected Status: QUEUE_OK, Actual: %d\n", status);
    printf("Expected Count: 0, Actual Count: %u\n", Queue_Count(&queue));
    printf("Expected Empty: 1, Actual Empty: %d\n\n", Queue_Is_Empty(&queue));

    /*================ Step 2: Enqueue Elements ================*/
    printf("Step 2: Enqueue Elements\n");
    for (uint32_t i = 1; i <= QUEUE_SIZE; i++)
    {
        status = Queue_Enqueue(&queue, &i);
        printf("Enqueue %u -> Status: %d\n", i, status);
        printf("Added element: %u\n", i);
        printf("Current Count: %u\n", Queue_Count(&queue));

        Queue_Peek_Front(&queue, &val);
        printf("Front Element: %u\n", val);

        Queue_Peek_Rear(&queue, &val);
        printf("Rear Element: %u\n\n", val);
    }

    /*================ Step 3: Enqueue into Full Queue ================*/
    printf("Step 3: Attempt Enqueue into Full Queue\n");
    uint32_t extra = 99;
    status = Queue_Enqueue(&queue, &extra);
    printf("Enqueue %u -> Expected: QUEUE_FULL, Actual Status: %d\n\n", extra, status);

    /*================ Step 4: Peek By Index ================*/
    printf("Step 4: Peek Elements By Index\n");
    for (uint32_t i = 0; i < Queue_Count(&queue); i++)
    {
        status = Queue_Peek_By_Index(&queue, i, &val);
        printf("Index %u -> Expected: %u, Actual: %u, Status: %d\n", i, i + 1, val, status);
    }
    printf("\n");

    /*================ Step 5: Dequeue Elements ================*/
    printf("Step 5: Dequeue All Elements\n");
    while (!Queue_Is_Empty(&queue))
    {
        status = Queue_Dequeue(&queue, &val);
        printf("Dequeued Element: %u, Status: %d\n", val, status);
        printf("Current Count: %u\n", Queue_Count(&queue));
        if (!Queue_Is_Empty(&queue))
        {
            Queue_Peek_Front(&queue, &val);
            printf("New Front: %u\n", val);
        }
        printf("\n");
    }

    /*================ Step 6: Enqueue for Reverse Test ================*/
    printf("Step 6: Enqueue Elements for Reverse Test\n");
    for (uint32_t i = 10; i < 10 + QUEUE_SIZE; i++)
    {
        status = Queue_Enqueue(&queue, &i);
        printf("Enqueue %u -> Status: %d\n", i, status);
        printf("Added element: %u\n", i);
    }

    /*================ Step 7: Peek Queue Before Reverse ================*/
    printf("\nStep 7: Queue Before Reverse\n");
    for (uint32_t i = 0; i < Queue_Count(&queue); i++)
    {
        Queue_Peek_By_Index(&queue, i, &val);
        printf("Index %u -> %u\n", i, val);
    }

    /*================ Step 8: Reverse Queue ================*/
    printf("\nStep 8: Reverse Queue\n");
    status = Queue_Reverse(&queue);
    printf("Reverse Status: %d\n", status);

    /*================ Step 9: Peek Queue After Reverse ================*/
    printf("\nStep 9: Queue After Reverse\n");
    for (uint32_t i = 0; i < Queue_Count(&queue); i++)
    {
        Queue_Peek_By_Index(&queue, i, &val);
        printf("Index %u -> %u\n", i, val);
    }
    printf("Expected order: Reversed\n\n");

    /*================ Step 10: Clear Queue ================*/
    printf("Step 10: Clear Queue\n");
    status = Queue_Clear(&queue);
    printf("Clear Status: %d\n", status);
    printf("Expected Empty: 1, Actual Empty: %d\n", Queue_Is_Empty(&queue));
    printf("Expected Count: 0, Actual Count: %u\n", Queue_Count(&queue));

    printf("\n===== Queue Test Finished =====\n");
}

