//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xCheckSum.h"

//[Prototype Declare]
void TEST_CRC8 (void);
void TEST_CRC16(void);
void TEST_CRC32(void);
void TEST_CRC64(void);

//[Variable Declare]
U8 Data1[] = "123456789";
U32 Len1 = sizeof(Data1) - 1;

//Main Code
int main(void)
{
  TEST_CRC8();      printf("\n\n");
  TEST_CRC16();     printf("\n\n");
  TEST_CRC32();     printf("\n\n");
  TEST_CRC64();     printf("\n\n");
  return 0;
}


///@Function: TEST_CRC8
///@Descript: CRC-8 TEST
void TEST_CRC8(void)
{
  printf("CRC-8 [NONE       ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_NONE         ,Data1,Len1));    //PASS[F4]
  printf("CRC-8 [AUTOSAR    ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_AUTOSAR      ,Data1,Len1));    //PASS[DF]
  printf("CRC-8 [BLUETOOTH  ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_BLUETOOTH    ,Data1,Len1));    //PASS[26]
  printf("CRC-8 [CDMA2000   ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_CDMA2000     ,Data1,Len1));    //PASS[DA]
  printf("CRC-8 [DARC       ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_DARC         ,Data1,Len1));    //PASS[15]
  printf("CRC-8 [DVB_S2     ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_DVB_S2       ,Data1,Len1));    //PASS[BC]
  printf("CRC-8 [GSM_A      ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_GSM_A        ,Data1,Len1));    //PASS[37]
  printf("CRC-8 [GSM_B      ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_GSM_B        ,Data1,Len1));    //PASS[94]
  printf("CRC-8 [HITAG      ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_HITAG        ,Data1,Len1));    //PASS[B4]
  printf("CRC-8 [I432_1     ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_I432_1       ,Data1,Len1));    //PASS[A1]
  printf("CRC-8 [ICODE      ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_ICODE        ,Data1,Len1));    //PASS[7E]
  printf("CRC-8 [LTE        ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_LTE          ,Data1,Len1));    //PASS[EA]
  printf("CRC-8 [MAXIM_DOW  ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_MAXIM_DOW    ,Data1,Len1));    //PASS[A1]
  printf("CRC-8 [MIFARE_MAD ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_MIFARE_MAD   ,Data1,Len1));    //PASS[99]
  printf("CRC-8 [NRCS5      ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_NRCS5        ,Data1,Len1));    //PASS[F7]
  printf("CRC-8 [OPENSAFETY ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_OPENSAFETY   ,Data1,Len1));    //PASS[3E]
  printf("CRC-8 [ROHC       ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_ROHC         ,Data1,Len1));    //PASS[D0]
  printf("CRC-8 [SAE_J1850  ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_SAE_J1850    ,Data1,Len1));    //PASS[4B]
  printf("CRC-8 [SMBUS      ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_SMBUS        ,Data1,Len1));    //PASS[F4]
  printf("CRC-8 [TECH_3250  ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_TECH_3250    ,Data1,Len1));    //PASS[97]
  printf("CRC-8 [WCDMA      ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_WCDMA        ,Data1,Len1));    //PASS[25]
  printf("CRC-8 [GSM        ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC3_TYPE_GSM          ,Data1,Len1));    //PASS[04]
  printf("CRC-8 [ROHC       ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC3_TYPE_ROHC         ,Data1,Len1));    //PASS[06]
  printf("CRC-8 [INTERLAKEN ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC4_TYPE_INTERLAKEN   ,Data1,Len1));    //PASS[0B]
  printf("CRC-8 [ITU        ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC4_TYPE_ITU          ,Data1,Len1));    //PASS[07]
  printf("CRC-8 [EPC        ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC5_TYPE_EPC          ,Data1,Len1));    //PASS[00]
  printf("CRC-8 [ITU        ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC5_TYPE_ITU          ,Data1,Len1));    //PASS[07]
  printf("CRC-8 [USB        ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC5_TYPE_USB          ,Data1,Len1));    //PASS[19]
  printf("CRC-8 [ITU        ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC6_TYPE_ITU          ,Data1,Len1));    //PASS[06]
  printf("CRC-8 [CDMA2000A  ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC6_TYPE_CDMA2000A    ,Data1,Len1));    //PASS[0D]
  printf("CRC-8 [CDMA2000B  ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC6_TYPE_CDMA2000B    ,Data1,Len1));    //PASS[3B]
  printf("CRC-8 [DARC       ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC6_TYPE_DARC         ,Data1,Len1));    //PASS[26]
  printf("CRC-8 [GSM        ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC6_TYPE_GSM          ,Data1,Len1));    //PASS[13]
  printf("CRC-8 [UMTS       ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC7_TYPE_UMTS         ,Data1,Len1));    //PASS[61]
  printf("CRC-8 [MMC        ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC7_TYPE_MMC          ,Data1,Len1));    //PASS[75]
}


///@Function: TEST_CRC16
///@Descript: CRC-16 TEST
void TEST_CRC16(void)
{
  printf("CRC-16[NONE       ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_NONE       ,Data1,Len1));    //PASS[BB3D] IBM
  printf("CRC-16[ARC        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_ARC        ,Data1,Len1));    //PASS[BB3D]
  printf("CRC-16[CDMA2000   ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_CDMA2000   ,Data1,Len1));    //PASS[4C06]
  printf("CRC-16[CMS        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_CMS        ,Data1,Len1));    //PASS[AEE7]
  printf("CRC-16[DDS110     ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_DDS110     ,Data1,Len1));    //PASS[9ECF]
  printf("CRC-16[DECTR      ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_DECTR      ,Data1,Len1));    //PASS[007E]
  printf("CRC-16[DECTX      ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_DECTX      ,Data1,Len1));    //PASS[007F]
  printf("CRC-16[DNP        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_DNP        ,Data1,Len1));    //PASS[EA82]
  printf("CRC-16[EN13757    ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_EN13757    ,Data1,Len1));    //PASS[C2B7]
  printf("CRC-16[GENIBUS    ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_GENIBUS    ,Data1,Len1));    //PASS[D64E]
  printf("CRC-16[GSM        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_GSM        ,Data1,Len1));    //PASS[CE3C]
  printf("CRC-16[IBM3740    ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_IBM3740    ,Data1,Len1));    //PASS[29B1]
  printf("CRC-16[IBMSDLC    ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_IBMSDLC    ,Data1,Len1));    //PASS[906E]
  printf("CRC-16[ISO14443   ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_ISO14443   ,Data1,Len1));    //PASS[BF05]
  printf("CRC-16[KERMIT     ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_KERMIT     ,Data1,Len1));    //PASS[2189]
  printf("CRC-16[LJ1200     ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_LJ1200     ,Data1,Len1));    //PASS[BDF4]
  printf("CRC-16[M17        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_M17        ,Data1,Len1));    //PASS[772B]
  printf("CRC-16[MAXIM_DOW  ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_MAXIM_DOW  ,Data1,Len1));    //PASS[44C2]
  printf("CRC-16[MCRF4XX    ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_MCRF4XX    ,Data1,Len1));    //PASS[6F91]
  printf("CRC-16[MODBUS     ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_MODBUS     ,Data1,Len1));    //PASS[4B37]
  printf("CRC-16[NRSC5      ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_NRSC5      ,Data1,Len1));    //PASS[A066]
  printf("CRC-16[OPENSAFETYA]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_OPENSAFETYA,Data1,Len1));    //PASS[5D38]
  printf("CRC-16[OPENSAFETYB]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_OPENSAFETYB,Data1,Len1));    //PASS[20FE]
  printf("CRC-16[PROFIBUS   ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_PROFIBUS   ,Data1,Len1));    //PASS[A819]
  printf("CRC-16[RIELLO     ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_RIELLO     ,Data1,Len1));    //PASS[63D0]
  printf("CRC-16[SPI_FUJITSU]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_SPI_FUJITSU,Data1,Len1));    //PASS[E5CC]
  printf("CRC-16[T10_DIF    ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_T10_DIF    ,Data1,Len1));    //PASS[D0DB]
  printf("CRC-16[TELEDISK   ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_TELEDISK   ,Data1,Len1));    //PASS[0FB3]
  printf("CRC-16[TMS37157   ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_TMS37157   ,Data1,Len1));    //PASS[26B1]
  printf("CRC-16[UMTS       ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_UMTS       ,Data1,Len1));    //PASS[FEE8]
  printf("CRC-16[USB        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_USB        ,Data1,Len1));    //PASS[B4C8]
  printf("CRC-16[XMODEM     ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC16_TYPE_XMODEM     ,Data1,Len1));    //PASS[31C3]
  printf("CRC-16[ATM        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC10_TYPE_ATM        ,Data1,Len1));    //PASS[199]
  printf("CRC-16[CDMA2000   ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC10_TYPE_CDMA2000   ,Data1,Len1));    //PASS[233]
  printf("CRC-16[GSM        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC10_TYPE_GSM        ,Data1,Len1));    //PASS[12A]
  printf("CRC-16[FLEXRAY    ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC11_TYPE_FLEXRAY    ,Data1,Len1));    //PASS[5A3]
  printf("CRC-16[UMTS       ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC11_TYPE_UMTS       ,Data1,Len1));    //PASS[061]
  printf("CRC-16[CDMA2000   ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC12_TYPE_CDMA2000   ,Data1,Len1));    //PASS[D4D]
  printf("CRC-16[DECT       ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC12_TYPE_DECT       ,Data1,Len1));    //PASS[F5B]
  printf("CRC-16[GSM        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC12_TYPE_GSM        ,Data1,Len1));    //PASS[B34]
  printf("CRC-16[UMTS       ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC12_TYPE_UMTS       ,Data1,Len1));    //PASS[DAF]
  printf("CRC-16[BBC        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC13_TYPE_BBC        ,Data1,Len1));    //PASS[04FA]
  printf("CRC-16[DARC       ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC14_TYPE_DARC       ,Data1,Len1));    //PASS[082D]
  printf("CRC-16[GSM        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC14_TYPE_GSM        ,Data1,Len1));    //PASS[30AE]
  printf("CRC-16[CAN        ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC15_TYPE_CAN        ,Data1,Len1));    //PASS[059E]
  printf("CRC-16[MPT1327    ]: 0x%X\n",xCheckSum_CRC16_Calculate(xCRC15_TYPE_MPT1327    ,Data1,Len1));    //PASS[2566]
}


///@Function: TEST_CRC32
///@Descript: CRC-32 TEST
void TEST_CRC32(void)
{
  printf("CRC-32[NONE       ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_NONE      ,Data1,Len1));     //PASS[CBF43926]
  printf("CRC-32[AIXM       ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_AIXM      ,Data1,Len1));     //PASS[3010BF7F]
  printf("CRC-32[AUTOSAR    ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_AUTOSAR   ,Data1,Len1));     //PASS[1697D06A]
  printf("CRC-32[BASE91D    ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_BASE91D   ,Data1,Len1));     //PASS[87315576]
  printf("CRC-32[BZIP2      ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_BZIP2     ,Data1,Len1));     //PASS[FC891918]
  printf("CRC-32[CDOMREDC   ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_CDOMREDC  ,Data1,Len1));     //PASS[6EC2EDC4]
  printf("CRC-32[CKSUM      ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_CKSUM     ,Data1,Len1));     //PASS[765E7680]
  printf("CRC-32[ISCSI      ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_ISCSI     ,Data1,Len1));     //PASS[E3069283]
  printf("CRC-32[HLDC       ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_HLDC      ,Data1,Len1));     //PASS[CBF43926]
  printf("CRC-32[JAMCRC     ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_JAMCRC    ,Data1,Len1));     //PASS[340BC6D9]
  printf("CRC-32[MEF        ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_MEF       ,Data1,Len1));     //PASS[D2C22F51]
  printf("CRC-32[MPEG2      ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_MPEG2     ,Data1,Len1));     //PASS[0376D6E7]
  printf("CRC-32[XFER       ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_XFER      ,Data1,Len1));     //PASS[BD0BE338]
  printf("CRC-32[KOOPMAN    ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC32_TYPE_KOOPMAN   ,Data1,Len1));     //PASS[2D3DD0AE]
  printf("CRC-32[CANFD      ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC17_TYPE_CANFD     ,Data1,Len1));     //PASS[04F03]
  printf("CRC-32[CANFD      ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC21_TYPE_CANFD     ,Data1,Len1));     //PASS[0ED841]
  printf("CRC-32[BLE        ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC24_TYPE_BLE       ,Data1,Len1));     //PASS[C25A56]
  printf("CRC-32[FLEXRAYA   ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC24_TYPE_FLEXRAYA  ,Data1,Len1));     //PASS[7979BD]
  printf("CRC-32[FLEXRAYB   ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC24_TYPE_FLEXRAYB  ,Data1,Len1));     //PASS[1F23B8]
  printf("CRC-32[INTERLAKEN ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC24_TYPE_INTERLAKEN,Data1,Len1));     //PASS[B4F3E6]
  printf("CRC-32[LTE_A      ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC24_TYPE_LTE_A     ,Data1,Len1));     //PASS[CDE703]
  printf("CRC-32[LTE_B      ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC24_TYPE_LTE_B     ,Data1,Len1));     //PASS[23EF52]
  printf("CRC-32[OPENPGP    ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC24_TYPE_OPENPGP   ,Data1,Len1));     //PASS[21CF02]
  printf("CRC-32[OS9        ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC24_TYPE_OS9       ,Data1,Len1));     //PASS[200FA5]
  printf("CRC-32[CDMA       ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC30_TYPE_CDMA      ,Data1,Len1));     //PASS[04C34ABF]
  printf("CRC-32[PHILIPS    ]: 0x%X\n",xCheckSum_CRC32_Calculate(xCRC31_TYPE_PHILIPS   ,Data1,Len1));     //PASS[0CE9E46C]
}


///@Function: TEST_CRC64
///@Descript: CRC-64 TEST
void TEST_CRC64(void)
{
  printf("CRC-64[NONE       ]: 0x%llX\n",xCheckSum_CRC64_Calculate(xCRC64_TYPE_NONE   ,Data1,Len1));      //PASS[6C40DF5F0B497347]
  printf("CRC-64[GO_ISO     ]: 0x%llX\n",xCheckSum_CRC64_Calculate(xCRC64_TYPE_GO_ISO ,Data1,Len1));      //PASS[B90956C775A41001]
  printf("CRC-64[MS         ]: 0x%llX\n",xCheckSum_CRC64_Calculate(xCRC64_TYPE_MS     ,Data1,Len1));      //PASS[75D4B74F024ECEEA]
  printf("CRC-64[NVME       ]: 0x%llX\n",xCheckSum_CRC64_Calculate(xCRC64_TYPE_NVME   ,Data1,Len1));      //PASS[AE8B14860A799888]
  printf("CRC-64[REDIS      ]: 0x%llX\n",xCheckSum_CRC64_Calculate(xCRC64_TYPE_REDIS  ,Data1,Len1));      //PASS[E9C6D914C4B8D9CA]
  printf("CRC-64[WE         ]: 0x%llX\n",xCheckSum_CRC64_Calculate(xCRC64_TYPE_WE     ,Data1,Len1));      //PASS[62EC59E3F1A4F00A]
  printf("CRC-64[XZ         ]: 0x%llX\n",xCheckSum_CRC64_Calculate(xCRC64_TYPE_XZ     ,Data1,Len1));      //PASS[995DC9BBDF1939FA]
}




