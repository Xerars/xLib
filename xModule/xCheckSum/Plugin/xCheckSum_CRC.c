//[xLib Include]
#include "xCheckSum_CRC.h"

//Author  : William Hsiao
//Descript: Data Validation Library for Embedded Systems(CRC)
//Version : 1.0.0

//[Prototype Declare]
static U8  xCRC8_Reflect(U8 Data,U8 Len);
static U16 xCRC16_Reflect(U16 Data,U8 Len);
static U32 xCRC32_Reflect(U32 Data,U8 Len);
static U64 xCRC64_Reflect(U64 Data,U8 Len);

//[Variable Declare]
//CRC-8 Table
static const xCRC8 CRC8_Table[] = 
{//      Type                 Width     Poly               Init       XOR_Out  RefIn  RefOut
  [xCRC8_TYPE_DEFAULT]      = {8,   xCRC8_POLY_NONE        ,0x00       ,0x00,        0,     0 },     //CRC-8
  [xCRC8_TYPE_AUTOSAR]      = {8,   xCRC8_POLY_AUTOSAR     ,0xFF       ,0xFF,        0,     0 },     //AutoSar
  [xCRC8_TYPE_BLUETOOTH]    = {8,   xCRC8_POLY_BLUETOOTH   ,0x00       ,0x00,        1,     1 },     //Bluetooth
  [xCRC8_TYPE_CDMA2000]     = {8,   xCRC8_POLY_CDMA2000    ,0xFF       ,0x00,        0,     0 },     //CDMA2000
  [xCRC8_TYPE_DARC]         = {8,   xCRC8_POLY_DARC        ,0x00       ,0x00,        1,     1 },     //DARC
  [xCRC8_TYPE_DVB_S2]       = {8,   xCRC8_POLY_DVB_S2      ,0x00       ,0x00,        0,     0 },     //DVB-S2
  [xCRC8_TYPE_GSM_A]        = {8,   xCRC8_POLY_GSM_A       ,0x00       ,0x00,        0,     0 },     //GSM-A
  [xCRC8_TYPE_GSM_B]        = {8,   xCRC8_POLY_GSM_B       ,0x00       ,0xFF,        0,     0 },     //GSM-B
  [xCRC8_TYPE_HITAG]        = {8,   xCRC8_POLY_HITAG       ,0xFF       ,0x00,        0,     0 },     //HitAg
  [xCRC8_TYPE_I432_1]       = {8,   xCRC8_POLY_I432_1      ,0x00       ,0x55,        0,     0 },     //I432-1
  [xCRC8_TYPE_ICODE]        = {8,   xCRC8_POLY_ICODE       ,0xFD       ,0x00,        0,     0 },     //ICode
  [xCRC8_TYPE_LTE]          = {8,   xCRC8_POLY_LTE         ,0x00       ,0x00,        0,     0 },     //LTE
  [xCRC8_TYPE_MAXIM_DOW]    = {8,   xCRC8_POLY_MAXIM_DOW   ,0x00       ,0x00,        1,     1 },     //Maxim Dow
  [xCRC8_TYPE_MIFARE_MAD]   = {8,   xCRC8_POLY_MIFARE_MAD  ,0xC7       ,0x00,        0,     0 },     //Mifare Dow
  [xCRC8_TYPE_NRCS5]        = {8,   xCRC8_POLY_NRSC5       ,0xFF       ,0x00,        0,     0 },     //NRSC-5
  [xCRC8_TYPE_OPENSAFETY]   = {8,   xCRC8_POLY_OPENSAFETY  ,0x00       ,0x00,        0,     0 },     //Open Safety
  [xCRC8_TYPE_ROHC]         = {8,   xCRC8_POLY_ROHC        ,0xFF       ,0x00,        1,     1 },     //ROHC
  [xCRC8_TYPE_SAE_J1850]    = {8,   xCRC8_POLY_SAE_J1850   ,0xFF       ,0xFF,        0,     0 },     //SAE-J1850
  [xCRC8_TYPE_SMBUS]        = {8,   xCRC8_POLY_SMBUS       ,0x00       ,0x00,        0,     0 },     //SMBus
  [xCRC8_TYPE_TECH_3250]    = {8,   xCRC8_POLY_TECH_3250   ,0xFF       ,0x00,        1,     1 },     //Tech-3250
  [xCRC8_TYPE_WCDMA]        = {8,   xCRC8_POLY_WCDMA       ,0x00       ,0x00,        1,     1 },     //WCDMA
  //CRC-3 / CRC-4 / CRC-5 / CRC-6 / CRC-7  
  [xCRC3_TYPE_GSM]          = {3,   xCRC3_POLY_GSM         ,0x00       ,0x07,        0,     0 },     //CRC-3/GSM
  [xCRC3_TYPE_ROHC]         = {3,   xCRC3_POLY_ROHC        ,0x07       ,0x00,        1,     1 },     //CRC-3/ROHC
  [xCRC4_TYPE_INTERLAKEN]   = {4,   xCRC4_POLY_INTERLAKEN  ,0x0F       ,0x0F,        0,     0 },     //CRC-4/INTERLAKEN
  [xCRC4_TYPE_ITU]          = {4,   xCRC4_POLY_ITU         ,0x00       ,0x00,        1,     1 },     //CRC-4/ITU
  [xCRC5_TYPE_EPC]          = {5,   xCRC5_POLY_EPC         ,0x09       ,0x00,        0,     0 },     //CRC-5/EPC
  [xCRC5_TYPE_ITU]          = {5,   xCRC5_POLY_ITU         ,0x00       ,0x00,        1,     1 },     //CRC-5/ITU
  [xCRC5_TYPE_USB]          = {5,   xCRC5_POLY_USB         ,0x1F       ,0x1F,        1,     1 },     //CRC-5/USB
  [xCRC6_TYPE_ITU]          = {6,   xCRC6_POLY_ITU         ,0x00       ,0x00,        1,     1 },     //CRC-6/ITU
  [xCRC6_TYPE_CDMA2000A]    = {6,   xCRC6_POLY_CDMA2000A   ,0x3F       ,0x00,        0,     0 },     //CRC-6/CDMA2000-A
  [xCRC6_TYPE_CDMA2000B]    = {6,   xCRC6_POLY_CDMA2000B   ,0x3F       ,0x00,        0,     0 },     //CRC-6/CDMA2000-B
  [xCRC6_TYPE_DARC]         = {6,   xCRC6_POLY_DARC        ,0x00       ,0x00,        1,     1 },     //CRC-6/DARC
  [xCRC6_TYPE_GSM]          = {6,   xCRC6_POLY_GSM         ,0x00       ,0x3F,        0,     0 },     //CRC-6/GSM
  [xCRC7_TYPE_UMTS]         = {7,   xCRC7_POLY_UMTS        ,0x00       ,0x00,        0,     0 },     //CRC-7/UMTS
  [xCRC7_TYPE_MMC]          = {7,   xCRC7_POLY_MMC         ,0x00       ,0x00,        0,     0 },     //CRC-7/MMC
};

