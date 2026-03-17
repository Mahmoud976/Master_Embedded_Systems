
#include "Registers.h"

int main(void)
{
	DDRD &=~(1<<0); 
	DDRD |=(111<<4);
	DDRD |=(1<<7);
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
			PORTD &=~(111<<4);
			PORTD &=~(1<<7);
		}
		else if (count==1)
		{
			PORTD |=(1<<5);
			PORTD |=(1<<4);
			
		}
		else if (count==2)
		{
			PORTD &=~(1<<5);
			PORTD |=(1<<6);
		    PORTD &=~(1<<4);

		}
		else 
		{   PORTD &=~(1<<6);
			PORTD |=(1<<7);
			PORTD |=(1<<4);
		}
    }
}

