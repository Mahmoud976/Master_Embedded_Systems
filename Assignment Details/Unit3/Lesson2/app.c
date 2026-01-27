#include "uart.h"

char message[100]="Learn_In_Depth: Mahmoud Saleh";

void main (void){

Uart_Send_String(message);
}