//CRC-16 Table
static const xCRC16 CRC16_Table[] = 
{//      Type                 Width      Poly                Init   XOR_Out RefIn  RefOut
  [xCRC16_TYPE_DEFAULT]     = {16,  xCRC16_POLY_NONE       ,0x0000     ,0x0000,      1,     1 },     //CRC-16
  [xCRC16_TYPE_ARC]         = {16,  xCRC16_POLY_ARC        ,0x0000     ,0x0000,      1,     1 },     //ARC
  [xCRC16_TYPE_CDMA2000]    = {16,  xCRC16_POLY_CDMA2000   ,0xFFFF     ,0x0000,      0,     0 },     //CDMA-2000
  [xCRC16_TYPE_CMS]         = {16,  xCRC16_POLY_CMS        ,0xFFFF     ,0x0000,      0,     0 },     //CMD
  [xCRC16_TYPE_DDS110]      = {16,  xCRC16_POLY_DDS110     ,0x800D     ,0x0000,      0,     0 },     //DDS-110
  [xCRC16_TYPE_DECTR]       = {16,  xCRC16_POLY_DECTR      ,0x0000     ,0x0001,      0,     0 },     //DECTR
  [xCRC16_TYPE_DECTX]       = {16,  xCRC16_POLY_DECTX      ,0x0000     ,0x0000,      0,     0 },     //DECTX
  [xCRC16_TYPE_DNP]         = {16,  xCRC16_POLY_DNP        ,0x0000     ,0xFFFF,      1,     1 },     //DNP
  [xCRC16_TYPE_EN13757]     = {16,  xCRC16_POLY_EN13757    ,0x0000     ,0xFFFF,      0,     0 },     //EN13757
  [xCRC16_TYPE_GENIBUS]     = {16,  xCRC16_POLY_GENIBUS    ,0xFFFF     ,0xFFFF,      0,     0 },     //GENIBUS
  [xCRC16_TYPE_GSM]         = {16,  xCRC16_POLY_GSM        ,0x0000     ,0xFFFF,      0,     0 },     //GSM
  [xCRC16_TYPE_IBM3740]     = {16,  xCRC16_POLY_IBM3740    ,0xFFFF     ,0x0000,      0,     0 },     //IBM3740
  [xCRC16_TYPE_IBMSDLC]     = {16,  xCRC16_POLY_IBMSDLC    ,0xFFFF     ,0xFFFF,      1,     1 },     //IBM-SDLC
  [xCRC16_TYPE_ISO14443]    = {16,  xCRC16_POLY_ISO14443   ,0xC6C6     ,0x0000,      1,     1 },     //ISO-14443
  [xCRC16_TYPE_KERMIT]      = {16,  xCRC16_POLY_KERMIT     ,0x0000     ,0x0000,      1,     1 },     //Kermit
  [xCRC16_TYPE_LJ1200]      = {16,  xCRC16_POLY_LJ1200     ,0x0000     ,0x0000,      0,     0 },     //LJ1200
  [xCRC16_TYPE_M17]         = {16,  xCRC16_POLY_M17        ,0xFFFF     ,0x0000,      0,     0 },     //M17
  [xCRC16_TYPE_MAXIM_DOW]   = {16,  xCRC16_POLY_MAXIM_DOW  ,0x0000     ,0xFFFF,      1,     1 },     //Maxim-Dow
  [xCRC16_TYPE_MCRF4XX]     = {16,  xCRC16_POLY_MCRF4XX    ,0xFFFF     ,0x0000,      1,     1 },     //MCRF4XX
  [xCRC16_TYPE_NRSC5]       = {16,  xCRC16_POLY_NRSC5      ,0xFFFF     ,0x0000,      1,     1 },     //NRCS-5
  [xCRC16_TYPE_MODBUS]      = {16,  xCRC16_POLY_MODBUS     ,0xFFFF     ,0x0000,      1,     1 },     //Mobus
  [xCRC16_TYPE_OPENSAFETYA] = {16,  xCRC16_POLY_OPENSAFETYA,0x0000     ,0x0000,      0,     0 },     //OpenSafetyA
  [xCRC16_TYPE_OPENSAFETYB] = {16,  xCRC16_POLY_OPENSAFETYB,0x0000     ,0x0000,      0,     0 },     //OpenSafetyB
  [xCRC16_TYPE_PROFIBUS]    = {16,  xCRC16_POLY_PROFIBUS   ,0xFFFF     ,0xFFFF,      0,     0 },     //Profibus
  [xCRC16_TYPE_RIELLO]      = {16,  xCRC16_POLY_RIELLO     ,0xB2AA     ,0x0000,      1,     1 },     //Riello
  [xCRC16_TYPE_SPI_FUJITSU] = {16,  xCRC16_POLY_SPI_FUJITSU,0x1D0F     ,0x0000,      0,     0 },     //SPI-Fujitsu
  [xCRC16_TYPE_T10_DIF]     = {16,  xCRC16_POLY_T10_DIF    ,0x0000     ,0x0000,      0,     0 },     //T10-DIF
  [xCRC16_TYPE_TELEDISK]    = {16,  xCRC16_POLY_TELEDISK   ,0x0000     ,0x0000,      0,     0 },     //TELEDISK
  [xCRC16_TYPE_TMS37157]    = {16,  xCRC16_POLY_TMS37157   ,0x89EC     ,0x0000,      1,     1 },     //TMS37157
  [xCRC16_TYPE_UMTS]        = {16,  xCRC16_POLY_UMTS       ,0x0000     ,0x0000,      0,     0 },     //UMTS
  [xCRC16_TYPE_USB]         = {16,  xCRC16_POLY_USB        ,0xFFFF     ,0xFFFF,      1,     1 },     //USB
  [xCRC16_TYPE_XMODEM]      = {16,  xCRC16_POLY_XMODEM     ,0x0000     ,0x0000,      0,     0 },     //XMODEM
  //CRC-10 /CRC-11 / CRC-12 / CRC-13 / CRC-14 / CRC-15
  [xCRC10_TYPE_ATM]         = {10,  xCRC10_POLY_ATM        ,0x0000     ,0x0000,      0,     0 },     //CRC-10/ATM
  [xCRC10_TYPE_CDMA2000]    = {10,  xCRC10_POLY_CDMA2000   ,0x03FF     ,0x0000,      0,     0 },     //CRC-10/CDMA2000
  [xCRC10_TYPE_GSM]         = {10,  xCRC10_POLY_GSM        ,0x0000     ,0x03FF,      0,     0 },     //CRC-10/GSM
  [xCRC11_TYPE_FLEXRAY]     = {11,  xCRC11_POLY_FLEXRAY    ,0x001A     ,0x0000,      0,     0 },     //CRC-11/FLEXRAY
  [xCRC11_TYPE_UMTS]        = {11,  xCRC11_POLY_UMTS       ,0x0000     ,0x0000,      0,     0 },     //CRC-11/UMTS
  [xCRC12_TYPE_CDMA2000]    = {12,  xCRC12_POLY_CDMA2000   ,0x0FFF     ,0x0000,      0,     0 },     //CRC-12/CDMA2000
  [xCRC12_TYPE_DECT]        = {12,  xCRC12_POLY_DECT       ,0x0000     ,0x0000,      0,     0 },     //CRC-12/DECT
  [xCRC12_TYPE_GSM]         = {12,  xCRC12_POLY_GSM        ,0x0000     ,0x0FFF,      0,     0 },     //CRC-12/GSM
  [xCRC12_TYPE_UMTS]        = {12,  xCRC12_POLY_UMTS       ,0x0000     ,0x0000,      0,     1 },     //CRC-12/UMTS
  [xCRC13_TYPE_BBC]         = {13,  xCRC13_POLY_BBC        ,0x0000     ,0x0000,      0,     0 },     //CRC-13/BBC
  [xCRC14_TYPE_DARC]        = {14,  xCRC14_POLY_DARC       ,0x0000     ,0x0000,      1,     1 },     //CRC-14/DARC
  [xCRC14_TYPE_GSM]         = {14,  xCRC14_POLY_GSM        ,0x0000     ,0x3FFF,      0,     0 },     //CRC-14/GSM
  [xCRC15_TYPE_CAN]         = {15,  xCRC15_POLY_CAN        ,0x0000     ,0x0000,      0,     0 },     //CRC-15/CAN
  [xCRC15_TYPE_MPT1327]     = {15,  xCRC15_POLY_MPT1327    ,0x0000     ,0x0001,      0,     0 },     //CRC-15/MPT-1327
};


