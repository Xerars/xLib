# xCheckSum

> **Project** : xCheckSum
> **Author**  : William Hsiao
> **Descript**: Data validation library for embedded systems.


## Introduction
`xCheckSum` is one of the core modules in the `xDuff` tool library, designed to provide an efficient and reliable error detection mechanism for data communication and storage.

This module is optimized for embedded environments, supports multiple industry-standard protocols, and provides dual `APIs` for both "computation" and "verification," simplifying the development process.

## Features
1. Comprehensive Support: Covers CheckSum, BCC, LRC, Fletcher, Adler, and the complete CRC family.
2. Parameterized Configuration: The CRC module supports over 100 standard models and allows flexible switching between Poly and inversion configurations.
3. High-Performance Optimization: Optimized for bit operations, providing processing capabilities across different widths from U8 to U64.
4. Easy Integration: Unified API design (Calculate/Verify) supports streaming data processing.


### CheckSum Module
Includes basic two's complement summation, the `Fletcher` algorithm, and `Adler-32`, balancing computational speed and error detection capabilities.

### BCC Module
Block Check Character provides block check based on XOR (`XOR`) and SUM (`SUM`) operations, suitable for traditional instruction communication protocols.

### LRC Module
Longitudinal Redundancy Check is primarily used in the `Modbus ASCII` protocol, based on two's complement arithmetic.

### CRC Module
Cyclic Redundancy Check is currently the most reliable check mechanism in the industry. This library supports the full range of standard models from `3-bit` to `64-bit` and has optimized computational performance for embedded environments.

##### CRC-8
|       Name (Type)       | Width |  Poly  | Initial | Output XOR | RefIn/Out |        Alias       |
| :---------------------- | :---: | :----- | :------ | :--------- | :-------: | :----------------- |
| `xCRC3_TYPE_GSM`        |   3   |  0x03  |  0x00   |    0x07    |    0/0    | CRC-3/GSM          |
| `xCRC3_TYPE_ROHC`       |   3   |  0x03  |  0x07   |    0x00    |    1/1    | CRC-3/ROHC         |
| `xCRC4_TYPE_INTERLAKEN` |   4   |  0x03  |  0x0F   |    0x0F    |    0/0    | CRC-4/INTERLAKEN   |
| `xCRC4_TYPE_ITU`        |   4   |  0x03  |  0x00   |    0x00    |    1/1    | CRC-4/ITU          |
| `xCRC5_TYPE_EPC`        |   5   |  0x09  |  0x09   |    0x00    |    0/0    | CRC-5/EPC          |
| `xCRC5_TYPE_ITU`        |   5   |  0x15  |  0x00   |    0x00    |    1/1    | CRC-5/ITU          |
| `xCRC5_TYPE_USB`        |   5   |  0x05  |  0x1F   |    0x1F    |    1/1    | CRC-5/USB          |
| `xCRC6_TYPE_ITU`        |   6   |  0x03  |  0x00   |    0x00    |    1/1    | CRC-6/ITU          |
| `xCRC6_TYPE_CDMA2000A`  |   6   |  0x27  |  0x3F   |    0x00    |    0/0    | CRC-6/CDMA2000-A   |
| `xCRC6_TYPE_CDMA2000B`  |   6   |  0x07  |  0x3F   |    0x00    |    0/0    | CRC-6/CDMA2000-B   |
| `xCRC6_TYPE_DARC`       |   6   |  0x19  |  0x00   |    0x00    |    1/1    | CRC-6/DARC         |
| `xCRC6_TYPE_GSM`        |   6   |  0x2F  |  0x00   |    0x3F    |    0/0    | CRC-6/GSM          |
| `xCRC7_TYPE_UMTS`       |   7   |  0x45  |  0x00   |    0x00    |    0/0    | CRC-7/UMTS         |
| `xCRC7_TYPE_MMC`        |   7   |  0x09  |  0x00   |    0x00    |    0/0    | CRC-7/MMC, SD Card |
| `xCRC8_TYPE_DEFAULT`    |   8   |  0x07  |  0x00   |    0x00    |    0/0    | CRC-8              |
| `xCRC8_TYPE_AUTOSAR`    |   8   |  0x2F  |  0xFF   |    0xFF    |    0/0    | AutoSar            |
| `xCRC8_TYPE_BLUETOOTH`  |   8   |  0xA7  |  0x00   |    0x00    |    1/1    | Bluetooth          |
| `xCRC8_TYPE_CDMA2000`   |   8   |  0x9B  |  0xFF   |    0x00    |    0/0    | CDMA2000           |
| `xCRC8_TYPE_DARC`       |   8   |  0x39  |  0x00   |    0x00    |    1/1    | DARC               |
| `xCRC8_TYPE_DVB_S2`     |   8   |  0xD5  |  0x00   |    0x00    |    0/0    | DVB-S2             |
| `xCRC8_TYPE_GSM_A`      |   8   |  0x1D  |  0x00   |    0x00    |    0/0    | GSM-A              |
| `xCRC8_TYPE_GSM_B`      |   8   |  0x49  |  0x00   |    0xFF    |    0/0    | GSM-B              |
| `xCRC8_TYPE_HITAG`      |   8   |  0x1D  |  0xFF   |    0x00    |    0/0    | HitAg              |
| `xCRC8_TYPE_I432_1`     |   8   |  0x07  |  0x00   |    0x55    |    0/0    | I432-1, ITU        |
| `xCRC8_TYPE_ICODE`      |   8   |  0x1D  |  0xFD   |    0x00    |    0/0    | ICode              |
| `xCRC8_TYPE_LTE`        |   8   |  0x9B  |  0x00   |    0x00    |    0/0    | LTE                |
| `xCRC8_TYPE_MAXIM_DOW`  |   8   |  0x31  |  0x00   |    0x00    |    1/1    | Maxim Dow, DOW-CRC |
| `xCRC8_TYPE_MIFARE_MAD` |   8   |  0x1D  |  0xC7   |    0x00    |    0/0    | Mifare MAD         |
| `xCRC8_TYPE_NRCS5`      |   8   |  0x31  |  0xFF   |    0x00    |    0/0    | NRSC-5             |
| `xCRC8_TYPE_OPENSAFETY` |   8   |  0x2F  |  0x00   |    0x00    |    0/0    | OpenSafety         |
| `xCRC8_TYPE_ROHC`       |   8   |  0x07  |  0xFF   |    0x00    |    1/1    | ROHC               |
| `xCRC8_TYPE_SAE_J1850`  |   8   |  0x1D  |  0xFF   |    0xFF    |    0/0    | SAE-J1850          |
| `xCRC8_TYPE_SMBUS`      |   8   |  0x07  |  0x00   |    0x00    |    0/0    | SMBus              |
| `xCRC8_TYPE_TECH_3250`  |   8   |  0x1D  |  0xFF   |    0x00    |    1/1    | Tech-3250          |
| `xCRC8_TYPE_WCDMA`      |   8   |  0x9B  |  0x00   |    0x00    |    1/1    | WCDMA              |


