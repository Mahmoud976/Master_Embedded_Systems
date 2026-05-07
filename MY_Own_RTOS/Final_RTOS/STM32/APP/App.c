#include "App.h"



/* ---------- Flag for ISR ---------- */
volatile uint8_t EXTI9_flag = 0;

/* ---------- EXTI9 Callback ---------- */
void EXTI9PB9_Callback(void)
{
    EXTI9_flag = 1;
}

/* ---------- Initialization ---------- */
void APP_Init(void)
{


    // EXTI Config
    EXTI_PinConfig_t EXTI_CFG;
    EXTI_CFG.EXTI_PIN = EXTI9PB9;
    EXTI_CFG.IRQ_EN = EXTI_IRQ_Enable;
    EXTI_CFG.Trigger_Case = EXTI_Trigger_Rising;
    EXTI_CFG.P_IRQ_CallBack = EXTI9PB9_Callback;

    // Enable EXTI
    EXTI_GPIO_Init(&EXTI_CFG);
}

/* ---------- Main Loop / Password Mode ---------- */
void APP_Mode(void)
{
    while(1)
    {
        if(EXTI9_flag)
        {
            EXTI9_flag = 0;  // reset flag
        }
    }
}
