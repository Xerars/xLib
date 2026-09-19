# xSTM Sample4

> **Project** : xSTM Sample4
> **Author**  : William Hsiao
> **Descript**: `xSTM_Power` 時脈控制與低功耗模式範例


## 簡介

本範例說明如何導入 `xSTM_Power`，演示 `HCLK` 調整與還原，以及 `Sleep`、`Stop`、`Standby` 模式的進入方式。

`App_Init()` 進行時脈控制；`App_Service()` 在指定時間後依 `APP_POWER_TEST_MODE` 進入選定模式一次。


## 使用

#### 1. 建立 `STM32CubeMX` 專案

1. 在 `STM32CubeMX` 選擇目標 `STM32` 與開發板。
2. 啟用輸出使用的 `USART`，設定為 `Asynchronous` 模式。
3. 本範例預設使用 `USART2` 與 `huart2`。使用其他 `USART` 時，請同步修改 `App.c` 的 `USART2_Init()` 與 `xSTM_Config.h` 的 `xSTM_DEBUG_HANDLE`。
4. 設定 `UART` 參數，使用相同設定開啟序列終端。
5. 將工具鏈設為 `MDK-ARM` 後產生專案。

#### 2. 啟用 `xSTM_Power`

在 `xSTM_Config.h` 確認設定如下：

```c
#define xSTM_SUPPORT_POWER                1       //Support Power
```

設定為 `0` 時，`xSTM.h` 不會包含 `xSTM_Power.h`，呼叫 `xSTM_Power_*` 會出現函式未宣告的編譯警告。

#### 3. 啟用 `MicroLIB`

在 `Keil` 開啟 `Project` → `Options for Target` → `Target`，勾選 `Use MicroLIB`。本範例以 `printf` 輸出資訊至偵錯 `UART`。

#### 4. 加入 `Header Path`

在 `Keil` 的 `Options for Target` → `C/C++` → `Include Paths` 加入：

```text
../Code
../Code/App
../Code/xSTM
../Code/xSTM/PlugIn
```

保留 `STM32CubeMX` 產生的 `HAL`、`CMSIS` 與 `Core` 路徑。

#### 5. 導入 `Source`

在 `Keil` 的 `App` 與 `xSTM` 群組，使用 `Add Existing Files to Group...` 加入：

```text
../Code/App/App.c
../Code/xSTM/PlugIn/xSTM_Power.c
../Code/xSTM/PlugIn/xSTM_Sys.c
../Code/xSTM/PlugIn/xSTM_Debug.c
```

`xSTM_Power.c` 提供時脈與低功耗模式功能；`xSTM_Sys.c` 提供 `xSTM_SYS_GetTick()`；`xSTM_Debug.c` 提供 `printf` 的 `UART` 重新導向。僅加入 `Header Path` 不會將 `.c` 檔編譯至 `Target`。

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

#### 7. 選擇測試模式

在 `App.c` 設定 `APP_POWER_TEST_MODE`。首次建議使用 `APP_POWER_MODE_NONE`，確認時脈切換與 `UART` 輸出正常。

| 設定值 | 功能 |
| --- | --- |
| `APP_POWER_MODE_NONE` | 僅演示時脈控制 |
| `APP_POWER_MODE_SLEEP` | 進入 `Sleep` 模式 |
| `APP_POWER_MODE_STOP` | 進入 `Stop` 模式 |
| `APP_POWER_MODE_STANDBY` | 進入 `Standby` 模式 |

#### 8. 編譯與燒錄

1. 在 `Keil` 選擇 `Project` → `Rebuild all target files`。
2. 確認建置紀錄包含 `App.c`、`xSTM_Power.c`、`xSTM_Sys.c` 與 `xSTM_Debug.c`。
3. 選擇實際除錯器與對應 `Flash` 演算法後執行 `Download`。
4. 使用與 `STM32CubeMX` 相同設定的序列終端開啟偵錯 `UART`。


## 範例說明

#### `App_Init`

`App_Init()` 讀取目前 `HCLK`，用 `xSTM_Power_SetClock()` 將時脈降為 `xSTM_SYS_CLOCK` 的一半，接著呼叫 `USART2_Init()` 重新計算 `UART` Baud Rate。之後用 `xSTM_Power_RestoreClock()` 還原時脈並再次初始化 `UART`。

切換 `HCLK` 會改變 `APB` 與 `UART` 輸入時脈。若未重新初始化 `UART`，終端可能顯示亂碼。

#### `App_Service`

當 `xSTM_SYS_GetTick()` 到達 `APP_POWER_ENTER_TICK`，程式只會進入選定模式一次。`Sleep` 返回後會輸出 `Wake from Sleep`；`Stop` 與 `Standby` 需先設定喚醒來源；`Standby` 醒來時會重新啟動，不會執行 `xSTM_Power_Standby()` 後方的程式。

#### 預期輸出

使用 `APP_POWER_MODE_NONE` 時：

```text
[xSTM Power Sample]: Start
[Clock]: HCLK: 84000000 Hz
[Clock]: Set: 42000000 Hz
[Clock]: Restore: 84000000 Hz
[Power]: Mode: 0 Enter After: 5000 ms
[xSTM Power Sample]: Init Finish
[Power]: Mode Disabled
```


## 注意事項

#### `UART` 時脈

範例中的 `USART2_Init()` 綁定 `USART2` 與 `huart2`。使用其他 `UART` 時，必須同步替換 Handle、Instance 與初始化函式。

#### 低功耗模式驗證

測試低功耗模式前，準備 `EXTI` 按鍵、`RTC` 或 `Wakeup Pin` 等喚醒來源。`SysTick` 也是中斷來源，可能使 `Sleep` 立即醒來。`Stop` 醒來後需執行 `SystemClock_Config()` 並重設 `UART`；`Standby` 可在開機初期讀取 `PWR_FLAG_SB` 判斷是否由 `Standby` 醒來。


## 授權條款

本範例採用 `MIT License` 授權使用。
