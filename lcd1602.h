#ifndef __LCD1602_H__
#define __LCD1602_H__

/*****************************
* ��LCD1602�Ĺ��ܺ�����������
* �Ա㱻�����ļ�����
******************************/
void GPIO_Init(void);
void Write_Commond(unsigned char commond);
void Write_Data(unsigned char data);
void LCD1602_Init(void);

#endif