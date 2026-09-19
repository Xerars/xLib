//[xLib Include]
#include "xSTM_Sys.h"

//Author  : William Hsiao
//Descript: STM32 CPU and Reset System Utility
//Version : 1.0.0

///@Function: xSTM_SYS_GetUID
///@Descript: Get 96-Bit STM32 Unique ID
void xSTM_SYS_GetUID(U32 UID[3])
{
  if(UID == NULL)
    return;

  UID[0] = HAL_GetUIDw0();
  UID[1] = HAL_GetUIDw1();
  UID[2] = HAL_GetUIDw2();
}


///@Function: xSTM_SYS_GetCPUID
///@Descript: Get Cortex-M CPU ID Register
U32 xSTM_SYS_GetCPUID(void)
{
  return SCB->CPUID;
}


///@Function: xSTM_SYS_GetVer
///@Descript: Get Cortex-M CPU Revision
U32 xSTM_SYS_GetVer(void)
{
  return (xSTM_SYS_GetCPUID() & SCB_CPUID_REVISION_Msk) >> SCB_CPUID_REVISION_Pos;
}


///@Function: xSTM_SYS_GetDeviceID
///@Descript: Get STM32 Device ID
U32 xSTM_SYS_GetDeviceID(void)
{
  return HAL_GetDEVID();
}


///@Function: xSTM_SYS_GetDevVer
///@Descript: Get STM32 Device Revision
U32 xSTM_SYS_GetDevVer(void)
{
  return HAL_GetREVID();
}

///@Function: xSTM_SYS_GetReason
///@Descript: Get STM32 Reset Reason Flags
U32 xSTM_SYS_GetReason(void)
{
  U32 Reason = xSTM_RESET_REASON_NONE;

  if(__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST) != RESET)    Reason |= xSTM_RESET_REASON_LOW_POWER;       //Low Power Reset
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)    Reason |= xSTM_RESET_REASON_WINDOW_WDT;      //Window Watchdog Reset
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)    Reason |= xSTM_RESET_REASON_INDEPEND_WDT;    //Independent Watchdog Reset
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)  != RESET)    Reason |= xSTM_RESET_REASON_SOFTWARE;        //Software Reset
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST)  != RESET)    Reason |= xSTM_RESET_REASON_POWER_ON;        //Power On Reset
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)  != RESET)    Reason |= xSTM_RESET_REASON_PIN;             //Pin Reset
#ifdef RCC_FLAG_BORRST
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST) != RESET)
    Reason |= xSTM_RESET_REASON_BROWN_OUT;          //Brown Out Reset
#endif
  return Reason;
}


///@Function: xSTM_SYS_ClearReason
///@Descript: Clear STM32 Reset Reason Flags
void xSTM_SYS_ClearReason(void)
{
  __HAL_RCC_CLEAR_RESET_FLAGS();
}


///@Function: xSTM_SYS_SoftReset
///@Descript: Trigger Cortex-M Software Reset
void xSTM_SYS_SoftReset(void)
{
  NVIC_SystemReset();
}


///@Function: xSTM_SYS_GetTick
///@Descript: Get HAL System Tick
U32 xSTM_SYS_GetTick(void)
{
  return HAL_GetTick();
}


///@Function: xSTM_SYS_Delay
///@Descript: Delay HAL System Tick
void xSTM_SYS_Delay(U32 Tick)
{
  HAL_Delay(Tick);
}


///@Function: xSTM_SYS_GetClockInfo
///@Descript: Get STM32 System Clock Information
void xSTM_SYS_GetClockInfo(xSTM_SYS_Clock_Info *ClockInfo)
{
  if(ClockInfo == NULL)
    return;

  ClockInfo->SYSCLK = HAL_RCC_GetSysClockFreq();
  ClockInfo->HCLK   = HAL_RCC_GetHCLKFreq();
  ClockInfo->PCLK1  = HAL_RCC_GetPCLK1Freq();
  ClockInfo->PCLK2  = HAL_RCC_GetPCLK2Freq();
}


///@Function: xSTM_SYS_GetBootAddress
///@Descript: Get Current Vector Table Address
U32 xSTM_SYS_GetBootAddress(void)
{
  return SCB->VTOR;
}


#if xSTM_SYS_SUPPORT_UNIT_TEST
///@Function: xSTM_TEST_SYS
///@Descript: Run Basic SYS Function Test
void xSTM_TEST_SYS(void)
{
  U32 UID[3] = {0};
  xSTM_SYS_Clock_Info ClockInfo = {0};

  printf("[SYS TEST]: Start\r\n");
  //CPU
  xSTM_SYS_GetUID(UID);
  printf("[SYS TEST]: UID    : %08lX %08lX %08lX\r\n",(U32)UID[0],(U32)UID[1],(U32)UID[2]);
  printf("[SYS TEST]: CPUID  : 0x%08lX\r\n",(U32)xSTM_SYS_GetCPUID());
  printf("[SYS TEST]: CPU Ver: %lu    \r\n",(U32)xSTM_SYS_GetVer());
  printf("[SYS TEST]: Dev ID : 0x%03lX\r\n",(U32)xSTM_SYS_GetDeviceID());
  printf("[SYS TEST]: Dev Ver: 0x%04lX\r\n",(U32)xSTM_SYS_GetDevVer());

  //System
  U32 Tick = xSTM_SYS_GetTick();
  xSTM_SYS_Delay(1);
  printf("[SYS TEST]: Tick   : %lu MS \r\n",(U32)(xSTM_SYS_GetTick() - Tick));
  xSTM_SYS_GetClockInfo(&ClockInfo);
  printf("[SYS TEST]: SYSCLK : %lu Hz \r\n",(U32)ClockInfo.SYSCLK);
  printf("[SYS TEST]: HCLK   : %lu Hz \r\n",(U32)ClockInfo.HCLK);
  printf("[SYS TEST]: PCLK1  : %lu Hz \r\n",(U32)ClockInfo.PCLK1);
  printf("[SYS TEST]: PCLK2  : %lu Hz \r\n",(U32)ClockInfo.PCLK2);
  printf("[SYS TEST]: Boot   : 0x%08lX\r\n",(U32)xSTM_SYS_GetBootAddress());

  //Reset
  U32 Reason = xSTM_SYS_GetReason();
  printf("[SYS TEST]: Reason : 0x%08lX\r\n",(U32)Reason);
  printf("[SYS TEST]: Finish\r\n");
}
#endif  //xSTM_SYS_SUPPORT_UNIT_TEST
