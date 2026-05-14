#ifndef __XLRC_H__ //__XLRC_H__
#define __XLRC_H__ //__XLRC_H__

//Author  : William Hsiao
//Descript: Data Validation Library for Embedded Systems(LRC)
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
//LRC Calculate
U8  xCheckSum_LRC8_Calculate (U8 *Data,U32 Len);
U16 xCheckSum_LRC16_Calculate(U8 *Data,U32 Len);
U32 xCheckSum_LRC32_Calculate(U8 *Data,U32 Len);

//LRC Verify
int xCheckSum_LRC8_Verify (U8 *Data,U32 Len);
int xCheckSum_LRC16_Verify(U8 *Data,U32 Len);
int xCheckSum_LRC32_Verify(U8 *Data,U32 Len);

#ifdef __cplusplus
}
#endif

#endif  //__XLRC_H__