##### CRC-16
|       Name (Type)        | Width |  Poly  | Initial | Output XOR | RefIn/Out |        Alias       |
| :----------------------- | :---: | :----- | :------ | :--------- | :-------: | :----------------- |
| `xCRC10_TYPE_ATM`        |  10   | 0x0233 | 0x0000  |  0x0000    |    0/0    | CRC-10/ATM         |
| `xCRC10_TYPE_CDMA2000`   |  10   | 0x03D9 | 0x03FF  |  0x0000    |    0/0    | CRC-10/CDMA2000    |
| `xCRC10_TYPE_GSM`        |  10   | 0x0175 | 0x0000  |  0x03FF    |    0/0    | CRC-10/GSM         |
| `xCRC11_TYPE_FLEXRAY`    |  11   | 0x0385 | 0x001A  |  0x0000    |    0/0    | CRC-11/FlexRay     |
| `xCRC11_TYPE_UMTS`       |  11   | 0x0307 | 0x0000  |  0x0000    |    0/0    | CRC-11/UMTS        |
| `xCRC12_TYPE_CDMA2000`   |  12   | 0x0F13 | 0x0FFF  |  0x0000    |    0/0    | CRC-12/CDMA2000    |
| `xCRC12_TYPE_DECT`       |  12   | 0x080F | 0x0000  |  0x0000    |    0/0    | CRC-12/DECT        |
| `xCRC12_TYPE_GSM`        |  12   | 0x0D31 | 0x0000  |  0x0FFF    |    0/0    | CRC-12/GSM         |
| `xCRC12_TYPE_UMTS`       |  12   | 0x080F | 0x0000  |  0x0000    |    0/1    | CRC-12/UMTS        |
| `xCRC13_TYPE_BBC`        |  13   | 0x1CF5 | 0x0000  |  0x0000    |    0/0    | CRC-13/BBC         |
| `xCRC14_TYPE_DARC`       |  14   | 0x0805 | 0x0000  |  0x0000    |    1/1    | CRC-14/DARC        |
| `xCRC14_TYPE_GSM`        |  14   | 0x202D | 0x0000  |  0x3FFF    |    0/0    | CRC-14/GSM         |
| `xCRC15_TYPE_CAN`        |  15   | 0x4599 | 0x0000  |  0x0000    |    0/0    | CRC-15/CAN         |
| `xCRC15_TYPE_MPT1327`    |  15   | 0x6815 | 0x0000  |  0x0001    |    0/0    | CRC-15/MPT-1327    |
| `xCRC16_TYPE_DEFAULT`    |  16   | 0x8005 | 0x0000  |  0x0000    |    1/1    | CRC-16/IBM         |
| `xCRC16_TYPE_ARC`        |  16   | 0x8005 | 0x0000  |  0x0000    |    1/1    | ARC, LHA           |
| `xCRC16_TYPE_CDMA2000`   |  16   | 0xC867 | 0xFFFF  |  0x0000    |    0/0    | CDMA2000           |
| `xCRC16_TYPE_CMS`        |  16   | 0x8005 | 0xFFFF  |  0x0000    |    0/0    | CMS                |
| `xCRC16_TYPE_DDS110`     |  16   | 0x8005 | 0x800D  |  0x0000    |    0/0    | DDS-110            |
| `xCRC16_TYPE_DECTR`      |  16   | 0x0589 | 0x0000  |  0x0001    |    0/0    | DECT-R             |
| `xCRC16_TYPE_DECTX`      |  16   | 0x0589 | 0x0000  |  0x0000    |    0/0    | DECT-X             |
| `xCRC16_TYPE_DNP`        |  16   | 0x3D65 | 0x0000  |  0xFFFF    |    1/1    | DNP-16             |
| `xCRC16_TYPE_EN13757`    |  16   | 0x3D65 | 0x0000  |  0xFFFF    |    0/0    | EN-13757           |
| `xCRC16_TYPE_GENIBUS`    |  16   | 0x1021 | 0xFFFF  |  0xFFFF    |    0/0    | GENIBUS            |
| `xCRC16_TYPE_GSM`        |  16   | 0x1021 | 0x0000  |  0xFFFF    |    0/0    | GSM                |
| `xCRC16_TYPE_IBM3740`    |  16   | 0x1021 | 0xFFFF  |  0x0000    |    0/0    | IBM-3740, AUTOSAR  |
| `xCRC16_TYPE_IBMSDLC`    |  16   | 0x1021 | 0xFFFF  |  0xFFFF    |    1/1    | IBM-SDLC, ISO-HDLC |
| `xCRC16_TYPE_ISO14443`   |  16   | 0x1021 | 0xC6C6  |  0x0000    |    1/1    | ISO-14443          |
| `xCRC16_TYPE_KERMIT`     |  16   | 0x1021 | 0x0000  |  0x0000    |    1/1    | KERMIT             |
| `xCRC16_TYPE_LJ1200`     |  16   | 0x6F63 | 0x0000  |  0x0000    |    0/0    | LJ1200             |
| `xCRC16_TYPE_M17`        |  16   | 0x5935 | 0xFFFF  |  0x0000    |    0/0    | M17                |
| `xCRC16_TYPE_MAXIM_DOW`  |  16   | 0x8005 | 0x0000  |  0xFFFF    |    1/1    | Maxim-Dow          |
| `xCRC16_TYPE_MCRF4XX`    |  16   | 0x1021 | 0xFFFF  |  0x0000    |    1/1    | MCRF4XX            |
| `xCRC16_TYPE_NRSC5`      |  16   | 0x8005 | 0xFFFF  |  0x0000    |    1/1    | NRSC-5             |
| `xCRC16_TYPE_MODBUS`     |  16   | 0x080B | 0xFFFF  |  0x0000    |    1/1    | Modbus             |
| `xCRC16_TYPE_OPENSAFETYA`|  16   | 0x5935 | 0x0000  |  0x0000    |    0/0    | OpenSafety-A       |
| `xCRC16_TYPE_OPENSAFETYB`|  16   | 0x755B | 0x0000  |  0x0000    |    0/0    | OpenSafety-B       |
| `xCRC16_TYPE_PROFIBUS`   |  16   | 0x1DCF | 0xFFFF  |  0xFFFF    |    0/0    | Profibus   　      |
| `xCRC16_TYPE_RIELLO`     |  16   | 0x1021 | 0xB2AA  |  0x0000    |    1/1    | Riello             |
| `xCRC16_TYPE_SPI_FUJITSU`|  16   | 0x1021 | 0x1D0F  |  0x0000    |    0/0    | SPI-Fujitsu        |
| `xCRC16_TYPE_T10_DIF`    |  16   | 0x8BB7 | 0x0000  |  0x0000    |    0/0    | T10-DIF            |
| `xCRC16_TYPE_TELEDISK`   |  16   | 0xA097 | 0x0000  |  0x0000    |    0/0    | Teledisk           |
| `xCRC16_TYPE_TMS37157`   |  16   | 0x1021 | 0x89EC  |  0x0000    |    1/1    | TMS37157           |
| `xCRC16_TYPE_UMTS`       |  16   | 0x8005 | 0x0000  |  0x0000    |    0/0    | UMTS               |
| `xCRC16_TYPE_USB`        |  16   | 0x8005 | 0xFFFF  |  0xFFFF    |    1/1    | USB                |
| `xCRC16_TYPE_XMODEM`     |  16   | 0x1021 | 0x0000  |  0x0000    |    0/0    | XMODEM, ZMODEM     |

