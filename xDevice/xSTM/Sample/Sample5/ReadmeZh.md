# xSTM Sample5

> **Project** : xSTM Sample5
> **Author**  : William Hsiao
> **Descript**: `xSTM_Flash` 保留區配置、功能演示與 `Unit Test` 範例


## `Flash` 配置

本文件說明 `xSTM_Flash` 的安全配置方式。`Sample5` 的 `Unit Test` 會擦除、寫入並再次擦除指定 `Flash Sector`；完成 `linker` 保留區設定前，請勿燒錄或執行範例。


#### 1. 確認目標 `STM32`

目前設定適用於具有 `512 KB` `Internal Flash` 的 `STM32F446`。`Flash` 範圍為：

```text
0x08000000 ~ 0x0807FFFF
```

本範例保留最後一個 `Flash Sector` 作為測試區。若 `MCU` 型號、`Flash` 容量或 `Sector Layout` 不同，必須依 `Datasheet` 重新計算位址、`Sector` 與大小。

#### 2. 保留 `Flash` 測試區

`STM32F446` 的最後一個 `Sector` 為 `FLASH_SECTOR_7`：

| 項目                | 值                       |
| :------------------ | :----------------------- |
| `Test Sector`       | `FLASH_SECTOR_7`         |
| `Start Address`     | `0x08060000`             |
| `End Address`       | `0x0807FFFF`             |
| `Size`              | `0x00020000`（`128 KB`） |

此區域將由 `xSTM_TEST_Flash()` 完整擦除。請勿放置程式碼、常數資料、向量表或其他需要保留的資料。

#### 3. 設定 `Keil` `IROM1`

在 `Keil` 開啟 `Project` → `Options for Target` → `Target`，設定 `IROM1`：

| 設定                | 值             |
| :------------------ | :------------- |
| `Start`             | `0x08000000`   |
| `Size`              | `0x00060000`   |

此設定讓 `linker` 只將程式放入 `0x08000000` 到 `0x0805FFFF`，保留 `0x08060000` 到 `0x0807FFFF` 給 `Flash Unit Test`。

若程式大小超過 `384 KB`，`Keil` 應產生空間不足錯誤；請不要藉由增加 `IROM1 Size` 覆蓋測試區。

#### 4. 確認 `xSTM_Flash` 設定

確認 `xSTM_Flash.h` 的 `Unit Test` 設定與保留區一致：

```c
#define xSTM_FLASH_SUPPORT_UNIT_TEST     1
#define xSTM_FLASH_TEST_ADDR             0x08060000UL
#define xSTM_FLASH_TEST_SECTOR           FLASH_SECTOR_7
#define xSTM_FLASH_TEST_SECTOR_COUNT     1
#define xSTM_FLASH_TEST_SIZE             0x00020000UL
```

`xSTM_FLASH_VOLTAGE_RANGE` 位於 `xSTM_Config.h`。對一般 `3.3 V` 的 `STM32F4`，目前的 `FLASH_VOLTAGE_RANGE_3` 設定適用；實際供電條件不同時必須重新確認。

#### 5. 導入 `Source`

在 `Keil` 的 `Target` 加入：

```text
../Code/App/App.c
../Code/xSTM/PlugIn/xSTM_Flash.c
../Code/xSTM/PlugIn/xSTM_Debug.c
```

並保留下列 `Header Path`：

```text
../Code
../Code/App
../Code/xSTM
../Code/xSTM/PlugIn
```

`xSTM_Debug.c` 用於將 `Flash Unit Test` 的 `printf` 輸出導向偵錯 `UART`。

#### 6. 配置檢查

燒錄前確認：

1. `IROM1 Size` 為 `0x00060000`。
2. `xSTM_FLASH_TEST_ADDR` 為 `0x08060000UL`。
3. `xSTM_FLASH_TEST_SECTOR` 為 `FLASH_SECTOR_7`。
4. `xSTM_Flash.c`、`xSTM_Debug.c` 與 `Sample` `App.c` 都已加入同一個 `Target`。
5. 已確認測試區沒有任何需要保留的資料。


## 範例說明

