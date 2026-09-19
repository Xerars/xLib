# xSTM

> **Project** : xSTM
> **Author**  : William Hsiao
> **Descript**: STM32 硬體與周邊工具庫
> **Version** : 1.0.0

## 簡介

`xSTM` 是供使用 `STM32 HAL` 的專案使用的輕量級工具庫，透過單一管理標頭 `xSTM.h` 集中常用的裝置層功能。

本庫採用可獨立選用的 `PlugIn` 架構。在 `xSTM_Config.h` 選擇應用程式需要的 `PlugIn`，並將對應的 `.c` 檔加入 `Target`。目前預設設定使用 `STM32F4 HAL` (`stm32f4xx_hal.h`)；若移植至其他 `STM32` 系列，需調整 `HAL Include` 及該系列專屬的 `Flash`、電源設定。

## 特性

1. PlugIn 架構：Debug、DWT、Flash、Sys、Power 可各自啟用或關閉。
2. 集中設定：`HAL`、時脈、`UART` 與 `Flash` 設定皆放在 `xSTM_Config.h`。
3. `UART` 除錯輸出：支援標準 `I/O` 重新導向、分類訊息與十六進位資料輸出。
4. `DWT` 計時：提供 `Cycle` 延遲、微秒計時、效能量測與週期事件。
5. 系統資訊：讀取 `CPU`、裝置、時脈、`UID`、`Boot Address` 與 `Reset Reason`。
6. `Flash` 存取：提供內部 `Flash Word`／`Buffer` 讀寫、抹除及抹除狀態檢查。
7. 電源控制：支援 `Sleep`、`Stop`、`Standby` 模式，以及 `HCLK` 分頻調整與還原。
8. C/C++ 相容：公開標頭皆提供 `extern "C"` 保護。

## 目錄結構

```text
xSTM/
├── xSTM.h                 PlugIn 管理標頭
├── xSTM_Config.h          Target HAL 與 PlugIn 設定
├── PlugIn/                PlugIn 標頭與原始碼
├── Sample/                Keil / STM32CubeMX 整合範例
└── Doc/                   函式庫文件
```

## 快速開始

1. 將 `xSTM` 資料夾複製至 `STM32CubeMX` 產生的專案。
2. 在編譯器 `Include Path` 加入 xLib 根目錄、`xSTM` 與 `xSTM/PlugIn`。
3. 編輯 `xSTM_Config.h`：選擇正確 `HAL` 標頭，設定實際系統時脈與 `Debug UART Handle`，並只啟用需要的 `xSTM_SUPPORT_*`。
4. 將使用到的 `PlugIn` `.c` 檔加入 `Target`；只有 `Include` 標頭不會編譯實作。
5. 在應用程式 Include `xSTM.h`。

```c
#include "xSTM.h"

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_USART2_UART_Init();

  xSTM_DWT_Init();
  xSTM_DEBUG_INFO("xSTM ready\r\n");
  while(1)
  {
  }
}
```

若在 Keil 透過 `xSTM_Debug` 使用 `printf`，請在 `Options for Target` → `Target` 啟用 `Use MicroLIB`。

## 設定

`xSTM_Config.h` 是唯一的 `Target` 相依設定位置。

```c
#include "stm32f4xx_hal.h"

#define xSTM_SUPPORT_DEBUG  1
#define xSTM_SUPPORT_DWT    1
#define xSTM_SUPPORT_FLASH  1
#define xSTM_SUPPORT_SYS    1
#define xSTM_SUPPORT_POWER  1

#define xSTM_SYS_CLOCK      84      // MHz，必須與 CubeMX 時脈設定一致
#define xSTM_DEBUG_HANDLE   huart2
```

將不需要的 `xSTM_SUPPORT_*` 設為 `0`，`xSTM.h` 便不會 `Include` 對應標頭；同時也不要將該 `PlugIn` `.c` 檔加入建置。

