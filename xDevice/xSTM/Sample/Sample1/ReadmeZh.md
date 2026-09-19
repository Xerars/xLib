# xSTM Sample1

> **Project** : xSTM Sample1
> **Author**  : William Hsiao
> **Descript**: `xSTM_Debug` 的 `UART` 輸入輸出與偵錯功能範例


## 簡介

本範例說明如何將 `xSTM_Debug` 導入 `STM32CubeMX` 與 `Keil MDK-ARM` 專案，並透過 `UART` 重新導向 `printf`、`scanf`、`fputc` 與 `fgetc`。

程式也會示範 `Info`、`Warn`、`Error` 訊息、資料 `HexDump`，以及內建 `Unit Test`。`App_Init()` 適合在 `main` 的初始化階段呼叫；`App_Service()` 則持續由 `while` 主迴圈呼叫。


## 使用

#### 1. 建立 `STM32CubeMX` 專案

1. 在 `STM32CubeMX` 選擇目標 `STM32` 與開發板。
2. 啟用作為偵錯通訊的 `USART`，並設定為 `Asynchronous` 模式。
3. 本範例預設使用 `USART2` 與 `huart2`。若使用其他 `USART`，請在 `xSTM_Config.h` 修改 `xSTM_DEBUG_HANDLE`。
4. 設定 `UART` 鮑率、資料位元、停止位元與同位元，並使用相同設定開啟序列終端。
5. 將工具鏈設為 `MDK-ARM`，然後產生專案。

#### 2. 啟用 `MicroLIB`

在 `Keil` 開啟 `Project` → `Options for Target` → `Target`，勾選 `Use MicroLIB`。

此設定讓 `printf`、`scanf`、`fputc` 與 `fgetc` 可由 `xSTM_Debug` 重新導向至 `UART`。

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
../Code/xSTM/PlugIn/xSTM_Debug.c
```

`Header Path` 只能讓編譯器找到 `.h` 檔；`xSTM_Debug.c` 必須加入 `Target` 才能提供 `xSTM_HexDump`、`xSTM_TEST_Debug_Print` 與 `xSTM_TEST_Debug_Scanf` 的實作。

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

#### 6. 編譯

在 `Keil` 選擇 `Project` → `Rebuild all target files`。建置紀錄必須包含 `App.c` 與 `xSTM_Debug.c` 的編譯訊息。

#### 7. 燒錄與開啟終端

1. 在 `Keil` 的 `Options for Target` → `Debug` 選擇實際的除錯器，例如 `ST-Link Debugger`。
2. 在 `Utilities` 勾選 `Use Target Driver for Flash Programming`，加入對應的 `Flash` 演算法。
3. 執行 `Download` 燒錄程式。
4. 使用序列終端連接偵錯 `UART`，設定為與 `STM32CubeMX` 相同的通訊參數。


## 範例說明

#### `App_Init`

`App_Init()` 在開機後執行一次，依序示範：

1. `xSTM_TEST_Debug_Print()`：驗證格式化整數、十六進位與浮點輸出。
2. `xSTM_TEST_Debug_Scanf()`：要求輸入一個字元與一個字串，驗證 `scanf` 與 `fgetc` 的重新導向。
3. `printf` 與 `fputc`：驗證標準輸出重新導向至偵錯 `UART`。
4. `xSTM_DEBUG_INFO`、`xSTM_DEBUG_WARN`、`xSTM_DEBUG_ERROR`：輸出不同類型的偵錯訊息。
5. `xSTM_HexDump` 與 `xSTM_DEBUG_HEXDUMP`：以十六進位格式輸出 16 bytes 範例資料。

#### `App_Service`

`App_Service()` 應持續放在 `while` 主迴圈中。本範例每隔 `1000 ms` 輸出一次服務計數，確認非阻塞式的週期性訊息輸出。

#### 預期輸出

啟動後，終端會先顯示 `Unit Test` 並要求輸入字元與字串；完成後會輸出標準輸入輸出、偵錯訊息與 `HexDump`。

```text
[xSTM Debug Sample]: Start
Unit TEST
[DEBUG TEST]: Start  Print Test...
[KeyIn Char]   >>
[KeyIn String] >>
[printf]: UART Redirect Success
[fputc ]: OK
[Info] : Debug Information
[Warn] : Debug Warning
[Error]: Debug Error
[Hex]: 00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF
[Hex]: 00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF
[xSTM Debug Sample]: Init Finish
[Info] : Service Count: 1
[Info] : Service Count: 2
[Info] : Service Count: 3
```


## 注意事項

#### `Unit Test` 的阻塞行為

`xSTM_TEST_Debug_Scanf()` 會等待終端輸入。若產品程式不需要互動式測試，請在 `xSTM_Debug.h` 將 `xSTM_DEBUG_SUPPORT_UNIT_TEST` 設為 `0`，或不要在 `App_Init()` 呼叫該函式。

#### `UART` 與 `HAL` 設定

`xSTM_Debug` 預設使用 `xSTM_Config.h` 中的 `huart2`。請確認該 `UART` 已由 `STM32CubeMX` 初始化，且 `xSTM_DEBUG_HANDLE`、鮑率與終端設定一致。

#### `xMeta.h` 名稱衝突

若 `xMeta.h` 定義通用的 `OR` 巨集，可能與部分 `STM32` `HAL` 暫存器欄位衝突。建議避免使用 `OR`、`AND`、`NOT` 這類過於通用的巨集名稱。


## 授權條款

本範例採用 `MIT License` 授權使用。