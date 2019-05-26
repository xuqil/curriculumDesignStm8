#ifndef __BEEP_H__
#define __BEEP_H__
#include <iostm8s105c6.h>
#include "delay.h"
#include "stm8s_type.h"

#define BEEP_ON  PD_ODR_ODR4 = 0
#define BEEP_OFF PD_ODR_ODR4 = 1

void GPIO_BEEP_Init(void);
void BeepAlert(void);
void delay(u16 num);
#endif
