#include "key.h"
#include "delay.h"

int value_limit = 0;
int value_max = 0;
char value_str[3];
int value_flag = 0;

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
	if(key0==0)
	{
            value_limit -- ;
            value_flag = 1;
	}
	
	else if(key1==0)
	{
            value_max ++;
            value_flag = 2;
	}
	
	else if(key2==0&&value_flag)
	{
            if(value_flag == 1)
            {
              SaveToEEPROM(0, value_limit);
            }
            else if(value_flag == 2)
            {
               SaveToEEPROM(4, value_max);
            }
            value_flag = 0;
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
		;
	}
}