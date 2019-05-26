#include "beep.h"

void GPIO_BEEP_Init(void)
{
	PD_DDR_DDR4 = 1;	//BEEP->PD4
	PD_CR1_C14  = 1;
	PD_ODR_ODR4 = 1;
}

void BeepAlert(void)
{
        BEEP_ON;
        delay(100);
        BEEP_OFF;
        delay(100);
        
        BEEP_ON;
        delay(100);
        BEEP_OFF;
        delay(100);
        
        //delay_ms(1000);
}

void delay(u16 num)
{
    u16 i, j;
    for(i=0;i<num;i++)
    {
            for(j=0;j<1300;j++)
                    ;
    }
}