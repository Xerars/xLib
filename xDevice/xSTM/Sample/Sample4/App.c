//Demo xSTM_Power Clock Control and Power Mode Entry

//[App Include]
#include "App.h"

//[xLib Include]
#include "xSTM.h"

//[Macro Declare]
#define APP_POWER_MODE_NONE             0                       //Disable Power Mode Entry
#define APP_POWER_MODE_SLEEP            1                       //Enter Sleep Mode
#define APP_POWER_MODE_STOP             2                       //Enter Stop Mode
#define APP_POWER_MODE_STANDBY          3                       //Enter Standby Mode

#define APP_POWER_TEST_MODE             APP_POWER_MODE_NONE			//Power Mode for Sample Test
#define APP_POWER_ENTER_TICK            5000                    //Power Mode Entry Delay(MS)

//[Prototype Declare]
static void USART2_Init(void);


///@Function: App_Init
///@Descript: Initialize xSTM Power Sample and Test Clock Control
void App_Init(void)
{
  U32 TargetHCLK = (xSTM_SYS_CLOCK * 1000000UL) / 2;
  U32 HCLK;

  printf("\r\n[xSTM Power Sample]: Start\r\n");
  printf("[Clock]: HCLK: %d Hz\r\n",HAL_RCC_GetHCLKFreq());

  //Clock Control
  HCLK = xSTM_Power_SetClock(TargetHCLK);
	USART2_Init();     //Calculate UART BaudRate

  printf("[Clock]: Set: %d Hz\r\n",HCLK);
  HCLK = xSTM_Power_RestoreClock();
	USART2_Init();     //Calculate UART BaudRate
  printf("[Clock]: Restore: %d Hz\r\n",HCLK);

  //Power Mode
  printf("[Power]: Mode: %d Enter After: %d ms\r\n",APP_POWER_TEST_MODE,APP_POWER_ENTER_TICK);
  printf("[xSTM Power Sample]: Init Finish\r\n");
}


///@Function: App_Service
///@Descript: Enter Selected Power Mode Once
void App_Service(void)
{
  static xBOOL Entered = xFALSE;

  if(Entered == xTRUE)
    return;
  if(xSTM_SYS_GetTick() < APP_POWER_ENTER_TICK)
    return;

  Entered = xTRUE;
  switch(APP_POWER_TEST_MODE)
  {
    case APP_POWER_MODE_SLEEP:
      printf("[Power]: Enter Sleep\r\n");
      xSTM_Power_Sleep();
      printf("[Power]: Wake from Sleep\r\n");
      break;

    case APP_POWER_MODE_STOP:
      printf("[Power]: Enter Stop\r\n");
      xSTM_Power_Stop();
      break;

    case APP_POWER_MODE_STANDBY:
      printf("[Power]: Enter Standby\r\n");
      xSTM_Power_Standby();
      break;

    default:
      printf("[Power]: Mode Disabled\r\n");
      break;
  }
}


///@Function: USART2_Init
///@Descript: USART2 Initial
static void USART2_Init(void)
{
  huart2.Instance 					= USART2;
  huart2.Init.BaudRate 			= 115200;
  huart2.Init.WordLength 		= UART_WORDLENGTH_8B;
  huart2.Init.StopBits 			= UART_STOPBITS_1;
  huart2.Init.Parity 				= UART_PARITY_NONE;
  huart2.Init.Mode 					= UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl 		= UART_HWCONTROL_NONE;
  huart2.Init.OverSampling 	= UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart2);
}
