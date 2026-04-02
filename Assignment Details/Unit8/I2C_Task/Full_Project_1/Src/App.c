#include "App.h"

#define master
#ifdef  master

#include "App.h"

#define SLAVE_ADDR   0x68
#define BUFFER_SIZE  8

I2C_Handle_t i2c1;

/* Data to send to slave */
uint8_t MasterTxBuffer[BUFFER_SIZE] = {'H','e','l','l','o','!','\n','\0'};

void APP_Init(void)
{
    /* Configure I2C as Master */
    i2c1.Instance = I2C1;

    i2c1.Config.ClockSpeed     = I2C_SM_100K;
    i2c1.Config.OwnAddress     = I2C_OWN_ADDRESS_7BIT(0x50); // Master address
    i2c1.Config.ACKControl     = I2C_ACK_ENABLE;
    i2c1.Config.AddressingMode = I2C_ADDRESS_7BIT_MODE;
    i2c1.Config.DualAddress    = I2C_DUAL_DISABLE;
    i2c1.Config.SecondAddress  = I2C_SECOND_ADDRESS_DISABLE;
    i2c1.Config.IT_Config      = 0;
    i2c1.Config.Callback       = I2C_CALLBACK_NULL;
    i2c1.Config.ErrorCallback  = I2C_CALLBACK_NULL;

    i2c1.State = I2C_STATE_READY;
    i2c1.Lock  = I2C_UNLOCKED;

    /* Enable I2C clock */
    I2C_PeriClockControl(I2C1, ENABLE);

    /* Initialize I2C */
    I2C_Init(&i2c1);

    /* Enable I2C peripheral */
    I2C_Enable(i2c1.Instance);
}

void APP_Mode(void)
{
    /* Send data to slave */
    I2C_Master_Transmit(&i2c1, SLAVE_ADDR, MasterTxBuffer, BUFFER_SIZE, I2C_STOP, 1000);

    /* Small delay to avoid continuous flooding */
    for(volatile int i = 0; i < 10000; i++);
}
#endif

#ifndef master

#include "App.h"

#define SLAVE_ADDR   0x68
#define BUFFER_SIZE  8

I2C_Handle_t i2c1;
UART_ConfigPin_t huart1;

/* Buffer to receive data from master */
uint8_t SlaveRxBuffer[BUFFER_SIZE];

void APP_Init(void)
{
    /* Configure I2C as Slave */
    i2c1.Instance = I2C1;

    i2c1.Config.ClockSpeed     = I2C_SM_100K;
    i2c1.Config.OwnAddress     = I2C_OWN_ADDRESS_7BIT(SLAVE_ADDR);
    i2c1.Config.ACKControl     = I2C_ACK_ENABLE;
    i2c1.Config.AddressingMode = I2C_ADDRESS_7BIT_MODE;
    i2c1.Config.DualAddress    = I2C_DUAL_DISABLE;
    i2c1.Config.SecondAddress  = I2C_SECOND_ADDRESS_DISABLE;
    i2c1.Config.IT_Config      = 0;
    i2c1.Config.Callback       = I2C_CALLBACK_NULL;
    i2c1.Config.ErrorCallback  = I2C_CALLBACK_NULL;

    i2c1.State = I2C_STATE_READY;
    i2c1.Lock  = I2C_UNLOCKED;

    /* Enable I2C clock */
    I2C_PeriClockControl(I2C1, ENABLE);

    /* Initialize I2C */
    I2C_Init(&i2c1);

    /* Enable I2C peripheral */
    I2C_Enable(i2c1.Instance);

    /* Configure UART (for printing received data) */
    huart1.UART            = UART1;
    huart1.Mode            = UART_Mode_TX;
    huart1.BaudRate        = UART_BaudRate_115200;
    huart1.Payload_Length  = UART_Payload_Length_8B;
    huart1.Parity          = UART_Parity_NONE;
    huart1.StopBits        = UART_StopBits_1;
    huart1.HW_FlowCTL      = UART_HW_FlowCTL_NONE;
    huart1.IRQ_Enable      = UART_IRQ_Enable_NONE;
    huart1.p_IRQ_CallBack  = NULL;

    UART_Init(&huart1);
}

void APP_Mode(void)
{
    /* Receive data from master */
    if (I2C_Slave_Receive(&i2c1, SlaveRxBuffer, BUFFER_SIZE) == I2C_OK)
    {
        /* Send received data over UART */
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            uint16_t data = SlaveRxBuffer[i];
            UART_Send_Data(&huart1, &data);
            UART_Wait_TC(&huart1);
        }
    }
}
#endif
