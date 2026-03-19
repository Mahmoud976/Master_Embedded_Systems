#include "App.h"

/* ---------- LED Config ---------- */
Led_Config_t GreenLed = {PORTB, GPIO_PIN0,LED_ACTIVE_HIGH};
Led_Config_t RedLed   = {PORTB, GPIO_PIN1,LED_ACTIVE_HIGH};

/* ---------- Button Config ---------- */
Button_Config_t Button1 = {PORTA, GPIO_PIN0};

/* ---------- Keypad Config ---------- */
static const uint8_t KeyMap[4][4] =
{
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'C','0','=','+'}
};

KeyPad_ConfigType KeyPad1 =
{
    .Rows = 4,
    .Cols = 4,
    .RowPins = {{PORTA, GPIO_PIN0},{PORTA, GPIO_PIN1},{PORTA, GPIO_PIN2},{PORTA, GPIO_PIN3}},
    .ColPins = {{PORTA, GPIO_PIN4},{PORTA, GPIO_PIN5},{PORTA, GPIO_PIN6},{PORTA, GPIO_PIN7}},
    .KeyMap = KeyMap
};

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

/* ---------- Password ---------- */
static const uint8_t StoredPassword[PASSWORD_LENGTH + 1] = "1234";
static uint8_t InputBuffer[PASSWORD_LENGTH + 1];
static uint8_t Index = 0;
static PassState_t PassState = PASS_IDLE;

/* ---------- Initialization ---------- */
void APP_Password_Init(void)
{
    Lcd_Init(&Lcd1);
    KeyPad_Init(&KeyPad1);
    Led_Init(&GreenLed);
    Led_Init(&RedLed);

    Led_OFF(&GreenLed);
    Led_OFF(&RedLed);
}

/* ---------- Password Mode ---------- */
void APP_PasswordMode(void)
{
    uint8_t key;

    switch(PassState)
    {
        case PASS_IDLE:
            Lcd_Clear(&Lcd1);
            Lcd_SendString(&Lcd1, "Enter Pass:");
            Lcd_SetCursor(&Lcd1, 1, 0);
            Index = 0;
            PassState = PASS_ENTER;
            break;

        case PASS_ENTER:
            if(KeyPad_GetKey(&KeyPad1, &key) == E_OK)
            {
                if((key >= '0') && (key <= '9') && (Index < PASSWORD_LENGTH))
                {
                    InputBuffer[Index++] = key;
                    Lcd_SendChar(&Lcd1, '*');
                }
                else if(key == '=') // Enter key
                {
                    InputBuffer[Index] = '\0';
                    PassState = PASS_CHECK;
                }
                else if(key == 'C') // Clear key
                {
                    Index = 0;
                    Lcd_Clear(&Lcd1);
                    Lcd_SendString(&Lcd1, "Enter Pass:");
                    Lcd_SetCursor(&Lcd1, 1, 0);
                }
            }
            break;

        case PASS_CHECK:
            if(strcmp((char*)InputBuffer, (char*)StoredPassword) == 0)
            {
                Lcd_Clear(&Lcd1);
                Lcd_SendString(&Lcd1, "Correct");
                Led_ON(&GreenLed);
                Led_OFF(&RedLed);
            }
            else
            {
                Lcd_Clear(&Lcd1);
                Lcd_SendString(&Lcd1, "Wrong");
                Led_ON(&RedLed);
                Led_OFF(&GreenLed);
            }
            PassState = PASS_RESULT;
            break;

        case PASS_RESULT:
            for(volatile uint32_t i = 0; i < 800000; i++); // simple delay
            Led_OFF(&GreenLed);
            Led_OFF(&RedLed);
            PassState = PASS_IDLE;
            break;
    }
}
