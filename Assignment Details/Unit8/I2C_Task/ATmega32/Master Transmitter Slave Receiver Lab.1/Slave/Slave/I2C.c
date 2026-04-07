/*
 * I2C.c
 *
 * Created: 8/12/2021 3:21:35 AM
 *  Author: Kirellos Emad Samir
 */ 
#include "I2C.h"

void I2C_Set_Address(unsigned char address)
{
	TWAR = address;
}
unsigned char I2C_Read(unsigned char ack)
{
	unsigned char x=0;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & 1<<7) == 0);
	while ((TWSR) != 0x60) x = TWSR;             // own SLA+W(0) has been transmitted and ACK has been returned
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);  
	while ((TWCR & 1<<7) == 0);
	while ((TWSR) != 0x80) x = TWSR;          // Data has been transmitted and ACK has been returned
	return TWDR;
}