//CRC-32 Table
static const xCRC32 CRC32_Table[] = 
{//      Type                 Width     Poly                Init      XOR_Out    RefIn  RefOut
  [xCRC32_TYPE_DEFAULT]     = {32,  xCRC32_POLY_NONE       ,0xFFFFFFFF ,0xFFFFFFFF,  1,     1 },     //CRC-32(HLDC)
  [xCRC32_TYPE_AIXM]        = {32,  xCRC32_POLY_AIXM       ,0x00000000 ,0x00000000,  0,     0 },     //AXIM
  [xCRC32_TYPE_AUTOSAR]     = {32,  xCRC32_POLY_AUTOSAR    ,0xFFFFFFFF ,0xFFFFFFFF,  1,     1 },     //AUTOSAR
  [xCRC32_TYPE_BASE91D]     = {32,  xCRC32_POLY_BASE91D    ,0xFFFFFFFF ,0xFFFFFFFF,  1,     1 },     //BASE91-D
  [xCRC32_TYPE_BZIP2]       = {32,  xCRC32_POLY_BZIP2      ,0xFFFFFFFF ,0xFFFFFFFF,  0,     0 },     //BZIP2
  [xCRC32_TYPE_CDOMREDC]    = {32,  xCRC32_POLY_CDOMREDC   ,0x00000000 ,0x00000000,  1,     1 },     //CD-ROM-EDC
  [xCRC32_TYPE_CKSUM]       = {32,  xCRC32_POLY_CKSUM      ,0x00000000 ,0xFFFFFFFF,  0,     0 },     //CKSUM
  [xCRC32_TYPE_ISCSI]       = {32,  xCRC32_POLY_ISCSI      ,0xFFFFFFFF ,0xFFFFFFFF,  1,     1 },     //ISCSI
  [xCRC32_TYPE_HLDC]        = {32,  xCRC32_POLY_HLDC       ,0xFFFFFFFF ,0xFFFFFFFF,  1,     1 },     //ISO-HDLC
  [xCRC32_TYPE_JAMCRC]      = {32,  xCRC32_POLY_JAMCRC     ,0xFFFFFFFF ,0x00000000,  1,     1 },     //JAMCRC
  [xCRC32_TYPE_MEF]         = {32,  xCRC32_POLY_MEF        ,0xFFFFFFFF ,0x00000000,  1,     1 },     //MEF
  [xCRC32_TYPE_MPEG2]       = {32,  xCRC32_POLY_MPEG2      ,0xFFFFFFFF ,0x00000000,  0,     0 },     //MPEG-2
  [xCRC32_TYPE_XFER]        = {32,  xCRC32_POLY_XFER       ,0x00000000 ,0x00000000,  0,     0 },     //Xfer
  [xCRC32_TYPE_KOOPMAN]     = {32,  xCRC32_POLY_KOOPMAN    ,0xFFFFFFFF ,0xFFFFFFFF,  1,     1 },     //Xfer
  //CRC-17 / CRC-21 / CRC-24 / CRC-30 / CRC-31
  [xCRC17_TYPE_CANFD]       = {17,  xCRC17_POLY_CANFD      ,0x00000    ,0x00000   ,  0,     0 },     //CRC-17/CAN-FD
  [xCRC21_TYPE_CANFD]       = {21,  xCRC21_POLY_CANFD      ,0x000000   ,0x000000  ,  0,     0 },     //CRC-21/CAN-FD
  [xCRC24_TYPE_BLE]         = {24,  xCRC24_POLY_BLE        ,0x555555   ,0x000000  ,  1,     1 },     //CRC-24/BLE
  [xCRC24_TYPE_FLEXRAYA]    = {24,  xCRC24_POLY_FLEXRAY    ,0xFEDCBA   ,0x000000  ,  0,     0 },     //CRC-24/Flexray-A
  [xCRC24_TYPE_FLEXRAYB]    = {24,  xCRC24_POLY_FLEXRAY    ,0xABCDEF   ,0x000000  ,  0,     0 },     //CRC-24/Flexray-B
  [xCRC24_TYPE_INTERLAKEN]  = {24,  xCRC24_POLY_INTERLAKEN ,0xFFFFFF   ,0xFFFFFF  ,  0,     0 },     //CRC-24/Interlaken
  [xCRC24_TYPE_LTE_A]       = {24,  xCRC24_POLY_LTE_A      ,0x000000   ,0x000000  ,  0,     0 },     //CRC-24/LTE-A
  [xCRC24_TYPE_LTE_B]       = {24,  xCRC24_POLY_LTE_B      ,0x000000   ,0x000000  ,  0,     0 },     //CRC-24/LTE-B
  [xCRC24_TYPE_OPENPGP]     = {24,  xCRC24_POLY_OPENPGP    ,0xB704CE   ,0x000000  ,  0,     0 },     //CRC-24/OpenPGP
  [xCRC24_TYPE_OS9]         = {24,  xCRC24_POLY_OS9        ,0xFFFFFF   ,0xFFFFFF  ,  0,     0 },     //CRC-24/OS-9
  [xCRC30_TYPE_CDMA]        = {30,  xCRC30_POLY_CDMA       ,0x3FFFFFFF ,0x3FFFFFFF,  0,     0 },     //CRC-30/CDMA
  [xCRC31_TYPE_PHILIPS]     = {31,  xCRC31_POLY_PHILIPS    ,0x7FFFFFFF ,0x7FFFFFFF,  0,     0 },     //CRC-31/Philips
};


