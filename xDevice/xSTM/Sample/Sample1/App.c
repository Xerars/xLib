//Demo xSTM_Debug UART Redirect, Debug Message, HexDump and Unit Test

//[App Include]
#include "App.h"

//[xLib Include]
#include "xSTM.h"

//[Macro Declare]
#define APP_SERVICE_TICK                1000                    //Service Interval(MS)


///@Function: App_Init
///@Descript: Initialize xSTM Debug Sample and Run Unit Test
void App_Init(void)
{
  U8 Data[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
               0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};

  printf("\r\n[xSTM Debug Sample]: Start\r\n");

	printf("Unit TEST\r\n");
  //Unit Test
  xSTM_TEST_Debug_Print();
  xSTM_TEST_Debug_Scanf();

  //STD IO Redirect
  printf("[printf]: UART Redirect Success\r\n");
  printf("[fputc ]: ");
  fputc('O',stdout);
  fputc('K',stdout);
  fputc('\r',stdout);
  fputc('\n',stdout);

  //Debug Message
  xSTM_DEBUG_INFO("Debug Information\r\n");
  xSTM_DEBUG_WARN("Debug Warning\r\n");
  xSTM_DEBUG_ERROR("Debug Error\r\n");

  //HexDump
  xSTM_HexDump(Data,(U16)ASIZE(Data));
  xSTM_DEBUG_HEXDUMP(Data,(U16)ASIZE(Data));

  printf("[xSTM Debug Sample]: Init Finish\r\n");
}


///@Function: App_Service
///@Descript: Print Sample Service Message Periodically
void App_Service(void)
{
  static U32 LastTick = 0;
  static U32 Count    = 0;

  U32 CurTick = HAL_GetTick();
  if((CurTick - LastTick) < APP_SERVICE_TICK)
    return;

  LastTick = CurTick;
  Count++;
  xSTM_DEBUG_INFO("Service Count: %lu\r\n",(unsigned long)Count);
}
