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
unsigned char alert[16]="Alert!  Alert!  ";
char buffer[8];
char buffer_limit[3], buffer_max[3]; //缓存
void ReadToBuffer(void);

int main(void)
{  
    float tempetature;
    int i;
  
    
    CLK_SWCR_SWEN = 1;
    CLK_SWR = 0xB4;             //主时钟
    
    UART_Init();                //串口初始化
    GPIO_KEY_Init();            //按键初始化
    __enable_interrupt();       //开启总中断
    LCD1602_Init();             //LCD初始化
    asm("rim");
    tempetature = DS18B20_ReadTemperature(); // 获取温度值
    ReadToBuffer();
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
            ReadToBuffer();
            value_limit = atoi((char*)buffer_limit); 
            value_max = atoi((char*)buffer_max); 
          }
          _delay_ms(1000);
         // _delay_ms(1000);
         // printf("下限：%d\n", value_limit);
        //  printf("上限：%d\n", value_max);
        

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
          if((value_limit > (int)tempetature)||(value_max <  (int)tempetature))
          {
            tempetature = DS18B20_ReadTemperature();
             Write_Commond(0x80);		//0x80为第一行的首地址
            for(i=0; i<16; ++i)
            {
                  Write_Data(alert[i]);
            }
          }

      }

    }
}


/*****************************
*      从EEPROM中读取阈值
******************************/
void ReadToBuffer(void)
{
      memset(buffer_limit,'\0',sizeof(buffer_limit));
      memset(buffer_max,'\0',sizeof(buffer_max));
      //读取下限
      if((EEPROM_Read(0) == '-')&&(EEPROM_Read(1) == '\0'))
      {
        if(EEPROM_Read(2) == '\0')
           sprintf(buffer_limit, "%c%c", EEPROM_Read(0), EEPROM_Read(1));
        else
          sprintf(buffer_limit, "%c%c%c", EEPROM_Read(0), EEPROM_Read(1), EEPROM_Read(2));
      }
      else
      {        
         if(EEPROM_Read(1) == '\0')
            sprintf(buffer_limit, "%c", EEPROM_Read(0));
         else if(EEPROM_Read(2) == '\0')
           sprintf(buffer_limit, "%c%c", EEPROM_Read(0), EEPROM_Read(1));
         else 
           sprintf(buffer_limit, "%c%c%c", EEPROM_Read(0), EEPROM_Read(1), EEPROM_Read(2));
      }
      
      //读取上限
       if((EEPROM_Read(4) == '-')&&(EEPROM_Read(5) == '\0'))
      {
        if(EEPROM_Read(6) == '\0')
           sprintf(buffer_max, "%c%c", EEPROM_Read(4), EEPROM_Read(5));
        else
          sprintf(buffer_max, "%c%c%c", EEPROM_Read(4), EEPROM_Read(5), EEPROM_Read(6));
      }
      else
      {
         if(EEPROM_Read(5) == '\0')
            sprintf(buffer_max, "%c", EEPROM_Read(4));
         else if(EEPROM_Read(6) == '\0')
           sprintf(buffer_max, "%c%c", EEPROM_Read(4), EEPROM_Read(5));
         else 
           sprintf(buffer_max, "%c%c%c", EEPROM_Read(4), EEPROM_Read(5), EEPROM_Read(6));
      }
      read_flag = 0;
}

