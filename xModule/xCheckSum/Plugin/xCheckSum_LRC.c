//[xLib Inclulde]
#include "xCheckSum_LRC.h"

//Author  : William Hsiao
//Descript: Data Validation Library for Embedded Systems(LRC)
//Version : 1.0.0

///@Function: xCheckSum_LRC8_Calculate
///@Descript: Compute 8-Bit LRC With Sum Complement(Modbus-Style)
U8 xCheckSum_LRC8_Calculate(U8 *Data,U32 Len)
{
  U16 Result = 0x00;
  if(!Data || Len <= 0)
    return 0x00;
  
  for(U32 i=0;i<Len;i++)
    Result += Data[i];
  return (U8)((0x100-Result) & 0xFF);
}


///@Function: xCheckSum_LRC16_Calculate
///@Descript: Compute 16-Bit LRC With Sum Complement
U16 xCheckSum_LRC16_Calculate(U8 *Data,U32 Len)
{
  U32 Result = 0x0000;
  if(!Data || Len <= 0)
    return 0x0000;
  
  for(U32 i=0;i<Len;i++)
    Result += Data[i];
  
  Result &= 0xFFFF;
  return (U16)((0x10000-Result) & 0xFFFF);
}


///@Function: xCheckSum_LRC32_Calculate
///@Descript: Compute 32-Bit LRC With Sum Complement
U32 xCheckSum_LRC32_Calculate(U8 *Data,U32 Len)
{
  U64 Result = 0x00000000;
  if(!Data || Len <= 0)
    return 0x00000000;

  for(U32 i=0;i<Len;i++)
    Result += Data[i];
  
  Result &= 0xFFFFFFFF;
  return (U32)((0x100000000UL-Result) & 0xFFFFFFFF);
}


///@Function: xCheckSum_LRC8_Verify
///@Descript: Verify 8-Bit LRC With Sum-Zero Validation(LRC + Data = 0)
int xCheckSum_LRC8_Verify(U8 *Data,U32 Len)
{
  U8 Result = 0x00;
  if(!Data || Len <= 0)
    return 0;    

  for(U32 i=0;i<Len;i++)
    Result += Data[i];
  return (Result == 0);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_LRC16_Verify
///@Descript: Verify 16-Bit LRC With Sum-Zero Validation(LRC + Data = 0)
int xCheckSum_LRC16_Verify(U8 *Data,U32 Len)
{
  U16 Result = 0;
  if(!Data || Len <= 2)
    return 0;

  U32 RawLen = Len - 2;
  for(U32 i = 0;i < RawLen;i++)
    Result += Data[i];

  U16 RecvLRC = ((U16)Data[RawLen] << 8) | (U16)Data[RawLen + 1];
  Result += RecvLRC;
  return (Result == 0);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_LRC32_Verify
///@Descript: Verify 32-Bit LRC With Sum-Zero Validation(LRC + Data = 0)
int xCheckSum_LRC32_Verify(U8 *Data,U32 Len)
{
  U32 Result = 0x00000000;
  if(!Data || Len < 4)
    return 0;

  U32 RawLen = Len - 4;
  for(U32 i = 0;i < RawLen;i++)
    Result += Data[i];

  U32 RecvCheckSum = ((U32)Data[RawLen]  <<24)|((U32)Data[RawLen+1]<<16) |
                     ((U32)Data[RawLen+2]<<8) |((U32)Data[RawLen+3]);
  Result += RecvCheckSum;
  return (Result == 0);   //[1]:OK [0]:Fail
}