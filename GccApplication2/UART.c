/*
 * UART.c
 *
 * Created: 2012.10.28 15:12:10
 *  Author: Karolis
 */ 
#include <avr/io.h>
#include "string.h"
#include "UART.h"
#define F_CPU	        1000000L
#define BAUD 	        9600
#define MYUBRR	((F_CPU/(BAUD*16UL))-1)

char commsg[LOGMAX];

static void TransmitCharUSART(char cData);

void InitUSART(void)
{
	UBRRL = MYUBRR;
	UBRRH = (MYUBRR >> 8);
	
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (0 << USBS) | (3 << UCSZ0);		//8 data bits, 2 stop bits
}

static void TransmitCharUSART(char cData)
{
	while(!(UCSRA & (1 << UDRE))) {};
	UDR = cData;
}

void TransmitUnsignedInt(unsigned int val)
{
	TransmitCharUSART(val >> 8);
	TransmitCharUSART(val & 0xFF);
}

void print_to_com(const char *data){
	
	unsigned int safe = 0;
	
	safe = LOGMAX;
	
	while(*data && safe--){
		TransmitUnsignedInt(*data);
		data++;	
	}
	
	memset(commsg,0,LOGMAX);
}