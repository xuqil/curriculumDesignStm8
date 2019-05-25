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
unsigned char arr1[16]="Welcom to use!  ";
char buffer[8];


int main(void)
{  
    float tempetature;
    int i;
    char buffer_limit[3], buffer_max[3]; //缓存
    
    CLK_SWCR_SWEN = 1;
    CLK_SWR = 0xB4;             //主时钟
    
    UART_Init();                //串口初始化
    GPIO_KEY_Init();            //按键初始化
    __enable_interrupt();       //开启总中断
    LCD1602_Init();             //LCD初始化
    asm("rim");
    tempetature = DS18B20_ReadTemperature(); // 获取温度值
    sprintf(buffer_limit, "%c%c", EEPROM_Read(0), EEPROM_Read(1));
    sprintf(buffer_max, "%c%c", EEPROM_Read(4), EEPROM_Read(5));
    if(buffer_limit != '\0'|| buffer_max != '\0') //存储的数据不为空时,阈值从EEPROM取值
    {
      value_limit = atoi((char*)buffer_limit); 
      value_max = atoi((char*)buffer_max); 
    }
    else //存储的数据为空时,阈值从现测温度值取值
    {
      value_limit = (int)tempetature; 
      value_max = (int)tempetature; 
    }
     Write_Commond(0x80);		//0x80为第一行的首地址
      for(i=0; i<16; ++i)
      {
            Write_Data(arr1[i]);
      }
    while(1)
    {
       if(write_flag == 0)
      {
         
          if (read_flag) //当重新设置阈值时
          {
            memset(buffer_limit,'\0',sizeof(buffer_limit));
            memset(buffer_max,'\0',sizeof(buffer_max));
            sprintf(buffer_limit, "%c%c", EEPROM_Read(0), EEPROM_Read(1));
            sprintf(buffer_max, "%c%c", EEPROM_Read(4), EEPROM_Read(5));
            read_flag = 0;
          }
          _delay_ms(1000);
          _delay_ms(1000);
          printf("下限：%d", value_limit);
          printf("上限：%d", value_max);
        

          tempetature = DS18B20_ReadTemperature();
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
}


