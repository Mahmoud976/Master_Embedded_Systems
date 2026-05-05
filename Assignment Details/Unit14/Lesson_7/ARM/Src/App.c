#include "App.h"

/* ---------- Flag for ISR ---------- */

volatile uint8_t taskA_flag , taskB_flag, EXTI9_flag = 0;


#define TaskA_Stack_Size  100
#define TaskB_Stack_Size  100

extern int _estack;
//Main Stack
unsigned int _S_MSP = &_estack;
unsigned int _E_MSP;

//process stack Task A
unsigned int _S_PSP_TA ;
unsigned int _E_PSP_TA ;


//process stack Task B
unsigned int _S_PSP_TB ;
unsigned int _E_PSP_TB ;


enum CPU_AccesseLevel
{
	privilege,
	unprivilege,
};

/************************************************/
#define SWITCH_CPU_ACCESS_LEVEL(level)      \
    if ((level) == privilege)              \
    {                                       \
        __asm volatile (                   \
            "MRS r3, CONTROL \n\t"         \
            "BIC r3, r3, #1  \n\t"         \
            "MSR CONTROL, r3 \n\t"         \
            "ISB             \n\t"         \
        );                                  \
    }                                       \
    else                                    \
    {                                       \
        __asm volatile (                   \
            "MRS r0, CONTROL \n\t"         \
            "ORR r0, r0, #1  \n\t"         \
            "MSR CONTROL, r0 \n\t"         \
            "ISB             \n\t"         \
        );                                  \
    }


#define OS_Set_PSP(add)   __asm volatile ("mov r0 ,%0  \n\t  msr PSP ,r0" ::"r"(add));

#define OS_Switch_SP_to_PSP   __asm volatile ("mrs r0 ,CONTROL  \n\t  mov r1,#0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL ,r0");
#define OS_Switch_SP_to_MSP   __asm volatile ("mrs r0 ,CONTROL  \n\t  mov r1,#0x05 \n\t orr r0,r0,r1 \n\t msr CONTROL ,r0");


#define OS_Generate_Exception __asm volatile ("SVC #0X3");


void taskA()
{
	GPIO_WritePin(PORTB,GPIO_PIN14,1);
	GPIO_WritePin(PORTB,GPIO_PIN15,0);

}

void taskB()
{
	GPIO_WritePin(PORTB,GPIO_PIN14,0);
	GPIO_WritePin(PORTB,GPIO_PIN15,1);

}


void EXTI9PB9_Callbk(void)
{
	if(EXTI9_flag==0)
	{
		taskA_flag=1;
		taskB_flag=0;
		EXTI9_flag=1;
	}
	else if (EXTI9_flag==1)
	{
		taskB_flag =1;
		taskA_flag=0;
		EXTI9_flag=0;
	}

}

void mainOs()
{
	_E_MSP=(_S_MSP -512);

	_S_PSP_TA = (_E_MSP-16);
	_E_PSP_TA = (_S_PSP_TA - TaskA_Stack_Size);

	_S_PSP_TB=(_E_PSP_TA -16);
	_E_PSP_TB=(_S_PSP_TB -TaskB_Stack_Size);

	while(1)
	{
		__asm("NOP");
		if(taskA_flag==1)
		{

			//Set PSP Register = _S_PSP
			OS_Set_PSP(_S_PSP_TA);
			//SP >> PSP
			OS_Switch_SP_to_PSP;
			// switch from privilege to un-privilege
			SWITCH_CPU_ACCESS_LEVEL(unprivilege);
			taskA();
			// switch from un-privilege to privilege
			OS_Generate_Exception;
			//SP -> MSP
			OS_Switch_SP_to_MSP;




		}
		else if(taskB_flag==1)
		{

			//Set PSP Register = _S_PSP
			OS_Set_PSP(_S_PSP_TB);
			//SP >> PSP
			OS_Switch_SP_to_PSP;
			// switch from privilege to un-privilege
			SWITCH_CPU_ACCESS_LEVEL(unprivilege);

			 taskB();
			// switch from un-privilege to privilege
			OS_Generate_Exception;
			//SP -> MSP
			OS_Switch_SP_to_MSP;

		}
	}

}


void PendSV_Handler()
{


}
void OS_SVC(int * Stack_Frame)
{
	//r0 ,r1 ,r2,r3,r12,lr,pc,xpsr
	unsigned char SVC_Number;
	unsigned int val1 ,val2;
	val1=Stack_Frame[0];
	val2=Stack_Frame[1];
	SVC_Number =*((unsigned char *)(((unsigned char*)Stack_Frame[6])-2));

	switch(SVC_Number)
	{
	case 0 :
		Stack_Frame[0]=val1+val2;
		break;

	case 1 :
		Stack_Frame[0]=val1-val2;
		break;

	case 2 :
		Stack_Frame[0]=val1*val2;
		break;
	case 3 :
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		break;

	}


}
__attribute ((naked)) void SVC_Handler()
{
	//SWITCH_CPU_ACCESS_LEVEL(privilege);
	__asm("tst lr ,#4 \n\t ITE EQ \n\t  mrseq  r0,msp \n\t mrsne r0,psp \n\t B OS_SVC");
}
int OS_SVC_Set(int a, int b,int SVC_ID)
{
	int result;
	switch(SVC_ID)
	{
	case 1:
		__asm("svc #0x00");
		break;
	case 2 :
		__asm("svc #0x01");
		break;

	case 3 :
		__asm("svc #0x02");
		break;
	}

	__asm("mov %0 , r0":"=r"(result));
	return result;
}

/* ---------- Initialization ---------- */
void APP_Init(void)
{
  /*  // EXTI Config
    EXTI_PinConfig_t EXTI_CFG;
    EXTI_CFG.EXTI_PIN = EXTI9PB9;
    EXTI_CFG.IRQ_EN = EXTI_IRQ_Enable;
    EXTI_CFG.Trigger_Case = EXTI_Trigger_Falling;
    EXTI_CFG.P_IRQ_CallBack = EXTI9PB9_Callbk;
    // Enable EXTI
    EXTI_GPIO_Init(&EXTI_CFG);
    //enable taskB led
    GPIO_Config_Pin_t TASKB;
	TASKB.PORTx=PORTB;
    TASKB.Pin_Number=GPIO_PIN14;
    TASKB.mode=GPIO_MODE_Output_PP;
    TASKB.Speed=GPIO_SPEED_10M;
    GPIO_InitPin(&TASKB);
    //enable task A led
    GPIO_Config_Pin_t TASKA;
	TASKA.PORTx=PORTB;
	TASKA.Pin_Number=GPIO_PIN15;
	TASKA.mode=GPIO_MODE_Output_PP;
	TASKA.Speed=GPIO_SPEED_10M;
    GPIO_InitPin(&TASKA);
    mainOs();*/

	int result;
	result = OS_SVC_Set(3, 3,0);
	result = OS_SVC_Set(3, 3,1);
	result = OS_SVC_Set(3, 3,2);

}
/* ---------- Main Loop / Password Mode ---------- */
void APP_Mode(void)
{
        if(EXTI9_flag)
        {
            EXTI9_flag = 0;  // reset flag
        }
        else{/*Misra*/}

}
