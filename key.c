#include "key.h"
#include "delay.h"

int value_limit = 0;
int value_max = 0;
char value_str[3];
int write_flag = 0;
int read_flag = 0;

int i;
char display_limit[16];
char display_max[16];
char save_string[16] = "    Succeed!    ";

void GPIO_KEY_Init(void)
{
      PA_DDR &= 0x8F;		//按键为PA4/5/6,上拉输入
      PA_CR1 |= 0x70;		//
      PA_CR2 |= 0x70;		//使能引脚中断功能

      PE_DDR_DDR7 = 0;	//触摸电容为PE7,上拉输入
      PE_CR1_C17  = 1;
      PE_CR2_C27  = 1;	//使能引脚中断功能
      
      EXTI_CR1 |= 0x02;	//将PA口设置为下降沿触发模式
      EXTI_CR2 |= 0x02;	//将PE口设置为下降沿触发模式
}



/*****************************
* PA口的外部中断函数
******************************/
#pragma vector=5		//此值为中断向量号加2
__interrupt void EXTI_PORTA_IRQHandler(void)
{
	delay_ms(10);		//延时消抖
	if(key0==0)
	{
            write_flag = 1;
            value_limit -- ;
            //SaveToTuple(display_limit, value_limit);
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
            Write_Commond(0x80);		//0x80为第一行的首地址
            for(i=0; i<16; ++i)
            {
                  Write_Data(display_limit[i]);
            }
	}
	
	else if(key1==0)
	{
            write_flag = 2;
            value_max ++;
            //SaveToTuple(display_max, value_max);
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
            Write_Commond(0x80);		//0x80为第一行的首地址
            for(i=0; i<16; ++i)
            {
                  Write_Data(display_max[i]);
            }
            
	}
	
	else if(key2==0&&write_flag)
	{
            if(write_flag == 1)
            {
              SaveToEEPROM(0, value_limit);
            }
            else if(write_flag == 2)
            {
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
* PE口的外部中断函数
******************************/
#pragma vector=9		//此值为中断向量号加2
__interrupt void EXTI_PORTE_IRQHandler(void)
{
	delay_ms(10);
	if(key3==0)
	{
		;
	}
}