//Demo xSTM_Sys CPU, Device, Clock, Reset and Unit Test

//[App Incdde]
#include "App.h"

//[xLib Incdde]
#include "xSTM.h"

//[Macro Declare]
#define APP_SERVICE_TICK                1000                    //Service Interval(MS)
#define APP_RESET_COUNTDOWN             60                      //Software Reset Countdown(S)

//[Prototype Declare]
static void App_SYS_PrintReason(U32 Reason);


///@Function: App_Init
///@Descript: Print xSTM SYS Information and Run Unit Test
void App_Init(void)
{
  U32 UID[3] = {0};
  U32 Reason;
  xSTM_SYS_Clock_Info ClkInfo = {0};

  printf("\r\n[xSTM SYS Sample]: Start\r\n");


  //Unit Test
  xSTM_TEST_SYS();

  //CPU
  xSTM_SYS_GetUID(UID);
  printf("[CPU]: UID: %08X %08X %08X\r\n",UID[0],UID[1],UID[2]);
  printf("[CPU]: ID: 0x%08X | Ver: %d\r\n",xSTM_SYS_GetCPUID(),xSTM_SYS_GetVer());

  //Device
  printf("[Device]: ID:0x%03X | Ver: 0x%04X\r\n",xSTM_SYS_GetDeviceID(),xSTM_SYS_GetDevVer());
  printf("[Device]: Boot: 0x%08X\r\n",xSTM_SYS_GetBootAddress());

  //Clock
  xSTM_SYS_GetClockInfo(&ClkInfo);
  printf("[Clock]: SYSCLK: %d HCLK: %d PCLK1: %d PCLK2: %d\r\n"
	,ClkInfo.SYSCLK,ClkInfo.HCLK,ClkInfo.PCLK1,ClkInfo.PCLK2);

  //Reset
  Reason = xSTM_SYS_GetReason();
  printf("[Reset]: Reason: 0x%08X\r\n",Reason);
  App_SYS_PrintReason(Reason);
  printf("[Soft Reset]: %d s\r\n",APP_RESET_COUNTDOWN);
  printf("[xSTM SYS Sample]: Init Finish\r\n");
}


///@Function: App_Service
///@Descript: Count Down and Trigger Software Reset
void App_Service(void)
{
  static U32 LastTick  = 0;
  static U32 CountDown = APP_RESET_COUNTDOWN;

  U32 CurTick = xSTM_SYS_GetTick();
  if((CurTick - LastTick) < APP_SERVICE_TICK)
    return;

  LastTick = CurTick;
  CountDown--;
  printf("[Soft Reset]: %d s\r\n",CountDown);
  if(CountDown == 0)
  {
    printf("[Soft Reset]: Reset Now\r\n");
    xSTM_SYS_SoftReset();
  }
}


///@Function: App_SYS_PrintReason
///@Descript: Print Reset Reason Flags
static void App_SYS_PrintReason(U32 Reason)
{
  if(Reason == xSTM_RESET_REASON_NONE)
  {
    printf("[Reset]: None\r\n");
    return;
  }

  if(Reason & xSTM_RESET_REASON_LOW_POWER)    printf("[Reset]: Low Power\r\n");
  if(Reason & xSTM_RESET_REASON_WINDOW_WDT)   printf("[Reset]: Window Watchdog\r\n");
  if(Reason & xSTM_RESET_REASON_INDEPEND_WDT) printf("[Reset]: Independent Watchdog\r\n");
  if(Reason & xSTM_RESET_REASON_SOFTWARE)     printf("[Reset]: Software\r\n");
  if(Reason & xSTM_RESET_REASON_POWER_ON)     printf("[Reset]: Power On\r\n");
  if(Reason & xSTM_RESET_REASON_PIN)          printf("[Reset]: Reset Pin\r\n");
  if(Reason & xSTM_RESET_REASON_BROWN_OUT)    printf("[Reset]: Brown Out\r\n");
}
