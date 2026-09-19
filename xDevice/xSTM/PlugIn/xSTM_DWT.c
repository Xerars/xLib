//[xLib Include]
#include "xSTM_DWT.h"

//Author  : William Hsiao
//Descript: DWT Cycle Counter Utility for Delay, Performance and Timer Event.
//Version : 1.0.0


///@Function: xSTM_DWT_Init
///@Descript: Initialize DWT Cycle Counter for High-Precision Timing
void xSTM_DWT_Init(void)
{
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;   //Enable ARM Trace Module
  DWT->CYCCNT       = 0;                            //Clear Cycle Count Register
  DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;       //Enable DWT Cycle Counter
}


///@Function: xSTM_DWT_DelayCycle
///@Descript: Delay in Cycles Using DWT Cycle Counter
void xSTM_DWT_DelayCycle(U32 Cycle)
{
  U32 Start = DWT->CYCCNT;
  while((DWT->CYCCNT - Start) < Cycle);
}

///@Function: xSTM_DWT_DelayMS
///@Descript: Delay in Milliseconds Using DWT Cycle Counter
void xSTM_DWT_DelayMS(U32 Tick)
{
  U32 Start  = DWT->CYCCNT;                         //Get Current Counter
  U32 Period = Tick * xSTM_DWT_CYCLES_PER_MS;
  while((DWT->CYCCNT - Start) < Period);
}


///@Function: xSTM_DWT_Delay10US
///@Descript: Delay in 10 Microsecond Units Using DWT Cycle Counter
void xSTM_DWT_Delay10US(U32 Tick)
{
  U32 Start  = DWT->CYCCNT;                         //Get Current Counter
  U32 Period = Tick * xSTM_DWT_CYCLES_PER_10US;
  while((DWT->CYCCNT - Start) < Period);
}


///@Function: xSTM_DWT_DelayUS
///@Descript: Delay in Microseconds Using DWT Cycle Counter
void xSTM_DWT_DelayUS(U32 Tick)
{
  U32 Start  = DWT->CYCCNT;                         //Get Current Counter
  U32 Period = Tick * xSTM_DWT_CYCLES_PER_US;
  while((DWT->CYCCNT - Start) < Period);
}


///@Function: xSTM_DWT_GetCycle
///@Descript: Get Current DWT Cycle Count
U32 xSTM_DWT_GetCycle(void)
{
  return DWT->CYCCNT;
}


///@Function: xSTM_DWT_GetUS
///@Descript: Get Current DWT Time in Microseconds
U32 xSTM_DWT_GetUS(void)
{
  return xSTM_DWT_GetCycle() / xSTM_DWT_CYCLES_PER_US;
}


///@Function: xSTM_DWT_PerfStart
///@Descript: Get Current DWT Cycle Count for Performance Measurement
U32 xSTM_DWT_PerfStart(void)
{
  return xSTM_DWT_GetCycle();
}


///@Function: xSTM_DWT_PerfFinish
///@Descript: Calculate Elapsed Microseconds Since Performance Start
U32 xSTM_DWT_PerfFinish(U32 Start)
{
  U32 Elapsed   = DWT->CYCCNT - Start;
  U32 ElapsedUS = Elapsed / xSTM_DWT_CYCLES_PER_US;
#if xSTM_DWT_SUPPORT_DEBUG
  printf("[Perf]: Elapsed: %lu us(%lu Cycle)\r\n"
  ,(unsigned long)ElapsedUS,(unsigned long)Elapsed);
#endif  //xSTM_DWT_SUPPORT_DEBUG
  return ElapsedUS;
}


///@Function: xSTM_DWT_TimerEvent
///@Descript: Process a Non-Blocking DWT Timer Event
void xSTM_DWT_TimerEvent(U32 Tick,xBOOL Once,xSTM_DWT_Event_CB CB)
{
  static xSTM_DWT_EVENT_STATE State  = xSTM_DWT_EVENT_IDLE;
  static U32                  Start  = 0;
  static U32                  Period = 0;
  static xSTM_DWT_Event_CB    LastCB = NULL;

  if(CB == NULL)
    return;

  switch(State)
  {
    case xSTM_DWT_EVENT_IDLE:
      Start  = DWT->CYCCNT;
      Period = Tick * xSTM_DWT_CYCLES_PER_MS;
      LastCB = CB;
      State  = xSTM_DWT_EVENT_WAIT;
      break;

    case xSTM_DWT_EVENT_WAIT:
      if((DWT->CYCCNT - Start) >= Period)
      {
        LastCB();
        if(Once == xSTM_DWT_EVENT_ONCE)
          State = xSTM_DWT_EVENT_FINISH;
        else
          Start += Period;
      }
      break;

    case xSTM_DWT_EVENT_FINISH:
      break;

    default:
      State = xSTM_DWT_EVENT_IDLE;
      break;
  }
}


#if xSTM_DWT_SUPPORT_UNIT_TEST
///@Function: xSTM_TEST_DWT
///@Descript: Run Basic DWT Function Test
void xSTM_TEST_DWT(void)
{
  printf("[DWT TEST]: Start\r\n");
  xSTM_DWT_Init();

  //Delay
  U32 Start = xSTM_DWT_GetCycle();
  xSTM_DWT_DelayCycle(5);       //Delay 5  Cycle
  xSTM_DWT_DelayUS(5);          //Delay 5  us
  xSTM_DWT_Delay10US(5);        //Delay 50 us
  xSTM_DWT_DelayMS(5);          //Delay 5  ms
  U32 Elapsed = xSTM_DWT_GetCycle() - Start;
  xBOOL DelayPass = (Elapsed >= (1UL + xSTM_DWT_CYCLES_PER_US + xSTM_DWT_CYCLES_PER_10US + xSTM_DWT_CYCLES_PER_MS));

  //Perf
  Start      = xSTM_DWT_PerfStart();
  xSTM_DWT_DelayMS(10);         //Delay 10 ms
  U32 PerfUS = xSTM_DWT_PerfFinish(Start);

  printf("[DWT TEST]: Delay : %s   \r\n",DelayPass? "PASS": "FAILED");
  printf("[DWT TEST]: Time  : %d us\r\n",(U32)xSTM_DWT_GetUS());
  printf("[DWT TEST]: Perf  : %d us\r\n",(U32)PerfUS);
  printf("[DWT TEST]: Finish\r\n");
}
#endif  //xSTM_DWT_SUPPORT_UNIT_TEST
