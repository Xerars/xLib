# xSTM Sample3

> **Project** : xSTM Sample3
> **Author**  : William Hsiao
> **Descript**: `xSTM_Sys` CPU、裝置、時脈與 Reset 資訊範例


## 簡介

本範例說明如何將 `xSTM_Sys` 導入 `STM32CubeMX` 與 `Keil MDK-ARM` 專案，並透過偵錯 `UART` 列印 CPU、裝置、系統時脈、Boot Address 與 Reset Reason。

`App_Init()` 在系統初始化完成後執行 `Unit Test` 並輸出系統資訊；`App_Service()` 由 `while` 主迴圈持續呼叫，執行 60 秒倒數後觸發 Software Reset。重新開機後可由 Reset Reason 確認 Software Reset。


## 使用

#### 1. 建立 `STM32CubeMX` 專案

1. 在 `STM32CubeMX` 選擇目標 `STM32` 與開發板。
2. 啟用作為偵錯輸出的 `USART`，並設定為 `Asynchronous` 模式。
3. 本範例預設使用 `USART2` 與 `huart2`。若使用其他 `USART`，請在 `xSTM_Config.h` 修改 `xSTM_DEBUG_HANDLE`。
4. 設定 `UART` 通訊參數，並使用相同設定開啟序列終端。
5. 將工具鏈設為 `MDK-ARM`，然後產生專案。

#### 2. 啟用 `MicroLIB`

在 `Keil` 開啟 `Project` → `Options for Target` → `Target`，勾選 `Use MicroLIB`。

此範例使用 `printf` 將 `xSTM_Sys` 的測試結果與系統資訊輸出至偵錯 `UART`。

#### 3. 加入 `Header Path`

在 `Keil` 開啟 `Options for Target` → `C/C++` → `Include Paths`，加入下列路徑；相對路徑請依實際專案位置調整。

```text
../Code
../Code/App
../Code/xSTM
../Code/xSTM/PlugIn
```

`STM32CubeMX` 產生的 `HAL`、`CMSIS` 與專案 `Core` 路徑也必須保留。

#### 4. 導入 `Source`

在 `Keil` 的 `Project` 視窗建立或選擇 `App` 與 `xSTM` 群組，使用 `Add Existing Files to Group...` 加入：

```text
../Code/App/App.c
../Code/xSTM/PlugIn/xSTM_Sys.c
../Code/xSTM/PlugIn/xSTM_Debug.c
```

`xSTM_Sys.c` 提供系統資訊與 Reset 功能；`xSTM_Debug.c` 提供 `printf` 的 `UART` 重新導向。僅加入 `Header Path` 不會將 `.c` 檔編譯至 `Target`。

#### 5. 在 `main` 呼叫 `App`

在 `main.c` 加入 `App.h`，於初始化完成後呼叫 `App_Init()`，並在 `while` 主迴圈呼叫 `App_Service()`。

```c
#include "App.h"

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  App_Init();
  while(1)
  {
    App_Service();
  }
}
```

若使用的不是 `USART2`，請將 `MX_USART2_UART_Init()` 換成實際由 `STM32CubeMX` 產生的初始化函式，並同步更新 `xSTM_Config.h`。

#### 6. 編譯、燒錄與開啟終端

1. 在 `Keil` 選擇 `Project` → `Rebuild all target files`。
2. 確認建置紀錄包含 `App.c`、`xSTM_Sys.c` 與 `xSTM_Debug.c`。
3. 在 `Options for Target` → `Debug` 選擇實際的除錯器，例如 `ST-Link Debugger`。
4. 使用序列終端連接偵錯 `UART`，設定為與 `STM32CubeMX` 相同的通訊參數。


## 範例說明

#### `App_Init`

`App_Init()` 在開機後執行一次，依序示範：

