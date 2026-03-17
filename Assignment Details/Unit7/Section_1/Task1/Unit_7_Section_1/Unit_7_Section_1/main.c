/*
 * Unit_7_Section_1.c
 *
 * Created: 3/17/2026 12:32:25 AM
 * Author : Mahmoud Saleh
 */ 
#include "Registers.h"

int main(void)
{
	DDRD &=~(1<<0); 
	DDRD |=(111<<5);
    int count =0 ;
    while (1) 
    {
		if((PIND & (1<<0))>>0)
		{
			count++;
			count %=4; 
			while((PIND & (1<<0))>>0);
		}
		if (count==0)
		{
			PORTD &=~(111<<5);
		}
		else if (count==1)
		{
			PORTD |=(1<<5);
		}
		else if (count==2)
		{
			PORTD |=(1<<6);
		}
		else 
		{
			PORTD |=(1<<7);
		}
    }
}

