
#include "CortexMx_OS_Porting.h"

void NMI_Handler(void)
{
	while(1);
}
void HardFault_Handler(void)
{
	while(1);
}
void MemManage_Handler(void)
{
	while(1);
}
void BusFault_Handler(void)
{
	while(1);
}
void UsageFault_Handler(void)
{
	while(1);
}

__attribute ((naked)) void SVC_Handler()
{
	//SWITCH_CPU_ACCESS_LEVEL(privilege);
	__asm("TST LR ,#4 \n\t ITE EQ \n\t  MRSEQ  r0,MSP \n\t MRSNE r0,PSP \n\t  B OS_SVC");
}



void HW_Init(void)
{
	//Initialize Clock Tree (RCC -> SysTick Timer & CPU ) 8MHZ
	// 8 MHZ
	// 1 count -> 0.125 us
	// x count -> 1 ms
	// x = 8000 count

}
