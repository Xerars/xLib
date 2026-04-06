# Rule

## 概述
本文件說明本專案的開發規則與設計理念，目的在於提升程式碼品質與開發效率，並確保整體架構具備良好的可維護性與擴展性。

本專案在開發過程中，盡量遵循以下原則:
1. 精簡程式碼，降低不必要的長度與複雜度
2. 建立清晰且一致的檔案與目錄結構
3. 採用模組化設計，使各組件可自由組合與重用
4. 提高可攜性，讓程式能在不同系統或平台上運行

上述原則為設計方向與建議，而非強制規範。開發者可依實際需求彈性調整，以達到最佳的開發體驗與實作效果。


## 核心設計概念(Core)
#### <參數>
1. 參數命名方式: 採用大駝峰命名法 (每一個單字的首字母都採用大寫字母)
``` c
  int Handle = 1;
  int Device = 2;
  int Status = 3;
```

2. 常用的固定情況可以在前綴加入小寫字母或符號
  1. `tStart`: 表示計時可以在前綴加上 `t` ，表示 `Time`   ，可以在開發期間快速的知道是時間相關變數。
  2. `gValue`: 全局變數可以在前綴加上 `g` ，表示 `Global` ，可以在開發期間快速的知道是全局變數。
  3. `nData `: 表示數量可以在前綴加上 `n` ，表示 `Numeric`，可以在開發期間快速的分辨數量還是資料。
  4. `pArray`: 表示指標可以在前綴加上 `p` ，表示 `Pointer`，可以在開發期間快速的分辨指標還是變數。

3. 像是 `unsigned char` 這種兩段式的變數型別，盡量不使用，可以用`xType.h`，或者是`Macro`去重新包裝成較短(`U8`)的變數型別。

4. 可以使用一些縮寫去優化縮寫長度
  1. Status  => Stat
  2. Count   => Cnt
  3. Enable  => En
  4. Length  => Len
  5. Index   => Idx
  6. Buffer  => Buf
  7. Address => Addr
  8. Initial => Init
  9. Message => Msg

#### <宏/宏函數>
1. 宏定義應以該檔案名稱(或模組名稱)作為前綴，並使用全大寫字母。這能有效建立命名空間，防止不同模組間因名稱相同而產生衝突。
2. 宏的名稱、數值、續行符以及註解應盡量垂直對齊，保持代碼整潔。
3. 換行符對齊: 多行宏結尾的續行符 `\` 必須垂直對齊。
4. 定義多行宏函數時，必須使用 `do { ... } while(0)` 包裹邏輯。
5. 定義多行宏函數時，建議使用 `/* ... */` 進行註解，以避免部分老舊編譯器對 `//` 續行處理的異常，單行則不再此限。

``` c
#define XDATA_MIN_SIZE          5         //Min Size               
#define XDATA_MAX_SIZE          10        //Max Size

#define XDATA_CONFIG(A,B,C,D)   \
do                              \
{                               \
  A+=B;                         \
  B+=C;                         \
  C+=D;  /* C = C + D */        \
} while(0)

```

#### <列舉>
1. 程式邏輯中嚴禁直接出現硬編碼數字(`Type = 3`)，凡是具有狀態、型別或選項意義的數值，必須使用 `Enum` 定義，以提高代碼的可讀性。
2. 為了簡化變數宣告並符合型別安全，一律使用 `typedef enum` 格式。
3. 起始標籤緊跟在 `enum` 後，建議以底線 `_` 開頭，並使用全大寫字母
4. 結尾型別位於 `}` 後，應與標籤名稱對應(去掉底線)，可選擇性加上 `_E` 作為後綴
5. 列舉內的所有元素必須使用全大寫字母
6. 元素應儘量明確賦予數值，且等號 `=` 應垂直對齊，提升視覺閱讀效率
7. 結尾建議增加 `_MAX` 成員。這方便於 `for` 迴圈遍歷，也能在接收資料時進行「邊界檢查」

``` c
typedef enum _DATE_TYPE
{
  DATA_TYPE_INT   = 0,
  DATA_TYPE_FLAOT = 1,
  DATA_TYPE_CHAR  = 2,
  DATA_TYPE_MAX,
} DATA_TYPE;
```

#### <結構>
1. 使用 `typedef struct` 進行定義，避免在後續宣告變數時重複書寫 `struct` 關鍵字
2. 起始標籤應緊跟在 `struct` 後方，必須以底線 `_` 開頭
3. 結尾型別位於大括號 `}` 後方，名稱應與起始標籤一致，但移除開頭`_`
4. 後綴結尾型別可保持原名，或統一加上 `_t` 後綴(代表 `Type`)
5. 結構內元素盡量要對齊，如果可以盡量加上註解
6. 結構內回呼函數應先使用 `typedef` 定義該回呼函數的型別名稱，再於結構體內引用

