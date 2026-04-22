//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xTCA9555.h"

//[Macro Declare]

//[Prototype Declare]
void TCA_Fake_I2C_Write(U8 Addr,U8 Reg,U8 *pData,U32 Len);
void TCA_Fake_I2C_Read(U8 Addr,U8 Reg,U8 *pData,U32 Len);

//[Variable]
U8 Register[8] = {0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF};

//Main Code
int main(void)
{
  xTCA      DevTCA;
  xTCA_Port DevTCA_Port;

  //Regist Port
  DevTCA_Port.I2C_ID    = xTCA_SLAVE_ADDR(0,0,0);
  DevTCA_Port.I2C_Speed = 400000;
  DevTCA_Port.Write     = TCA_Fake_I2C_Write;
  DevTCA_Port.Read      = TCA_Fake_I2C_Read;

  //Init
  xTCA_Init(&DevTCA,&DevTCA_Port);

  //Dir
  xTCA_SetDir(TCA_PIN_P00 | TCA_PIN_P01,xTCA_DIR_OUT);
  xTCA_SetDir(TCA_PIN_P10 | TCA_PIN_P11,xTCA_DIR_IN);

  //Write & Toggle
  xTCA_WritePin(TCA_PIN_P00 | TCA_PIN_P01,xTCA_LEVEL_LOW);
  xTCA_TogglePin(TCA_PIN_P00);

  //Read
  U16 Value = xTCA_ReadPort();
  xTCA_LEVEL Level = xTCA_ReadPin(TCA_PIN_P11);

  printf("Value: %d\n",Value);
  printf("P1.1 = %d\n",Level);

  //Invert
  xTCA_SetInvert(TCA_PIN_P00,1);
  return 0;
}


///@Function: TCA_Fake_I2C_Write
///@Descript: Fake I2C Write Function
void TCA_Fake_I2C_Write(U8 Addr,U8 Reg,U8 *pData,U32 Len)
{
  printf("[I2C Write] Addr: 0x%02X, Reg: 0x%02X(%d) -> ",Addr,Reg,Len);
  for(U32 i = 0;i < Len;i++)
    if((Reg+i)<8)
    {
      Register[Reg + i] = pData[i];
      printf("0x%02X ",pData[i]);
    }
  printf("\n");
}


///@Function: TCA_Fake_I2C_Read
///@Descript: Fake I2C Read Function
void TCA_Fake_I2C_Read(U8 Addr,U8 Reg,U8 *pData,U32 Len)
{
  printf("[I2C Read ] Addr: 0x%02X, Reg: 0x%02X(%d) -> ",Addr,Reg,Len);
  for(U32 i = 0;i < Len;i++)
    if((Reg + i) < 8)
    {
      pData[i] = Register[Reg + i];
      printf("0x%02X ",pData[i]);
    }
  printf("\n");
}