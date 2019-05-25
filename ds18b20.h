#ifndef __DS18B20_H__
#define __DS18B20_H__

#include <iostm8s105c6.h>


#define DS18B20_DQ_OUT          PA_DDR_DDR3 = 1   //���
#define DS18B20_DQ_IN           PA_DDR_DDR3 = 0   //����
#define DS18B20_DQ_HIGH         PA_ODR_ODR3 = 1   //����
#define DS18B20_DQ_LOW          PA_ODR_ODR3 = 0   //����
#define DS18B20_DQ_PULL_UP      PA_CR1_C13  = 1   //����
#define DS18B20_DQ_FLOATING     PA_CR1_C13  = 0   //����
#define DS18B20_DQ_PUSH_PULL    PA_CR1_C13  = 1   //����
#define DS18B20_DQ_OPEN_DRAIN   PA_CR1_C13  = 0   //��©
#define DS18B20_DQ_VALUE        PA_IDR_IDR3       //DQֵ


void _delay_us(unsigned int i);
void _delay_ms(unsigned int i);
void DS18B20_Init(void);
void DS18B20_WriteByte(unsigned char _data);
unsigned char DS18B20_ReadByte(void);
float DS18B20_ReadTemperature(void);

#endif
