/*
 * UART.h
 *
 * Created: 2012.10.28 16:02:05
 *  Author: Karolis
 */ 

extern unsigned char uartBuff[50];

void InitUSART(void);


void TransmitCharUSART(char cData);


void TransmitUnsignedInt(unsigned int val);

void print_to_serial (unsigned char *data);