//CRC-64 Table
static const xCRC64 CRC64_Table[] = 
{
//   Type                     Width       Poly                Init                XOR_Out      RefIn  RefOut
  [xCRC64_TYPE_DEFAULT]     = {64,  xCRC64_POLY_ECMA ,0x0000000000000000ULL, 0x0000000000000000ULL, 0, 0},    //ECMA-182
  [xCRC64_TYPE_GO_ISO]      = {64,  xCRC64_POLY_ISO  ,0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 1, 1},    //GO-ISO
  [xCRC64_TYPE_MS]          = {64,  xCRC64_POLY_MS   ,0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 1, 1},    //MS
  [xCRC64_TYPE_NVME]        = {64,  xCRC64_POLY_NVME ,0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 1, 1},    //NVME
  [xCRC64_TYPE_REDIS]       = {64,  xCRC64_POLY_REDIS,0x0000000000000000ULL, 0x0000000000000000ULL, 1, 1},    //REDIS
  [xCRC64_TYPE_WE]          = {64,  xCRC64_POLY_WE   ,0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0, 0},    //WE
  [xCRC64_TYPE_XZ]          = {64,  xCRC64_POLY_XZ   ,0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 1, 1},    //XZ
};


///@Function: xCheckSum_CRC8_Calculate
///@Descript: Calculate a 8-Bit CheckSum
U8 xCheckSum_CRC8_Calculate(xCRC8_TYPE Type,U8 *Data,U32 Len)
{
  if(Type >= xCRC8_TYPE_MAX)
    return 0;

  const xCRC8 *pCRC = &CRC8_Table[Type];
  U8 Shift    = 8 - pCRC->Width;
  U8 Mask     = (1<<pCRC->Width) - 1;
  U8 Result   = pCRC->Init << Shift;
  U8 Poly     = pCRC->Poly << Shift;
  U8 XOR_Out  = pCRC->XOR_Out;

  for(U32 i=0;i<Len;i++)
  {
    U8 Byte = Data[i];

    if(pCRC->RefIn)
      Byte = xCRC8_Reflect(Byte,8);

    Result ^= Byte;  
    for(U8 Bit = 0;Bit < 8;Bit++)
      if(Result & 0x80)
        Result = (Result << 1) ^ Poly;
      else
        Result <<= 1;
  }

  Result >>= Shift;
  if(pCRC->RefOut)
    Result = xCRC8_Reflect(Result,pCRC->Width);
  return (Result ^ XOR_Out) & Mask;
}


