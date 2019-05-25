#ifndef __KEY_H__
#define __KEY_H__
#include <iostm8s105c6.h>
#include "intrinsics.h"
#include "stm8s_type.h"
#include "stm8s_eeprom.h"
#include "handle.h"
#include "lcd1602.h"


#define key0  PA_IDR_IDR4	//将PA口的bit4定义为key0
#define key1  PA_IDR_IDR5
#define key2  PA_IDR_IDR6
#define key3  PE_IDR_IDR7

extern int value_limit;        //温度下限
extern int value_max;          //温度上限
extern char value_str[3];      //缓存数组
extern int write_flag;         //写标志
extern int read_flag;          //读标志

void GPIO_KEY_Init(void);

#endif