#include "App.h"


uint8_t ch;
UART_ConfigPin_t UART_CFG;

void fun(){UART_Send_Data(&UART_CFG,&ch);
}
void APP_Init(void)
{
	UART_CFG.BaudRate=UART_BaudRate_57600;
	UART_CFG.HW_FlowCTL=UART_HW_FlowCTL_NONE;
	UART_CFG.IRQ_Enable=UART_IRQ_Enable_RXNE;
	UART_CFG.Mode=UART_Mode_TX_RX;
	UART_CFG.Parity=UART_Parity_NONE;
	UART_CFG.Payload_Length=UART_Payload_Length_8B;
	UART_CFG.StopBits=UART_StopBits_1;
	UART_CFG.UART=UART1;
	UART_CFG.p_IRQ_CallBack=fun;
	UART_Init(&UART_CFG);
}

void APP_Mode(void)
{
UART_Receive_Data(&UART_CFG, &ch);
}