///@Function: xCheckSum_CRC16_Calculate
///@Descript: Calculate a 16-Bit CheckSum
U16 xCheckSum_CRC16_Calculate(xCRC16_TYPE Type,U8 *Data,U32 Len)
{
  if(Type >= xCRC16_TYPE_MAX)
    return 0;

  const xCRC16 *pCRC = &CRC16_Table[Type];
  U8  Shift    = 16 - pCRC->Width;
  U16 Mask     = (0xFFFF >> Shift);
  U16 Result   = pCRC->Init << Shift;
  U16 Poly     = pCRC->Poly << Shift;
  U16 XOR_Out  = pCRC->XOR_Out; 

  for(U32 i=0;i<Len;i++)
  {
    U16 Byte = Data[i];
    if(pCRC->RefIn)
      Byte = (U16)xCRC16_Reflect(Byte,8);
    
    Result ^= (Byte<<8);

    for(U8 Bit = 0;Bit<8;Bit++)
      if(Result & 0x8000)
        Result = (Result << 1) ^ Poly;
      else
        Result <<= 1;
  }

  Result >>= Shift;
  if(pCRC->RefOut)
    Result = xCRC16_Reflect(Result,pCRC->Width);
  return (Result ^ XOR_Out) & Mask;
}


///@Function: xCheckSum_CRC32_Calculate
///@Descript: Calculate a 32-Bit CRC CheckSum
U32 xCheckSum_CRC32_Calculate(xCRC32_TYPE Type,U8 *Data,U32 Len)
{
  if(Type >= xCRC32_TYPE_MAX)
    return 0;

  const xCRC32 *pCRC = &CRC32_Table[Type];
  U8  Shift   = 32 - pCRC->Width;
  U32 Mask    = (0xFFFFFFFF >> Shift);
  U32 Result  = pCRC->Init << Shift;
  U32 Poly    = pCRC->Poly << Shift;
  U32 XOR_Out = pCRC->XOR_Out;

  for(U32 i=0;i<Len;i++)
  {
    U32 Byte = Data[i];

    if(pCRC->RefIn)
      Byte = xCRC32_Reflect(Byte,8);

    Result ^= (Byte << 24);
    for(U8 Bit = 0;Bit < 8;Bit++)
      if(Result & 0x80000000)
        Result = (Result << 1) ^ Poly;
      else
        Result <<= 1;
  }

  Result >>= Shift;
  if(pCRC->RefOut)
    Result = xCRC32_Reflect(Result,pCRC->Width);
  return (Result ^ XOR_Out) & Mask;
}


