#include "handle.h"

/*****************************
*          ����
******************************/
void SaveToTuple(char tuple[], int value)
{
  memset(value_str,'\0',sizeof(value_str)); //�������   
  if (0 <= value)
  {
    sprintf(tuple, "%d", value);
  }
  else if (value < 0)
  {
    value = -value;
    sprintf(tuple, "%d", value);
  }
}

/*****************************
*          д����
******************************/
void SaveToEEPROM(u8 addr, int data)
{
  SaveToTuple(value_str, data);
  
   int i;
   for(i = 0; i < sizeof(value_str); i++)
    {
        if(value_str[i] == '\0')
         continue;
        EEPROM_Write(addr + i,  (u8)value_str[i]); 
    }
}

