/***************************
作者：许其龙
时间：2019/5/23
版本：V1.0
email：xuqi19218@foxmail.com
***************************/
#ifndef __STM8S_EEPROM_H__
#define __STM8S_EEPROM_H__

#include <iostm8s105c6.h>
#include "stm8s_type.h"

#define EP_HEADER_ADDR    0x4000

void EEPROM_Init(void);
void EEPROM_Lock(void);
void EEPROM_Write(u8 addr, u8 dat);
u8 EEPROM_Read(u8 addr);
#endif