///@Function: xCheckSum_CRC64_Calculate
///@Descript: Calculate a 64-Bit CRC CheckSum
U64 xCheckSum_CRC64_Calculate(xCRC64_TYPE Type,U8 *Data,U32 Len)
{
  if(Type >= xCRC64_TYPE_MAX)
    return 0;

  const xCRC64 *pCRC = &CRC64_Table[Type];
  U64 Mask     = (pCRC->Width == 64) ? 0xFFFFFFFFFFFFFFFFULL : ((1ULL << pCRC->Width) - 1);
  U64 Result   = pCRC->Init;
  U64 Poly     = pCRC->Poly;
  U64 XOR_Out  = pCRC->XOR_Out;

  for(U32 i = 0;i < Len;i++)
  {
    U64 Byte = Data[i];

    if(pCRC->RefIn)
      Byte = xCRC64_Reflect(Byte,8);

    Result ^= (Byte << 56);
    for(U8 Bit = 0;Bit < 8;Bit++)
      if(Result & 0x8000000000000000ULL)
        Result = (Result << 1) ^ Poly;
      else
        Result <<= 1;
  }

  if(pCRC->RefOut)
    Result = xCRC64_Reflect(Result,pCRC->Width);

  return (Result ^ XOR_Out) & Mask;
}


