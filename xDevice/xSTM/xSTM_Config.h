#ifndef __XSTM_CONFIG_H__  // __XSTM_CONFIG_H__
#define __XSTM_CONFIG_H__  // __XSTM_CONFIG_H__

//Configuration for xSTM Module
//Keep All Target and HAL Settings Here

//[HAL Lib Include]
#include "stm32f4xx_hal.h"              //STM32 HAL(Target MCU)


//[Macro Declare]
//PlugIn Select
#ifndef xSTM_SUPPORT_DEBUG              //Enable xSTM_Debug PlugIn
  #define xSTM_SUPPORT_DEBUG             1
#endif

#ifndef xSTM_SUPPORT_DWT                //Enable xSTM_DWT PlugIn
  #define xSTM_SUPPORT_DWT               1
#endif

#ifndef xSTM_SUPPORT_FLASH              //Enable xSTM_Flash PlugIn
  #define xSTM_SUPPORT_FLASH             1
#endif

#ifndef xSTM_SUPPORT_SYS                //Enable xSTM_Sys PlugIn
  #define xSTM_SUPPORT_SYS               1
#endif

#ifndef xSTM_SUPPORT_POWER              //Enable xSTM_Power PlugIn
  #define xSTM_SUPPORT_POWER             1
#endif

//Clock
#define xSTM_SYS_CLOCK                   84                           //System Clock(MHz)

//[xSTM_Debug PlugIn]
#define xSTM_DEBUG_HANDLE                huart2                       //UART Handle for Debug
#define xSTM_DEBUG_SEND_TICK             10                           //Transmit Timeout(MS)
#define xSTM_DEBUG_RECV_TICK             HAL_MAX_DELAY                //Receive Timeout

//[xSTM_DWT PlugIn]
#define xSTM_DWT_SYS_CLOCK               xSTM_SYS_CLOCK               //System Clock(MHz)

//[xSTM_Power PlugIn]
#define xSTM_POWER_SLEEP_REGULATOR       PWR_MAINREGULATOR_ON         //Sleep Regulator
#define xSTM_POWER_SLEEP_ENTRY           PWR_SLEEPENTRY_WFI           //Sleep Entry
#define xSTM_POWER_STOP_REGULATOR        PWR_LOWPOWERREGULATOR_ON     //Stop  Regulator
#define xSTM_POWER_STOP_ENTRY            PWR_STOPENTRY_WFI            //Stop  Entry

//[xSTM_Flash PlugIn]
#define xSTM_FLASH_PROGRAM_TYPE          FLASH_TYPEPROGRAM_WORD       //Flash Program Type
#define xSTM_FLASH_VOLTAGE_RANGE         FLASH_VOLTAGE_RANGE_3        //Flash Voltage Range

#ifdef __cplusplus
extern "C" {
#endif
//[Extern Variable Declare]
extern UART_HandleTypeDef                huart2;

#ifdef __cplusplus
}
#endif

#endif // __XSTM_CONFIG_H__
