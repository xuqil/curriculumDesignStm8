#include "stm8s_eeprom.h"

void EEPROM_Init(void)
{
  do
  {
    FLASH_CR1=0x00;
    FLASH_CR2=0x00;
    FLASH_NCR2=0xFF;
    FLASH_DUKR = 0xAE;	// д���һ����Կ
    FLASH_DUKR = 0x56;	// д��ڶ�����Կ
  } while((FLASH_IAPSR & 0x08) == 0);	// ������δ�ɹ�������������
}

void EEPROM_Lock(void)
{
  FLASH_IAPSR=(u8)(~0x08); //��������
}

//EEPROMָ����ַд��һ������ addr:��Ե�ַ dat:����
void EEPROM_Write(u8 addr, u8 dat)
{
  EEPROM_Init();
  u8 *p;
  p=(u8 *)(EP_HEADER_ADDR + addr);
  *p=dat;
  while(!(FLASH_IAPSR&0x04)); //�ȴ�д�����ɹ�
  EEPROM_Lock();
}
 
//EEPROMָ����ַ����һ������ addr:��Ե�ַ
u8 EEPROM_Read(u8 addr)
{
  u8 *p;
  p=(u8 *)(EP_HEADER_ADDR + addr); 
  return *p; 
}

