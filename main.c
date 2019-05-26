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
char buffer_limit[3], buffer_max[3]; //����
void ReadToBuffer(void);

int main(void)
{  
    float tempetature;
    int i;
  
    
    CLK_SWCR_SWEN = 1;
    CLK_SWR = 0xB4;             //��ʱ��
    
    UART_Init();                //���ڳ�ʼ��
    GPIO_KEY_Init();            //������ʼ��
    __enable_interrupt();       //�������ж�
    LCD1602_Init();             //LCD��ʼ��
    asm("rim");
    tempetature = DS18B20_ReadTemperature(); // ��ȡ�¶�ֵ
    ReadToBuffer();
    if(buffer_limit != '\0'|| buffer_max != '\0') //�洢�����ݲ�Ϊ��ʱ,��ֵ��EEPROMȡֵ
    {
      value_limit = atoi((char*)buffer_limit); 
      value_max = atoi((char*)buffer_max); 
    }
    else //�洢������Ϊ��ʱ,��ֵ���ֲ��¶�ֵȡֵ
    {
      value_limit = (int)tempetature; 
      value_max = (int)tempetature; 
    }
     Write_Commond(0x80);		//0x80Ϊ��һ�е��׵�ַ
      for(i=0; i<16; ++i)
      {
            Write_Data(arr1[i]);
      }
    while(1)
    {
       if(write_flag == 0)
      {
         
          if (read_flag) //������������ֵʱ
          {
            ReadToBuffer();
            value_limit = atoi((char*)buffer_limit); 
            value_max = atoi((char*)buffer_max); 
          }
          _delay_ms(1000);
         // _delay_ms(1000);
         // printf("���ޣ�%d\n", value_limit);
        //  printf("���ޣ�%d\n", value_max);
        

          tempetature = DS18B20_ReadTemperature();
          memset(buffer,'\0',sizeof(buffer)); //�������  
          if(tempetature < 0)
            sprintf(buffer,"%.3fC",tempetature);
          else
            sprintf(buffer," %.3fC",tempetature); 
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
          if((value_limit > (int)tempetature)||(value_max <  (int)tempetature))
          {
            tempetature = DS18B20_ReadTemperature();
             Write_Commond(0x80);		//0x80Ϊ��һ�е��׵�ַ
            for(i=0; i<16; ++i)
            {
                  Write_Data(alert[i]);
            }
          }

      }

    }
}


/*****************************
*      ��EEPROM�ж�ȡ��ֵ
******************************/
void ReadToBuffer(void)
{
      memset(buffer_limit,'\0',sizeof(buffer_limit));
      memset(buffer_max,'\0',sizeof(buffer_max));
      //��ȡ����
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
      
      //��ȡ����
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

