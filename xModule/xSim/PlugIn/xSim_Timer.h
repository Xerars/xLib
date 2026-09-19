#ifndef __XSIM_TIMER_H__  //__XSIM_TIMER_H__
#define __XSIM_TIMER_H__  //__XSIM_TIMER_H__

//[POSIX Lib Include]
#include <pthread.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
#define xSIM_TIMER_MAX        16        //Max Num of Timer

//[Callback Function Declare]
typedef void (*xSim_Timer_CB)(void);

//[Struct Declare]
typedef struct _xSim_Timer
{
  xSim_Timer_CB         CB;             //Callback Function
  U8                    IsRun;          //Is Run
  pthread_t             TaskID;         //Task ID
  U8                    Inited;         //Inited
} xSim_Timer;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Delay
void xSim_DelayUS(U32 Tick);
void xSim_DelayMS(U32 Tick);
void xSim_Delay(U32 Tick);

//Timer
void xSim_Timer_Regist(xSim_Timer_CB CB);
void xSim_Timer_UnRegist(void);
void xSim_Timer_Init(void);

//SysTick
void xSim_SysTick_Init(void);
U32  xSim_GetSysTick(void);

#ifdef __cplusplus
}
#endif

#endif  //__XSIM_TIMER_H__
