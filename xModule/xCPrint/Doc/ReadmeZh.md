# xCPrint

> **Project** : xCPrint
> **Author**  : William Hsiao
> **Descript**: 跨平台彩色終端控制與格式化輸出庫

## 簡介
`xCPrint` 是一個專為嵌入式系統與跨平台 C 開發設計的輕量級輸出工具庫。
針對 `Windows` 環境提供 `API` 兼容處理，解決了傳統 `printf` 無法直接輸出彩色的問題。

* 跨平台支援: 自動偵測 `_WIN32` 環境。
* 零開銷宏: 大部分功能透過預處理宏實作，不調用函數時不佔用程式空間。
* 類型安全: 嚴格遵循 `C99` 標準，支援可變參數宏 (__VA_ARGS__)。

## 特性
1. `ANSI` 顏色控制 : 支援 `8` 種基礎顏色、高亮度`(Bold)`模式以及背景顏色設定。
2. 終端狀態恢復    : 所有輸出函數在結尾自動附加`RESET`碼，避免顏色污染後續輸出。
3. `Windows` 兼容 : 內建`xWin_AnsiEnable`，一鍵開啟`Windows`終端對`ANSI`的支援。
4. 極簡依賴       : 僅依賴`xType.h`與`xMeta.h`。

## API
#### [顏色宏定義]
1. `xFG_CLI_COLOR     `: 基礎前景顏色 `ANSI` 字串。
2. `xFG_CLI_BOLD_COLOR`: 加粗/高亮度前景顏色。
3. `xBG_CLI_COLOR     `: 背景顏色設定。
4. `xTYPE_CLI_BOLD... `: 粗體、斜體、下劃線等文字風格。

#### [核心函數]
1. `xWin_AnsiEnable`: (`Windows`專用)透過 `SetConsoleMode`啟用`ANSI`轉義序列處理。
2. `xWin_CPrint    `: (`Windows`專用)使用原生`API`進行顏色輸出，不依賴`ANSI`碼。

#### [核心宏函數]
1. `xRPRINT/xGPRINT/xBPRINT`: 糖果系列。最常用的紅色、綠色、藍色快捷輸出。
2. `xFG_RPRINT/xFG_GPRINT  `: 標準前景顏色輸出。
3. `xFB_RPRINT/xFB_GPRINT  `: 高亮度 (`Bold`) 前景顏色輸出。
4. `xPRINT(ATTR,FMT, ...)  `: 通用輸出。可自定義`ATTR`(如同時設定背景與前景)。
5. `xWIN_RPRINT/xWIN_GPRINT`: (`Windows`專用) 強制使用 `Windows API` 畫筆輸出

## 庫資訊
1. `xCPrint` 庫大小在Linux: `0KB`
2. 在 `Linux` 是單純宏庫

## 編譯依賴
##### [標頭依賴]
1. `xMeta.h`
2. `xType.h`

##### [編譯]
在 `xCPrint` 資料夾內使用指令 `make all`

```shell
make all
```

## 範例
在 `Sample` 資料夾內使用指令 `make all`

```shell
make all
```

#### [範例一]
1. 演示使用 `xCPrint` 在 `Linux` 平台上使用

```c
int main(void)
{
  int i = 0;
  xFG_RPRINT("This is Color Red    [%d]\n",i++);
  xFB_RPRINT("This is Bold Red     [%d]\n",i++);
  //Type
  xPRINT(xTYPE_CLI_ITALIC ,"Italic Text\n");
  xPRINT(xTYPE_CLI_STRIKE ,"Strikethrough Text\n");
  xPRINT(xTYPE_CLI_REVERSE,"Reversed Color\n");
  xPRINT(xTYPE_CLI_BLINK  ,"Blinking Text\n");
  printf("\n\n");

  //Candy
  xRPRINT("This is Bold Red     [%d]\n",i++);
  printf("\n\n");

  //Custom
  xPRINT(xBG_CLI_RED  xFG_CLI_WHITE, " White text on Red background\n");
  xPRINT(xBG_CLI_BLUE xFG_CLI_YELLOW xTYPE_CLI_BOLD, " Bold Yellow text on Blue background\n");
  printf("\n\n");

  //Format
  int   Status   = 404;
  char *Msg      = "Not Found"; 
  DBL   Progress = 85.5;
  xFB_RPRINT("Error [%d]: %s\n",Status,Msg);
  xFB_GPRINT("System Update: %.1f%% Complete\n",Progress);
  return 0;
}
```

#### [範例二]
1. 演示使用 `CPrint` 在 `Windwos` 上用 `ANSI Color`
2. 內容同範例一，但須加上以下內容
```c
#ifdef __WIN32
  xWin_AnsiEnable();    //Windows ANSI Enable
#endif
```

#### [範例三]
1. 演示使用 `CPrint` 在 `Windows` 下用包裝畫筆的函數

```c
//Main Code
int main(void)
{
#ifdef __WIN32
  int Value = 5;
  xWIN_RPRINT("Windows Color Red    [%d]\n",Value);
  xWIN_GPRINT("Windows Color Green  [%d]\n",Value);
  xWIN_BPRINT("Windows Color Blue   [%d]\n",Value);
  xWIN_YPRINT("Windows Color Yellow [%d]\n",Value);
  xWIN_CPRINT("Windows Color Cyan   [%d]\n",Value);
  xWIN_MPRINT("Windows Color Magenta[%d]\n",Value);
  xWIN_WPRINT("Windows Color White  [%d]\n",Value);
#endif
  return 0;
}
```

## 授權條款
本專案採用 `MIT License` 授權使用
