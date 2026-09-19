# xSTM Sample2

> **Project** : xSTM Sample2
> **Author**  : William Hsiao
> **Descript**: `xSTM_DWT` 延遲、時間、效能與計時事件範例


## 簡介

本範例說明如何將 `xSTM_DWT` 導入 `STM32CubeMX` 與 `Keil MDK-ARM` 專案。`DWT` 使用 Cortex-M 的 Cycle Counter，提供精準延遲、時間讀取、效能量測與非阻塞計時事件。

`App_Init()` 在系統初始化完成後執行 DWT 初始化與 `Unit Test`；`App_Service()` 則由 `while` 主迴圈持續呼叫，演示週期 `Timer Event` 與 `Timer Macro`。


## 使用

#### 1. 建立 `STM32CubeMX` 專案

1. 在 `STM32CubeMX` 選擇目標 `STM32` 與開發板。
2. 啟用作為輸出結果使用的 `USART`，並設定為 `Asynchronous` 模式。
3. 本範例預設使用 `USART2` 與 `huart2`。若使用其他 `USART`，請在 `xSTM_Config.h` 修改 `xSTM_DEBUG_HANDLE`。
4. 設定 `UART` 通訊參數，並使用相同設定開啟序列終端。
5. 將工具鏈設為 `MDK-ARM`，然後產生專案。

#### 2. 確認系統時脈

在 `xSTM_Config.h` 設定 `xSTM_SYS_CLOCK`，其值必須與 `STM32CubeMX` 的實際 `System Clock` 相同，單位為 `MHz`。

```c
#define xSTM_SYS_CLOCK                   84      //System Clock(MHz)
#define xSTM_DWT_SYS_CLOCK               xSTM_SYS_CLOCK
```

`xSTM_DWT` 會使用此值將 Cycle Counter 轉換為 `us` 與 `ms`。時脈設定不正確時，Delay 與時間量測結果也會不正確。

#### 3. 啟用 `MicroLIB`

在 `Keil` 開啟 `Project` → `Options for Target` → `Target`，勾選 `Use MicroLIB`。

此範例使用 `printf` 將 DWT 的測試與量測結果輸出至偵錯 `UART`。

#### 4. 加入 `Header Path`

在 `Keil` 開啟 `Options for Target` → `C/C++` → `Include Paths`，加入下列路徑；相對路徑請依實際專案位置調整。

```text
../Code
../Code/App
../Code/xSTM
../Code/xSTM/PlugIn
```

`STM32CubeMX` 產生的 `HAL`、`CMSIS` 與專案 `Core` 路徑也必須保留。

#### 5. 導入 `Source`

在 `Keil` 的 `Project` 視窗建立或選擇 `App` 與 `xSTM` 群組，使用 `Add Existing Files to Group...` 加入：

```text
../Code/App/App.c
../Code/xSTM/PlugIn/xSTM_DWT.c
../Code/xSTM/PlugIn/xSTM_Debug.c
```

`xSTM_DWT.c` 提供 DWT 功能；`xSTM_Debug.c` 提供 `printf` 的 `UART` 重新導向。僅加入 `Header Path` 不會將 `.c` 檔編譯至 `Target`。

#### 6. 在 `main` 呼叫 `App`

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

#### 7. 編譯、燒錄與開啟終端

1. 在 `Keil` 選擇 `Project` → `Rebuild all target files`。
2. 確認建置紀錄包含 `App.c`、`xSTM_DWT.c` 與 `xSTM_Debug.c`。
3. 在 `Options for Target` → `Debug` 選擇實際的除錯器，例如 `ST-Link Debugger`。
4. 在 `Utilities` 設定對應的 `Flash` 演算法，然後執行 `Download`。
5. 使用序列終端連接偵錯 `UART`，設定為與 `STM32CubeMX` 相同的通訊參數。


## 範例說明

#### `App_Init`

`App_Init()` 在開機後執行一次，依序示範：

1. `xSTM_DWT_Init()`：啟用 DWT Cycle Counter。
2. `xSTM_TEST_DWT()`：執行 Delay、時間與 Performance 的內建 `Unit Test`。
3. `xSTM_DWT_DelayCycle()`、`xSTM_DWT_DelayUS()`、`xSTM_DWT_Delay10US()`、`xSTM_DWT_DelayMS()`：不同單位的阻塞延遲。
4. `xSTM_DWT_GetCycle()` 與 `xSTM_DWT_GetUS()`：讀取目前 Cycle 與微秒時間。
5. `xSTM_DWT_PERF_START()` 與 `xSTM_DWT_PERF_FINISH()`：量測一段程式的執行時間。

#### `App_Service`

`App_Service()` 應持續放在 `while` 主迴圈中，並演示兩種非阻塞計時方式：

1. `xSTM_DWT_TimerEvent()`：每隔 `1000 ms` 呼叫一次 `App_DWT_TimerEvent()` callback。
2. `xSTM_DWT_TIMER_START()` 與 `xSTM_DWT_TIMER_FINISH()`：每隔 `2000 ms` 輸出一次訊息。

#### 預期輸出

啟動後會顯示 DWT 初始化、內建 `Unit Test`、時間資訊與效能量測。進入主迴圈後，`Timer Event` 每秒遞增，`Timer Macro` 每兩秒輸出一次。

```text
[xSTM DWT Sample]: Start
[DWT TEST]: Start
[Perf]: Elapsed: 10000 us(840034 Cycle)
[DWT TEST]: Delay : PASS
[DWT TEST]: Time  : 21961 us
[DWT TEST]: Perf  : 10000 us
[DWT TEST]: Finish
[Time]: 2587875 Cycle, 30808 us
[Perf]: Elapsed: 10 us(877 Cycle)
[Perf Macro]: 10 us
[xSTM DWT Sample]: Init Finish
[Timer Event]: 1
[Timer Macro]: 2000 ms
[Timer Event]: 2
[Timer Event]: 3
[Timer Macro]: 2000 ms
[Timer Event]: 4
[Timer Event]: 5

```


## 注意事項

#### `DWT` 支援

`DWT` 由 Cortex-M Core 提供，實際支援度依目標 `STM32` 與核心而定。本範例使用 `STM32F4` 與 `DWT->CYCCNT`；不適用於未提供 Cycle Counter 的目標。

#### `Timer Event` 數量

目前 `xSTM_DWT_TimerEvent()` 內部使用單一靜態狀態機，因此同時間只能管理一個 `Timer Event`。若需要多個獨立事件，應使用 `xSTM_DWT_TIMER_START/FINISH` macro，或後續擴充 Handle 型式的 timer。

#### 長時間計時

`DWT->CYCCNT` 是 `32-Bit` 計數器，會自然溢位。使用相減計算短時間間隔可正確處理溢位，但不適合作為永久遞增的絕對時間。


## 授權條款

本範例採用 `MIT License` 授權使用。