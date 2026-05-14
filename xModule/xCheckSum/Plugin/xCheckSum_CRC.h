#ifndef __XCRC_H__ //__XCRC_H__
#define __XCRC_H__ //__XCRC_H__

//Author  : William Hsiao
//Descript: Data Validation Library for Embedded Systems(CRC)
//Version : 1.0.0

//[STD Lib Include]
#include <stdio.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
//CRC-3
#define xCRC3_POLY_GSM              0x03        //x^3+x+1
#define xCRC3_POLY_ROHC             0x03        //x^3+x+1

//CRC-4
#define xCRC4_POLY_INTERLAKEN       0x03        //x^4+x+1
#define xCRC4_POLY_ITU              0x03        //x^4+x+1

//CRC-5
#define xCRC5_POLY_EPC              0x09        //x^5+x^3+1
#define xCRC5_POLY_ITU              0x15        //x^5+x^4+x^2+1
#define xCRC5_POLY_USB              0x05        //x^5+x^2+1

//CRC-6
#define xCRC6_POLY_ITU              0x03        //x^6+x+1
#define xCRC6_POLY_CDMA2000A        0x27        //x^6+x^5+x^2+x+1
#define xCRC6_POLY_CDMA2000B        0x07        //x^8+x^2+x+1
#define xCRC6_POLY_DARC             0x19        //x^6+x^4+x^3+1
#define xCRC6_POLY_GSM              0x2F        //x^6+x^5+x^3+x^2+x+1

//CRC-7
#define xCRC7_POLY_UMTS             0x45        //x^7+x^6+x^2+1
#define xCRC7_POLY_MMC              0x09        //x^7+x^3+1

//CRC-8
#define xCRC8_POLY_NONE             0x07        //x^8+x^2+x+1
#define xCRC8_POLY_AUTOSAR          0x2F        //x^8+x^5+x^3+x^2+x+1
#define xCRC8_POLY_BLUETOOTH        0xA7        //x^8+x^7+x^5+x^2+x+1
#define xCRC8_POLY_CDMA2000         0x9B        //x^8+x^7+x^4+x^3+x+1
#define xCRC8_POLY_DARC             0x39        //x^8+x^5+x^4+x^3+1
#define xCRC8_POLY_DVB_S2           0xD5        //x^8+x^7+x^6+x^4+x^2+1
#define xCRC8_POLY_GSM_A            0x1D        //x^8+x^4+x^3+x^2+1
#define xCRC8_POLY_GSM_B            0x49        //x^8+x^6+x^3+x+1
#define xCRC8_POLY_HITAG            0x1D        //x^8+x^4+x^3+x^2+1
#define xCRC8_POLY_I432_1           0x07        //x^8+x^2+x+1
#define xCRC8_POLY_ICODE            0x1D        //x^8+x^4+x^3+x^2+1
#define xCRC8_POLY_LTE              0x9B        //x^8+x^7+x^4+x^3+x+1
#define xCRC8_POLY_MAXIM_DOW        0x31        //x^8+x^5+x^4+x+1
#define xCRC8_POLY_MIFARE_MAD       0x1D        //x^8+x^4+x^3+x^2+1
#define xCRC8_POLY_NRSC5            0x31        //x^8+x^5+x^4+x+1
#define xCRC8_POLY_OPENSAFETY       0x2F        //x^8+x^5+x^3+x^2+x+1
#define xCRC8_POLY_ROHC             0x07        //x^8+x^2+x+1
#define xCRC8_POLY_SAE_J1850        0x1D        //x^8+x^4+x^3+x^2+1
#define xCRC8_POLY_SMBUS            0x07        //x^8+x^2+x+1
#define xCRC8_POLY_TECH_3250        0x1D        //x^8+x^4+x^3+x^2+1
#define xCRC8_POLY_WCDMA            0x9B        //x^8+x^7+x^4+x^3+x+1

// CRC-10
#define xCRC10_POLY_ATM             0x0233      // x^10+x^9+x^5+x^4+x+1
#define xCRC10_POLY_CDMA2000        0x03D9      // x^10+x^9+x^8+x^7+x^6+x^4+x^3+1
#define xCRC10_POLY_GSM             0x0175      // x^10+x^8+x^7+x^5+x^4+x^2+1

// CRC-11
#define xCRC11_POLY_FLEXRAY         0x0385      // x^11+x^9+x^8+x^7+x^2+1
#define xCRC11_POLY_UMTS            0x0307      // x^11+x^8+x^2+x+1