``` c
typedef struct _PersonInfo
{
  int   ID;
  char *Name;
  int   Score
} PersonInfo;
```

#### <函數>
1. 在源文件 `(.c)` 的函數定義上方，必須使用 `///@` 開頭的註解。
  * 原因: 此格式在 `Keil C` 中會以藍色高亮顯示，便於快速定位與閱讀功能說明
  * 要求: 僅需標註函數名與簡要功能，避免冗長的 `@param` 或 `@return` 描述
```c
///@Function: ShowData
///@Descript: 執行數據的串口列印與格式化輸出
void ShowData(void)
{}
```
2. 函數名加參數的總長度應以「`IDE 無須拉動水平捲軸`」為準，確保一眼看清完整宣告。
3. 單個函數邏輯建議控制在 `100` 行以內。
4. 減少參數數量:若參數過多，應封裝進`結構體`後以指標傳入。
5. 避免在參數列使用 `const char*` 等冗長的原始修飾詞，應採用 `xType` 定義過的精簡型別(如 `CCHAR` 或 `BOOL`)，以縮短宣告長度。
6. 函數命名應具備明確意義，優先考慮「`動詞+名詞`」結構(如`Get_Voltage、Set_State`)，確保開發者無需查看代碼內容即可理解其目的。


## 源文件(Source)
1. 每一個函數(包含 static)`上方必須包含:
  * `///@Function`: 函數名稱。
  * `///@Descript`: 簡短的功能說明。
``` c
///@Function: 
///@Descript: 
void TEST_Function(void)
{}
```
2. 所有 `static` 函數必須先在 `[Prototype Declare]` 區塊定義原型。
3. 為了不干擾閱讀主要的公開 `API`，`static` 函數的實體建議放在檔案的最末尾。
4. 如果該 `.c` 檔案支援獨立編譯測試`(透過 main)`，則 `main` 必須放在所有函數實作的最前面，方便開發者第一時間確認程式入口。
5. 放置的順序如下
  1. `[xxx Lib Include]          ` : 最優先，包含基礎型別定義。
  2. `[Typedef Declare]          ` : 外部類型定義的引入。
  3. `[Macro Declare]            ` : 靜態常數定義。
  4. `[Enum Declare]             ` : 狀態與枚舉定義。
  5. `[Callback Function Declare]` : 函式指標定義。
  6. `[Struct Declare]           ` : 資料結構主體定義。
  7. `[Prototype Declare]        ` : 函式原型。
  8. `[Variable Declare]         ` : 外部全域變數。
  9. `Function`


## 頭文件(Header)
1. `Guard` 巨集統一使用 `__檔名_H__`(全大寫)
2. 在 `#ifndef`、`#define` 與 `#endif` 後方必須加上 `//__檔名_H__` 以利快速識別區塊
```c
#ifndef __TEST_H__  //__TEST_H__
#define __TEST_H__  //__TEST_H__
#endif  //__TEST_H__
```
3. 頭文件建議都要有 `extern "C"` 宣告，不管有沒有使用 `C++`
4. extern "C" 內部僅允許放置變數宣告`(Variable)` 與 函數原型`(Prototype)`，其它不建議放進去。
5. 宏定義 `(Macro)`、結構定義 `(Struct/Enum)` 建議放在 `extern "C"` 之外(除非涉及 `C++` 不相容的特殊連結需處理)。
```c
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
```
6. 標題註解格式必須使用 `//[Title Name]` 格式
7. 若該區塊無內容，請標註 `//None` 或直接移除
8. `extern "C"` 隔離區內部僅限 `[Variable Declare]` 與 `[Prototype Declare]`
9. 外部:放置 `Enum`、`Struct`、`Typedef` 等類型定義，這些在 `C/C++` 中是語法通用的
10. Macro Function 放置於檔案最末尾，可以確保巨集函數在使用到前面定義的 `Struct` 或 `Variable` 時，相關符號已經完全展開。
11. 放置順序建議依序如下
    1.  `[xxx Lib Include]           `: 最優先，包含基礎型別定義。
    2.  `[Config Include]            `: 模組專屬的設定參數。
    3.  `[Typedef Include]           `: 外部類型定義的引入。
    4.  `[Macro Declare]             `: 靜態常數定義。
    5.  `[Enum Declare]              `: 狀態與枚舉定義。
    6.  `[Callback Function Declare] `: 函式指標定義。
    7.  `[Struct Declare]            `: 資料結構主體定義。
    8.  `[Variable Declare]          `: (必須在`Extern C`內部) 外部全域變數。
    9.  `[Prototype Declare]         `: (必須在`Extern C`內部) 函式原型。
    10. `[Macro Function Declare]    `: (置於最末尾) 巨集函數。