1. `xSTM_TEST_SYS()`：列印內建的 CPU、裝置、時脈、Boot Address 與 Reset 資訊。
2. `xSTM_SYS_GetUID()`：讀取 96-Bit `UID`。
3. `xSTM_SYS_GetCPUID()` 與 `xSTM_SYS_GetVer()`：讀取 Cortex-M CPU ID 與 Revision。
4. `xSTM_SYS_GetDeviceID()` 與 `xSTM_SYS_GetDevVer()`：讀取 `STM32` Device ID 與 Revision。
5. `xSTM_SYS_GetBootAddress()`：讀取目前的 Vector Table Address。
6. `xSTM_SYS_GetClockInfo()`：讀取 `SYSCLK`、`HCLK`、`PCLK1` 與 `PCLK2`。
7. `xSTM_SYS_GetReason()`：讀取並解析目前的 Reset Reason。

#### `App_Service`

`App_Service()` 應持續放在 `while` 主迴圈中。它每隔 `1000 ms` 更新剩餘秒數；從 `60 s` 倒數至 `0 s` 後，呼叫 `xSTM_SYS_SoftReset()` 重新啟動 MCU。

此設計用來實際驗證 Software Reset 與下一次開機時的 Reset Reason。範例不呼叫 `xSTM_SYS_ClearReason()`，避免清除 Software Reset Flag。

#### 預期輸出

第一次開機後，輸出會顯示 CPU、Device、Clock 與目前 Reset Reason，然後開始倒數。Soft Reset 後，新的輸出應包含 `Software` Reset Reason。

```text
[xSTM SYS Sample]: Start
[SYS TEST]: Start
[SYS TEST]: UID    : 0043005A 31385119 36323738
[SYS TEST]: CPUID  : 0x410FC241
[SYS TEST]: CPU Ver: 1
[SYS TEST]: Dev ID : 0x421
[SYS TEST]: Dev Ver: 0x1000
[SYS TEST]: Tick   : 2 MS
[SYS TEST]: SYSCLK : 84000000 Hz
[SYS TEST]: HCLK   : 84000000 Hz
[SYS TEST]: PCLK1  : 42000000 Hz
[SYS TEST]: PCLK2  : 84000000 Hz
[SYS TEST]: Boot   : 0x00000000
[SYS TEST]: Reason : 0x00000078
[SYS TEST]: Finish
[CPU]: UID: 0043005A 31385119 36323738
[CPU]: ID: 0x410FC241 | Ver: 1
[Device]: ID:0x421 | Ver: 0x1000
[Device]: Boot: 0x00000000
[Clock]: SYSCLK: 84000000 HCLK: 84000000 PCLK1: 42000000 PCLK2: 84000000
[Reset]: Reason: 0x00000078
[Reset]: Software
[Reset]: Power On
[Reset]: Reset Pin
[Reset]: Brown Out
[Soft Reset]: 60 s
[xSTM SYS Sample]: Init Finish
[Soft Reset]: 59 s
[Soft Reset]: 58 s
[Soft Reset]: 57 s
[Soft Reset]: 56 s
[Soft Reset]: 55 s
[Soft Reset]: 54 s
...
[Soft Reset]: 0 s
[Soft Reset]: Reset Now
```


## 注意事項

#### 會實際重開機

本範例會在 60 秒後呼叫 `xSTM_SYS_SoftReset()`，MCU 會立即重新開機。若只想檢視系統資訊，請暫時註解 `App_Service()` 中的 `xSTM_SYS_SoftReset()`。

#### Reset Reason Flag

Reset Reason Flag 會在 Reset 後保留，直到呼叫 `xSTM_SYS_ClearReason()`。本範例刻意不清除 Flag，以便於下一次開機時確認 Software Reset。

#### `UID` 與 Device 資訊

`UID`、Device ID 與 Revision 為目標 MCU 的硬體資訊，每顆晶片與不同型號的輸出值都可能不同。


## 授權條款

本範例採用 `MIT License` 授權使用。