// CRC-12
#define xCRC12_POLY_CDMA2000        0x0F13      // x^12+x^11+x^10+x^9+x^8+x^4+x+1
#define xCRC12_POLY_DECT            0x080F      // x^12+x^11+x^3+x^2+x+1
#define xCRC12_POLY_GSM             0x0D31      // x^12+x^11+x^10+x^8+x^5+x^4+1
#define xCRC12_POLY_UMTS            0x080F      // x^12+x^11+x^3+x^2+x+1

// CRC-13
#define xCRC13_POLY_BBC             0x1CF5      // x^13+x^12+x^11+x^10+x^7+x^6+x^5+x^4+x^2+1

// CRC-14
#define xCRC14_POLY_DARC            0x0805      // x^14+x^11+x^2+1
#define xCRC14_POLY_GSM             0x202D      // x^14+x^13+x^5+x^3+x^2+1
#define xCRC14_POLY_CAN             0x0599      // x^14+x^10+x^8+x^7+x^4+x^3+1

// CRC-15
#define xCRC15_POLY_CAN             0x4599      // x^14+x^10+x^8+x^7+x^4+x^3+1
#define xCRC15_POLY_MPT1327         0x6815      // x^15+x^14+x^11+x^4+x^2+1

//CRC-16
#define xCRC16_POLY_NONE            0x8005      //x^16+x^15+x^2+1
#define xCRC16_POLY_ARC             0x8005      //x^16+x^15+x^2+1
#define xCRC16_POLY_CDMA2000        0xC867      //x^16+x^15+x^14+x^11+x^6+x^5+x^2+x+1
#define xCRC16_POLY_CMS             0x8005      //x^16+x^15+x^2+1
#define xCRC16_POLY_DDS110          0x8005      //x^16+x^15+x^2+1
#define xCRC16_POLY_DECTR           0x0589      //x^16+x^10+x^8+x^7+x^3+1
#define xCRC16_POLY_DECTX           0x0589      //x^16+x^10+x^8+x^7+x^3+1
#define xCRC16_POLY_DNP             0x3D65      //x^16+x^13+x^12+x^11+x^10+x^8+x^6+x^5+x^2+1
#define xCRC16_POLY_EN13757         0x3D65      //x^16+x^13+x^12+x^11+x^10+x^8+x^6+x^5+x^2+1
#define xCRC16_POLY_GENIBUS         0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_GSM             0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_IBM3740         0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_IBMSDLC         0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_ISO14443        0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_KERMIT          0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_LJ1200          0x6F63      //x^16+x^14+x^13+x^11+x^10+x^9+x^6+x^5+x+1
#define xCRC16_POLY_M17             0x5935      //x^16+x^14+x^12+x^11+x^8+x^5+x^4+x^2+1
#define xCRC16_POLY_MAXIM_DOW       0x8005      //x^16+x^15+x^2+1
#define xCRC16_POLY_MCRF4XX         0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_NRSC5           0x8005      //x^16+x^15+x^2+1
#define xCRC16_POLY_MODBUS          0x080B      //x^16+x^11+x^3+x+1
#define xCRC16_POLY_OPENSAFETYA     0x5935      //x^16+x^14+x^12+x^11+x^8+x^5+x^4+x^2+1
#define xCRC16_POLY_OPENSAFETYB     0x755B      //x^16+x^14+x^12+x^10+x^8+x^6+x^4+x^3+x+1
#define xCRC16_POLY_PROFIBUS        0x1DCF      //x^16+x^12+x^11+x^10+x^7+x^3+x^2+x+1
#define xCRC16_POLY_RIELLO          0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_SPI_FUJITSU     0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_T10_DIF         0x8BB7      //x^16+x^15+x^11+x^9+x^8+x^5+x^4+x^2+x+1
#define xCRC16_POLY_TELEDISK        0xA097      //x^16+x^15+x^13+x^7+x^4+x^2+x+1
#define xCRC16_POLY_TMS37157        0x1021      //x^16+x^12+x^5+1
#define xCRC16_POLY_UMTS            0x8005      //x^16+x^15+x^2+1
#define xCRC16_POLY_USB             0x8005      //x^16+x^15+x^2+1
#define xCRC16_POLY_XMODEM          0x1021      //x^16+x^12+x^5+1

//CRC-17
#define xCRC17_POLY_CANFD           0x1685B     //x^17+x^16+x^14+x^13+x^11+x^6+x^4+x^3+x+1

//CRC-21
#define xCRC21_POLY_CANFD           0x102899    //x^21+x^20+x^13+x^11+x^7+x^4+x^3+1

