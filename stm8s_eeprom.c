#include "stm8s_eeprom.h"

void EEPROM_Init(void)
{
  do
  {
    FLASH_CR1=0x00;
    FLASH_CR2=0x00;
    FLASH_NCR2=0xFF;
    FLASH_DUKR = 0xAE;	// 写入第一个密钥
    FLASH_DUKR = 0x56;	// 写入第二个密钥
  } while((FLASH_IAPSR & 0x08) == 0);	// 若解锁未成功，则重新再来
}

void EEPROM_Lock(void)
{
  FLASH_IAPSR=(u8)(~0x08); //重新上锁
}

//EEPROM指定地址写入一个数据 addr:相对地址 dat:数据
void EEPROM_Write(u8 addr, u8 dat)
{
  EEPROM_Init();
  u8 *p;
  p=(u8 *)(EP_HEADER_ADDR + addr);
  *p=dat;
  while(!(FLASH_IAPSR&0x04)); //等待写操作成功
  EEPROM_Lock();
}
 
//EEPROM指定地址读出一个数据 addr:相对地址
u8 EEPROM_Read(u8 addr)
{
  u8 *p;
  p=(u8 *)(EP_HEADER_ADDR + addr); 
  return *p; 
}

