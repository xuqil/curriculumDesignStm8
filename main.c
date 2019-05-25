#include <iostm8s105c6.h>
#include <stdio.h>
#include "lcd1602.h"
#include "delay.h"
#include "ds18b20.h"
#include "usart2.h"
#include <string.h>
#include <stdlib.h>

unsigned char arr0[16]="Temperature:    ";
char buffer[8];

int main(void)
{  
    CLK_SWCR_SWEN = 1;
    CLK_SWR = 0xB4;    //HSE selected as master clock source
    unsigned char i;
    
    UART_Init();
    LCD1602_Init();
    asm("rim");
    
    while(1)
    {
        _delay_ms(1000);
        printf("温度：%.3fC\n", DS18B20_ReadTemperature());
        memset(buffer,'\0',sizeof(buffer)); //清空数组  
        if(DS18B20_ReadTemperature() < 0)
          sprintf(buffer,"%.3fC",DS18B20_ReadTemperature());
        else
          sprintf(buffer," %.3fC",DS18B20_ReadTemperature()); 
        Write_Commond(0x80);		//0x80为第一行的首地址
	for(i=0; i<16; ++i)
	{
		Write_Data(arr0[i]);
	}
	
	Write_Commond(0x80+0x40);	//0x80+0x40为第二行的首地址
	for(i=0; i<sizeof(buffer); ++i)
	{
		Write_Data(buffer[i]);
	}
    }
}



