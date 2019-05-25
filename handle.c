#include "handle.h"

/*****************************
*          »º´æ
******************************/
void SaveToTuple(int value)
{
  memset(value_str,'\0',sizeof(value_str)); //Çå¿ÕÊý×é   
  if (0 <= value)
  {
    sprintf(value_str, "%d", value);
  }
  else if (value < 0)
  {
    value = -value;
    sprintf(value_str, "%d", value);
  }
}

/*****************************
*          write eeprom
******************************/
void SaveToEEPROM(u8 addr, int value)
{
  SaveToTuple(value);
  
   int i;
   for(i = 0; i < sizeof(value_str); i++)
    {
        if(value_str[i] == '\0')
         continue;
        EEPROM_Write(addr + i,  (u8)value_str[i]); 
    }
}