##### CRC-32
|       Name (Type)        | Width |    Poly    |  Initial   | Output XOR | RefIn/Out |       Alias        |
| :----------------------- | :---: | :--------- | :--------- | :--------- | :-------: | :----------------- |
| `xCRC17_TYPE_CANFD`      |  17   | 0x1685B    | 0x00000    | 0x00000    |    0/0    | CRC-17/CAN-FD      |
| `xCRC21_TYPE_CANFD`      |  21   | 0x102899   | 0x000000   | 0x000000   |    0/0    | CRC-21/CAN-FD      |
| `xCRC24_TYPE_BLE`        |  24   | 0x00065B   | 0x555555   | 0x000000   |    1/1    | CRC-24/BLE         |
| `xCRC24_TYPE_FLEXRAYA`   |  24   | 0x5D6DCB   | 0xFEDCBA   | 0x000000   |    0/0    | CRC-24/FlexRay-A   |
| `xCRC24_TYPE_FLEXRAYB`   |  24   | 0x5D6DCB   | 0xABCDEF   | 0x000000   |    0/0    | CRC-24/FlexRay-B   |
| `xCRC24_TYPE_INTERLAKEN` |  24   | 0x328B63   | 0xFFFFFF   | 0xFFFFFF   |    0/0    | CRC-24/Interlaken  |
| `xCRC24_TYPE_LTE_A`      |  24   | 0x864CFB   | 0x000000   | 0x000000   |    0/0    | CRC-24/LTE-A       |
| `xCRC24_TYPE_LTE_B`      |  24   | 0x800063   | 0x000000   | 0x000000   |    0/0    | CRC-24/LTE-B       |
| `xCRC24_TYPE_OPENPGP`    |  24   | 0x864CFB   | 0xB704CE   | 0x000000   |    0/0    | CRC-24/OpenPGP     |
| `xCRC24_TYPE_OS9`        |  24   | 0x800063   | 0xFFFFFF   | 0xFFFFFF   |    0/0    | CRC-24/OS-9        |
| `xCRC30_TYPE_CDMA`       |  30   | 0x2030B9C7 | 0x3FFFFFFF | 0x3FFFFFFF |    0/0    | CRC-30/CDMA        |
| `xCRC31_TYPE_PHILIPS`    |  31   | 0x04C11DB7 | 0x7FFFFFFF | 0x7FFFFFFF |    0/0    | CRC-31/Philips     |
| `xCRC32_TYPE_DEFAULT`    |  32   | 0x04C11DB7 | 0xFFFFFFFF | 0xFFFFFFFF |    1/1    | CRC-32 (ISO/HDLC)  |
| `xCRC32_TYPE_AIXM`       |  32   | 0x814141AB | 0x00000000 | 0x00000000 |    0/0    | AIXM               |
| `xCRC32_TYPE_AUTOSAR`    |  32   | 0xF4ACFB13 | 0xFFFFFFFF | 0xFFFFFFFF |    1/1    | AUTOSAR            |
| `xCRC32_TYPE_BASE91D`    |  32   | 0xA833982B | 0xFFFFFFFF | 0xFFFFFFFF |    1/1    | BASE91-D           |
| `xCRC32_TYPE_BZIP2`      |  32   | 0x04C11DB7 | 0xFFFFFFFF | 0xFFFFFFFF |    0/0    | BZIP2              |
| `xCRC32_TYPE_CDOMREDC`   |  32   | 0x8001801B | 0x00000000 | 0x00000000 |    1/1    | CD-ROM-EDC         |
| `xCRC32_TYPE_CKSUM`      |  32   | 0x04C11DB7 | 0x00000000 | 0xFFFFFFFF |    0/0    | CKSUM (POSIX)      |
| `xCRC32_TYPE_ISCSI`      |  32   | 0x1EDC6F41 | 0xFFFFFFFF | 0xFFFFFFFF |    1/1    | iSCSI (Castagnoli) |
| `xCRC32_TYPE_HLDC`       |  32   | 0x04C11DB7 | 0xFFFFFFFF | 0xFFFFFFFF |    1/1    | ISO-HDLC           |
| `xCRC32_TYPE_JAMCRC`     |  32   | 0x04C11DB7 | 0xFFFFFFFF | 0x00000000 |    1/1    | JAMCRC             |
| `xCRC32_TYPE_MEF`        |  32   | 0x741B8CD7 | 0xFFFFFFFF | 0x00000000 |    1/1    | MEF                |
| `xCRC32_TYPE_MPEG2`      |  32   | 0x04C11DB7 | 0xFFFFFFFF | 0x00000000 |    0/0    | MPEG-2             |
| `xCRC32_TYPE_XFER`       |  32   | 0x000000AF | 0x00000000 | 0x00000000 |    0/0    | Xfer               |
| `xCRC32_TYPE_KOOPMAN`    |  32   | 0x741B8CD7 | 0xFFFFFFFF | 0xFFFFFFFF |    1/1    | Koopman            |

