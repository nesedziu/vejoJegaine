/*
 * UART.c
 *
 * Created: 2012.10.28 15:12:10
 *  Author: Karolis
 */ 
#include <avr/io.h>
#define F_CPU	        8000000UL
#define BAUD 	        9600
#define MYUBRR	((F_CPU/(BAUD*16UL))-1)

unsigned char uartBuff[50];

void InitUSART(void)
{
	UBRRL = MYUBRR;
	UBRRH = (MYUBRR >> 8);
	
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (0 << USBS) | (3 << UCSZ0);		//8 data bits, 1 stop bits
}

void TransmitCharUSART(char cData)
{
	while(!(UCSRA & (1 << UDRE))) {};
	UDR = cData;
}


void TransmitUnsignedInt(unsigned int val)
{
	TransmitCharUSART(val >> 8);
	TransmitCharUSART(val & 0xFF);
}

void print_to_serial (unsigned char *data){
	
	while(*data){
		TransmitCharUSART(*data);
		data++;			
	}
}