//CRC-24
#define xCRC24_POLY_BLE             0x00065B    //x^24+x^10+x^9+x^6+x^4+x^3+x+1
#define xCRC24_POLY_FLEXRAY         0x5D6DCB    //x^24+x^22+x^20+x^19+x^18+x^16+x^14+x^13+x^11+x^10+x^8+x^7+x^6+x^3+x+1
#define xCRC24_POLY_INTERLAKEN      0x328B63    //x^24+x^21+x^20+x^17+x^15+x^11+x^9+x^8+x^6+x^5+x^2+1
#define xCRC24_POLY_LTE_A           0x864CFB    //x^24+x^23+x^18+x^17+x^14+x^11+x^10+x^7+x^6+x^5+x^4+x^3+x+1
#define xCRC24_POLY_LTE_B           0x800063    //x^24+x^23+x^6+x^5+x^1+1
#define xCRC24_POLY_OPENPGP         0x864CFB    //x^24+x^23+x^18+x^17+x^14+x^11+x^10+x^7+x^6+x^5+x^4+x^3+x+1
#define xCRC24_POLY_OS9             0x800063    //x^24+x^23+x^6+x^5+x^1+1

//CRC-30
#define xCRC30_POLY_CDMA            0x2030B9C7  //x^30+x^29+x^21+x^20+x^15+x^13+x^12+x^11+x^8+x^7+x^6+x^2+x+1

//CRC-31
#define xCRC31_POLY_PHILIPS         0x04C11DB7  //x^31+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1

//CRC-32
#define xCRC32_POLY_NONE            0x04C11DB7  //x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1
#define xCRC32_POLY_AIXM            0x814141AB  //x^31+x^24+x^22+x^16+x^14+x^8+x^7+x^5+x^3+x+1
#define xCRC32_POLY_AUTOSAR         0xF4ACFB13  //x^31+x^30+x^29+x^28+x^26+x^23+x^22+x^19+x^18+x^17+x^15+x^14+x^13+x^12+x^11+x^8+x^4+x+1
#define xCRC32_POLY_BASE91D         0xA833982B  //x^31+x^29+x^25+x^24+x^21+x^20+x^19+x^16+x^15+x^12+x^11+x^5+x^3+x+1
#define xCRC32_POLY_BZIP2           0x04C11DB7  //x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1 [ISO3309]
#define xCRC32_POLY_CDOMREDC        0x8001801B  //x^31+x^16+x^15+x^4+x^3+x+1
#define xCRC32_POLY_CKSUM           0x04C11DB7  //x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1 [POSIX]
#define xCRC32_POLY_ISCSI           0x1EDC6F41  //x^28+x^27+x^26+x^25+x^23+x^22+x^20+x^19+x^18+x^14+x^13+x^11+x^10+x^9+x^8+x^6+1 [Castagnoli]
#define xCRC32_POLY_HLDC            0x04C11DB7  //x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1
#define xCRC32_POLY_JAMCRC          0x04C11DB7  //x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1
#define xCRC32_POLY_MEF             0x741B8CD7  //x^30+x^29+x^28+x^26+x^24+x^23+x^20+x^19+x^17+x^15+x^14+x^11+x^10+x^7+x^6+x^4+x^2+x+1
#define xCRC32_POLY_MPEG2           0x04C11DB7  //x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1
#define xCRC32_POLY_XFER            0x000000AF  //x^7+x^5+x^3+x^2+x+1
#define xCRC32_POLY_KOOPMAN         0x741B8CD7  //x^30+x^29+x^28+x^26+x^24+x^23+x^20+x^19+x^17+x^15+x^14+x^11+x^10+x^7+x^6+x^4+x^2+x+1

//CRC-64
#define xCRC64_POLY_ECMA            0x42F0E1EBA9EA3693ULL         //x^64+x^62+x^57+x^55+x^54+x^53+x^52+x^47+x^46+...
#define xCRC64_POLY_ISO             0x000000000000001BULL         //x^64+x^4+x^3+x+1
#define xCRC64_POLY_MS              0x259C84CBA6426349ULL         //x^64+x^61+x^58+x^56+x^55+x^52+x^51+...
#define xCRC64_POLY_NVME            0xAD93D23594C93659ULL         //x^64+x^63+x^61+x^59+x^58+...
#define xCRC64_POLY_REDIS           0xAD93D23594C935A9ULL         //x^64+x^63+x^61+x^59+x^58+...
#define xCRC64_POLY_WE              0x42F0E1EBA9EA3693ULL         //x^64+x^62+x^57+x^55+x^54+x^53+x^52+x^47+x^46+...
#define xCRC64_POLY_XZ              0x42F0E1EBA9EA3693ULL         //x^64+x^62+x^57+x^55+x^54+x^53+x^52+x^47+x^46+...


