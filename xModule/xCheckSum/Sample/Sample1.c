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

  //Fletcher
  U8  C21 = xCheckSum_Fletcher8_Calculate (Data1,Len1);   //0C        (https://tool.idocdown.com/hashing/fletcher-8-checksum/)
  U16 C22 = xCheckSum_Fletcher16_Calculate(Data1,Len1);   //1EDE      (https://tool.idocdown.com/hashing/fletcher-16-checksum/)
  U32 C23 = xCheckSum_Fletcher32_Calculate(Data1,Len1);   //DF09D509  (https://tool.idocdown.com/hashing/fletcher-32-checksum/)

  U8 *Out21 = (U8*)malloc(Len1 + 1);
  U8 *Out22 = (U8*)malloc(Len1 + 2);
  U8 *Out23 = (U8*)malloc(Len1 + 4);

  MEMCOPY(Out21,Data1,Len1);
  MEMCOPY(Out22,Data1,Len1);
  MEMCOPY(Out23,Data1,Len1);

  Out21[Len1]   = C21;
  
  Out22[Len1]   = (U8)(C22 >> 8);
  Out22[Len1+1] = (U8)(C22 & 0xFF);

  Out23[Len1]   = (U8)(C23 >> 24);
  Out23[Len1+1] = (U8)(C23 >> 16);
  Out23[Len1+2] = (U8)(C23 >> 8);
  Out23[Len1+3] = (U8)(C23 & 0xFF);
  int V21 = xCheckSum_Fletcher8_Verify (Out21,Len1+1);
  int V22 = xCheckSum_Fletcher16_Verify(Out22,Len1+2);
  int V23 = xCheckSum_Fletcher32_Verify(Out23,Len1+4);
  printf("Fletcher-8  : 0x%X (Check:%d)\n",C21,V21);
  printf("Fletcher-16 : 0x%X (Check:%d)\n",C22,V22);
  printf("Fletcher-32 : 0x%X (Check:%d)\n",C23,V23);

  SAFE_DESTROY(Out21);
  SAFE_DESTROY(Out22);
  SAFE_DESTROY(Out23);

  //Adler
  U32 C31 = xCheckSum_Adler32_Calculate(Data1,Len1);      //09E01DE   (https://tool.idocdown.com/hashing/adler-32-checksum/)

  U8 *Out31 = (U8*)malloc(Len1 + 4);
  MEMCOPY(Out31,Data1,Len1);
  Out31[Len1]   = (U8)(C31 >> 24);
  Out31[Len1+1] = (U8)(C31 >> 16);
  Out31[Len1+2] = (U8)(C31 >> 8);
  Out31[Len1+3] = (U8)(C31 & 0xFF);
  int V31 = xCheckSum_Adler32_Verify(Out31,Len1+4);
  printf("Adler-32    : 0x%X (Check:%d)\n",C31,V31);

  SAFE_DESTROY(Out31);

  //Complete
  U8  C41 = xCheckSum_Comp8_Calculate (Data1,Len1);       //UnVerified
  U16 C42 = xCheckSum_Comp16_Calculate(Data1,Len1);       //UnVerified
  U32 C43 = xCheckSum_Comp32_Calculate(Data1,Len1);       //UnVerified

  U8 *Out41 = (U8*)malloc(Len1 + 1);
  U8 *Out42 = (U8*)malloc(Len1 + 2);
  U8 *Out43 = (U8*)malloc(Len1 + 4);

  MEMCOPY(Out41,Data1,Len1);
  MEMCOPY(Out42,Data1,Len1);
  MEMCOPY(Out43,Data1,Len1);

  Out41[Len1]   = C41;
  
  Out42[Len1]   = (U8)(C42 >> 8);
  Out42[Len1+1] = (U8)(C42 & 0xFF);

  Out43[Len1]   = (U8)(C43 >> 24);
  Out43[Len1+1] = (U8)(C43 >> 16);
  Out43[Len1+2] = (U8)(C43 >> 8);
  Out43[Len1+3] = (U8)(C43 & 0xFF);

  int V41 = xCheckSum_Comp8_Verify (Out41,Len1+1);
  int V42 = xCheckSum_Comp16_Verify(Out42,Len1+2);
  int V43 = xCheckSum_Comp32_Verify(Out43,Len1+4);
  printf("Comp'2s-8   : 0x%X (Check:%d)\n",C41,V41);
  printf("Comp'2s-16  : 0x%X (Check:%d)\n",C42,V42);
  printf("Comp'2s-32  : 0x%X (Check:%d)\n",C43,V43);

  SAFE_DESTROY(Out41);
  SAFE_DESTROY(Out42);
  SAFE_DESTROY(Out43);
  return 0;
}
