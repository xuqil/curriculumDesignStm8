#ifndef __LCD1602_H__
#define __LCD1602_H__

/*****************************
* 对LCD1602的功能函数进行声明
* 以便被其他文件调用
******************************/
void GPIO_Init(void);
void Write_Commond(unsigned char commond);
void Write_Data(unsigned char data);
void LCD1602_Init(void);

#endif