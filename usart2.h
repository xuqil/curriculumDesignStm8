#ifndef __USART2_H__
#define __USART2_H__
#include <iostm8s105c6.h>

#define BAUD_RATE     9600         //波特率
#define F_MASTER      16000000     //主频率


void UART_Init(void);
void UART_TxByte(unsigned char _data);
int putchar(int c);
#endif
