#include "key.h"
#include "delay.h"

int value_limit = 0;
int value_max = 0;
char value_str[3];
int write_flag = 0;
int read_flag = 0;

int i;
int mode=0; //ģʽѡ��0�������ޣ�-1��������
//LCD��ʾ����
char display_limit[16];
char display_max[16];
char save_string[16] = "    Succeed!    ";

void GPIO_KEY_Init(void)
{
      PA_DDR &= 0x8F;		//����ΪPA4/5/6,��������
      PA_CR1 |= 0x70;		//
      PA_CR2 |= 0x70;		//ʹ�������жϹ���

      PE_DDR_DDR7 = 0;	//��������ΪPE7,��������
      PE_CR1_C17  = 1;
      PE_CR2_C27  = 1;	//ʹ�������жϹ���
      
      EXTI_CR1 |= 0x02;	//��PA������Ϊ�½��ش���ģʽ
      EXTI_CR2 |= 0x02;	//��PE������Ϊ�½��ش���ģʽ
}



/*****************************
* PA�ڵ��ⲿ�жϺ���
******************************/
#pragma vector=5		//��ֵΪ�ж������ż�2
__interrupt void EXTI_PORTA_IRQHandler(void)
{
	delay_ms(10);		//��ʱ����
	if(key0==0)   //��
	{
            write_flag = 1;
            
            if(mode == 0) //��������
            {
               value_limit -- ;
              memset(display_limit,'\0',sizeof(display_limit));
              if(value_limit >= 10) 
                sprintf(display_limit, "limit:%dC        ", value_limit);
              else if(value_limit >= 100)
                sprintf(display_limit, "limit:%dC       ", value_limit);
              else if(0 <= value_limit < 10)
                sprintf(display_limit, "limit:%dC         ", value_limit);
              else if(-10 < value_limit < 0)
                sprintf(display_limit, "limit:%dC        ", value_limit);
              else if(value_limit < -10)
                sprintf(display_limit, "limit:%dC       ", value_limit);
              Write_Commond(0x80);		//0x80Ϊ��һ�е��׵�ַ
              for(i=0; i<16; ++i)
              {
                    Write_Data(display_limit[i]);
              }
            }
            else if(mode == -1)//��������
            {
              if(value_limit <= value_max)
                value_max --;
              else
                value_max ++;
              memset(display_max,'\0',sizeof(display_max));
              if(value_limit >= 10) 
                sprintf(display_max, "max:%dC          ", value_max);
              else if(value_limit >= 100) 
                sprintf(display_max, "max:%dC         ", value_max);
              else if(0 <= value_limit < 10) 
                sprintf(display_max, "max:%dC           ", value_max);
              else if(-10 < value_limit < 0) 
                sprintf(display_max, "max:%dC          ", value_max);
              else if(value_limit <= -10) 
                sprintf(display_max, "max:%dC         ", value_max);
              Write_Commond(0x80);		//0x80Ϊ��һ�е��׵�ַ
              for(i=0; i<16; ++i)
              {
                    Write_Data(display_max[i]);
              }
            }
	}
	
	else if(key1==0)   //��
	{
            write_flag = 1;
            
            if(mode == 0) //��������
            {
              if(value_limit <= value_max)
                value_limit ++ ;
              else
                 value_limit -- ;
              //SaveToTuple(display_limit, value_limit);
              memset(display_limit,'\0',sizeof(display_limit));
              if(value_limit >= 10) 
                sprintf(display_limit, "limit:%dC        ", value_limit);
              else if(value_limit >= 100)
                sprintf(display_limit, "limit:%dC       ", value_limit);
              else if(0 <= value_limit < 10)
                sprintf(display_limit, "limit:%dC         ", value_limit);
              else if(-10 < value_limit < 0)
                sprintf(display_limit, "limit:%dC        ", value_limit);
              else if(value_limit < -10)
                sprintf(display_limit, "limit:%dC       ", value_limit);
              Write_Commond(0x80);		//0x80Ϊ��һ�е��׵�ַ
              for(i=0; i<16; ++i)
              {
                    Write_Data(display_limit[i]);
              }
            }
            else if(mode == -1) //��������
            {
              value_max ++;
              //SaveToTuple(display_max, value_max);
              memset(display_max,'\0',sizeof(display_max));
              if(value_limit >= 10) 
                sprintf(display_max, "max:%dC          ", value_max);
              else if(value_limit >= 100) 
                sprintf(display_max, "max:%dC         ", value_max);
              else if(0 <= value_limit < 10) 
                sprintf(display_max, "max:%dC           ", value_max);
              else if(-10 < value_limit < 0) 
                sprintf(display_max, "max:%dC          ", value_max);
              else if(value_limit <= -10) 
                sprintf(display_max, "max:%dC         ", value_max);
              Write_Commond(0x80);		//0x80Ϊ��һ�е��׵�ַ
              for(i=0; i<16; ++i)
              {
                    Write_Data(display_max[i]);
              }
            }       
	}
	
	else if(key2==0&&write_flag) // ��������
	{
            if(write_flag)
            {
              if(mode == 0)
                 SaveToEEPROM(0, value_limit);
              else 
                 SaveToEEPROM(4, value_max);
            }
             Write_Commond(0x80);
             for(i=0; i<16; ++i)
            {
                  Write_Data(save_string[i]);
            }
            write_flag = 0;
            read_flag = 1;
	}
}

/*****************************
* PE�ڵ��ⲿ�жϺ���
******************************/
#pragma vector=9		//��ֵΪ�ж������ż�2
__interrupt void EXTI_PORTE_IRQHandler(void)
{
	delay_ms(10);
	if(key3==0)
	{
           mode = ~mode;
	}
}