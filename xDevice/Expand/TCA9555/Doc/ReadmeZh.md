# TCA9555

> **Project** : xDuff
> **Author**  : xTCA9555
> **Descript**: TCA9555 驅動庫

## 簡介
TCA9555 是一個專為低壓 16 位元 I²C 和 SMBus 設計的 I/O 擴充器驅動庫。它支持 1.65V 至 5.5V 的廣泛電壓範圍，並提供中斷輸出與可配置暫存器功能，能有效地為微控制器擴展通用輸入/輸出 (GPIO) 接口。


## 特性
* 低待機電流消耗：最大僅 3.5 μA
* I²C 轉並行埠擴充器：高效轉換通訊協議
* 開漏低電平有效中斷輸出 (INT)：當輸入狀態改變時通知主控
* 5V 耐壓 I/O 端口：增強系統兼容性
* 相容性強：支持大多數微控制器架構
* 高速通訊：支持高達 400kHz 的 Fast I²C 匯流排
* 靈活定址：具備 3 個位址接腳，最高可設定 8 個不同從設備位址
* 極性反轉：內建極性反轉暫存器，可軟體切換輸入邏輯
* 強大驅動能力：具有大電流鎖存輸出，可直接驅動 LED
* 高可靠性：
  * 閂鎖性能超過 100 mA (符合 JESD 78 II 類標準)
  * ESD 保護超過 JESD 22 標準 (2000V HBM / 1000V CDM)

## API
#### [類型定義]
xTCA      : TCA9555 設備實體控制結構體，包含 I/O 端口配置與狀態陰影暫存器。
xTCA_Port : 定義 I²C 傳輸介面，包含從機地址、速率及硬體抽象層的讀寫回呼函數。
xTCA_PIN  : 16 位元引腳定義 (P0.0~P1.7)。
xTCA_DIR  : 方向定義。
xTCA_LEVEL: 電位定義。

#### [核心函數]
控制控制與初始化
1. xTCA_GetHandle : 獲取當前設備句柄指針。
2. xTCA_SetHandle : 設定當前操作的設備句柄。
3. xTCA_Init      : 初始化 TCA9555 設備，配置通訊介面並綁定回呼函數。
4. xTCA_Reset     : 軟體重置設備狀態，將陰影暫存器恢復至預設值。

I/O 配置與操作
1. xTCA_SetDir    : 設定指定引腳的方向(輸入或輸出)。
2. xTCA_WritePin  : 寫入指定引腳的電位狀態。
3. xTCA_TogglePin : 翻轉指定引腳的電位狀態。
4. xTCA_ReadPort  : 讀取整個 16-bit 端口的當前輸入狀態。
5. xTCA_ReadPin   : 讀取單一特定引腳的電位狀態。
6. xTCA_SetInvert : 設定輸入引腳的極性反轉功能。


## 庫資訊
1. `xTCA9555`: 庫大小 1.204 KB

``` c
xTCA_GetHandle      // 佔用 12  Bytes
xTCA_I2C_Read       // 佔用 49  Bytes
xTCA_I2C_Write      // 佔用 49  Bytes
xTCA_Init           // 佔用 81  Bytes
xTCA_ReadPin        // 佔用 25  Bytes
xTCA_ReadPort       // 佔用 89  Bytes
xTCA_Reset          // 佔用 28  Bytes
xTCA_SetDir         // 佔用 107 Bytes
xTCA_SetHandle      // 佔用 12  Bytes
xTCA_SetInvert      // 佔用 107 Bytes
xTCA_TogglePin      // 佔用 93  Bytes
xTCA_WritePin       // 佔用 107 Bytes
```

## 編譯依賴
#### [標頭依賴]
1. xMeta.h
2. xType.h

``` shell
make all
```

## 範例
在 `Sample` 資料夾內使用指令 `make all`

本範例展示了如何定義虛擬的 I²C 讀寫函數，並透過 xTCA_Init 初始化驅動程序。
隨後演示了設定引腳方向、寫入/翻轉輸出電位、讀取輸入狀態以及設定極性反轉的完整流程

```c
//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xTCA9555.h"

//[Prototype Declare]
void TCA_Fake_I2C_Write(U8 Addr, U8 Reg, U8 *pData, U32 Len);
void TCA_Fake_I2C_Read(U8 Addr, U8 Reg, U8 *pData, U32 Len);

//[Variable]
U8 Register[8] = {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF};

int main(void)
{
  xTCA      DevTCA;
  xTCA_Port DevTCA_Port;

  //Regist Communication Port and Address
  DevTCA_Port.I2C_ID    = xTCA_SLAVE_ADDR(0,0,0);
  DevTCA_Port.I2C_Speed = 400000;
  DevTCA_Port.Write     = TCA_Fake_I2C_Write;
  DevTCA_Port.Read      = TCA_Fake_I2C_Read;

  //Initial Device
  xTCA_Init(&DevTCA, &DevTCA_Port);

  //Set Direction P0.0,P0.1 Output; P1.0 P1.1 Input
  xTCA_SetDir(TCA_PIN_P00 | TCA_PIN_P01, xTCA_DIR_OUT);
  xTCA_SetDir(TCA_PIN_P10 | TCA_PIN_P11, xTCA_DIR_IN);

  //Write & Toggle
  xTCA_WritePin(TCA_PIN_P00 | TCA_PIN_P01, xTCA_LEVEL_LOW);
  xTCA_TogglePin(TCA_PIN_P00);

  //Read Status
  U16 Value = xTCA_ReadPort();
  xTCA_LEVEL Level = xTCA_ReadPin(TCA_PIN_P11);

  printf("Port Value: 0x%04X\n", Value);
  printf("P1.1 Level: %d\n", Level);

  //Set P0.0 as Invert Polarity
  xTCA_SetInvert(TCA_PIN_P00, 1);
  return 0;
}

//Fake I2C Write
void TCA_Fake_I2C_Write(U8 Addr, U8 Reg, U8 *pData, U32 Len)
{
  printf("[I2C Write] Addr: 0x%02X, Reg: 0x%02X(%d) \n",Addr,Reg,Len);
  for(U32 i = 0; i < Len; i++)
    if((Reg + i) < 8)
      Register[Reg + i] = pData[i];
}

//Fake I2C Read
void TCA_Fake_I2C_Read(U8 Addr, U8 Reg, U8 *pData, U32 Len)
{
  printf("[I2C Read ] Addr: 0x%02X, Reg: 0x%02X(%d) \n",Addr,Reg,Len);
  for(U32 i = 0; i < Len; i++)
    if((Reg + i) < 8)
      pData[i] = Register[Reg + i];
}
```

## 授權條款
本專案採用 `MIT License` 授權使用
