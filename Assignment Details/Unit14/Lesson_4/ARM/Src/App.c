#include "App.h"



/* ---------- Flag for ISR ---------- */
volatile uint8_t EXTI9_flag = 0;
enum CPU_AccesseLevel
{
	priviledge,
	unpriviledge
};


/************************************************/

void Switch_CPU_AccesseLevel(enum CPU_AccesseLevel level)
{
	switch(level)
	{
	case priviledge:
		__asm("MRS r3,CONTROL");
		__asm("LSR r3,r3,#0x1");
		__asm("LSL r3,r3,#0x1");
		__asm("MSR CONTROL,r3");
		break;
	case unpriviledge:
		//set bit 0 in CONTROL Register
		__asm("MRS r0,CONTROL");
		__asm("ORR r0,r0,#0x1");
		__asm("MSR CONTROL,r0");

		break;
	}
}

/* ---------- EXTI9 Callback ---------- */
void EXTI9PB9_Callbk(void)
{
    EXTI9_flag = 1;
    Switch_CPU_AccesseLevel(priviledge);

}
/* ---------- Initialization ---------- */
void APP_Init(void)
{

    // EXTI Config
    EXTI_PinConfig_t EXTI_CFG;
    EXTI_CFG.EXTI_PIN = EXTI9PB9;
    EXTI_CFG.IRQ_EN = EXTI_IRQ_Enable;
    EXTI_CFG.Trigger_Case = EXTI_Trigger_Rising;
    EXTI_CFG.P_IRQ_CallBack = EXTI9PB9_Callbk;

    // Enable EXTI
    EXTI_GPIO_Init(&EXTI_CFG);

    Switch_CPU_AccesseLevel(unpriviledge);


}

/* ---------- Main Loop / Password Mode ---------- */
void APP_Mode(void)
{

        if(EXTI9_flag)
        {
            EXTI9_flag = 0;  // reset flag
        }

}
