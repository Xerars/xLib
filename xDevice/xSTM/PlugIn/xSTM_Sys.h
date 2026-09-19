#ifndef __XSTM_SYS_H__  //__XSTM_SYS_H__
#define __XSTM_SYS_H__  //__XSTM_SYS_H__

//Author  : William Hsiao
//Descript: STM32 CPU and Reset System Utility
//Version : 1.0.0

//[STD Lib Include]
#include <stdio.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xSTM_Config.h"

//[Macro Declare]
//Reset Reason
#define xSTM_RESET_REASON_NONE           0x00000000UL                     //No Reset Flag
#define xSTM_RESET_REASON_LOW_POWER      0x00000001UL                     //Low Power Reset
#define xSTM_RESET_REASON_WINDOW_WDT     0x00000002UL                     //Window Watchdog Reset
#define xSTM_RESET_REASON_INDEPEND_WDT   0x00000004UL                     //Independent Watchdog Reset
#define xSTM_RESET_REASON_SOFTWARE       0x00000008UL                     //Software Reset
#define xSTM_RESET_REASON_POWER_ON       0x00000010UL                     //Power On Reset
#define xSTM_RESET_REASON_PIN            0x00000020UL                     //Reset Pin Reset
#define xSTM_RESET_REASON_BROWN_OUT      0x00000040UL                     //Brown Out Reset

//Support
#define xSTM_SYS_SUPPORT_UNIT_TEST       1                                //Build SYS Unit Test When Enabled


//[Struct Declare]
typedef struct _xSTM_SYS_Clock_Info
{
  U32 SYSCLK;                            //System Clock(Hz)
  U32 HCLK;                              //AHB  Clock(Hz)
  U32 PCLK1;                             //APB1 Clock(Hz)
  U32 PCLK2;                             //APB2 Clock(Hz)
} xSTM_SYS_Clock_Info;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//CPU
void xSTM_SYS_GetUID(U32 UID[3]);                                         //Get 96-Bit Unique ID
U32  xSTM_SYS_GetCPUID(void);                                             //Get CPU ID Register
U32  xSTM_SYS_GetVer(void);                                               //Get CPU Revision

//Device
U32  xSTM_SYS_GetDeviceID(void);                                          //Get STM32 Device ID
U32  xSTM_SYS_GetDevVer(void);                                            //Get STM32 Device Revision

//Reset
U32  xSTM_SYS_GetReason(void);                                            //Get   Reset Reason Flags
void xSTM_SYS_ClearReason(void);                                          //Clear Reset Reason Flags
void xSTM_SYS_SoftReset(void);                                            //Trigger Software Reset

//System
U32  xSTM_SYS_GetTick(void);                                              //Get System Tick(MS)
void xSTM_SYS_Delay(U32 Tick);                                            //Delay System Tick(MS)
void xSTM_SYS_GetClockInfo(xSTM_SYS_Clock_Info *ClockInfo);               //Get System Clock Info
U32  xSTM_SYS_GetBootAddress(void);                                       //Get Vector Table Address

//Unit Test
#if xSTM_SYS_SUPPORT_UNIT_TEST
void xSTM_TEST_SYS(void);                                                 //Run SYS Unit Test
#endif

#ifdef __cplusplus
}
#endif

#endif  //__XSTM_SYS_H__
