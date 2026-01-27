#include "uart.h"

#define UART0DR  *((volatile int* const)((unsigned int*)0x101f1000))

void Uart_Send_String(unsigned char* message)
{

while (*message !='\0')
	{
	UART0DR=(unsigned int)(*message);
	message++;

	}

}
