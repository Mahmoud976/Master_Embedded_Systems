/*
 * scheduler.h
 *
 *  Created on: May 5, 2026
 *      Author: mahmo
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMx_OS_Porting.h"

typedef enum
{
	NO_ERROR,
	Ready_Queue_Init_Error,
	Task_Exceeded_Stack_Size,
	Mutex_is_Reaced_To_Max_Number_Of_Users

}MY_RTOS_Error_ID;


typedef struct{
	unsigned int* Current_PSP ;//Not Entered by the user
	unsigned int Stack_Size;
	unsigned char priority;
	void (*P_Task_Entry)(void); //pointer to Tack C Function
	unsigned char AutoStart ;
	unsigned int _S_PSP_Task ;//Not Entered by the user
	unsigned int _E_PSP_Task ;//Not Entered by the user
	char Task_Name[30] ;
	enum{
		Suspend,
		Running,
		Waiting,
		ready
	}Task_State	;//Not Entered by the user
struct{
		enum{
			Enable,
			Disable
		}Blocking;
		 int Ticks_Count ;
	}Timing_Waiting;
}Task_ref;


typedef struct {
	unsigned char* P_payload;
	unsigned int   Payload_Size ;
	Task_ref* 	   Current_TUser ;
	Task_ref* 	   Next_TUser ;
	char 		   Mutex_Name[30]  ;
} Mutex_ref;

#define element_type Task_ref*


MY_RTOS_Error_ID MY_RTOS_Init();
MY_RTOS_Error_ID MY_RTOS_Create_Task(Task_ref* Tref);
void MY_RTOS_Activate_Task (Task_ref* Tref);
void MY_RTOS_Terminate_Task (Task_ref* Tref);
void MY_RTOS_START_OS() ;
void MY_RTOS_Task_Wait(unsigned int NoTICKS,Task_ref* SelfTref);

MY_RTOS_Error_ID MY_RTOS_Acquire_Mutex(Mutex_ref* Mref , Task_ref* Tref);
void MY_RTOS_Release_Mutex(Mutex_ref* Mref);

#endif /* INC_SCHEDULER_H_ */
