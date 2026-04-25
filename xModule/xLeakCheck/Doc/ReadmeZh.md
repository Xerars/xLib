# xLeakCheck

> **Project** : xLeakCheck
> **Author**  : William Hsiao
> **Descript**: 輕量化記憶體洩漏檢測工具庫

## 簡介
`xLeakCheck` 是一個極其輕量的 C 語言工具庫，專為嵌入式系統與 `C` 專案開發設計。
它透過宏替換在不改變原有程式邏輯的前提下，追蹤所有動態記憶體的申請與釋放行為，
幫助開發者精準定位記憶體洩漏發生的檔案、函式與行號。

## 特性
1. 極度輕量：核心代碼約 `200` 行
2. 無縫整合：透過宏定義覆蓋標準庫 `malloc`, `calloc`, `realloc`, `free`。
3. 精準定位：自動記錄洩漏點的 `__FILE__`, `__LINE__`, `__func__` 資訊。
4. `C/C++` 兼容：支援 `C99` 標準，適用於各類編譯環境。
5. 單元測試友好：`xLeak_MemInfo` 回傳洩漏計數，便於自動化測試集成。

## API
#### [核心函數]
1. xLeak_Malloc : 封裝 `malloc`  並記錄追蹤資訊。
2. xLeak_Calloc : 封裝 `calloc`  並記錄追蹤資訊。
3. xLeak_Realloc: 封裝 `realloc` 並更新追蹤鏈表。
4. xLeak_Free   : 釋放記憶體並從追蹤清單中移除。
5. xLeak_MemInfo: 打印當前所有未釋放的記憶體資訊，並返回洩漏區塊總數。

#### [核心宏函數]
為了保持開發習慣，庫中定義了與標準庫同名的宏，會自動擷取調用位置：
1. `malloc(S)`
2. `calloc(C,S)`
3. `realloc(P,S)`
4. `free(P)`

同時提供顯式調用版本：
1. `Leak_Malloc(S)`
2. `Leak_Calloc(C,S)`
3. `Leak_Realloc(P,S)`
4. `Leak_Free(P)`

## 庫資訊
1. `xLeakCheck` 庫大小在Linux: `1.433KB`

```c
xLeak_Calloc        // 占用 55  KB
xLeak_Free          // 占用 126 KB
xLeak_Malloc        // 占用 127 KB
xLeak_MemInfo       // 占用 224 KB
xLeak_Realloc       // 占用 108 KB
```

## 編譯依賴
##### [標頭依賴]
1. `xMeta.h`
2. `xType.h`

##### [編譯]
在 `xLeakCheck` 資料夾內使用指令 `make all`

```shell
make all
```

## 範例
在 `Sample` 資料夾內使用指令 `make all`

```shell
make all
```

#### [範例一]
1. 演示使用 `xLeakCheck` 申請記憶體後不釋放的結果

```c
//Main Code
int main(void)
{
#ifdef LEAKCHECK
  atexit(Show_LeakMemInfo);
#endif    //LEAKCHECK

  int* ptr1 = malloc(1000*sizeof(int));
  int* ptr2 = calloc(1000,sizeof(int));

  memset(ptr1,0,1000*sizeof(int));
  memset(ptr2,0,1000*sizeof(int));

  ptr1=realloc(ptr1,2000*sizeof(int));
  memset(ptr1,0,2000*sizeof(int));

  return 0;
}

void Show_LeakMemInfo(void)
{
  xLeak_MemInfo();
}
```

## 授權條款
本專案採用 `MIT License` 授權使用
