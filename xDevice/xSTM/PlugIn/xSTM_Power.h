#ifndef __XSTM_POWER_H__  //__XSTM_POWER_H__
#define __XSTM_POWER_H__  //__XSTM_POWER_H__

//Author  : William Hsiao
//Descript: STM32 Power Mode Utility
//Version : 1.0.0

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xSTM_Config.h"

#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Mode
void xSTM_Power_Sleep(void);                                             //Enter Sleep Mode
void xSTM_Power_Stop(void);                                              //Enter Stop Mode
void xSTM_Power_Standby(void);                                           //Enter Standby Mode

//Clock
U32  xSTM_Power_SetClock(U32 Freq);                                      //Set Target HCLK(Hz)
U32  xSTM_Power_RestoreClock(void);                                      //Restore Saved HCLK Divider

#ifdef __cplusplus
}
#endif

#endif  //__XSTM_POWER_H__