//[Enum Declare]
//CRC-8 Type
typedef enum _xCRC8_TYPE
{
  xCRC8_TYPE_DEFAULT     = 0,
  xCRC8_TYPE_AUTOSAR     = 1,
  xCRC8_TYPE_BLUETOOTH   = 2,
  xCRC8_TYPE_CDMA2000    = 3,
  xCRC8_TYPE_DARC        = 4,
  xCRC8_TYPE_DVB_S2      = 5,
  xCRC8_TYPE_GSM_A       = 6,
  xCRC8_TYPE_GSM_B       = 7,
  xCRC8_TYPE_HITAG       = 8,
  xCRC8_TYPE_I432_1      = 9,
  xCRC8_TYPE_ICODE       = 10,
  xCRC8_TYPE_LTE         = 11,
  xCRC8_TYPE_MAXIM_DOW   = 12,
  xCRC8_TYPE_MIFARE_MAD  = 13,
  xCRC8_TYPE_NRCS5       = 14,
  xCRC8_TYPE_OPENSAFETY  = 15,
  xCRC8_TYPE_ROHC        = 16,
  xCRC8_TYPE_SAE_J1850   = 17,
  xCRC8_TYPE_SMBUS       = 18,
  xCRC8_TYPE_TECH_3250   = 19,
  xCRC8_TYPE_WCDMA       = 20,
  xCRC3_TYPE_GSM         = 21,
  xCRC3_TYPE_ROHC        = 22,
  xCRC4_TYPE_INTERLAKEN  = 23,
  xCRC4_TYPE_ITU         = 24,
  xCRC5_TYPE_EPC         = 25,
  xCRC5_TYPE_ITU         = 26,
  xCRC5_TYPE_USB         = 27,
  xCRC6_TYPE_ITU         = 28,
  xCRC6_TYPE_CDMA2000A   = 29,
  xCRC6_TYPE_CDMA2000B   = 30,
  xCRC6_TYPE_DARC        = 31,
  xCRC6_TYPE_GSM         = 32,
  xCRC7_TYPE_UMTS        = 33,
  xCRC7_TYPE_MMC         = 34,
  xCRC8_TYPE_MAX,
} xCRC8_TYPE;


//CRC-16 Type
typedef enum _xCRC16_TYPE
{
  xCRC16_TYPE_DEFAULT     = 0,
  xCRC16_TYPE_ARC         = 1,
  xCRC16_TYPE_CDMA2000    = 2,
  xCRC16_TYPE_CMS         = 3,
  xCRC16_TYPE_DDS110      = 4,
  xCRC16_TYPE_DECTR       = 5,
  xCRC16_TYPE_DECTX       = 6,
  xCRC16_TYPE_DNP         = 7,
  xCRC16_TYPE_EN13757     = 8,
  xCRC16_TYPE_GENIBUS     = 9,
  xCRC16_TYPE_GSM         = 10,
  xCRC16_TYPE_IBM3740     = 11,
  xCRC16_TYPE_IBMSDLC     = 12,
  xCRC16_TYPE_ISO14443    = 13,
  xCRC16_TYPE_KERMIT      = 14,
  xCRC16_TYPE_LJ1200      = 15,
  xCRC16_TYPE_M17         = 16,
  xCRC16_TYPE_MAXIM_DOW   = 17,
  xCRC16_TYPE_MCRF4XX     = 18,
  xCRC16_TYPE_MODBUS      = 19,
  xCRC16_TYPE_NRSC5       = 20,
  xCRC16_TYPE_OPENSAFETYA = 21,
  xCRC16_TYPE_OPENSAFETYB = 22,
  xCRC16_TYPE_PROFIBUS    = 23,
  xCRC16_TYPE_RIELLO      = 24,
  xCRC16_TYPE_SPI_FUJITSU = 25,
  xCRC16_TYPE_T10_DIF     = 26,
  xCRC16_TYPE_TELEDISK    = 27,
  xCRC16_TYPE_TMS37157    = 28,
  xCRC16_TYPE_UMTS        = 29,
  xCRC16_TYPE_USB         = 30,
  xCRC16_TYPE_XMODEM      = 32,
  xCRC10_TYPE_ATM         = 33,
  xCRC10_TYPE_CDMA2000    = 34,
  xCRC10_TYPE_GSM         = 35,
  xCRC11_TYPE_FLEXRAY     = 36,
  xCRC11_TYPE_UMTS        = 37,
  xCRC12_TYPE_CDMA2000    = 38,
  xCRC12_TYPE_DECT        = 39,
  xCRC12_TYPE_GSM         = 40,
  xCRC12_TYPE_UMTS        = 41,
  xCRC13_TYPE_BBC         = 42,
  xCRC14_TYPE_DARC        = 43,
  xCRC14_TYPE_GSM         = 44,
  xCRC15_TYPE_CAN         = 45,
  xCRC15_TYPE_MPT1327     = 46,
  xCRC16_TYPE_MAX,
} xCRC16_TYPE;


