#define _POSIX_C_SOURCE 200809L

//[STD Lib Inlcude]
#include <stdio.h>
#include <time.h>

//[POSIX Lib Include]
#include <unistd.h>

//[xLib Include]
#include "xSim_Timer.h"

//[Prototype Declare]
static void* xSim_Timer_Task(void *Arg);
static U32   _GetSysTick(void);

//[Variable Declare]
static xSim_Timer gTimer = {0};
static U32        gSysStart = 0;

///@Function: xSim_DelayUS
///@Descript: Delay for Specified MicroSeconds(us)
void xSim_DelayUS(U32 Tick)
{
  if(Tick == 0)
    return;

  struct timespec TS;
  TS.tv_sec  = Tick / 1000000;
  TS.tv_nsec = (Tick % 1000000) * 1000;
  nanosleep(&TS,NULL);
}


///@Function: xSim_DelayMS
///@Descript: Delay for Specific MilliSeconds(ms)
void xSim_DelayMS(U32 Tick)
{
  if(Tick == 0)
    return;

  struct timespec TS;
  TS.tv_sec  = Tick / 1000;
  TS.tv_nsec = (Tick % 1000) * 1000000;
  nanosleep(&TS,NULL);
}


///@Function: xSim_Delay
///@Descript: Delay for Specified Seconds(s)
void xSim_Delay(U32 Tick)
{
  if(Tick == 0)
    return;

  struct timespec TS;
  TS.tv_sec  = Tick;
  TS.tv_nsec = 0;
  nanosleep(&TS,NULL);
}


///@Function: xSim_Timer_Regist
///@Descript: Regist the Tick Callback Function
void xSim_Timer_Regist(xSim_Timer_CB CB)
{
  gTimer.CB = CB;
}


///@Function: xSim_Timer_UnRegist
///@Descript: UnRegist/Remove the Tick Callback Function
void xSim_Timer_UnRegist(void)
{
  gTimer.CB = NULL;
}


///@Function: xSim_Timer_Init
///@Descript: Initialize Timer Thread Run Every 1MS
void xSim_Timer_Init(void)
{
  if(gTimer.Inited == 0)
  {
    gTimer.CB    = NULL;
    gTimer.IsRun = 1;

    pthread_attr_t Attr;
    pthread_attr_init(&Attr);
    pthread_attr_setdetachstate(&Attr,PTHREAD_CREATE_DETACHED);
    int Ret = pthread_create(&gTimer.TaskID,&Attr,xSim_Timer_Task,NULL);
    if(Ret != 0)
    {
      perror("xSim_Timer: Create Thread Failed!!\n");
      return;
    }
    pthread_attr_destroy(&Attr);
    gTimer.Inited = 1;
  }
}



///@Function: xSim_Timer_Task
///@Descript: Background Thread Running Every 1ms Precisely
static void* xSim_Timer_Task(void *Arg)
{
  xUNUSED(Arg);

  struct timespec Next;
  struct timespec Interval;

  Interval.tv_sec  = 0;
  Interval.tv_nsec = 1000000L;    //1ms
  clock_gettime(CLOCK_MONOTONIC,&Next);
  while(gTimer.IsRun)
  {
    Next.tv_nsec += Interval.tv_nsec;
    if(Next.tv_nsec >= 1000000000L)
    {
      Next.tv_sec  += 1;
      Next.tv_nsec -= 1000000000L;
    }

    clock_nanosleep(CLOCK_MONOTONIC,TIMER_ABSTIME,&Next,NULL);
    if(gTimer.CB != NULL)
      gTimer.CB();
  }
  return NULL;
}



///@Function: xSim_SysTick_Init
///@Descript: Initialize  System Tick Base Time
void xSim_SysTick_Init(void)
{
  gSysStart = _GetSysTick();
}


///@Function: xSim_GetSysTick
///@Descript: Get Elapsed Tick(ms) Since Initial Was Called
U32 xSim_GetSysTick(void)
{
  U32 Cur = _GetSysTick();
  if((Cur >= gSysStart) && (gSysStart != 0))
    return Cur - gSysStart;
  else
    return (0xFFFFFFFF - gSysStart) + Cur + 1;
}


///@Function: _GetSysTick
///@Descript: Get System Tick(ms)
static U32 _GetSysTick(void)
{
  struct timespec TS;
  clock_gettime(CLOCK_MONOTONIC,&TS);
  return (U32)(TS.tv_sec * 1000 + TS.tv_nsec / 1000000);
}