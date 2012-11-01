/*
 * UART.h
 *
 * Created: 2012.10.28 16:02:05
 *  Author: Karolis
 */ 
#define LOGMAX 72
extern char commsg[LOGMAX];

void InitUSART(void);
void print_to_com(const char *data);