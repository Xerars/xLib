//[xLib Include]
#include "xTCA9555.h"

//Author  : William Hsiao
//Descript: TCA9555 Device Driver
//Version : 1.0.0

//[Variable Declare]
static xTCA *gTCA = NULL;

///@Function: xTCA_GetHandle
///@Descript: Get the Pointer of the Current Active TCA9555 Device Handle
xTCA* xTCA_GetHandle(void)
{
  return gTCA;
}


///@Function: xTCA_SetHandle
///@Descript: Set the Specific Device Handle as the Current Active Target
void xTCA_SetHandle(xTCA *pTCA)
{
  gTCA = pTCA;
}


///@Function: xTCA_Init
///@Descript: Initialize the TCA9555 Device With Port Setting and Default States
void xTCA_Init(xTCA *pTCA,xTCA_Port *Port)
{
  if(!pTCA || !Port)
    return;
  
  //Set Handle
  xTCA_SetHandle(pTCA);
  //Set Port
  pTCA->Port.I2C_ID    = Port->I2C_ID;
  pTCA->Port.I2C_Speed = Port->I2C_Speed;
  pTCA->Port.Write     = Port->Write; 
  pTCA->Port.Read      = Port->Read;
  //Set Data
  xTCA_Reset();
}


///@Function: xTCA_Reset
///@Descript: Reset Shadow Registers to Default
void xTCA_Reset(void)
{
  //Set Data
  gTCA->Dir   = 0xFFFF;       //Input
  gTCA->Level = 0xFFFF;       //High Level
  gTCA->Inv   = 0x0000;       //No Invert
}


///@Function: xTCA_SetDir
///@Descript: Configure Pin Directions as Either Input or Output
void xTCA_SetDir(U16 Pin, xTCA_DIR Dir)
{
  if(gTCA == NULL)
    return;

  U8 Buf[2] = {0};
  if(Dir == xTCA_DIR_IN)
    gTCA->Dir |= Pin;         //Set Bit
  else
    gTCA->Dir &= ~Pin;        //Clear Bit

  Buf[0] = (U8) (gTCA->Dir & 0xFF);           //Port 0
  Buf[1] = (U8)((gTCA->Dir >> 8) & 0xFF);     //Port 1
  xTCA_I2C_Write(REG_TCA_CONF_PORT0,Buf,2);
}


///@Function: xTCA_WritePin
///@Descript: Set the Output Logic Level (High/Low) for Specified Pins
void xTCA_WritePin(U16 Pin,xTCA_LEVEL Level)
{
  if(gTCA == NULL)
    return;
  
  if(Level == xTCA_LEVEL_HIGH)
    gTCA->Level |= Pin;
  else
    gTCA->Level &= ~Pin;

  U8 Buf[2] = {0};
  Buf[0] = (U8) (gTCA->Level & 0xFF);         //Port 0
  Buf[1] = (U8)((gTCA->Level >> 8) & 0xFF);   //Port 1
  xTCA_I2C_Write(REG_TCA_OUT_PORT0,Buf,2);
}


///@Function: xTCA_TogglePin
///@Descript: Flip the Current Logic Level of the Specified Pins
void xTCA_TogglePin(U16 Pin)
{
  if(gTCA == NULL)
    return;
  gTCA->Level ^= Pin;
  U8 Buf[2] = {0};
  Buf[0] = (U8)(gTCA->Level & 0xFF);
  Buf[1] = (U8)(gTCA->Level >> 8);
  xTCA_I2C_Write(REG_TCA_OUT_PORT0,Buf,2);
}


///@Function: xTCA_ReadPort
///@Descript: Read the 16-Bit Input Status from Both Port 0 and Port 1
U16 xTCA_ReadPort(void)
{
  if(gTCA == NULL)
    return 0x00;

  U8 Buf[2] = {0};
  xTCA_I2C_Read(REG_TCA_IN_PORT0,Buf,2);
  U16 Ret = ((U16)(Buf[1]<<8) | Buf[0]);
  return Ret;
}


///@Function: xTCA_ReadPin
///@Descript: Get the Logic Level of a Specific Input Pin
xTCA_LEVEL xTCA_ReadPin(xTCA_PIN Pin)
{
  U16 Data = xTCA_ReadPort();
  return (Data & Pin) ? xTCA_LEVEL_HIGH : xTCA_LEVEL_LOW;
}


///@Function: xTCA_SetInvert
///@Descript: Enabel or Disable Polarity Inversion for Specificed Input Pins
void xTCA_SetInvert(U16 Pin,U8 Invert)
{
  if(gTCA == NULL)
    return;

  if(Invert)
    gTCA->Inv |= Pin;
  else
    gTCA->Inv &= ~Pin;

  U8 Buf[2] = {0};
  Buf[0] = (U8) (gTCA->Inv & 0xFF);
  Buf[1] = (U8)((gTCA->Inv >> 8) & 0xFF);
  xTCA_I2C_Write(REG_TCA_POLAR_INV_PORT0,Buf,2);
}


///@Function: xTCA_I2C_Write
///@Descript: I2C Write to Send Data to the Device
void xTCA_I2C_Write(U8 Reg,U8 *pData,U32 Len)
{
  if(gTCA->Port.Write != NULL)
    gTCA->Port.Write(gTCA->Port.I2C_ID,Reg,pData,Len);
}


///@Function: xTCA_I2C_Read
///@Descript: I2C Read to Receive Data from the Device
void xTCA_I2C_Read(U8 Reg,U8 *pData,U32 Len)
{
  if(gTCA->Port.Read != NULL)
    gTCA->Port.Read(gTCA->Port.I2C_ID,Reg,pData,Len);
}
