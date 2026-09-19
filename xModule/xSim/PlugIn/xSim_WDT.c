#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE       199309L

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//[POSIX Lib Include]
#include <pthread.h>
#include <unistd.h>

//[xLib Include]
#include "xSim_WDT.h"

//[Prototype Declare]
static void* xSim_WDT_Task(void *Arg);
static U32  _GetSysTick(void);
static void _MutexLock(void);
static void _MutexUnLock(void);

//[Variable Declare]
static xSim_WDT gWDT = {0};
static U32      gWDT_Start = 0;
static pthread_mutex_t gWDT_Mutex = PTHREAD_MUTEX_INITIALIZER;

///@Function: xSim_WDT_Regist
///@Descript: Register and Initialize WDT Parameter With the Given TimeOut
void xSim_WDT_Regist(U32 TimeOut)
{
  _MutexLock();
  gWDT.TimeOut = TimeOut;
  gWDT.Counter = _GetSysTick();
  gWDT.En      = 0;
  gWDT.Exit    = 1;
  _MutexUnLock();
}


///@Function: xSim_WDT_UnRegist
///@Descript: UnRegister the WDT By Disable Its Function
void xSim_WDT_UnRegist(void)
{
  _MutexLock();
  gWDT.En      = 0;
  _MutexUnLock();
}


///@Function: xSim_WDT_Init
///@Descript: Initialize the WDT Background Monitoring Thread
void xSim_WDT_Init(void)
{
  pthread_t       WDT_Task_ID;
  pthread_attr_t  WDT_Attr;

  pthread_attr_init(&WDT_Attr);
  size_t Stack_Size = 20 * 1024;    //20KB
  pthread_attr_setstacksize(&WDT_Attr,Stack_Size);

  int Res = pthread_create(&WDT_Task_ID,&WDT_Attr,xSim_WDT_Task,NULL);
  if(Res == 0)
    pthread_detach(WDT_Task_ID);    //Auto Release
  else
    perror("[WDT]: Failed to Create WatchDog Thread!\n");

  gWDT_Start = _GetSysTick();
  //Destroy Attribute
  pthread_attr_destroy(&WDT_Attr);
}


///@Function: xSim_WDT_Feed
///@Descript: Pet/Feed the Watch Dog to Reset the Timeout Counter
void xSim_WDT_Feed(void)
{
  _MutexLock();
  gWDT.Counter = _GetSysTick();
  _MutexUnLock();
}


///@Function: xSim_WDT_SetTimeOut
///@Descript: Set a New Timeout Value for the Watch Dog
void xSim_WDT_SetTimeOut(U32 TimeOut)
{
  _MutexLock();
  gWDT.TimeOut = TimeOut;
  _MutexUnLock();
}


///@Function: xSim_WDT_SetEn
///@Descript: Enable or Disable the Watch Dog Monitoring
void xSim_WDT_SetEn(U8 En)
{
  _MutexLock();
  gWDT.En = En;
  if(En)
    gWDT.Counter = _GetSysTick();
  _MutexUnLock();
}


///@Function: xSim_WDT_SetExit
///@Descript: Set the Behavior When Timeout Occurs
void xSim_WDT_SetExit(U8 Exit)
{
  _MutexLock();
  gWDT.Exit = Exit;
  _MutexUnLock();
}


///@Function: xSim_WDT_Task
///@Descript: Background Worker Thread that Peridically Check for WDT Timeout
static void* xSim_WDT_Task(void *Arg)
{
  xUNUSED(Arg);
  while(1)
  {
    //Update Parameter
    _MutexLock();
    U8  En      = gWDT.En;
    U32 TimeOut = gWDT.TimeOut; 
    U32 Counter = gWDT.Counter;
    U8  Exit    = gWDT.Exit;
    _MutexUnLock();

    if(En)
    {
      U32 Cur = _GetSysTick();
      if((Cur - Counter) > TimeOut)
      {
        printf("%u::[WDT-1]: Timeout Expired!\n",Cur - gWDT_Start);
        if(Exit == 1)
          exit(EXIT_FAILURE);
        else
          break;
      }
    }
    usleep(1000);   //1ms
  }
  return NULL;
}


///@Function: _GetSysTick
///@Descript: Get the Current System Monotonic Time in ms
static U32 _GetSysTick(void)
{
  struct timespec TS;
  clock_gettime(CLOCK_MONOTONIC, &TS);
  U32 MS = (U32)(TS.tv_sec * 1000) + (U32)(TS.tv_nsec / 1000000);
  return MS;
}


///@Function: _MutexLock
///@Descript: Acquire the WDT Mutex Lock
static void _MutexLock(void)
{
  pthread_mutex_lock(&gWDT_Mutex);
}


///@Function: _MutexUnLock
///@Descript: Release the WDT Mutex Lock
static void _MutexUnLock(void)
{
  pthread_mutex_unlock(&gWDT_Mutex);
}