#### 範例行為

`App_Init()` 依序執行內建 `Unit Test` 與 `App_FlashDemo()`。

`Unit Test` 會擦除測試區、確認全區為 `0xFF`、寫入並讀回一個 `Word`、寫入並讀回 `Buffer`，最後再次擦除測試區。

`App_FlashDemo()` 額外逐一展示下列公開 `API`：

1. `xSTM_Flash_Erase()`：擦除保留的 `FLASH_SECTOR_7`。
2. `xSTM_Flash_IsErased()`：確認擦除後為 `0xFF`，以及寫入後不再是擦除狀態。
3. `xSTM_Flash_Write()` 與 `xSTM_Flash_Read()`：寫入並讀回一個 `32-Bit Word`。
4. `xSTM_Flash_WriteBuf()` 與 `xSTM_Flash_ReadBuf()`：寫入、讀回並比對一組 `Buffer`。
5. `xSTM_HexDump()`：以 `Hex` 格式輸出讀回的 `Buffer` 資料。
6. 再次執行 `Erase` 與 `IsErased`，清空測試區。

#### 實際輸出

以下為 `STM32F446` 實測通過的輸出：

```text
[Flash]: Test Addr: 0x08060000 Sector: 7 Size: 20000 Bytes
[FLASH TEST]: Start
[FLASH TEST]: Read Word : 0x12345678
[FLASH TEST]: Read Buf  : 12 34 56 78 9A BC DE F0
[FLASH TEST]: PASS
[Flash Demo]: Start
[Erase]: OK
[IsErased]: YES
[Write Word]: OK
[Read Word ]: 0x12345678
[IsErased  ]: NO
[Write Buf ]: OK
[Read Buf  ]: OK
[Hex]: 10 32 54 76 98 BA DC FE 55
[Compare Buf]: PASS
[Clean     ]: OK
[IsErased  ]: YES
[Flash Demo]: Finish
[xSTM Flash Sample]: Init Finish
```


## 注意事項

#### 擦除不可復原

`Flash Sector` 擦除會清除整個 `128 KB` 測試區，無法復原。請在確認 `linker` 已保留區域後才啟用 `xSTM_FLASH_SUPPORT_UNIT_TEST`。

#### `Flash` 寫入限制

`Flash` 寫入只能將 `bit` 從 `1` 變為 `0`，無法直接將 `bit` 從 `0` 變為 `1`。例如 `0xFF` 可以寫成 `0x12`，但已寫入的 `0x12` 不能直接改回 `0xFF`。

目前 `xSTM_Flash_Write()` 與 `xSTM_Flash_WriteBuf()` 使用 `FLASH_TYPEPROGRAM_WORD`，寫入單位為 `4 Bytes`，且起始 `Address` 必須 `4 Bytes` 對齊。即使後續改用 `Byte Program`，將 `bit` 由 `0` 改回 `1` 仍必須先擦除 `Sector`。

#### 更新既有資料

更新已寫入的設定資料時，建議依序：

1. 從 `Flash` 讀出同一個 `Sector` 內所有需要保留的資料到 `RAM`。
2. 在 `RAM` 修改目標欄位。
3. 擦除整個 `Sector`。
4. 將修改後與需要保留的資料全部寫回 `Flash`。

不可只讀出單一結構後就擦除 `Sector`，否則同 `Sector` 的其他資料也會遺失。

#### 頻繁更新資料

設定資料若經常更新，可在 `Sector` 內採用追加式 `Record`。每次將新資料寫到下一個仍為 `0xFF` 的位置，讀取時採用最後一筆有效 `Record`；直到 `Sector` 用完時，才整理最新資料、擦除 `Sector` 並重新寫入。此方式可減少擦除次數並延長 `Flash` 使用壽命。

#### 不同 `MCU` 的 `Sector Layout`

`FLASH_SECTOR_7` 與 `0x08060000` 僅適用於目前的 `512 KB` `STM32F446` 配置。其他 `STM32F4` 型號可能有不同的 `Sector` 數量與大小。


## 授權條款

本範例採用 `MIT License` 授權使用。