//CRC-32 Type
typedef enum _xCRC32_TYPE
{
  xCRC32_TYPE_DEFAULT     = 0,
  xCRC32_TYPE_AIXM        = 1,
  xCRC32_TYPE_AUTOSAR     = 2,
  xCRC32_TYPE_BASE91D     = 3,
  xCRC32_TYPE_BZIP2       = 4,
  xCRC32_TYPE_CDOMREDC    = 5,
  xCRC32_TYPE_CKSUM       = 6,
  xCRC32_TYPE_ISCSI       = 7,
  xCRC32_TYPE_HLDC        = 8,
  xCRC32_TYPE_JAMCRC      = 9,
  xCRC32_TYPE_MEF         = 10,
  xCRC32_TYPE_MPEG2       = 11,
  xCRC32_TYPE_XFER        = 12,
  xCRC32_TYPE_KOOPMAN     = 13,
  xCRC17_TYPE_CANFD       = 14,
  xCRC21_TYPE_CANFD       = 15,
  xCRC24_TYPE_BLE         = 16,
  xCRC24_TYPE_FLEXRAYA    = 17,
  xCRC24_TYPE_FLEXRAYB    = 18,
  xCRC24_TYPE_INTERLAKEN  = 19,
  xCRC24_TYPE_LTE_A       = 20,
  xCRC24_TYPE_LTE_B       = 21,
  xCRC24_TYPE_OPENPGP     = 22,
  xCRC24_TYPE_OS9         = 23,
  xCRC30_TYPE_CDMA        = 24,
  xCRC31_TYPE_PHILIPS     = 25,
  xCRC32_TYPE_MAX,
} xCRC32_TYPE;


//CRC-64
typedef enum _xCRC64_TYPE
{
  xCRC64_TYPE_DEFAULT     = 0,        //ECMA-182
  xCRC64_TYPE_GO_ISO      = 1,
  xCRC64_TYPE_MS          = 2,
  xCRC64_TYPE_NVME        = 3,
  xCRC64_TYPE_REDIS       = 4,
  xCRC64_TYPE_WE          = 5,
  xCRC64_TYPE_XZ          = 6,
  xCRC64_TYPE_MAX,
} xCRC64_TYPE;



//[Struct Declare]
typedef struct _xCRC8
{
  int Width;          //Width
  U8  Poly;           //Polynomial
  U8  Init;           //Initial Value
  U8  XOR_Out;        //XOR Output
  U8  RefIn;          //Reverse Input
  U8  RefOut;         //Reverse Output
} xCRC8;


typedef struct _xCRC16
{
  int Width;          //Width
  U16 Poly;           //Polynimial
  U16 Init;           //Initial Value
  U16 XOR_Out;        //XOR Output
  U8  RefIn;          //Reverse Input
  U8  RefOut;         //Reverse Output
} xCRC16;


typedef struct _xCRC32
{
  int Width;          //Width
  U32 Poly;           //Polynomial
  U32 Init;           //Initial Value
  U32 XOR_Out;        //XOR Output
  U8  RefIn;          //Reverse Input
  U8  RefOut;         //Reverse Output
} xCRC32;


typedef struct _xCRC64
{
  int Width;          //Width
  U64 Poly;           //Polynomial
  U64 Init;           //Initial Value
  U64 XOR_Out;        //XOR Output
  U8  RefIn;          //Reverse Input
  U8  RefOut;         //Reverse Output
} xCRC64;


#ifdef __cplusplus
extern "C" {
#endif
//CRC 8/16/32/64
U8  xCheckSum_CRC8_Calculate (xCRC8_TYPE Type ,U8 *Data,U32 Len);
U16 xCheckSum_CRC16_Calculate(xCRC16_TYPE Type,U8 *Data,U32 Len);
U32 xCheckSum_CRC32_Calculate(xCRC32_TYPE Type,U8 *Data,U32 Len);
U64 xCheckSum_CRC64_Calculate(xCRC64_TYPE Type,U8 *Data,U32 Len);

#ifdef __cplusplus
}
#endif

#endif  //__XCRC_H__
