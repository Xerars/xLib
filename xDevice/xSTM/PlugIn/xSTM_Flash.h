#ifndef __XSTM_FLASH_H__  //__XSTM_FLASH_H__
#define __XSTM_FLASH_H__  //__XSTM_FLASH_H__

//Author  : William Hsiao
//Descript: STM32 Internal Flash Read, Write and Erase Utility
//Version : 1.0.0

//[STD Lib Include]
#include <stdio.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xSTM_Config.h"

//[Macro Declare]
#define xSTM_FLASH_WORD_SIZE             4                             //Flash Program Word Size in Bytes

//Support
#define xSTM_FLASH_SUPPORT_UNIT_TEST     1                             //Build Flash Unit Test When Enabled

#if xSTM_FLASH_SUPPORT_UNIT_TEST
//@@ Flash Unit Test Erases the Reserved Flash Sector
//@@ Keil    : Reduce IROM1 Size or Exclude the Sector in the Scatter File
//@@ Makefile: Reduce FLASH LENGTH or Exclude the Sector in the Linker Script
//@@ Configure All Values for the Reserved Sector Before Enabling Unit Test
#define xSTM_FLASH_TEST_ADDR            0x08060000UL
#define xSTM_FLASH_TEST_SECTOR          FLASH_SECTOR_7
#define xSTM_FLASH_TEST_SECTOR_COUNT    1
#define xSTM_FLASH_TEST_SIZE            0x00020000UL
#endif  //xSTM_FLASH_SUPPORT_UNIT_TEST


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Read / Write
U32   xSTM_Flash_Read    (U32 Addr);                                  //Read  One Word from Flash
xErr  xSTM_Flash_Write   (U32 Addr,U32 Data);                         //Write One Word to   Flash
xErr  xSTM_Flash_ReadBuf (U32 Addr,U8 *Data,U32 Len);                 //Read  Data from Flash
xErr  xSTM_Flash_WriteBuf(U32 Addr,const U8 *Data,U32 Len);           //Write Data to   Flash

//Erase
xBOOL xSTM_Flash_IsErased(U32 Addr,U32 Len);                          //Check Flash Data is Erased
xErr  xSTM_Flash_Erase   (U32 Sector,U32 Count);                      //Erase Continuous Flash Sectors

//Unit Test
#if xSTM_FLASH_SUPPORT_UNIT_TEST
void xSTM_TEST_Flash(void);                                           //Run Flash Unit Test
#endif

#ifdef __cplusplus
}
#endif

#endif  //__XSTM_FLASH_H__