```c
//[xxx Lib Include]
//None
//[Config Include]
//None
//[Typedef Include]
//None
//[Macro Declare]
//None
//[Enum Declare]
//None
//[Callback Function Declare]
//None
//[Struct Declare]
//None
#ifdef __cplusplus
extern "C" {
#endif
//[Variable Declare]
//None
//[Prototype Declare]
//None
#ifdef __cplusplus
}
#endif
//[Macro Function Declare]
//None
```

12. `Config` 的定位，它決定了模組是否包含特定演算法、是否開啟 `Debug Log`、或是否支援特定的硬體特性
13. `Config` 的命名規範建議使用 `SUPPORT_XXXXX`。例如:`SUPPORT_REGEX`
14. `Config` 值定義建議採顯式定義為 `1` (開啟)或 `0` (關閉)
15. `Config` 判斷邏輯嚴禁使用 `#ifdef`，必須使用 `#if`

```c
#define SUPPORT_DEBUG       1       //Support Debug Information
#define SUPPORT_PERF        1       //Support Perf Function

```

16. `Prototype` 功能性質相近的函數必須放在同一個註解標題下
17. 一個模組內的函數分組建議不超過 `7` 個類型。若功能過多超過此限，應考慮將模組拆分或重新抽象化
```c
#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Image Quality
void  xIQ_SetBrightness(int Value);
void  xIQ_SetSharpness(int Value);
void  xIQ_SetContrast(int Value);

//Init
void  xIQ_Init(void);
void  xIQ_Destroy(void);
xIQ_t xIQ_GetHandle(void);

//File Operate
void ReadFile(char *FileName);
void WriteFile(char *FileName);
#ifdef __cplusplus
}
#endif
```

18. 若為 `Device` 類程序且涉及大量暫存器操作，應將硬體位址與位元定義抽離至獨立的 `xxx_Reg.h`，確保邏輯層不被硬體細節干擾
19. 若為 `Device` 類程序需調用實體接口`(如 GPIO,I2C,SPI)`，應定義 `xxx_Port.h` 作為硬體適配層，以提高程序在不同平台間的移植性。

## 模組規劃(Module)

1. 每個專案即為一個獨立模組。模組的核心程式碼`(.c/.h)`應直接放置於根目錄。
2. 目錄下的頭文件為該模組的主要對外接口。若功能複雜，允許存在多個導出標頭檔。
3. 若模組具備額外資源，應依功能分類建立以下子資料夾。
  1. `Plugin/`: 用於存放複雜功能的擴充插件或可選組件。
  2. `Sample/` 或 `Test/`: 存放演示範例與單元測試代碼。
  3. `Doc/`: 存放技術文檔、設計說明。
  4.: 存放輔助開發的小工具。
    1. 應區分為 `CLI` (命令列介面) 與 `GUI` (圖形介面)。
    2. 內含 `In/` 與 `Out/` 資料夾，用以隔離工具所需的輸入與輸出資源。
  1. `Spec/` 或 `Sch/`: 針對硬體驅動類模組(xDevice)，存放規格書`(DataSheet)`或電路原理圖。


``` shell
.
├── Doc
│   ├── ReadmeEn.md
│   └── ReadmeZh.md
├── Makefile
├── Sample
│   ├── Makefile
│   ├── Module.c
│   ├── Module_DPort.h
│   ├── Module.h
│   ├── Sample1.c
│   └── Sample2.c
├── Tooling
│   ├── CLI
│   │   ├── Makefile
│   │   └── Tool_DLoad_CLI.c
│   ├── In
│   │   ├── Module.h
│   │   └── ModulePlus.h
│   ├── Makefile
│   ├── Out
│   │   ├── Module_DPort.h
│   │   └── ModulePlus_DPort.h
│   ├── Tool_DLoad_Lib.c
│   └── Tool_DLoad_Lib.h
├── xDLoad.c
└── xDLoad.h
```

## 類別規劃(Class)
1. `xAdapter`: 基於第三方庫、不同功能的統一接口。
2. `xApp    `: 基於實際應用、有目的性、高度完整度的功能之程式。
3. `xDevice `: 基於實際硬體、感測器驅動、硬體模組的功能之程式。
4. `xFake   `: 基於模擬硬體或是用以其他方式模擬軟件功能之程式。
5. `xModule `: 基於純軟體演算法、通用資料、標準協議處理之程式。