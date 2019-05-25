#ifndef __KEY_H__
#define __KEY_H__
#include <iostm8s105c6.h>
#include "intrinsics.h"
#include "stm8s_type.h"
#include "stm8s_eeprom.h"
#include "handle.h"

#define key0  PA_IDR_IDR4	//��PA�ڵ�bit4����Ϊkey0
#define key1  PA_IDR_IDR5
#define key2  PA_IDR_IDR6
#define key3  PE_IDR_IDR7

extern int value_limit; //�¶�����
extern int value_max;  //�¶�����
extern char value_str[3]; //
extern int value_flag;

void GPIO_KEY_Init(void);

#endif