##### CRC-64
|       Name (Type)        | Width |        Poly        |        Initial     |    Output XOR      | RefIn/Out |    Alias    |
| :----------------------- | :---: | :----------------- | :----------------- | :----------------- | :-------: | :---------- |
| `xCRC64_TYPE_DEFAULT`    |  64   | 0x42F0E1EBA9EA3693 | 0x0000000000000000 | 0x0000000000000000 |     0/0   | ECMA-182    |
| `xCRC64_TYPE_GO_ISO`     |  64   | 0x000000000000001B | 0xFFFFFFFFFFFFFFFF | 0xFFFFFFFFFFFFFFFF |     1/1   | GO-ISO      |
| `xCRC64_TYPE_MS`         |  64   | 0x259C84CBA6426349 | 0xFFFFFFFFFFFFFFFF | 0x0000000000000000 |     1/1   | Microsoft   |
| `xCRC64_TYPE_NVME`       |  64   | 0xAD93D23594C93659 | 0xFFFFFFFFFFFFFFFF | 0xFFFFFFFFFFFFFFFF |     1/1   | NVMe        |
| `xCRC64_TYPE_REDIS`      |  64   | 0xAD93D23594C935A9 | 0x0000000000000000 | 0x0000000000000000 |     1/1   | Redis       |
| `xCRC64_TYPE_WE`         |  64   | 0x42F0E1EBA9EA3693 | 0xFFFFFFFFFFFFFFFF | 0xFFFFFFFFFFFFFFFF |     0/0   | CRC-64/WE   |
| `xCRC64_TYPE_XZ`         |  64   | 0x42F0E1EBA9EA3693 | 0xFFFFFFFFFFFFFFFF | 0xFFFFFFFFFFFFFFFF |     1/1   | XZ          |

