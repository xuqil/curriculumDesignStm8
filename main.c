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
#include "stm8s_type.h"
#include "handle.h"

unsigned char arr0[16]="Temperature:    ";
char buffer[8];




int main(void)
{  
    float tempetature;
    u8 result0, result1, result2, result3;
    int flag_limit, flag_max;
    int i;
    
    CLK_SWCR_SWEN = 1;
    CLK_SWR = 0xB4;    //HSE selected as master clock source
    
    UART_Init();
    GPIO_KEY_Init();
    __enable_interrupt();	//开启总中断
    LCD1602_Init();
    asm("rim");

    tempetature = DS18B20_ReadTemperature();
    value_limit = (int)tempetature; 
    value_max = (int)tempetature;  
    flag_limit = value_limit;
    flag_max = value_max;
    
   
    while(1)
    {

      
        result0 = EEPROM_Read(0);
        result1 = EEPROM_Read(1);
        result2 = EEPROM_Read(4);
        result3 = EEPROM_Read(5);
        _delay_ms(1000);
        _delay_ms(1000);
        printf("结果1：%c", result0);
        printf("%c  \n\n", result1);
        printf("结果2：%c", result2);
        printf("%c  \n\n", result3);


        //printf("下限：%d  \n\n", value_limit);
        //printf("上限：%d  \n\n", value_max);
        tempetature = DS18B20_ReadTemperature();
        //printf("温度：%.3fC\n", tempetature);
        memset(buffer,'\0',sizeof(buffer)); //清空数组  
        if(tempetature < 0)
         sprintf(buffer,"%.3fC",tempetature);
        else
          sprintf(buffer," %.3fC",tempetature); 
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


