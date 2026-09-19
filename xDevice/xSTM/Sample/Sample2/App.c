//Demo xSTM_DWT Delay, Time, Performance, Timer Event and Unit Test

//[App Include]
#include "App.h"

//[xLib Include]
#include "xSTM.h"

//[Prototype Declare]
static void App_DWT_TimerEvent(void);


///@Function: App_Init
///@Descript: Initialize xSTM DWT Sample and Run Unit Test
void App_Init(void)
{
  printf("\r\n[xSTM DWT Sample]: Start\r\n");
  xSTM_DWT_Init();

  //Unit Test
  xSTM_TEST_DWT();
	
  //Delay
  xSTM_DWT_DelayCycle(5);
  xSTM_DWT_DelayUS(1);
  xSTM_DWT_Delay10US(1);
  xSTM_DWT_DelayMS(1);

  //Time
  U32 Cycle  = xSTM_DWT_GetCycle();
  U32 TimeUS = xSTM_DWT_GetUS();
  printf("[Time]: %d Cycle, %d us\r\n",Cycle,TimeUS);

  //Perf Macro
  xSTM_DWT_PERF_START(Sample);
  xSTM_DWT_DelayUS(10);
  U32 PerfUS = xSTM_DWT_PERF_FINISH(Sample);
  printf("[Perf Macro]: %d us\r\n",PerfUS);

  printf("[xSTM DWT Sample]: Init Finish\r\n");
}


///@Function: App_Service
///@Descript: Process xSTM DWT Timer Event and Timer Macro
void App_Service(void)
{
  //Timer Event
  xSTM_DWT_TimerEvent(1000,xSTM_DWT_EVENT_PERIOD,App_DWT_TimerEvent);

  //Timer Macro
  xSTM_DWT_TIMER_START(Service,2000)
    printf("[Timer Macro]: 2000 ms\r\n");
  xSTM_DWT_TIMER_FINISH();
}


///@Function: App_DWT_TimerEvent
///@Descript: Print DWT Timer Event Message
static void App_DWT_TimerEvent(void)
{
  static U32 Count = 0;
  Count++;
  printf("[Timer Event]: %d\r\n",Count);
}
