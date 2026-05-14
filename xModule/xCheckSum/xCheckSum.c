//[xLib Include]
#include "xCheckSum.h"

//Author  : William Hsiao
//Descript: Data Validation Library for Embedded Systems
//Version : 1.0.0

///@Function: xCheckSum_Fletcher8_Calculate
///@Descript: Calculate 8-Bit Fletcher CheckSum
U8 xCheckSum_Fletcher8_Calculate(U8 *Data,U32 Len)
{
  U8 Sum1 = 0;
  U8 Sum2 = 0;
  for(U32 i=0;i<Len;i++)
  {
    Sum1 = (Sum1 + Data[i]) % 15;
    Sum2 = (Sum2 + Sum1) % 15;
  }
  return (U8)((Sum2 << 4) | Sum1);
}


///@Function: xCheckSum_Fletcher16_Calculate
///@Descript: Calculate 16-Bit Fletcher CheckSum
U16 xCheckSum_Fletcher16_Calculate(U8 *Data,U32 Len)
{
  U16 Sum1 = 0;
  U16 Sum2 = 0;
  for(U32 i=0;i<Len;i++)
  {
    Sum1 = (Sum1 + (Data[i])) % 255;
    Sum2 = (Sum2 + Sum1) % 255;
  }
  return (U16)((Sum2 << 8) | Sum1);
}


///@Function: xCheckSum_Fletcher32_Calculate
///@Descript: Calculate 32-Bit Fletcher CheckSum
U32 xCheckSum_Fletcher32_Calculate(U8 *Data,U32 Len)
{
  U32 Sum1 = 0;
  U32 Sum2 = 0;
  U32 i;

  if(!Data || Len == 0)
    return 0;

  for(i = 0;i < (Len & ~1);i += 2)
  {
    U16 Data16 = (U16)(Data[i] | (Data[i+1] << 8));
    Sum1 = (Sum1 + Data16) % 65535;
    Sum2 = (Sum2 + Sum1)   % 65535;
  }

  if(Len & 1)
  {
    U16 Data16 = (U16)Data[i]; 
    Sum1 = (Sum1 + Data16) % 65535;
    Sum2 = (Sum2 + Sum1)   % 65535;
  }
  return (U32)((Sum2 << 16) | Sum1);
}


///@Function: xCheckSum_Fletcher8_Verify
///@Descript: Re-Calculate 8-Bit CheckSum With the Provided Value
int xCheckSum_Fletcher8_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 1)
    return 0;
  U32 RawLen = Len - 1;
  U8  Recv   = Data[RawLen];
  U8  Calc   = xCheckSum_Fletcher8_Calculate(Data,RawLen);
  return (Calc == Recv);
}


///@Function: xCheckSum_Fletcher16_Verify
///@Descript: Re-Calculate 16-Bit CheckSum With the Provided Value
int xCheckSum_Fletcher16_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 2)
    return 0;
  U32 RawLen = Len - 2;
  U16 Recv   = ((U16)Data[RawLen] << 8) | (U16)Data[RawLen + 1];
  U16 Calc   = xCheckSum_Fletcher16_Calculate(Data,RawLen);
  return (Calc == Recv);
}


///@Function: xCheckSum_Fletcher32_Verify
///@Descript: Re-Calculate 32-Bit CheckSum With the Provided Value
int xCheckSum_Fletcher32_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 4)
    return 0;
  U32 RawLen = Len - 4;
  U32 Recv   = ((U32)Data[RawLen]  <<24)|((U32)Data[RawLen+1]<<16) |
               ((U32)Data[RawLen+2]<<8) |((U32)Data[RawLen+3]);
  U32 Calc   = xCheckSum_Fletcher32_Calculate(Data,RawLen);

  return (Calc == Recv);
}


///@Function: xCheckSum_Adler32_Calculate
///@Descript: Calculate Adler-32 With Prime Modulo 65521
U32 xCheckSum_Adler32_Calculate(U8 *Data,U32 Len)
{
  U32 S1 = 1;
  U32 S2 = 0;

  if(!Data || Len == 0)
    return 1;
  
  for(U32 i=0;i<Len;i++)
  {
    S1 = (S1 + Data[i]) % xCHECKSUM_ADLER_MOD;
    S2 = (S2 + S1) % xCHECKSUM_ADLER_MOD;
  }
  return (S2 << 16) | S1;
}


///@Function: xCheckSum_Adler32_Verify
///@Descript: Match Data Against a 32-Bit Adler CheckSum
int xCheckSum_Adler32_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len == 0)
    return 0;

  U32 RawDataLen   = Len - 4;
  U32 RecvCheckSum = ((U32)Data[RawDataLen]  <<24) | ((U32)Data[RawDataLen+1]<<16) |
                     ((U32)Data[RawDataLen+2]<<8)  | ((U32)Data[RawDataLen+3]);
  return (xCheckSum_Adler32_Calculate(Data,RawDataLen) == RecvCheckSum);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_Comp8_Calculate
///@Descript: Calculate 2's Complement 8-Bit Sum
U8 xCheckSum_Comp8_Calculate(U8 *Data,U32 Len)
{
  U8 Sum = 0;
  if(!Data || Len == 0)
    return 0;

  for(U32 i=0;i<Len;i++)
    Sum += Data[i];
  return (U8)(~Sum + 1);
}


///@Function: xCheckSum_Comp16_Calculate
///@Descript: Calculate 2's Complement 16-Bit Sum
U16 xCheckSum_Comp16_Calculate(U8 *Data,U32 Len)
{
  U16 Sum = 0;
  if(!Data || Len == 0)
    return 0;

  for(U32 i=0;i<Len;i++)
    Sum += Data[i];
  return (U16)(~Sum + 1);
}


///@Function: xCheckSum_Comp32_Calculate
///@Descript: Calculate 2's Complement 32-Bit Sum
U32 xCheckSum_Comp32_Calculate(U8 *Data,U32 Len)
{
  U32 Sum = 0;
  if(!Data || Len == 0)
    return 0;

  for(U32 i=0;i<Len;i++)
    Sum += Data[i];
  return (U32)(~Sum + 1);
}


///@Function: xCheckSum_Comp8_Verify
///@Descript: Validates If the Total 8-Bit Sum of Data
int xCheckSum_Comp8_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 1)
    return 0;
  
  U32 RawLen = Len - 1;
  U8  Recv   = Data[RawLen];
  U8  Calc   = xCheckSum_Comp8_Calculate(Data,RawLen);
  return (Calc == Recv);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_Comp16_Verify
///@Descript: Validates If the Total 16-Bit Sum of Data
int xCheckSum_Comp16_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 2)
    return 0;
  
  U32 RawLen = Len - 2;
  U16 Recv   = ((U16)Data[RawLen] << 8) | (U16)Data[RawLen + 1];
  U16 Calc   = xCheckSum_Comp16_Calculate(Data,RawLen);
  return (Calc == Recv);   //[1]:OK [0]:Fail
}


///@Function: xCheckSum_Comp32_Verify
///@Descript: Validates If the Total 32-Bit Sum of Data
int xCheckSum_Comp32_Verify(U8 *Data,U32 Len)
{
  if(!Data || Len <= 4)
    return 0;
  
  U32 RawLen = Len - 4;
  U32 Recv = ((U32)Data[RawLen]  <<24) | ((U32)Data[RawLen+1]<<16) |
             ((U32)Data[RawLen+2]<<8)  | ((U32)Data[RawLen+3]);
  U32 Calc = xCheckSum_Comp32_Calculate(Data, RawLen);
  return (Calc == Recv);   //[1]:OK [0]:Fail
}