使用 `Flash` 或 `Power` 前，請檢查同檔中的 `MCU` 系列專屬 `HAL` 常數。`xSTM_Config.h` 目前宣告 `extern UART_HandleTypeDef huart2`；若改用其他 `UART`，需一併修改此宣告與 `xSTM_DEBUG_HANDLE`。

## API

### xSTM_Debug
- `fputc`                   ：經由設定的 `UART` 重新導向標準輸出。
- `fgetc`                   ：經由設定的 `UART` 重新導向標準輸入。
- `xSTM_HexDump`            ：以十六進位輸出 `Byte Buffer`。
- `xSTM_DEBUG_INFO`         ：輸出 `Info` 分類訊息。
- `xSTM_DEBUG_WARN`         ：輸出 `Warning` 分類訊息。
- `xSTM_DEBUG_ERROR`        ：輸出 `Error` 分類訊息。
- `xSTM_DEBUG_HEXDUMP`      ：`HexDump` 巨集包裝。

### xSTM_DWT
- `xSTM_DWT_Init`           ：使用其他 `DWT` 函式前，先啟用 `Cortex-M DWT Cycle Counter`。
- `xSTM_DWT_DelayCycle`     ：以 `Cycle` 為單位進行阻塞式延遲。
- `xSTM_DWT_DelayUS`        ：以微秒為單位進行阻塞式延遲。
- `xSTM_DWT_Delay10US`      ：以 10 微秒為單位進行阻塞式延遲。
- `xSTM_DWT_DelayMS`        ：以毫秒為單位進行阻塞式延遲。
- `xSTM_DWT_GetCycle`       ：取得目前 `Cycle Count`。
- `xSTM_DWT_GetUS`          ：取得目前已過的微秒數。
- `xSTM_DWT_PerfStart`      ：取得效能量測的起始 `Cycle Count`。
- `xSTM_DWT_PerfFinish`     ：計算自起始時間經過的微秒數。
- `xSTM_DWT_TimerEvent`     ：處理一個非阻塞週期或單次事件。
- `xSTM_DWT_TIMER_START`    ：開始巨集式週期任務區段。
- `xSTM_DWT_TIMER_FINISH`   ：結束巨集式週期任務區段。

### xSTM_Flash
- `xSTM_Flash_Read`         ：讀取一個 32-bit `Flash Word`。
- `xSTM_Flash_Write`        ：寫入一個 32-bit `Flash Word`。
- `xSTM_Flash_ReadBuf`      ：從 `Flash` 讀取資料至 `Buffer`。
- `xSTM_Flash_WriteBuf`     ：將 `Buffer` 寫入 `Flash`。
- `xSTM_Flash_IsErased`     ：檢查指定位址範圍是否為抹除狀態。
- `xSTM_Flash_Erase`        ：抹除連續的 `Flash Sector`。

### xSTM_Sys
- `xSTM_SYS_GetUID`         ：取得 96-bit `Unique ID`。
- `xSTM_SYS_GetCPUID`       ：取得 `CPU ID Register`。
- `xSTM_SYS_GetVer`         ：取得 `CPU Revision`。
- `xSTM_SYS_GetDeviceID`    ：取得 `STM32 Device ID`。
- `xSTM_SYS_GetDevVer`      ：取得 `STM32 Device Revision`。
- `xSTM_SYS_GetReason`      ：取得 `Reset Reason Flag`。
- `xSTM_SYS_ClearReason`    ：清除 `Reset Reason Flag`。
- `xSTM_SYS_SoftReset`      ：觸發 `Software Reset`。
- `xSTM_SYS_GetTick`        ：取得系統 `Tick`，單位為毫秒。
- `xSTM_SYS_Delay`          ：進行系統 `Tick` 阻塞式延遲。
- `xSTM_SYS_GetClockInfo`   ：取得系統時脈資訊。
- `xSTM_SYS_GetBootAddress` ：取得目前 `Vector Table Address`。

