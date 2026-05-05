#include "App.h"

uint32_t CPU_CR;
uint32_t CPU_IPSR;
volatile uint8_t EXTI9_flag = 0;
void EXTI9PB9_Callbk(void)
{
    EXTI9_flag = 1;
    __asm(" nop \n \t nop \n \t nop");

    __asm("MRS  %[out1], IPSR"
    		:[out1]"=r"(CPU_IPSR));


    __asm(" nop \n \t nop \n \t nop");
}


uint8_t val1;
uint8_t val2;
uint8_t val3;

void APP_Init(void)
{
    __asm(" nop \n \t nop \n \t nop");

    __asm("MRS  %[out0] ,CONTROL"
    		:[out0]"=r"(CPU_CR));


    __asm("ADD  %[out0],%[in0],%[in1]"
        		:[out0]"=r"(val3)
				:[in0 ]"r" (val1)
				,[in1 ]"r" (val2)
    				);


    __asm(" nop \n \t nop \n \t nop");

    // EXTI Config
    EXTI_PinConfig_t EXTI_CFG;
    EXTI_CFG.EXTI_PIN = EXTI9PB9;
    EXTI_CFG.IRQ_EN = EXTI_IRQ_Enable;
    EXTI_CFG.Trigger_Case = EXTI_Trigger_Rising;
    EXTI_CFG.P_IRQ_CallBack = EXTI9PB9_Callbk;

    // Enable EXTI
    EXTI_GPIO_Init(&EXTI_CFG);

}

/* ---------- Main Loop / Password Mode ---------- */
void APP_Mode(void)
{

        if(EXTI9_flag)
        {
            EXTI9_flag = 0;  // reset flag
        }

}
