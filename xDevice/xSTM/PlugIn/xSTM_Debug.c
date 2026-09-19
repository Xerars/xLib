//[xLib Include]
#include "xSTM_Debug.h"

//Author  : William Hsiao
//Descript: Redirect Standard Input and Output to an STM32 UART
//Version : 1.1.0

///@Function: fputc
///@Descript: Send One Character through the Debug UART
int fputc(int Ch,FILE *fp)
{
  xUNUSED(fp);
  U8 TxCh = (U8)Ch;
  if(HAL_UART_Transmit(&xSTM_DEBUG_HANDLE,&TxCh,1,xSTM_DEBUG_SEND_TICK) == HAL_OK)
    return Ch;
  return EOF;
}


///@Function: fgetc
///@Descript: Receive One Character from the Debug UART
int fgetc(FILE *fp)
{
  xUNUSED(fp);
  U8 Ch;
  if(HAL_UART_Receive(&xSTM_DEBUG_HANDLE,&Ch,1,xSTM_DEBUG_RECV_TICK) == HAL_OK)
  {
#if xSTM_DEBUG_SUPPORT_RECV_ECHO
    HAL_UART_Transmit(&xSTM_DEBUG_HANDLE,&Ch,1,xSTM_DEBUG_SEND_TICK);
#endif  //xSTM_DEBUG_SUPPORT_RECV_ECHO
    return (int)Ch;
  }
  return EOF;
}


///@Function: xSTM_HexDump
///@Descript: Print Data as Hexadecimal Bytes through the Debug UART
void xSTM_HexDump(const void *Data,U16 Len)
{
  const U8 *Bytes = (const U8 *)Data;
  if((Bytes == NULL) || (Len == 0))
    return;

  printf("[Hex]: ");
  for(U16 Index = 0;Index < Len;Index++)
  {
    printf("%02X ",Bytes[Index]);
    if((((Index + 1) % 16) == 0) && ((Index + 1) < Len))  //More Line of Text
      printf("\r\n[Hex]: ");
  }
  printf("\r\n");
}

#if xSTM_DEBUG_SUPPORT_UNIT_TEST
///@Function: xSTM_TEST_Debug_Print
///@Descript: Print Basic Formatted Output for the Debug UART
void xSTM_TEST_Debug_Print(void)
{
  printf("[DEBUG TEST]: Start  Print Test...\r\n");
  printf("[1]-> Integer : %d\r\n",123456);
  printf("[2]-> Hex     : %x\r\n",0x123456);
  printf("[1]-> Double  : %f\r\n",0.123456);
  printf("[DEBUG TEST]: Finish Print Test...\r\n");
}


///@Function: xSTM_TEST_Debug_Scanf
///@Descript: Read and Print Basic Input for the Debug UART
void xSTM_TEST_Debug_Scanf(void)
{
  char Ch;
  char Buf[64] = {0};
  printf("[KeyIn Char]   >> ");
  if(scanf("%c",&Ch) == 1)
    printf("[SUCCESS]: Recv Data: %c\r\n",Ch);
  
  printf("[KeyIn String] >> ");
  if(scanf("%63s",Buf) == 1)
    printf("[SUCCESS]: Recv Data: %s\r\n",Buf);
}
#endif  //xSTM_DEBUG_SUPPORT_UNIT_TEST
