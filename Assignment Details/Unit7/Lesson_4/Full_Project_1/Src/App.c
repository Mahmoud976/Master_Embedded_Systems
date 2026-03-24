#include "App.h"

/* ---------- LCD Config (8-bit) ---------- */
Lcd_ConfigType Lcd1 =
{
    .Mode    = LCD_8BIT_MODE,
    .RS      = {PORTB, GPIO_PIN3},
    .EN      = {PORTB, GPIO_PIN4},
    .RW_Used = LCD_RW_NOT_USED,
    .DataPins = {
        {PORTA, GPIO_PIN11},  // D0
        {PORTA, GPIO_PIN10},  // D1
        {PORTA, GPIO_PIN9},   // D2
        {PORTA, GPIO_PIN8},   // D3
        {PORTB, GPIO_PIN15},  // D4
        {PORTB, GPIO_PIN14},  // D5
        {PORTB, GPIO_PIN13},  // D6
        {PORTB, GPIO_PIN12}   // D7
    }
};

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
    // LCD Init
    Lcd_Init(&Lcd1);
    Lcd_Clear(&Lcd1);

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
            Lcd_Clear(&Lcd1);
            Lcd_SendString(&Lcd1, "I love U");
        }
    }
}
