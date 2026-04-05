# xDLoad

> **Project**  : xDLoad
> **Author**  : William Hsiao
> **Descript**: 跨平台動態庫載入函式庫

## 簡介
`xDLoad` 是一個專為 `C/C++` 設計的輕量化、跨平台動態函式庫載入工具，
它封裝了 `Windows(dll)` 與 `Linux(so)` 在動態載入底層 `API` 上的差異，
提供一致且簡潔的介面。

## 特性
1. `C/C++` 兼容
2. 支持 `C99`
3. 跨平台支援
4. 自動化產生庫 (`DPort`)
5. 簡單的資源管控

## API
##### [類型定義]
1. `xDLib`: 動態函式庫的控制器

##### [核心函數]
1. `xDLIB_Load `: 載入指定的動態函式庫
2. `xDLIB_Close`: 卸載函式庫並釋放資源
3. `xDLIB_Get  `: 從函式庫中獲取指定符號

##### [快捷巨集]
1. `xDLOAD_OPEN `: 呼叫載入函數
2. `xDLOAD_CLOSE`: 呼叫關閉函數
3. `xDLOAD_BIN  `: 自動根據 `NAME` 搜尋符號，並將其轉型為 `TYPE` 類型的變數 `NAME`


## 庫資訊
1. `xDLoad` 庫大小: `0.187KB`

``` c
xDLIB_Load      //佔用 14B
xDLIB_Close     //佔用 17B
xDLIB_Get       //佔用 19B
```

## 編譯依賴
##### [標頭依賴]
1. `xMeta.h`
2. `xType.h`

##### [編譯]
在 `xDLoad` 資料夾內使用指令 `make all`

```shell
make all
```

## 範例
在 `Sample` 資料夾內使用指令 `make all`

```shell
make all
```

##### [範例一]
1. 演示使用 `xDLoad` 基本函數功能
2. 內容包含載入動態庫、取得符號並轉成函數、關閉動態庫

```c
//Main Code
int main(void)
{
  //Load DLib
  Lib = xDLIB_Load(DLIB_NAME);

  if(!Lib)
  {
  	printf("Load Module Lib Failed!\n");
  	return -1;
  }
  
  //Get Function
  Calculate = (MOD_Calculate) xDLIB_Get(Lib,"Calculate");
  PrintData = (MOD_PrintData) xDLIB_Get(Lib,"PrintData");
  Slogan    = (MOD_Slogan)    xDLIB_Get(Lib,"Slogan");
  GetRound  = (MOD_GetRound)  xDLIB_Get(Lib,"GetRound");
  
  //Get Variable
  xDLOAD_BIND(Lib,int*,Round);         //Demo Macro Function
  pRound = Round;

  //Run Test
  Run_Test();
  
  //Close Lib
  xDLIB_Close(Lib);
  return 0;
}

```

##### [範例二]
1. 使用 `DPort` 接口去將動態庫的符號做統一管理
2. 使用宏函數快速去將所有符號統一取出並儲存到結構內
3. `DPort` 的設計可以使用 `Tooling` 內的工具去產生

```c
//Main Code
int main(void)
{
  Module_DPort DPort;
  pDPort = &DPort;

  Lib = xDLOAD_OPEN(DLIB_NAME);   //Open DLib
  XDLIB_MODULE_GET(Lib,DPort);    //Get Module
  Run_Test();                     //Run Test
  xDLOAD_CLOSE(Lib);              //Close DLib
  return 0;
}
```

## 工具
#### [工具編譯]
1. CLI 工具: 在 `Tooling/CLI` 內使用指令 `make all`

編譯
``` shell
make all
```

#### [工具執行]
1. 在 `In` 資料夾放入頭文件 (也可在其他資料夾)
2. CLI 工具: 執行 `./Tool_DLoad_CLI <頭文件>`
3. 在 `Out` 資料夾產生出 `XXX_DPort.h` 文件

``` shell
./Tool_DLoad_CLI Module.h
```

## 授權條款
本專案採用 `MIT License` 授權使用
