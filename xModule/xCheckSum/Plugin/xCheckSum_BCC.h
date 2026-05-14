#ifndef __XBCC_H__ //__XBCC_H__
#define __XBCC_H__ //__XBCC_H__

//Author  : William Hsiao
//Descript: Data Validation Library for Embedded Systems(BCC)
//Version : 1.0.0

//[STD Lib Include]
#include <stdio.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//BCC Calculate
U8  xCheckSum_BCC8_XOR_Calculate (U8 *Data,U32 Len);
U8  xCheckSum_BCC8_SUM_Calculate (U8 *Data,U32 Len);
U16 xCheckSum_BCC16_XOR_Calculate(U8 *Data,U32 Len);
U16 xCheckSum_BCC16_SUM_Calculate(U8 *Data,U32 Len);
U32 xCheckSum_BCC32_XOR_Calculate(U8 *Data,U32 Len);
U32 xCheckSum_BCC32_SUM_Calculate(U8 *Data,U32 Len);

//BCC Verify
int xCheckSum_BCC8_XOR_Verify (U8 *Data,U32 Len);
int xCheckSum_BCC8_SUM_Verify (U8 *Data,U32 Len);
int xCheckSum_BCC16_XOR_Verify(U8 *Data,U32 Len);
int xCheckSum_BCC16_SUM_Verify(U8 *Data,U32 Len);
int xCheckSum_BCC32_XOR_Verify(U8 *Data,U32 Len);
int xCheckSum_BCC32_SUM_Verify(U8 *Data,U32 Len);

#ifdef __cplusplus
}
#endif

#endif  //__XBCC_H__