///@Function: xCRC8_Reflect
///@Descript: Perform Bit Reflection on a 8-Bit Value
static U8 xCRC8_Reflect(U8 Data,U8 Len)
{
  U8 Result = 0;
  for(U8 i=0;i<Len;i++)
    if(Data & (1<<i))
      Result |= (1<<(Len-1-i));
  return Result;
}


///@Function: xCRC16_Reflect
///@Descript: Perform Bit Reflection on a 16-Bit Value
static U16 xCRC16_Reflect(U16 Data,U8 Len)
{
  U16 Result = 0;
  for(U8 i=0;i<Len;i++)
    if(Data & (1<<i))
      Result |= (1<<(Len-1-i));
  return Result;
}

///@Function: xCRC32_Reflect
///@Descript: Perform Bit Reflection on a 32-Bit Value
static U32 xCRC32_Reflect(U32 Data,U8 Len)
{
  U32 Result = 0;
  for(U8 i=0;i<Len;i++)
    if(Data & (1 << i))
      Result |= (1 << (Len - 1 -i));
  return Result;
}

///@Function: xCRC64_Reflect
///@Descript: Performs Bit Reflection on a 64-Bit Value
static U64 xCRC64_Reflect(U64 Data,U8 Len)
{
  U64 Result = 0;
  for(U8 i = 0;i < Len;i++)
    if(Data & (1ULL << i))
      Result |= (1ULL << (Len - 1 - i));
  return Result;
}
