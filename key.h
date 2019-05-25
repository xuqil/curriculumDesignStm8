#ifndef __KEY_H__
#define __KEY_H__
#include <iostm8s105c6.h>
#include "intrinsics.h"

#define key0  PA_IDR_IDR4	//将PA口的bit4定义为key0
#define key1  PA_IDR_IDR5
#define key2  PA_IDR_IDR6
#define key3  PE_IDR_IDR7

extern int value;

void GPIO_KEY_Init(void);

#endif
