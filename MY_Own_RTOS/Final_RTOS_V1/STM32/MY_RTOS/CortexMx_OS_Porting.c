
#include "CortexMx_OS_Porting.h"

unsigned char SysTick_LED ;

void HardFault_Handler (void)
{
	while(1) ;
}
void MemManage_Handler (void)
{
	while(1) ;
}
void BusFault_Handler(void)
{
	while(1) ;
}
void UsageFault_Handler(void)
{
	while(1) ;
}


__attribute ((naked)) void SVC_Handler ()
{
	//	SWITCH_CPU_AccessLevel (privileged);
	__asm ("tst lr, #4 \n\t"
			"ITE EQ \n\t" //To execute Thumb instructions conditionally, you can either use an IT instruction, or a conditional branch instruction.
			"mrseq r0,MSP \n\t "
			"mrsne r0,PSP \n\t"
			"B OS_SVC");
}



void HW_Init()
{
	//Initialize Clock Tree (RCC -> SysTick Timer & CPU) 8MHZ
	//init HW
	//Clock tree
	//RCC Default Values makes CPU Clock & SySTick Timer clock = 8 M HZ

	//	8 MHZ
	//	1 count -> 0.125 us
	//	X count -> 1 ms
	//	X = 8000 Count



	//	decrease PenSV  interrupt priority to be  smaller than or equal  SySTICK Timer
	//SysTICK have a priority 14
	__NVIC_SetPriority(PendSV_IRQn, 15) ;

}



void Trigger_OS_PendSV()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;

}

void Start_Ticker()
{
	//	This clock tree should be defined in HW_init()
	//	8 MHZ
	//	1 count -> 0.125 us
	//	X count -> 1 s
	//	X = 8000 Count

	 SysTick_Config(24000);


}


void SysTick_Handler(void)
{
	SysTick_LED ^= 1 ;
	MY_RTOS_Update_Tasks_Waiting_Time();
	//Determine Pcurrent & Pnext
	Decide_What_Next();
	//Switch Context & restore
	Trigger_OS_PendSV();

}

