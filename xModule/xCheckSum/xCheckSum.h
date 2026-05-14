#ifndef __XCHECKSUM_H__ //__XCHECKSUM_H__
#define __XCHECKSUM_H__ //__XCHECKSUM_H__

//Author  : William Hsiao
//Descript: Data Validation Library for Embedded Systems
//Version : 1.0.0

//[Config Declare]
#define xCHECKSUM_SUPPORT_LRC         1           //Support LRC
#define xCHECKSUM_SUPPORT_BCC         1           //Support BCC
#define xCHECKSUM_SUPPORT_CRC         1           //Support CRC

//[STD Lib Include]
#include <stdio.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

#if xCHECKSUM_SUPPORT_LRC
  #include "xCheckSum_LRC.h"
#endif

#if xCHECKSUM_SUPPORT_BCC
  #include "xCheckSum_BCC.h"
#endif

#if xCHECKSUM_SUPPORT_CRC
  #include "xCheckSum_CRC.h"
#endif

//[Macro Declare]
#define xCHECKSUM_ADLER_MOD       65521       //Adler-32 MOD


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Fletcher
U8  xCheckSum_Fletcher8_Calculate (U8 *Data,U32 Len);
U16 xCheckSum_Fletcher16_Calculate(U8 *Data,U32 Len);
U32 xCheckSum_Fletcher32_Calculate(U8 *Data,U32 Len);

int xCheckSum_Fletcher8_Verify (U8 *Data,U32 Len);
int xCheckSum_Fletcher16_Verify(U8 *Data,U32 Len);
int xCheckSum_Fletcher32_Verify(U8 *Data,U32 Len);

//Adler
U32 xCheckSum_Adler32_Calculate(U8 *Data,U32 Len);
int xCheckSum_Adler32_Verify   (U8 *Data,U32 Len);

//2S
U8  xCheckSum_Comp8_Calculate (U8 *Data,U32 Len);
U16 xCheckSum_Comp16_Calculate(U8 *Data,U32 Len);
U32 xCheckSum_Comp32_Calculate(U8 *Data,U32 Len);

int xCheckSum_Comp8_Verify (U8 *Data,U32 Len);
int xCheckSum_Comp16_Verify(U8 *Data,U32 Len);
int xCheckSum_Comp32_Verify(U8 *Data,U32 Len);

#ifdef __cplusplus
}
#endif

#endif  //__XCHECKSUM_H__
