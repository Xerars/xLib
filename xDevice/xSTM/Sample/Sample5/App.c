//Demo xSTM_Flash Read, Write, Erase and Unit Test

//[App Include]
#include "App.h"

//[xLib Include]
#include "xSTM.h"

//[Macro Declare]
#define APP_FLASH_WORD_DATA              0x12345678UL              //Flash Word Test Data

//[Prototype Declare]
static void App_FlashDemo(void);


///@Function: App_Init
///@Descript: Run xSTM Flash Function Demo and Unit Test
void App_Init(void)
{
  printf("\r\n[xSTM Flash Sample]: Start\r\n");

  printf("[Flash]: Test Addr: 0x%08X Sector: %d Size: %x Bytes\r\n"
  ,(int)xSTM_FLASH_TEST_ADDR,xSTM_FLASH_TEST_SECTOR,(int)xSTM_FLASH_TEST_SIZE);

  //Unit Test
  xSTM_TEST_Flash();

  //Function Demo
  App_FlashDemo();
  printf("[xSTM Flash Sample]: Init Finish\r\n");
}


///@Function: App_Service
///@Descript: Keep Flash Sample Service Idle
void App_Service(void)
{
}


///@Function: App_FlashDemo
///@Descript: Demonstrate Flash Erase, Read, Write and Erased Check
static void App_FlashDemo(void)
{
  const U8 WriteData[] = {0x10,0x32,0x54,0x76,0x98,0xBA,0xDC,0xFE,0x55};
  U8        ReadData[sizeof(WriteData)] = {0};
  U32       Addr = xSTM_FLASH_TEST_ADDR;
  xBOOL     Match = xTRUE;

  printf("[Flash Demo]: Start\r\n");

  //Erase / IsErased
  xErr Result  = xSTM_Flash_Erase(xSTM_FLASH_TEST_SECTOR,xSTM_FLASH_TEST_SECTOR_COUNT);
  printf("[Erase]: %s\r\n",(Result == xSUCCESS)? "OK": "FAILED");
  xBOOL Erased = xSTM_Flash_IsErased(Addr,xSTM_FLASH_TEST_SIZE);
  printf("[IsErased]: %s\r\n",(Erased == xTRUE)? "YES": "NO");

  //Write / Read Word
  Result   = xSTM_Flash_Write(Addr,APP_FLASH_WORD_DATA);
  U32 Word = xSTM_Flash_Read(Addr);
  printf("[Write Word]: %s\r\n",(Result == xSUCCESS)? "OK": "FAILED");
  printf("[Read Word ]: 0x%08lX\r\n",(unsigned long)Word);
  printf("[IsErased  ]: %s\r\n",xSTM_Flash_IsErased(Addr,xSTM_FLASH_WORD_SIZE)? "YES": "NO");

  //Write / Read Buffer
  Result = xSTM_Flash_WriteBuf(Addr + xSTM_FLASH_WORD_SIZE,WriteData,sizeof(WriteData));
  printf("[Write Buf ]: %s\r\n",(Result == xSUCCESS)? "OK": "FAILED");
  Result = xSTM_Flash_ReadBuf(Addr + xSTM_FLASH_WORD_SIZE,ReadData,sizeof(ReadData));
  printf("[Read Buf  ]: %s\r\n",(Result == xSUCCESS)? "OK": "FAILED");
  xSTM_HexDump(ReadData,sizeof(ReadData));

  for(U32 Index = 0;Index < sizeof(WriteData);Index++)
  {
    if(ReadData[Index] != WriteData[Index])
      Match = xFALSE;
  }
  printf("[Compare Buf]: %s\r\n",(Match == xTRUE)? "PASS": "FAILED");

  //Clean Test Area
  Result = xSTM_Flash_Erase(xSTM_FLASH_TEST_SECTOR,xSTM_FLASH_TEST_SECTOR_COUNT);
  Erased = xSTM_Flash_IsErased(Addr,xSTM_FLASH_TEST_SIZE);
  printf("[Clean     ]: %s\r\n",(Result == xSUCCESS)? "OK" : "FAILED");
  printf("[IsErased  ]: %s\r\n",(Erased == xTRUE)   ? "YES": "NO");
  printf("[Flash Demo]: Finish\r\n");
}
