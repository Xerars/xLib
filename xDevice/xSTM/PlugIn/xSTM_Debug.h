#ifndef __XSTM_DEBUG_H__  //__XSTM_DEBUG_H__
#define __XSTM_DEBUG_H__  //__XSTM_DEBUG_H__

//Author  : William Hsiao
//Descript: Redirect Standard Input and Output to an STM32 UART.
//Version : 1.1.0

//[STD Lib Include]
#include <stdio.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xSTM_Config.h"

//[Config Declare]
#define xSTM_DEBUG_SUPPORT_RECV_ECHO     0                   //Echo Received Characters When Enabled
#define xSTM_DEBUG_SUPPORT_UNIT_TEST     1                   //Build Debug Unit Test When Enabled

#ifdef __cplusplus
extern "C" {
#endif
//IO Redirect
int  fputc(int Ch,FILE *fp);
int  fgetc(FILE *fp);

//Debug
void xSTM_HexDump(const void *Data,U16 Len);                //Print Data as Hexadecimal Bytes

//Unit Test
#if xSTM_DEBUG_SUPPORT_UNIT_TEST
void xSTM_TEST_Debug_Print(void);                           //Run Formatted Output Test
void xSTM_TEST_Debug_Scanf(void);                           //Run Formatted Input Test
#endif  //xSTM_DEBUG_SUPPORT_UNIT_TEST

#ifdef __cplusplus
}
#endif

//[Macro Function Declare]
#define xSTM_DEBUG_INFO(...)            do { printf("[Info] : "); printf(__VA_ARGS__);  } while(0) //Print an Information Message
#define xSTM_DEBUG_WARN(...)            do { printf("[Warn] : "); printf(__VA_ARGS__);  } while(0) //Print a Warning Message
#define xSTM_DEBUG_ERROR(...)           do { printf("[Error]: "); printf(__VA_ARGS__); } while(0) //Print an Error Message
#define xSTM_DEBUG_HEXDUMP(DATA,LEN)    xSTM_HexDump((DATA),(LEN))                                //Print Data as Hexadecimal Bytes

#endif  //__XSTM_DEBUG_H__
