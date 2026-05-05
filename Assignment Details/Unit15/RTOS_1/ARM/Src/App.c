#include "App.h"

Task_Ref Task1 , Task2 , Task3;
/* ---------- Initialization ---------- */
void task1()
{
	while(1);
}
void task2(void)
{
	 while(1);
}
void task3(void)
{
	 while(1);
}

void APP_Init(void)
{

	/*HW_Init (initialize Clock Tree ,Reset Controller )*/
	HW_Init();
	if(MY_RTOS_Init() != NO_ERROR)
	{
		while(1);
	}

	Task1.Stack_Size=1024;
	Task1.P_Task_Entry=task1;
	Task1.priority=3;
	strcpy(Task1.Task_Name,"TASK1");

	Task2.Stack_Size=1024;
	Task2.P_Task_Entry=task2;
	Task2.priority=3;
	strcpy(Task2.Task_Name,"TASK2");

	Task3.Stack_Size=1024;
	Task3.P_Task_Entry=task3;
	Task3.priority=3;
	strcpy(Task3.Task_Name,"TASK3");

	MY_RTOS_Create_Task(&Task1);
	MY_RTOS_Create_Task(&Task2);
	MY_RTOS_Create_Task(&Task3);



}
/* ---------- Main Loop / Password Mode ---------- */
void APP_Mode(void)
{


}
