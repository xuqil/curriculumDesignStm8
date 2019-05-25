#include <iostm8s105c6.h>
#include <stdio.h>
#include "lcd1602.h"
#include "delay.h"
#include "ds18b20.h"
#include "usart2.h"
#include <string.h>
#include <stdlib.h>
#include "stm8s_eeprom.h"
#include "key.h"

unsigned char arr0[16]="Temperature:    ";
char buffer[8];

int main(void)
{  
    u8 string = '1';
    u8 result;
    CLK_SWCR_SWEN = 1;
    CLK_SWR = 0xB4;    //HSE selected as master clock source
    unsigned char i;
    
    UART_Init();
     GPIO_KEY_Init();
    __enable_interrupt();	//�������ж�
    LCD1602_Init();
    asm("rim");
    EEPROM_Write(0, string);
    result = EEPROM_Read(0);
    while(1)
    {
        _delay_ms(1000);
        printf("�¶ȣ�%.3fC\n", DS18B20_ReadTemperature());
        printf("�����%c  \n\n", result);
        printf("value�����%d  \\nn", value);
        memset(buffer,'\0',sizeof(buffer)); //�������  
        if(DS18B20_ReadTemperature() < 0)
          sprintf(buffer,"%.3fC",DS18B20_ReadTemperature());
        else
          sprintf(buffer," %.3fC",DS18B20_ReadTemperature()); 
        Write_Commond(0x80);		//0x80Ϊ��һ�е��׵�ַ
	for(i=0; i<16; ++i)
	{
		Write_Data(arr0[i]);
	}
	
	Write_Commond(0x80+0x40);	//0x80+0x40Ϊ�ڶ��е��׵�ַ
	for(i=0; i<sizeof(buffer); ++i)
	{
		Write_Data(buffer[i]);
	}
    }
}



