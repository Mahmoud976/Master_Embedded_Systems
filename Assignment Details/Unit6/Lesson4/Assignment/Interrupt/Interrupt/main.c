/*
 * Interrupt.c
 *
 * Created: 3/14/2026 4:29:36 PM
 * Author : mahmo
 */ 

/*
#define SREG    *((volatile unsigned char*) 0x5F  )
#define GICR    *((volatile unsigned char*) 0x5B  )
#define GIFR    *((volatile unsigned char*) 0x5A  )
#define MCUCR   *((volatile unsigned char*) 0x55  )
#define PIND    *((volatile unsigned char*) 0x30  )
#define DDRD    *((volatile unsigned char*) 0x31  )
#define PORTD   *((volatile unsigned char*) 0x32  )
#define PINA    *((volatile unsigned char*) 0x3B  )
#define DDRA    *((volatile unsigned char*) 0x3A  )
#define PORTA   *((volatile unsigned char*) 0x39  )


//make pin2 in port D  input (for EXTI0) >> write on DDRx zero to input or one to output
//enable EXTI0  in GICR >> write  1 in bit 6 in GICR
//enable Any logical change on INT0 generates an interrupt request. >> write on MCUCR  0 1
//enable NVIC or Global Interrupt Enable >> wite 1 on bit 7 in SREG
//make weak and alias function >> void __vector_1 (void) __attribute__ ((signal, used, alias("__EXTI_0")));


void __vector_1 (void) __attribute__ ((signal, used, externally_visible));
void __vector_1 (void) __attribute__ ((alias("__EXTI_0")));
void __EXTI_0 (void) __attribute__ ((weak));

void __EXTI_0 (void) {
	PORTA ^= (1 << 0);
	GIFR |= (1<<6);
}



int main(void)
{
	DDRA |=(1<<0);
	
	
	DDRD &=~(1<<2);
	GICR |=(1<<6);
	MCUCR |=(1<<0);
	MCUCR &=~(1<<1);
	SREG |=(1<<7);
    while (1) 
    {
    }
}
*/

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	/* 1. I/O Pins Configuration */
	DDRA  |= (1 << 0);      // Set PA0 as Output (LED)
	PORTA |= (1<<0);       // to make led off with my schematic
	
	DDRD  &= ~(1 << 2);     // Set PD2 as Input (INT0)
	PORTD |= (1 << 2);      // Enable Internal Pull-up for PD2

	/* 2. Configure INT0 for "Any Logical Change" */
	// ISC01 = 0, ISC00 = 1
	MCUCR &= ~(1 << ISC01);
	MCUCR |=  (1 << ISC00);

	/* 3. Enable Interrupts */
	GICR |= (1 << INT0);    // Enable External Interrupt 0
	sei();                  // Global Interrupt Enable

	while (1)
	{
		// Main Application Loop
	}
}

/* Interrupt Service Routine for INT0 */
ISR(INT0_vect)
{
	// Step 1: Toggle LED (Turn it ON if it was OFF)
	PORTA ^= (1 << 0);
	
	// Step 2: Software Delay using volatile for loop
	// Adjust the number (100000) based on your Proteus simulation speed
	for(volatile uint32_t i = 0; i < 500000; i++);

	// Step 3: Toggle LED again (Turn it OFF to return to original state)
	PORTA ^= (1 << 0);
}
