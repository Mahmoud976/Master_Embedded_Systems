/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Saleh
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include"APP.h"
/* ================== Main Function ================== */

Task_ref Task1 , Task2 , Task3 ,Task4;

Mutex_ref MUTEX1;
unsigned char Payload [3]={1,2,3};

/* ---------- Initialization ---------- */
GPIO_Config_Pin_t t1,t2, t3,t4 ;


/**
 * @brief Task 1 Implementation (Lowest Priority).
 * This task demonstrates how a low-priority task can hold a resource (Mutex)
 * and trigger other tasks while still maintaining ownership.
 */
void task1() {
    while(1) {
        // 1. Attempt to acquire the shared Mutex
        MY_RTOS_Acquire_Mutex(&MUTEX1, &Task1);

        // 2. Set PB14 HIGH to indicate Task 1 has successfully started and owns the Mutex
        GPIO_WritePin(PORTB, GPIO_PIN14, 1);

        // 3. Busy-wait loop (Delay) to simulate work while holding the Mutex
        for(volatile int i = 0; i < 1000000; i++);

        // 4. Manually transition Task 2 to the 'ready' state.
        // If Task 2 has a higher priority, the Scheduler will preempt Task 1 immediately.
        MY_RTOS_Activate_Task(&Task2);

        // 5. Another Busy-wait loop to observe Priority Inversion effects before releasing the Mutex
        for(volatile int i = 0; i < 500000; i++);

        // 6. Release the Mutex to allow waiting tasks (like Task 4) to proceed
        MY_RTOS_Release_Mutex(&MUTEX1);

        // 7. Set PB14 LOW to indicate task completion
        GPIO_WritePin(PORTB, GPIO_PIN14, 0);

        // 8. Terminate the current task to yield CPU time back to the OS Scheduler
        MY_RTOS_Terminate_Task(&Task1);
    }
}


void task2(void)
{
	while(1)
	{

		GPIO_WritePin(PORTB, GPIO_PIN15,1);
		for(volatile int i =0 ;i<50000;i++);
		MY_RTOS_Activate_Task(&Task3);
		for(volatile int i =0 ;i<5000;i++);
		GPIO_WritePin(PORTB, GPIO_PIN15,0);
		MY_RTOS_Terminate_Task(&Task2);

	}
}
void task3(void)
{

	 while(1)
	 {
			GPIO_WritePin(PORTB, GPIO_PIN13,1);
			for(volatile int i =0 ;i<50000;i++);
			MY_RTOS_Activate_Task(&Task4);
			for(volatile int i =0 ;i<5000;i++);
			GPIO_WritePin(PORTB, GPIO_PIN13,0);
			MY_RTOS_Terminate_Task(&Task3);
	}
}
void task4(void)
{

	 while(1)
	 {
		 volatile int i=0;
		 GPIO_WritePin(PORTB, GPIO_PIN12,1);
		MY_RTOS_Acquire_Mutex(&MUTEX1,&Task4);
		for(i  ;i<5000;i++);

		MY_RTOS_Release_Mutex(&MUTEX1);
		i=0;
		for( i ;i<5000;i++);
		i=0;
		while(i){i++;GPIO_TogglePin(PORTB, GPIO_PIN12);}
		 GPIO_WritePin(PORTB, GPIO_PIN12,0);
		MY_RTOS_Terminate_Task(&Task4);


	}
}

int main(void)
{

	t1.PORTx=PORTB;
	t1.Pin_Number=GPIO_PIN14;
	t1.mode=GPIO_MODE_Output_PP;
	t1.Speed=GPIO_SPEED_10M;
	GPIO_InitPin(&t1);
	t2.PORTx=PORTB;
	t2.Pin_Number=GPIO_PIN15;
	t2.Speed=GPIO_SPEED_10M;
	t2.mode=GPIO_MODE_Output_PP;
	GPIO_InitPin(&t2);

	t3.PORTx=PORTB;
	t3.Pin_Number=GPIO_PIN13;
	t3.Speed=GPIO_SPEED_10M;
	t3.mode=GPIO_MODE_Output_PP;
	GPIO_InitPin(&t3);

	t4.PORTx=PORTB;
	t4.Pin_Number=GPIO_PIN12;
	t4.Speed=GPIO_SPEED_10M;
	t4.mode=GPIO_MODE_Output_PP;
	GPIO_InitPin(&t4);

/*** HW_Init (initialize Clock Tree ,Reset Controller ) ***/
	HW_Init();
	if(MY_RTOS_Init() != NO_ERROR)
	{
		while(1);
	}

	MUTEX1.P_payload=Payload;
	MUTEX1.Payload_Size=3;
	strcpy(MUTEX1.Mutex_Name,"mutex1 shared T1 T4");

	Task1.Stack_Size=1024;
	Task1.P_Task_Entry=task1;
	Task1.priority=5;
	strcpy(Task1.Task_Name,"TASK1");

	Task2.Stack_Size=1024;
	Task2.P_Task_Entry=task2;
	Task2.priority=4;
	strcpy(Task2.Task_Name,"TASK2");

	Task3.Stack_Size=1024;
	Task3.P_Task_Entry=task3;
	Task3.priority=3;
	strcpy(Task3.Task_Name,"TASK3");

	Task4.Stack_Size=1024;
	Task4.P_Task_Entry=task4;
	Task4.priority=4;
	strcpy(Task4.Task_Name,"TASK4");



	MY_RTOS_Create_Task(&Task1);
	MY_RTOS_Create_Task(&Task2);
	MY_RTOS_Create_Task(&Task3);
	MY_RTOS_Create_Task(&Task4);

	MY_RTOS_Activate_Task(&Task1);

	MY_RTOS_START_OS();


    while(1)
    {
    	__asm("NOP");
    }
}
