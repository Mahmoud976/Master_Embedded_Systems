/*
 * scheduler.h
 *
 *  Created on: May 5, 2026
 *      Author: mahmo
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMx_OS_Porting.h"
#include <string.h>
typedef enum
{
	NO_ERROR,
	Ready_Queue_Init_Error,
	Task_Exceeded_Stack_Size,

}MY_RTOS_Error_ID;


typedef struct {
	uint32_t Stack_Size;
	uint8_t  priority;
	void (*P_Task_Entry)(void);  // pointer to task C function
	uint8_t  AutoStart;
	uint32_t _S_PSP_Task;        // not entered by the user
	uint32_t _E_PSP_Task;		 // not entered by the user
	uint32_t * Current_PSP;
	char  Task_Name[30];
	enum{
		Suspend,
		Running,
		Waiting,
		Ready,
	}Task_State;         // Not Entered by the user
	struct{
		enum{
			enable,
			disable,
		}Blocking;
		uint32_t Ticks_Count;
	}Timing_Waiting;

}Task_Ref;

MY_RTOS_Error_ID MY_RTOS_Init();
MY_RTOS_Error_ID MY_RTOS_Create_Task(Task_Ref * Tref);

#endif /* INC_SCHEDULER_H_ */
