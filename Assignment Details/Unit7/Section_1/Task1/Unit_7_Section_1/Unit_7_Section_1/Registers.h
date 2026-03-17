/*
 * Registers.h
 *
 * Created: 3/17/2026 12:33:55 AM
 *  Author: mahmo
 */ 
#ifndef REGISRTERS_H
#define REGISRTERS_H
 /**************************************************************************
  *                            GPIO Register                               *
  **************************************************************************/
 //*************************** PORTA  **************************************
#define PORTA    *((volatile unsigned char *) 0x3B)
#define DDRA     *((volatile unsigned char *) 0x3A)
#define PINA     *((volatile unsigned char *) 0x39)
 //*************************** PORTB  **************************************
#define PORTB    *((volatile unsigned char *) 0x38)
#define DDRB     *((volatile unsigned char *) 0x37)
#define PINB     *((volatile unsigned char *) 0x36)
 //*************************** PORTC  **************************************
#define PORTC    *((volatile unsigned char *) 0x35)
#define DDRC     *((volatile unsigned char *) 0x34)
#define PINC     *((volatile unsigned char *) 0x33)
 //*************************** PORTD  **************************************
#define PORTD    *((volatile unsigned char *) 0x32)
#define DDRD     *((volatile unsigned char *) 0x31)
#define PIND     *((volatile unsigned char *) 0x30)





#endif