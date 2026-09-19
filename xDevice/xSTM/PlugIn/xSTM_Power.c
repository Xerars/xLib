//[xLib Include]
#include "xSTM_Power.h"

//Author  : William Hsiao
//Descript: STM32 Power Mode Utility
//Version : 1.0.0

//[Variables Declare]
static U32   xSTM_Power_NormalDivider = RCC_SYSCLK_DIV1;   //Saved Normal AHB Divider
static xBOOL xSTM_Power_HasNormalClock = xFALSE;            //Normal Clock State


///@Function: xSTM_Power_Sleep
///@Descript: Enter STM32 Sleep Mode
void xSTM_Power_Sleep(void)
{
  //@@ CPU Clock Stops; Peripherals, SRAM and Registers Keep Running
  //@@ Unavailable   : CPU Code Execution Until Interrupt or Event Wakeup
  //@@ Estimated Current(F405/F407): About 12 mA at 168 MHz With Peripherals Off
  //@@ Restore: Wakeup Returns Here; System Clock Remains Unchanged
  HAL_PWR_EnterSLEEPMode(xSTM_POWER_SLEEP_REGULATOR,xSTM_POWER_SLEEP_ENTRY);
}


///@Function: xSTM_Power_Stop
///@Descript: Enter STM32 Stop Mode
void xSTM_Power_Stop(void)
{
  //@@ CPU, AHB, APB, PLL, HSI and HSE Clocks Stop; SRAM Keeps Data
  //@@ Unavailable: Peripherals Except Wakeup Sources and Backup Domain
  //@@ Estimated Current(F405/F407): About 280 to 310 uA at Room Temperature
  //@@ Restore: Call Application SystemClock_Config to Restore PLL and Normal Clock
  HAL_PWR_EnterSTOPMode(xSTM_POWER_STOP_REGULATOR,xSTM_POWER_STOP_ENTRY);
}


///@Function: xSTM_Power_Standby
///@Descript: Enter STM32 Standby Mode
void xSTM_Power_Standby(void)
{
  //@@ V12 Domain Powers Off; SRAM, Registers and Peripherals Lose State
  //@@ Unavailable: All Functions Except Wakeup Pin, RTC and Backup Domain
  //@@ Estimated Current(F405/F407): About 2.2 uA Without RTC or 3.1 uA With RTC
  //@@ Restore: Wakeup Resets System; Restore State During Normal Boot
  HAL_PWR_EnterSTANDBYMode();
}


///@Function: xSTM_Power_SetClock
///@Descript: Set AHB Clock Not Higher Than Target Frequency
U32 xSTM_Power_SetClock(U32 Freq)
{
  static const U16 DividerList[] = {1,2,4,8,16,64,128,256,512};
  static const U32 HALDividerList[] =
  {
    RCC_SYSCLK_DIV1,RCC_SYSCLK_DIV2,RCC_SYSCLK_DIV4,RCC_SYSCLK_DIV8
   ,RCC_SYSCLK_DIV16,RCC_SYSCLK_DIV64,RCC_SYSCLK_DIV128,RCC_SYSCLK_DIV256
   ,RCC_SYSCLK_DIV512
  };
  RCC_ClkInitTypeDef ClockInfo;
  U32 FlashLatency;
  U32 SysClock;

  //@@ Input: Freq Is Target HCLK(Hz); Actual HCLK Is Not Higher Than Freq
  //@@ PLL Keeps Running; This Lowers CPU and AHB Frequency Only
  if(Freq == 0)
    return 0;

  HAL_RCC_GetClockConfig(&ClockInfo,&FlashLatency);          //Get Current Clock Config
  if(xSTM_Power_HasNormalClock == xFALSE)
  {
    xSTM_Power_NormalDivider = ClockInfo.AHBCLKDivider;      //Save Original AHB Divider
    xSTM_Power_HasNormalClock = xTRUE;
  }

  SysClock = HAL_RCC_GetSysClockFreq();                      //Get Current System Clock
  for(U32 Index = 0;Index < (sizeof(DividerList) / sizeof(DividerList[0]));Index++)
    if((SysClock / DividerList[Index]) <= Freq)
    {
      ClockInfo.ClockType = RCC_CLOCKTYPE_HCLK;               //Update HCLK Only
      ClockInfo.AHBCLKDivider = HALDividerList[Index];        //Set Target AHB Divider
      if(HAL_RCC_ClockConfig(&ClockInfo,FlashLatency) != HAL_OK)  //Apply Clock Config
        return 0;
      return HAL_RCC_GetHCLKFreq();                            //Return HCLK
    }

  return 0;
}


///@Function: xSTM_Power_RestoreClock
///@Descript: Restore Original AHB Divider
U32 xSTM_Power_RestoreClock(void)
{
  RCC_ClkInitTypeDef ClockInfo;
  U32 FlashLatency;

  if(xSTM_Power_HasNormalClock == xFALSE)
    return HAL_RCC_GetHCLKFreq();                            //Return HCLK

  HAL_RCC_GetClockConfig(&ClockInfo,&FlashLatency);          //Get Current Clock Config
  ClockInfo.ClockType = RCC_CLOCKTYPE_HCLK;               //Update HCLK Only
  ClockInfo.AHBCLKDivider = xSTM_Power_NormalDivider;        //Restore Saved AHB Divider
  if(HAL_RCC_ClockConfig(&ClockInfo,FlashLatency) != HAL_OK)  //Apply Clock Config
    return 0;

  xSTM_Power_HasNormalClock = xFALSE;
  return HAL_RCC_GetHCLKFreq();                            //Return HCLK
}
