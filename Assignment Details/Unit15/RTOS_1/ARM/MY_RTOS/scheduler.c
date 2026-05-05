
#include "scheduler.h"

#include "My_RTOS_FIFO.h"




struct {
	Task_Ref * OS_Tasks[100];   //Sch. Table
	uint32_t  _S_MSP_Task;
	uint32_t  _E_MSP_Task;
	uint32_t  PSP_Task_Locator;
	uint32_t  NI_OF_Active_Tasks;
	Task_Ref * Current_Task;
	Task_Ref * Next_Task;
	enum{
		OS_Suspend,
		OS_Running
	}OS_Mode_ID;
}OS_Control;

///////////////////////////////////////////////////////////////////////////////////////////////
//                   Global Variable                                //
//////////////////////////////////////////////////////////////////////////////////////////////



Queue_t  Ready_Queue;

Task_Ref * Ready_Queue_FIFO[100];

Task_Ref My_RTOS_Idel_Task;

///////////////////////////////////////////////////////////////////////////////////////////////
//                   Global Variable                                //
//////////////////////////////////////////////////////////////////////////////////////////////

void OS_SVC(int * Stack_Frame)
{
	//r0 ,r1 ,r2,r3,r4,r12,lr,pc,xpsr
	unsigned char SVC_Number;
	SVC_Number =*((unsigned char *)(((unsigned char*)Stack_Frame[6])-2));

	switch(SVC_Number)
	{
	case 0 :

		break;
	case 1 :

		break;
	case 2 :

		break;
	case 3 :
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		break;

	}
}




void PendSV_Handler()
{


}




void OS_SVC_Set(int SVC_ID)
{
	switch(SVC_ID)
	{
	case 1:
		__asm("SVC #0x00");
		break;
	case 2 :
		__asm("SVC #0x01");
		break;

	case 3 :
		__asm("SVC #0x02");
		break;
	}

}





void MY_RTOS_Create_Main_Stack(void)
{
	OS_Control._S_MSP_Task = &_estack;
	OS_Control._E_MSP_Task = (OS_Control._S_MSP_Task - Main_Stack_Size);
	//Aligned 8 bytes Space Between Main Task And PSP Tasks
	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task - 8);

}

void My_RTOS_idel_Task()
{
	while(1)
	{
		__ASM("NOP");
	}
}


MY_RTOS_Error_ID MY_RTOS_Init()
{
	MY_RTOS_Error_ID error =NO_ERROR;
	//Update OS Mode -> Suspend
	OS_Control.OS_Mode_ID=OS_Suspend;
	//Specify the Main Stack For OS
	MY_RTOS_Create_Main_Stack();
	//Create OS Ready Queue
	if(Queue_Init(&Ready_Queue, Ready_Queue_FIFO, 100))
	{
		error=Ready_Queue_Init_Error;
	}

	//Configure Idle Task

	strcpy(My_RTOS_Idel_Task.Task_Name,"Idel_Task");
	My_RTOS_Idel_Task.priority=255;
	My_RTOS_Idel_Task.Stack_Size=300;
	My_RTOS_Idel_Task.P_Task_Entry=My_RTOS_idel_Task;

	error= MY_RTOS_Create_Task(&My_RTOS_Idel_Task);

	return error;
}

void MY_RTOS_Create_Task_Stack(Task_Ref* Tref)
{
	/*
	 * Task Frame
	 * XPSR
	 * PC
	 * LR
	 * R12
	 * R4
	 * R3
	 * R2
	 * R1
	 * R0
	 * ***********
	 * R5 , R6 , R7 , R8 , R9 , R10 , R11
	 * */
	*(Tref->Current_PSP)=Tref->_S_PSP_Task;
	Tref->Current_PSP--;
	*(Tref->Current_PSP)=0x01000000; // DUMMY XPSR Should T=1 To avoid bus fault
	Tref->Current_PSP--;
	*(Tref->Current_PSP)=(unsigned int)Tref->P_Task_Entry; //PC
	Tref->Current_PSP--;
	*(Tref->Current_PSP)=0xFFFFFFFD;

	for(int j=0;j<13;j++)
	{
		Tref->Current_PSP--;
		*(Tref->Current_PSP)=0;
	}
}
MY_RTOS_Error_ID MY_RTOS_Create_Task(Task_Ref * Tref)
{
	MY_RTOS_Error_ID error =NO_ERROR;
	//Create its OWN PSP Stack
	//Check task Stack Size Exceeded the PSP Stack
	Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator;
	Tref->_E_PSP_Task = (Tref->_S_PSP_Task - Tref->Stack_Size);
	//
	// _S_PSP_Task
	// _E_PSP_Task
	//
	//
	//  _eheap
	//
	//
	if(Tref->_E_PSP_Task < (unsigned int )(& _eheap))
	{
		return Task_Exceeded_Stack_Size;
	}
	//Aligned 8 bytes space between task PSP and Other
	OS_Control.PSP_Task_Locator=(OS_Control._E_MSP_Task - 8 );
	//Initialize PSP Task
	MY_RTOS_Create_Task_Stack(Tref);

	//Task State Update Suspend
	Tref->Task_State = OS_Suspend;



	return error;
}
