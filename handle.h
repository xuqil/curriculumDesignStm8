/***************************
���ߣ�������
ʱ�䣺2019/5/23
�汾��V1.0
email��xuqi19218@foxmail.com
***************************/
#ifndef __HANDLE_H__
#define __HANDLE_H__
#include "stm8s_type.h"
#include <string.h>
#include <stdlib.h>
#include "key.h"
#include "stm8s_type.h"

void SaveToTuple(char tuple[], int value);
void SaveToEEPROM(u8 addr, int data);


#endif
