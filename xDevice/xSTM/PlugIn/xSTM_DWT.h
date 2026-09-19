#ifndef __XSTM_DWT_H__  //__XSTM_DWT_H__
#define __XSTM_DWT_H__  //__XSTM_DWT_H__

//Author  : William Hsiao
//Descript: DWT Cycle Counter Utility for Delay, Performance and Timer Event
//Version : 1.0.0

//[STD Lib Include]
#include <stdio.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xSTM_Config.h"

//[Config Declare]
#define xSTM_DWT_SUPPORT_DEBUG            1                               //Support DWT Debug Information

//[Macro Declare]
//Delay
#define xSTM_DWT_CYCLES_PER_US            (xSTM_DWT_SYS_CLOCK)            //Cycle Count per Microsecond
#define xSTM_DWT_CYCLES_PER_10US          (xSTM_DWT_SYS_CLOCK * 10UL)     //Cycle Count per 10 Microseconds
#define xSTM_DWT_CYCLES_PER_MS            (xSTM_DWT_SYS_CLOCK * 1000UL)   //Cycle Count per Millisecond

//Event
#define xSTM_DWT_EVENT_ONCE               1                               //Execute Event Once
#define xSTM_DWT_EVENT_PERIOD             0                               //Execute Event Periodically

//Support
#define xSTM_DWT_SUPPORT_UNIT_TEST        1                               //Build DWT Unit Test When Enabled


//[Enum Declare]
typedef enum _xSTM_DWT_EVENT_STATE
{
  xSTM_DWT_EVENT_IDLE   = 0,              //Event Idle
  xSTM_DWT_EVENT_WAIT   = 1,              //Event Waiting
  xSTM_DWT_EVENT_FINISH = 2,              //Event Finished
} xSTM_DWT_EVENT_STATE;

//[Callback Function Declare]
typedef void (*xSTM_DWT_Event_CB)(void);

#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Init
void xSTM_DWT_Init(void);                                                 //Initialize DWT Cycle Counter

//Delay
void xSTM_DWT_DelayCycle(U32 Cycle);                                      //Delay in Cycles
void xSTM_DWT_DelayMS   (U32 Tick);                                       //Delay in Milliseconds
void xSTM_DWT_Delay10US (U32 Tick);                                       //Delay in 10 Microsecond Units
void xSTM_DWT_DelayUS   (U32 Tick);                                       //Delay in Microseconds

//Time
U32  xSTM_DWT_GetCycle  (void);                                           //Get Current Cycle Count
U32  xSTM_DWT_GetUS     (void);                                           //Get Current Time(Microsecond)

//Perf
U32  xSTM_DWT_PerfStart (void);                                           //Get Performance Start Cycle
U32  xSTM_DWT_PerfFinish(U32 Start);                                      //Get Elapsed Performance Time in Microseconds

//Event
void xSTM_DWT_TimerEvent(U32 Tick,xBOOL Once,xSTM_DWT_Event_CB CB);       //Process Timer Event in Milliseconds

//Unit Test
#if xSTM_DWT_SUPPORT_UNIT_TEST
void xSTM_TEST_DWT(void);                                                 //Run DWT Unit Test
#endif  //xSTM_DWT_SUPPORT_UNIT_TEST

#ifdef __cplusplus
}
#endif

//[Macro Function Declare]
//Start
#define xSTM_DWT_TIMER_START(NAME,PERIOD_MS)                    \
do                                                              \
{                                                               \
  static U32 xSTM_DWT_LastTick_##NAME = 0;                      \
  U32 xSTM_DWT_CurTick = DWT->CYCCNT;                           \
  if((xSTM_DWT_CurTick - xSTM_DWT_LastTick_##NAME) >=           \
     ((U32)(PERIOD_MS) * xSTM_DWT_CYCLES_PER_MS))               \
  {                                                             \
    xSTM_DWT_LastTick_##NAME = xSTM_DWT_CurTick;

//Finish
#define xSTM_DWT_TIMER_FINISH()                                 \
  }                                                             \
} while(0)

//Perf
#define xSTM_DWT_PERF_START(NAME)          U32 xSTM_DWT_PerfStart_##NAME = xSTM_DWT_PerfStart()
#define xSTM_DWT_PERF_FINISH(NAME)         xSTM_DWT_PerfFinish(xSTM_DWT_PerfStart_##NAME)

#endif  //__XSTM_DWT_H__