### xSTM_Power
- `xSTM_Power_Sleep`        ：進入 `Sleep Mode`。
- `xSTM_Power_Stop`         ：進入 `Stop Mode`。
- `xSTM_Power_Standby`      ：進入 `Standby Mode`。
- `xSTM_Power_SetClock`     ：設定目標 `HCLK`。
- `xSTM_Power_RestoreClock` ：還原已保存的 `HCLK Divider`。

## 編譯依賴

### 標頭依賴

1. `xType.h`
2. `xMeta.h`
3. 選定 `Target` 的 `STM32 HAL` 與 `CMSIS` 標頭

### 原始碼

僅將已啟用的 `PlugIn` 原始碼加入 `Target`：

```text
xSTM/PlugIn/xSTM_Debug.c
xSTM/PlugIn/xSTM_DWT.c
xSTM/PlugIn/xSTM_Flash.c
xSTM/PlugIn/xSTM_Sys.c
xSTM/PlugIn/xSTM_Power.c
```

本庫會存取 `STM32 HAL` 與 `Cortex-M` 暫存器，不適合直接以 `Linux Host GCC` 編譯。請搭配 `STM32CubeMX` 產生的 `HAL`／`CMSIS`，以 `Keil MDK-ARM` 或 `arm-none-eabi-gcc` 等目標工具鏈建置。

## 庫大小量測

請從目標程式的 `ELF`／`AXF` 量測，而非 `Host` 系統。最終大小受 `MCU`、啟用的 `PlugIn`、最佳化等級、實際呼叫的 `API`、`HAL` 版本與 `linker` 未使用函式移除影響。

在相同設定下建置「基準應用程式」及「實際呼叫所需 `xSTM API` 的應用程式」，比較兩者 `Flash` 與 `RAM` 差值。`GNU Arm Embedded Toolchain` 可使用：

```shell
arm-none-eabi-size -A app.elf
arm-none-eabi-nm -S --size-sort --radix=d app.elf | grep xSTM_
```

`Keil` 的 `AXF` 輸出可使用 `fromelf --text -s app.axf` 檢視 `Section` 與 `Symbol`。

## 範例

| 範例      | `PlugIn` | 內容                                     |
| :-------- | :------- | :-------------------------------------- |
| `Sample1` | `Debug`  | `UART I/O` 重新導向、訊息與 `HexDump`    |
| `Sample2` | `DWT`    | 延遲、時間、效能與週期事件                |
| `Sample3` | `Sys`    | `CPU`、裝置、時脈、`UID`與`Reset`資訊    |
| `Sample4` | `Power`  | `HCLK` 調整與低功耗模式                  |
| `Sample5` | `Flash`  | 保留區設定、讀寫、抹除與單元測試          |

建置前請閱讀各 `Sample` 資料夾內的 `ReadmeEn.md` 或 `ReadmeZh.md`。

## 注意事項

1. `xSTM_SYS_CLOCK` 與 `xSTM_DWT_SYS_CLOCK` 必須符合 `MCU` 實際時脈，否則 `DWT` 延遲與計時結果會錯誤。
2. DWT `Cycle Counter` 是否可用取決於 `Cortex-M` 核心，請先確認目標裝置支援。
3. `xSTM_DWT_TimerEvent()` 使用一組內部 `static` 狀態，因此一次只能管理一個事件。
4. `Flash` 抹除不可復原；啟用 `xSTM_FLASH_SUPPORT_UNIT_TEST` 前，必須先於 `Linker` 設定保留測試 `Sector`。
5. `Flash Program Type`、電壓範圍、Sector 配置與低功耗常數皆與 `MCU` 系列相關，請依 `Reference Manual` 與 `HAL` 文件確認。
6. `Stop` 與 `Standby` 模式必須設定正確喚醒來源；`Standby` 喚醒後通常會重置 `MCU`。
7. 避免在應用程式標頭使用 `OR`、`AND`、`NOT` 等通用巨集名稱，以免與 `STM32 HAL` 暫存器欄位衝突。

## 授權條款

本專案採用 `MIT License` 授權使用。
