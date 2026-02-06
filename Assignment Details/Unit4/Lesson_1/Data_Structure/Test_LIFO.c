#include"Test_LIFO.h"

void Test_Stack(void)
{
    printf("========== LIFO STACK TEST START ==========\n\n");

#define STACK_SIZE 10
    int buffer[STACK_SIZE];

    LIFO_t myLifo;
    LIFO_Status_t status;

    /* ===================== INIT ===================== */
    printf("[INIT] Initializing LIFO stack...\n");
    status = LIFO_Init(&myLifo, buffer, STACK_SIZE, sizeof(int));
    if (status != LIFO_OK)
    {
        printf("[ERROR] LIFO_Init failed!\n");
        return;
    }

    printf("[OK] LIFO initialized | Capacity = %u\n\n",
        LIFO_Capacity(&myLifo));

    /* ===================== PUSH ===================== */
    printf("[PUSH] Pushing elements 0 -> 4\n");

    for (int i = 0; i < 5; i++)
    {
        printf("  -> Push %d ... ", i);
        status = LIFO_Push(&myLifo, &i);
        printf("%s | Count = %u\n",
            (status == LIFO_OK) ? "OK" : "FAIL",
            LIFO_Count(&myLifo));
    }
    printf("\n");

    /* ===================== PEEK ===================== */
    int value;

    printf("[PEEK TOP] Expected = 4\n");
    if (LIFO_Peek(&myLifo, &value) == LIFO_OK)
        printf("  -> Top = %d\n\n", value);

    printf("[PEEK FROM START] Index 0 | Expected = 0\n");
    if (LIFO_Peek_From_Start(&myLifo, 0, &value) == LIFO_OK)
        printf("  -> Value = %d\n\n", value);

    printf("[PEEK FROM END] Index 0 | Expected = 4\n");
    if (LIFO_Peek_From_End(&myLifo, 0, &value) == LIFO_OK)
        printf("  -> Value = %d\n\n", value);

    /* ===================== MIDDLE ===================== */
    printf("[MIDDLE] Expected = 2\n");
    if (LIFO_Get_Middle(&myLifo, &value) == LIFO_OK)
        printf("  -> Middle = %d\n\n", value);

    /* ===================== REVERSE ===================== */
    printf("[REVERSE] Reversing stack\n");

    printf("  -> Before: ");
    for (uint32_t i = 0; i < LIFO_Count(&myLifo); i++)
    {
        LIFO_Peek_From_Start(&myLifo, i, &value);
        printf("%d ", value);
    }
    printf("\n");

    LIFO_Reverse(&myLifo);

    printf("  -> After:  ");
    for (uint32_t i = 0; i < LIFO_Count(&myLifo); i++)
    {
        LIFO_Peek_From_Start(&myLifo, i, &value);
        printf("%d ", value);
    }
    printf("\n\n");

    /* ===================== POP ===================== */
    printf("[POP] Popping all elements (LIFO expected)\n");

    while (LIFO_Count(&myLifo) > 0)
    {
        LIFO_Pop(&myLifo, &value);
        printf("  -> Popped %d | New Count = %u\n",value, LIFO_Count(&myLifo));
    }
    printf("\n");

    /* ===================== CLEAR ===================== */
    printf("[CLEAR] Clearing stack\n");

    int x = 123;
    LIFO_Push(&myLifo, &x);
    printf("  -> Before clear: Count = %u\n", LIFO_Count(&myLifo));

    LIFO_Clear(&myLifo);
    printf("  -> After clear:  Count = %u (Expected = 0)\n\n",
        LIFO_Count(&myLifo));

    printf("========== LIFO STACK TEST END ==========\n");
}
