/*
 * CortexMx_OS_Porting.h
 *
 *  Created on: May 5, 2026
 *      Author: Mahmoud Saleh
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

#include "core_cm3.h"


extern int _estack;
extern int _eheap;
#define Main_Stack_Size   3072

/*****************************************************************************************************************************/
/*                                          FUNCTIONS Like Macros                                                            */
/*****************************************************************************************************************************/
#define SWITCH_CPU_ACCESS_LEVEL_privileged          __asm volatile (               \
													"MRS r3, CONTROL \n\t"         \
													"BIC r3, r3, #1  \n\t"         \
													"MSR CONTROL, r3 \n\t"         \
													"ISB             \n\t");


#define SWITCH_CPU_ACCESS_LEVEL_Unprivileged           __asm volatile (              \
													"MRS r0, CONTROL \n\t"         \
													"ORR r0, r0, #1  \n\t"         \
													"MSR CONTROL, r0 \n\t"         \
													"ISB             \n\t");


#define OS_Set_PSP(add)   __asm volatile ("MOV r0 ,%0  \n\t  MSR PSP ,r0" ::"r" (add) ) ;
#define OS_Get_PSP(add)   __asm volatile ("MRS r0 ,PSP  \n\t  MOV %0,r0 " :"=r" (add) ) ;


#define OS_Switch_SP_to_PSP   __asm volatile ("MRS r0 ,CONTROL  \n\t  MOV r1,#0x02 \n\t ORR r0,r0,r1 \n\t MSR CONTROL ,r0");
#define OS_Switch_SP_to_MSP   __asm volatile ("MRS r0 ,CONTROL  \n\t  MOV r1,#0x05 \n\t ORR r0,r0,r1 \n\t MSR CONTROL ,r0");





/*****************************************************************************************************************************/
/*                                          FUNCTIONS Like Macros                                                            */
/*****************************************************************************************************************************/




/*****************************************************************************************************************************/
/*                                          FUNCTIONS Like Macros                                                            */
/*****************************************************************************************************************************/




void HW_Init(void);

#endif /* INC_CORTEXMX_OS_PORTING_H_ */
