//[xLib Include]
#include "xSTM_Flash.h"

//Author  : William Hsiao
//Descript: STM32 Internal Flash Read, Write and Erase Utility
//Version : 1.0.0

///@Function: xSTM_Flash_Read
///@Descript: Read One 32-Bit Word from Internal Flash
U32 xSTM_Flash_Read(U32 Addr)
{
  return *(const U32 *)Addr;      //Read 32-Bit Word from Flash
}


///@Function: xSTM_Flash_ReadBuf
///@Descript: Read Data from Internal Flash
xErr xSTM_Flash_ReadBuf(U32 Addr,U8 *Data,U32 Len)
{
  if(Data == NULL)
    return xFAILED;

  const U8 *Flash = (const U8 *)Addr;
  for(U32 Index = 0;Index < Len;Index++)
    Data[Index] = Flash[Index];
  return xSUCCESS;
}


///@Function: xSTM_Flash_Write
///@Descript: Write One 32-Bit Word to Internal Flash
xErr xSTM_Flash_Write(U32 Addr,U32 Data)
{
  if(!IS_ALIGN(Addr,xSTM_FLASH_WORD_SIZE))
    return xFAILED;

  HAL_StatusTypeDef Status = HAL_FLASH_Unlock();    //Unlock Flash for Writing
  if(Status != HAL_OK)
    return xFAILED;

  //Program Flash with the Given Data
  Status = HAL_FLASH_Program(xSTM_FLASH_PROGRAM_TYPE,Addr,Data);
  HAL_FLASH_Lock();                                 //Lock Flash After Writing
  return (Status == HAL_OK)? xSUCCESS: xFAILED;
}


///@Function: xSTM_Flash_WriteBuf
///@Descript: Write Data to Internal Flash
xErr xSTM_Flash_WriteBuf(U32 Addr,const U8 *Data,U32 Len)
{
  if((Data == NULL) || (Len == 0))
    return xFAILED;
  if(!IS_ALIGN(Addr,xSTM_FLASH_WORD_SIZE))          //Address Must be Aligned to Flash Word Size
    return xFAILED;

  HAL_StatusTypeDef Status = HAL_FLASH_Unlock();    //Unlock Flash for Writing
  if(Status != HAL_OK)
    return xFAILED;

  for(U32 Offset = 0;Offset < Len;Offset += xSTM_FLASH_WORD_SIZE)
  {
    U32 Word = 0xFFFFFFFF;
    for(U32 Index = 0;Index < xSTM_FLASH_WORD_SIZE;Index++)
      if((Offset + Index) < Len)
      {
        Word &= ~(0xFFUL << (Index * 8));
        Word |= ((U32)Data[Offset + Index] << (Index * 8));
      }

    //Program Flash with the Constructed Word
    Status = HAL_FLASH_Program(xSTM_FLASH_PROGRAM_TYPE,Addr + Offset,Word);
    if(Status != HAL_OK)
      break;
  }

  HAL_FLASH_Lock();                                 //Lock Flash After Writing
  return (Status == HAL_OK)? xSUCCESS: xFAILED;
}


///@Function: xSTM_Flash_IsErased
///@Descript: Check Internal Flash Data is Erased (All Bytes are 0xFF)
xBOOL xSTM_Flash_IsErased(U32 Addr,U32 Len)
{
  const U8 *Flash = (const U8 *)Addr;
  for(U32 Index = 0;Index < Len;Index++)
  {
    if(Flash[Index] != 0xFF)
      return xFALSE;
  }
  return xTRUE;
}


///@Function: xSTM_Flash_Erase
///@Descript: Erase Continuous Internal Flash Sectors
xErr xSTM_Flash_Erase(U32 Sector,U32 Count)
{
  if(Count == 0)
    return xFAILED;

  FLASH_EraseInitTypeDef EraseInfo = {0};
  EraseInfo.TypeErase    = FLASH_TYPEERASE_SECTORS;
  EraseInfo.Sector       = Sector;
  EraseInfo.NbSectors    = Count;
  EraseInfo.VoltageRange = xSTM_FLASH_VOLTAGE_RANGE;      //Set Flash Voltage Range for Erasing

  U32 ErrorSector;
  HAL_StatusTypeDef Status = HAL_FLASH_Unlock();          //Unlock Flash for Erasing
  if(Status != HAL_OK)
    return xFAILED;

  Status = HAL_FLASHEx_Erase(&EraseInfo,&ErrorSector);    //Erase Flash Sectors
  HAL_FLASH_Lock();                                       //Lock Flash After Erasing
  return (Status == HAL_OK)? xSUCCESS: xFAILED;
}

#if xSTM_FLASH_SUPPORT_UNIT_TEST
//@@ Flash Unit Test Erases All Configured Test Sectors
//@@ Run This Test Only After Reserving the Test Area in the Linker Setting

///@Function: xSTM_TEST_Flash
///@Descript: Run Basic Flash Function Test
void xSTM_TEST_Flash(void)
{
  const U32 WordData     = 0x12345678UL;
  const U8  wData[8] = {0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0xF0};
  U8        rData[8] = {0};
  xBOOL     Pass = xTRUE;

  printf("[FLASH TEST]: Start\r\n");

  //Erase
  if(xSTM_Flash_Erase(xSTM_FLASH_TEST_SECTOR,xSTM_FLASH_TEST_SECTOR_COUNT) != xSUCCESS)                   Pass = xFALSE;
  if(xSTM_Flash_IsErased(xSTM_FLASH_TEST_ADDR,xSTM_FLASH_TEST_SIZE) == xFALSE)                            Pass = xFALSE;

  //Word
  if(xSTM_Flash_Write(xSTM_FLASH_TEST_ADDR,WordData) != xSUCCESS)                                         Pass = xFALSE;
  U32 rWord = xSTM_Flash_Read(xSTM_FLASH_TEST_ADDR);
  printf("[FLASH TEST]: Read Word : 0x%08X\r\n",rWord);

  //Buffer
  if(xSTM_Flash_WriteBuf(xSTM_FLASH_TEST_ADDR + xSTM_FLASH_WORD_SIZE,wData,sizeof(wData)) != xSUCCESS)    Pass = xFALSE;
  if(xSTM_Flash_ReadBuf(xSTM_FLASH_TEST_ADDR  + xSTM_FLASH_WORD_SIZE,rData,sizeof(rData)) != xSUCCESS)    Pass = xFALSE;
  printf("[FLASH TEST]: Read Buf  : ");
  for(U32 Index = 0;Index < sizeof(wData);Index++)
  {
    printf("%02X ",rData[Index]);
    if(rData[Index] != wData[Index])
      Pass = xFALSE;
  }
  printf("\r\n");

  //Clean
  if(xSTM_Flash_Erase(xSTM_FLASH_TEST_SECTOR,xSTM_FLASH_TEST_SECTOR_COUNT) != xSUCCESS)                   Pass = xFALSE;
  if(xSTM_Flash_IsErased(xSTM_FLASH_TEST_ADDR,xSTM_FLASH_TEST_SIZE) == xFALSE)                            Pass = xFALSE;

  printf("[FLASH TEST]: %s\r\n",Pass ? "PASS" : "FAILED");
}
#endif  //xSTM_FLASH_SUPPORT_UNIT_TEST
