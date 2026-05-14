//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xCheckSum.h"

//Main Code
int main(void)
{
  U8 Data1[] = "123456789";
  U32 Len1 = strlen((char*)Data1);

  U8  L8  = xCheckSum_LRC8_Calculate (Data1,Len1);    //0x23   (https://www.lddgo.net/en/encrypt/lrc)
  U16 L16 = xCheckSum_LRC16_Calculate(Data1,Len1);
  U32 L32 = xCheckSum_LRC32_Calculate(Data1,Len1);

  U8 *Out8  = (U8*)malloc(Len1+1);
  U8 *Out16 = (U8*)malloc(Len1+2);
  U8 *Out32 = (U8*)malloc(Len1+4);

  MEMCOPY(Out8, Data1,Len1);
  MEMCOPY(Out16,Data1,Len1);
  MEMCOPY(Out32,Data1,Len1);

  Out8[Len1]    = L8;

  Out16[Len1]   = (U8)(L16 >> 8);
  Out16[Len1+1] = (U8)(L16 & 0xFF);

  Out32[Len1]   = (U8)(L32 >> 24);
  Out32[Len1+1] = (U8)(L32 >> 16);
  Out32[Len1+2] = (U8)(L32 >> 8);
  Out32[Len1+3] = (U8)(L32 & 0xFF);

  int V8  = xCheckSum_LRC8_Verify (Out8, Len1 + 1);
  int V16 = xCheckSum_LRC16_Verify(Out16,Len1 + 2);
  int V32 = xCheckSum_LRC32_Verify(Out32,Len1 + 4);

  printf("LRC-8  : 0x%02X (Check:%d)\n",L8, V8);
  printf("LRC-16 : 0x%04X (Check:%d)\n",L16,V16);
  printf("LRC-32 : 0x%08X (Check:%d)\n",L32,V32);

  SAFE_DESTROY(Out8);
  SAFE_DESTROY(Out16);
  SAFE_DESTROY(Out32);
  return 0;
}