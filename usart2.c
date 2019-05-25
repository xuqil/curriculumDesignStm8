#include "usart2.h"

//串口配置
//数据位:8
//停止位:1
//校验位:None
void UART_Init(void)
{
    UART2_CR2_TEN = 1;
    UART2_CR2_REN = 1;
    UART2_CR2_RIEN = 1;
    UART2_BRR2 = ((unsigned char)((F_MASTER / BAUD_RATE) & 0x0f)) + (((unsigned char)((F_MASTER / BAUD_RATE) >> 8)) & 0xf0);
    UART2_BRR1 = ((unsigned char)((F_MASTER / BAUD_RATE) >> 4));
}

void UART_TxByte(unsigned char _data)
{
    while (UART2_SR_TXE == 0);
    UART2_DR = _data;
}

int putchar(int c)
{
    UART_TxByte(c);
    return c;
}

#pragma vector = UART2_R_RXNE_vector
__interrupt void UART2_IRQHandler(void)
{
    if (UART2_SR_RXNE == 1)
    {
        UART_TxByte(UART2_DR);
    }
}
