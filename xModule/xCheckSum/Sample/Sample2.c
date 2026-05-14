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
  U32 Len1 = sizeof(Data1) - 1;
  //(https://www.scadacore.com/tools/programming-calculators/online-checksum-calculator/)
  //BCC-8 XOR
  U8 *Out1 = (U8*)malloc(Len1 + 1);
  if(Out1)
  {
    U8 B8X = xCheckSum_BCC8_XOR_Calculate(Data1,Len1);
    MEMCOPY(Out1,Data1,Len1);
    Out1[Len1] = B8X;
    int V8X = xCheckSum_BCC8_XOR_Verify(Out1,Len1+1);
    printf("BCC-8 XOR    : 0x%02X (Check:%d)\n",B8X,V8X);
    SAFE_DESTROY(Out1);
  }

  //BCC-8 SUM
  U8 *Out2 = (U8*)malloc(Len1 + 1);
  if(Out2)
  {
    U8 B8S = xCheckSum_BCC8_SUM_Calculate(Data1,Len1);
    MEMCOPY(Out2,Data1,Len1);
    Out2[Len1] = B8S;
    int V8S = xCheckSum_BCC8_SUM_Verify(Out2,Len1+1);
    printf("BCC-8 SUM    : 0x%02X (Check:%d)\n",B8S,V8S);
    SAFE_DESTROY(Out2);
  }

  //BCC-16 XOR
  U8 *Out3 = (U8*)malloc(Len1 + 2);
  if(Out3)
  {
    U16 B16X = xCheckSum_BCC16_XOR_Calculate(Data1,Len1);
    MEMCOPY(Out3,Data1,Len1);
    Out3[Len1]   = (U8)(B16X >> 8);
    Out3[Len1+1] = (U8)(B16X & 0xFF);
    int V16X = xCheckSum_BCC16_XOR_Verify(Out3,Len1+2);
    printf("BCC-16 XOR   : 0x%04X (Check:%d)\n",B16X,V16X);
    SAFE_DESTROY(Out3);
  }

  //BCC-16 SUM
  U8 *Out4 = (U8*)malloc(Len1 + 2);
  if(Out4)
  {
    U16 B16S = xCheckSum_BCC16_SUM_Calculate(Data1,Len1);
    MEMCOPY(Out4,Data1,Len1);
    Out4[Len1]   = (U8)(B16S >> 8);
    Out4[Len1+1] = (U8)(B16S & 0xFF);
    int V16S = xCheckSum_BCC16_SUM_Verify(Out4,Len1+2);
    printf("BCC-16 SUM   : 0x%04X (Check:%d)\n",B16S,V16S);
    SAFE_DESTROY(Out4);
  }

  //BCC-32 XOR
  U8 *Out5 = (U8*)malloc(Len1 + 4);
  if(Out5)
  {
    U32 B32X = xCheckSum_BCC32_XOR_Calculate(Data1,Len1);
    MEMCOPY(Out5,Data1,Len1);
    Out5[Len1]   = (U8)(B32X >> 24);
    Out5[Len1+1] = (U8)(B32X >> 16);
    Out5[Len1+2] = (U8)(B32X >> 8);
    Out5[Len1+3] = (U8)(B32X & 0xFF);
    int V32X = xCheckSum_BCC32_XOR_Verify(Out5,Len1+4);
    printf("BCC-32 XOR   : 0x%08X (Check:%d)\n",B32X,V32X);
    SAFE_DESTROY(Out5);
  }

  //BCC-32 SUM
  U8 *Out6 = (U8*)malloc(Len1 + 4);
  if(Out6)
  {
    U32 B32S = xCheckSum_BCC32_SUM_Calculate(Data1,Len1);
    MEMCOPY(Out6,Data1,Len1);
    Out6[Len1]   = (U8)(B32S >> 24);
    Out6[Len1+1] = (U8)(B32S >> 16);
    Out6[Len1+2] = (U8)(B32S >> 8);
    Out6[Len1+3] = (U8)(B32S & 0xFF);
    int V32S = xCheckSum_BCC32_SUM_Verify(Out6,Len1+4);
    printf("BCC-32 SUM   : 0x%08X (Check:%d)\n",B32S,V32S);
    SAFE_DESTROY(Out6);
  }
  return 0;
}