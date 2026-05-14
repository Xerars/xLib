//[xLib Include]
#include "xCheckSum_BCC.h"

//Author  : William Hsiao
//Descript: Data Validation Library for Embedded Systems(BCC)
//Version : 1.0.0

///@Function: xCheckSum_BCC8_XOR_Calculate
///@Descript: Compute 8-Bit XOR Based Block CheckSum
U8 xCheckSum_BCC8_XOR_Calculate(U8 *Data,U32 Len)
{
  U8 Result = 0x00;
  if(!Data || Len == 0)
    return 0x00;
  
  for(U32 i=0;i<Len;i++)
    Result ^= Data[i];
  return Result;
}


///@Function: xCheckSum_BCC8_SUM_Calculate
///@Descript: Compute 8-Bit SUM Based Block CheckSum
U8 xCheckSum_BCC8_SUM_Calculate(U8 *Data,U32 Len)
{
  U8 Result = 0x00;
  if(!Data || Len == 0)
    return 0x00;

  for(U32 i=0;i<Len;i++)
    Result += Data[i];
  return (U8)(Result & 0xFF);
}


///@Function: xCheckSum_BCC16_XOR_Calculate
///@Descript: Compute 16-Bit XOR Based Block CheckSum
U16 xCheckSum_BCC16_XOR_Calculate(U8 *Data,U32 Len)
{
  U32 Result = 0x0000;
  if(!Data || Len == 0)
    return 0x0000;
  
  for(U32 i=0;i<Len;i++)
    Result ^= (U16)Data[i];
  return Result;
}


///@Function: xCheckSum_BCC16_SUM_Calculate
///@Descript: Compute 16-Bit SUM Based Block CheckSum
U16 xCheckSum_BCC16_SUM_Calculate(U8 *Data,U32 Len)
{
  U32 Result = 0x0000;
  if(!Data || Len == 0)
    return 0x0000;

  for(U32 i=0;i<Len;i++)
    Result += Data[i];
  return (U16)(Result & 0xFFFF);
}


///@Function: xCheckSum_BCC32_XOR_Calculate
///@Descript: Compute 32-Bit XOR Based Block CheckSum
U32 xCheckSum_BCC32_XOR_Calculate(U8 *Data,U32 Len)
{
  U64 Result = 0x00000000;
  if(!Data || Len == 0)
    return 0x00000000;
  
  for(U32 i=0;i<Len;i++)
    Result ^= (U32)Data[i];
  return Result;
}


///@Function: xCheckSum_BCC32_SUM_Calculate
///@Descript: Compute 32-Bit SUM Based Block CheckSum
U32 xCheckSum_BCC32_SUM_Calculate(U8 *Data,U32 Len)
{
  U64 Result = 0x00000000;
  if(!Data || Len == 0)
    return 0x00000000;

  for(U32 i=0;i<Len;i++)
    Result += Data[i];
  return (U16)(Result & 0xFFFF);
}


///@Function: xCheckSum_BCC8_XOR_Verify
///@Descript: Verify 8-Bit XOR BCC By ReComputation
int xCheckSum_BCC8_XOR_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 1)
    return 0;

  U8 Recv = Data[Len-1];
  U8 Calc = xCheckSum_BCC8_XOR_Calculate(Data,Len-1);
  return (Recv == Calc);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_BCC8_SUM_Verify
///@Descript: Verify 8-Bit SUM BCC By ReComputation
int xCheckSum_BCC8_SUM_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 1)
    return 0;

  U8 Recv = Data[Len-1];
  U8 Calc = xCheckSum_BCC8_SUM_Calculate(Data,Len-1);
  return (Recv == Calc);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_BCC16_XOR_Verify
///@Descript: Verify 16-Bit XOR BCC By ReComputation
int xCheckSum_BCC16_XOR_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 2)
    return 0;

  U16 Recv = ((U16)Data[Len-2] << 8) | (U16)Data[Len-1];
  U16 Calc = xCheckSum_BCC16_XOR_Calculate(Data,Len-2);
  return (Recv == Calc);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_BCC16_SUM_Verify
///@Descript: Verify 16-Bit SUM BCC By ReComputation
int xCheckSum_BCC16_SUM_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 2)
    return 0;

  U16 Recv = ((U16)Data[Len-2] << 8) | (U16)Data[Len-1];
  U16 Calc = xCheckSum_BCC16_SUM_Calculate(Data,Len-2);
  return (Recv == Calc);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_BCC32_XOR_Verify
///@Descript: Verify 32-Bit XOR BCC By ReComputation
int xCheckSum_BCC32_XOR_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 4)
    return 0;

  U32 Recv = ((U32)Data[Len-4] << 24) | ((U32)Data[Len-3] << 16) |
             ((U32)Data[Len-2] <<  8) | ((U32)Data[Len-1]);
  U32 Calc = xCheckSum_BCC32_XOR_Calculate(Data,Len-4);
  return (Recv == Calc);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_BCC32_SUM_Verify
///@Descript: Verify 32-Bit SUM BCC By ReComputation
int xCheckSum_BCC32_SUM_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 4)
    return 0;

  U32 Recv = ((U32)Data[Len-4] << 24) | ((U32)Data[Len-3] << 16) |
             ((U32)Data[Len-2] <<  8) | ((U32)Data[Len-1]);
  U32 Calc = xCheckSum_BCC32_SUM_Calculate(Data,Len-4);
  return (Recv == Calc);   //[1]:OK [0]:Fail
}