## API
### CheckSum Module
Provides higher-order checksums for `Fletcher` and `Adler`, as well as two's complement summation.
* `Fletcher` (`Fletcher` checksum)
  1. `xCheckSum_Fletcher8_Calculate`: Calculates the 8-bit Fletcher checksum (returns `U8`).
  2. `xCheckSum_Fletcher16_Calculate`: Calculates the 16-bit Fletcher checksum (returns `U16`).
  3. `xCheckSum_Fletcher32_Calculate`: Calculates the 32-bit Fletcher checksum (returns `U32`).
  4. `xCheckSum_Fletcher8_Verify`: Verifies the 8-bit Fletcher checksum.
  5. `xCheckSum_Fletcher16_Verify`: Verifies the correctness of the 16-bit Fletcher checksum.
  6. `xCheckSum_Fletcher32_Verify`: Verifies the correctness of the 32-bit Fletcher checksum.

* `Adler` (Adler-32 checksum)
  1. `xCheckSum_Adler32_Calculate`: Calculates the 32-bit Adler checksum, suitable for longer data.
  2. `xCheckSum_Adler32_Verify`: Verifies the correctness of the 32-bit Adler checksum.

* `2's Complement Sum` (2's complement sum)
  1. `xCheckSum_Comp8_Calculate`: Calculates the two's complement of the 8-bit sum.
  2. `xCheckSum_Comp16_Calculate`: Calculates the two's complement of a 16-bit sum.
  3. `xCheckSum_Comp32_Calculate`: Calculates the two's complement of a 32-bit sum.
  4. `xCheckSum_Comp8_Verify`: Verifies the 8-bit two's complement checksum at the end of the data.
  5. `xCheckSum_Comp16_Verify`: Verifies the 16-bit two's complement checksum at the end of the data.
  6. `xCheckSum_Comp32_Verify`: Verifies the 32-bit two's complement checksum at the end of the data.

### BCC Module
Block checksum, supporting both XOR (`Exclusive OR`) and SUM (`Sum`) modes.
1.  `xCheckSum_BCC8_XOR_Calculate` : Calculates an 8-bit XOR block checksum.
2.  `xCheckSum_BCC8_SUM_Calculate` : Calculates an 8-bit SUM block checksum.
3.  `xCheckSum_BCC16_XOR_Calculate`: Calculates a 16-bit XOR block checksum.
4.  `xCheckSum_BCC16_SUM_Calculate`: Calculates a 16-bit SUM block checksum.
5.  `xCheckSum_BCC32_XOR_Calculate`: Calculates a 32-bit XOR block checksum.
6.  `xCheckSum_BCC32_SUM_Calculate`: Calculates a 32-bit summation checksum.
7.  `xCheckSum_BCC8_XOR_Verify`    : Verifies an 8-bit XOR checksum.
8.  `xCheckSum_BCC8_SUM_Verify`    : Verifies an 8-bit summation checksum.
9.  `xCheckSum_BCC16_XOR_Verify`   : Verifies a 16-bit XOR checksum.
10. `xCheckSum_BCC16_SUM_Verify`   : Verifies a 16-bit summation checksum.
11. `xCheckSum_BCC32_XOR_Verify`   : Verifies a 32-bit XOR checksum.
12. `xCheckSum_BCC32_SUM_Verify`   : Verifies the cumulative check result of `32-bit`.

### LRC Module
Longitudinal redundancy check (LRC) is based on the operation of summing data and then taking its complement.
1.  `xCheckSum_LRC8_Calculate` : Calculates the 8-bit LRC checksum (commonly used in Modbus ASCII).
2.  `xCheckSum_LRC16_Calculate`: Calculates the 16-bit LRC checksum.
3.  `xCheckSum_LRC32_Calculate`: Calculates the 32-bit LRC checksum.
4.  `xCheckSum_LRC8_Verify`    : Verifies the 8-bit LRC (checks if the sum is 0).
5.  `xCheckSum_LRC16_Verify`   : Verifies the 16-bit LRC (checks if the sum is 0).
6.  `xCheckSum_LRC32_Verify`   : Verifies `32-Bit LRC` (checks if the sum is 0).

### CRC Module
A full range of cyclic redundancy check (CRC) functions, supporting table lookup and custom parameter configuration.
1.  `xCheckSum_CRC8_Calculate` : Calculates an 8-bit CRC checksum based on the specified type.
2.  `xCheckSum_CRC16_Calculate`: Calculates a 16-bit CRC checksum based on the specified type.
3.  `xCheckSum_CRC32_Calculate`: Calculates a 32-bit CRC checksum based on the specified type.
4.  `xCheckSum_CRC64_Calculate`: Calculates a 64-bit CRC checksum based on the specified type.


## Library Information
1. xCheckSum Library Size: `2.683` KB
```c
xCheckSum_Adler32_Calculate    // Occupied 118 Bytes
xCheckSum_Adler32_Verify       // Occupied 83  Bytes
xCheckSum_Comp16_Calculate     // Occupied 381 Bytes
xCheckSum_Comp16_Verify        // Occupied 67  Bytes
xCheckSum_Comp32_Calculate     // Occupied 437 Bytes
xCheckSum_Comp32_Verify        // Occupied 83  Bytes
xCheckSum_Comp8_Calculate      // Occupied 277 Bytes
xCheckSum_Comp8_Verify         // Occupied 51  Bytes
xCheckSum_Fletcher16_Calculate // Occupied 115 Bytes
xCheckSum_Fletcher16_Verify    // Occupied 67  Bytes
xCheckSum_Fletcher32_Calculate // Occupied 286 Bytes
xCheckSum_Fletcher32_Verify    // Occupied 83  Bytes
xCheckSum_Fletcher8_Calculate  // Occupied 115 Bytes
xCheckSum_Fletcher8_Verify     // Occupied 51  Bytes
```

2. xCheckSum_BCC library size: 3.245 KB
```c
xCheckSum_BCC16_SUM_Calculate  // Occupied 430 Bytes
xCheckSum_BCC16_SUM_Verify     // Occupied 67  Bytes
xCheckSum_BCC16_XOR_Calculate  // Occupied 430 Bytes
xCheckSum_BCC16_XOR_Verify     // Occupied 67  Bytes
xCheckSum_BCC32_SUM_Calculate  // Occupied 489 Bytes
xCheckSum_BCC32_SUM_Verify     // Occupied 83  Bytes
xCheckSum_BCC32_XOR_Calculate  // Occupied 490 Bytes
xCheckSum_BCC32_XOR_Verify     // Occupied 83  Bytes
xCheckSum_BCC8_SUM_Calculate   // Occupied 278 Bytes
xCheckSum_BCC8_SUM_Verify      // Occupied 51  Bytes
xCheckSum_BCC8_XOR_Calculate   // Occupied 358 Bytes
xCheckSum_BCC8_XOR_Verify      // Occupied 51  Bytes
```

1. xCheckSum_LRC library size: 2.696 KB
```c
xCheckSum_LRC16_Calculate      // Occupied 437 Bytes
xCheckSum_LRC16_Verify         // Occupied 429 Bytes
xCheckSum_LRC32_Calculate      // Occupied 489 Bytes
xCheckSum_LRC32_Verify         // Occupied 537 Bytes
xCheckSum_LRC8_Calculate       // Occupied 381 Bytes
xCheckSum_LRC8_Verify          // Occupied 277 Bytes
```

1. xCheckSum_CRC library size: 4.966 KB
```c
xCheckSum_CRC16_Calculate      // Occupied 793 Bytes
xCheckSum_CRC32_Calculate      // Occupied 645 Bytes
xCheckSum_CRC64_Calculate      // Occupied 649 Bytes
xCheckSum_CRC8_Calculate       // Occupied 750 Bytes

//Configuration table data usage
CRC16_Table                    // Occupied 564 Bytes
CRC32_Table                    // Occupied 520 Bytes
CRC64_Table                    // Occupied 280 Bytes
CRC8_Table                     // Occupied 420 Bytes
```

## Compilation Dependencies
##### [Header Dependencies]
1. `xMeta.h`
2. `xType.h`


#### [Compilation]
Use the command `make all` within the `xCheckSum` folder.

```shell
make all
```

#### [Standalone Use]
Each module can be used independently. Depending on the project size, it can be divided into independent modules for import and use; it's not necessary to use the entire `xCheckSum.h` file.
1. Use `xCheckSum_BCC.h` independently
2. Use `xCheckSum_CRC.h` independently
3. Use `xCheckSum_LRC.h` independently

```c
#include "xCheckSum_BCC.h"
#include "xCheckSum_CRC.h"
#include "xCheckSum_LRC.h"
```

#### [Example 1]
1. Demonstration of using the checksum calculation and verification functions within `xCheckSum`

```c
  U8 Data1[] = "123456789";
  U32 Len1 = sizeof(Data1)  - 1;

  //Fletcher
  U8  C21 = xCheckSum_Fletcher8_Calculate (Data1,Len1) ;
  U16 C22 = xCheckSum_Fletcher16_Calculate(Data1,Len1) ;
  U32 C23 = xCheckSum_Fletcher32_Calculate(Data1,Len1) ;

  U8 *Out21 = (U8*) malloc(Len1 + 1) ;
  U8 *Out22 = (U8*) malloc(Len1 + 2) ;
  U8 *Out23 = (U8*) malloc(Len1 + 4) ;

  MEMCOPY(Out21,Data1,Len1) ;
  MEMCOPY(Out22,Data1,Len1) ;
  MEMCOPY(Out23,Data1,Len1) ;

  Out21[Len1]   = C21;
  
  Out22[Len1]   = (U8) (C22 >> 8) ;
  Out22[Len1+1] = (U8) (C22 & 0xFF) ;

  Out23[Len1]   = (U8) (C23 >> 24) ;
  Out23[Len1+1] = (U8) (C23 >> 16) ;
  Out23[Len1+2] = (U8) (C23 >> 8) ;
  Out23[Len1+3] = (U8) (C23 & 0xFF) ;
  int V21 = xCheckSum_Fletcher8_Verify (Out21,Len1+1) ;
  int V22 = xCheckSum_Fletcher16_Verify(Out22,Len1+2) ;
  int V23 = xCheckSum_Fletcher32_Verify(Out23,Len1+4) ;
  printf("Fletcher-8  : 0x%X (Check:%d) \n",C21,V21) ;
  printf("Fletcher-16 : 0x%X (Check:%d) \n",C22,V22) ;
  printf("Fletcher-32 : 0x%X (Check:%d) \n",C23,V23) ;

  SAFE_DESTROY(Out21) ;
  SAFE_DESTROY(Out22) ;
  SAFE_DESTROY(Out23) ;
```

#### [Example 2] 
1. Demonstrating the use of the `BCC` function to calculate and verify the checksum.

```c
  U8 Data1[] = "123456789";
  U32 Len1 = sizeof(Data1)  - 1;
  //BCC-8 XOR
  U8 *Out1 = (U8*) malloc(Len1 + 1) ;
  if(Out1) 
  {
    U8 B8X = xCheckSum_BCC8_XOR_Calculate(Data1,Len1) ;
    MEMCOPY(Out1,Data1,Len1) ;
    Out1[Len1] = B8X;
    int V8X = xCheckSum_BCC8_XOR_Verify(Out1,Len1+1) ;
    printf("BCC-8 XOR    : 0x%02X (Check:%d) \n",B8X,V8X) ;
    SAFE_DESTROY(Out1) ;
  }
```

#### [Example 3]
1. Demonstrating the use of the `LRC` function to calculate and verify checksums.

```c
  U8 Data1[] = "123456789";
  U32 Len1 = strlen((char*) Data1) ;

  U8  L8  = xCheckSum_LRC8_Calculate (Data1,Len1) ;
  U16 L16 = xCheckSum_LRC16_Calculate(Data1,Len1) ;
  U32 L32 = xCheckSum_LRC32_Calculate(Data1,Len1) ;

  U8 *Out8  = (U8*) malloc(Len1+1) ;
  U8 *Out16 = (U8*) malloc(Len1+2) ;
  U8 *Out32 = (U8*) malloc(Len1+4) ;

  MEMCOPY(Out8, Data1,Len1) ;
  MEMCOPY(Out16,Data1,Len1) ;
  MEMCOPY(Out32,Data1,Len1) ;

  Out8[Len1]    = L8;

  Out16[Len1]   = (U8) (L16 >> 8) ;
  Out16[Len1+1] = (U8) (L16 & 0xFF) ;

  Out32[Len1]   = (U8) (L32 >> 24) ;
  Out32[Len1+1] = (U8) (L32 >> 16) ;
  Out32[Len1+2] = (U8) (L32 >> 8) ;
  Out32[Len1+3] = (U8) (L32 & 0xFF) ;

  int V8  = xCheckSum_LRC8_Verify (Out8, Len1 + 1) ;
  int V16 = xCheckSum_LRC16_Verify(Out16,Len1 + 2) ;
  int V32 = xCheckSum_LRC32_Verify(Out32,Len1 + 4) ;

  printf("LRC-8  : 0x%02X (Check:%d) \n",L8, V8) ;
  printf("LRC-16 : 0x%04X (Check:%d) \n",L16,V16) ;
  printf("LRC-32 : 0x%08X (Check:%d) \n",L32,V32) ;

  SAFE_DESTROY(Out8) ;
  SAFE_DESTROY(Out16) ;
  SAFE_DESTROY(Out32) ;
```

#### [Example 4]
1. Demonstrating the use of the `CRC` function to calculate and verify the checksum.

```C
  printf("CRC-8 [NONE       ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_NONE      ,Data1,Len1) ) ;       //PASS[F4]
  printf("CRC-8 [AUTOSAR    ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_AUTOSAR   ,Data1,Len1) ) ;       //PASS[DF]
  printf("CRC-8 [BLUETOOTH  ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_BLUETOOTH ,Data1,Len1) ) ;       //PASS[26]
  printf("CRC-8 [CDMA2000   ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_CDMA2000  ,Data1,Len1) ) ;       //PASS[DA]
  printf("CRC-8 [DARC       ]: 0x%X\n",xCheckSum_CRC8_Calculate(xCRC8_TYPE_DARC      ,Data1,Len1) ) ;       //PASS[15] 
```

## License Terms
This project is licensed under the `MIT License`.
