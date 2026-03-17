#define F_CPU   8000000UL
#include "Registers.h"
#include<util/delay.h>
int main(void)
{
	DDRC=0xFF;
	DDRD &=~(1<<0);
	volatile unsigned char count=0,temp1=0,temp2;
    while (1) 
    {
		
		if ((PIND & (1<<0))>>0)
		{
			PORTC &=0x0f;
			count++;
			if (count > 99) count = 0;
			while((PIND & (1<<0))>>0);
		}
		temp1 = count % 10;
		PORTC = (temp1 << 4) | (1 << 2);
		 _delay_ms(10);
		temp2 = count / 10;
		PORTC = (temp2 << 4) | (1 << 3);
		 _delay_ms(10);
    }
}

