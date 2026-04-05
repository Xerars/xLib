# xDuff

> **Project** : xDuff
> **Author**  : William Hsiao
> **Descript**: 基於達夫設備的高效能運算與輕量化協程函式庫

## 簡介
`xDuff` 是一個利用 `C` 語言經典的`達夫設備`語法特性開發的工具庫。
它提供了兩大核心功能:
* 極致的運算優化:透過`(迴圈展開)`技術，顯著提升記憶體操作與矩陣運算的執行效率。
* 輕量化協程：提供`(無堆疊)`的並發控制，支援`互斥鎖`、`信號量`等同步機制，適用於資源受限的嵌入式系統。


## 特性
1. `C/C++` 兼容
2. 支持 `C99`
3. 高效能利用達夫設備減少跳轉開銷
4. 涵蓋記憶體控制、矩陣運算、協程與同步鎖

## API
#### [類型定義]
1. `xDuff_Coro  `: 協程控制器
2. `xDuff_Locker`: 互斥鎖
3. `xDuff_Sem   `: 信號量

#### [核心函數]
記憶體控制
1. `xDuff_MemCopy` : 將資料從來源位址複製到目標位址
2. `xDuff_MemSet ` : 將指定範圍的記憶體全部填入同一個數值
3. `xDuff_MemCmp ` : 比較兩塊記憶體內容是否完全相同

矩陣計算
1. `xDuff_MatAdd  `: 兩個同維度矩陣對應位置相加 ($A_{ij} + B_{ij}$)
2. `xDuff_MatSub  `: 兩個同維度矩陣對應位置相減 ($A_{ij} - B_{ij}$)
3. `xDuff_MatMul  `: 標準的線性代數乘法
4. `xDuff_MatDot  `: 計算 $\sum (a_i \times b_i)$
5. `xDuff_MatScale`: 將矩陣中的每個元素都乘以同一個常數 $k$ ($k \times A_{ij}$)
6. `xDuff_MatTPose`: 將矩陣的列與行互換（$A_{ij} \rightarrow A_{ji}$）

#### [核心宏函數-運算]
1. `xDUFF_STRCPY    `: 將 SRC 前 N 個元素複製到 DST
2. `xDUFF_STRSET    `: 將 DST 前 N 個元素統一設為值 V
3. `xDUFF_STRCMP    `: 比較兩塊記憶體前 N 位元組是否一致

1. `xDUFF_MAT_ADD   `: 矩陣對應元素加法
2. `xDUFF_MAT_SUB   `: 矩陣對應元素減法
3. `xDUFF_MAT_MUL   `: 標準矩陣乘法 $C_{M \times K} = A_{M \times N} \times B_{N \times K}$
4. `xDUFF_MAT_DOT   `: 向量點積
5. `xDUFF_MAT_SCALE `: 縮放運算
6. `xDUFF_MAT_TPOSE `: 矩陣轉置

1. `xDUFF_ITER      `: 核心運算迭代器
2. `xDUFF_ADD       `: 將陣列內的每個元素與純量進行加法運算
3. `xDUFF_SUB       `: 將陣列內的每個元素與純量進行減法運算
4. `xDUFF_MUL       `: 將陣列內的每個元素與純量進行乘法運算
5. `xDUFF_DIV       `: 將陣列內的每個元素與純量進行除法運算
6. `xDUFF_MOD       `: 將陣列內的每個元素與純量進行餘數運算
7. `xDUFF_OR        `: 將陣列內的每個元素與純量進行或運算
8. `xDUFF_AND       `: 將陣列內的每個元素與純量進行與運算
9. `xDUFF_XOR       `: 將陣列內的每個元素與純量進行互斥或運算
10. `xDUFF_NOT      `: 將陣列內的每個元素與純量進行非運算
11. `xDUFF_ADD_SUM  `: 將陣列內的每個元素與純量進行加法校驗碼
12. `xDUFF_XOR_SUM  `: 將陣列內的每個元素與純量進行互斥或校驗法


#### [核心宏函數-協程]
1. `xDUFF_CORO_BEGIN       `: 標記協程函數的開始
2. `xDUFF_CORO_YIELD       `: 暫停當前進度，並在下次呼叫時從這裡恢復
3. `xDUFF_CORO_END         `: 標記協程的結束
4. `xDUFF_CORO_RESET       `: 將協程的狀態機計數器清零
5. `xDUFF_CORO_MUTEX_LOCK  `: 協程層級的互斥鎖上鎖
6. `xDUFF_CORO_MUTEX_UNLOCK`: 協程層級的互斥鎖解鎖
7. `xDUFF_CORO_SEM_WAIT    `: 協程信號量等待
8. `xDUFF_CORO_SEM_SIGNAL  `: 協程信號量發出信號
9. `xDUFF_CORO_WAIT_UNTIL  `: 阻塞等待 直到條件達成
10. `xDUFF_CORO_DELAY      `: 讓協程暫停指定的時間
11. `xDUFF_CORO_EVERY      `: 週期性執行任務

## 庫資訊
1. `xDuff` 庫大小: `3.853KB`
```c
xDuff_MatAdd      // 佔用 308 Bytes
xDuff_MatDot      // 佔用 344 Bytes
xDuff_MatMul      // 佔用 795 Bytes
xDuff_MatScale    // 佔用 205 Bytes
xDuff_MatSub      // 佔用 308 Bytes
xDuff_MatTPose    // 佔用 313 Bytes
xDuff_MemCmp      // 佔用 285 Bytes
xDuff_MemCopy     // 佔用 427 Bytes
xDuff_MemSet      // 佔用 205 Bytes
```

## 編譯依賴
##### [標頭依賴]
1. `xMeta.h`
2. `xType.h`

##### [編譯]
在 `xDuff` 資料夾內使用指令 `make all`

```shell
make all
```

## 範例
在 `Sample` 資料夾內使用指令 `make all`

```shell
make all
```
#### [範例一]
1. 演示使用`xDLoad`的記憶體控制功能
2. 內容包含運算效率計算與 `memcpy`、`memset`、`memcmp` 的比較

```c
//[Variable Declare]
static U8* gSrc = NULL;
static U8* gDst = NULL;

//Main Code
int main(void)
{
  //Allocate Memory
  gSrc = (U8*)malloc(TEST_DATA_SIZE);
  gDst = (U8*)malloc(TEST_DATA_SIZE);

  if(!gSrc || !gDst)
  {
    printf("[Error]: Memory Allocate Fail!\n");
    return -1;
  }

  //Test the Memory Copy
  memset(gSrc,0xAA,TEST_DATA_SIZE);
  printf("------------------- Memory Copy -------------------\n");
  PERF_TEST("Standard Memory Copy",TEST_DATA_SIZE,TEST_STD_Copy());
  PERF_TEST("ForLooop Memory Copy",TEST_DATA_SIZE,TEST_For_Copy());
  PERF_TEST("xDuff    Memory Copy",TEST_DATA_SIZE,TEST_Duff_Copy());
  PERF_TEST("SIMD     Memory Copy",TEST_DATA_SIZE,TEST_SIMD_Copy());
  
  //Test the Memory Set
  printf("------------------- Memory Set --------------------\n");
  PERF_TEST("Standard Memory Set" ,TEST_DATA_SIZE,TEST_STD_Set());
  PERF_TEST("ForLooop Memory Set" ,TEST_DATA_SIZE,TEST_For_Set());
  PERF_TEST("xDuff    Memory Set" ,TEST_DATA_SIZE,TEST_Duff_Set());
  PERF_TEST("SIMD     Memory Set" ,TEST_DATA_SIZE,TEST_SIMD_Set());

  //Test the Memory Compare
  printf("----------------- Memory Compare ------------------\n");
  memset(gSrc,0x55,TEST_DATA_SIZE);
  memset(gDst,0x55,TEST_DATA_SIZE);
  PERF_TEST("Standard Memory Compare" ,TEST_DATA_SIZE,TEST_STD_Cmp());
  PERF_TEST("ForLooop Memory Compare" ,TEST_DATA_SIZE,TEST_For_Cmp());
  PERF_TEST("xDuff    Memory Compare" ,TEST_DATA_SIZE,TEST_Duff_Cmp());
  PERF_TEST("SIMD     Memory Compare" ,TEST_DATA_SIZE,TEST_SIMD_Cmp());

  //Destroy
  SAFE_DESTROY(gSrc);
  SAFE_DESTROY(gDst);
  return 0;
}
```

##### 範例-1 函數效率
在 `O3` 的情況下
``` shell
------------------- Memory Copy -------------------
[Standard Memory Copy]     Time : 0.408298 sec  Rate : 2507.97 MB/s
[ForLooop Memory Copy]     Time : 0.168845 sec  Rate : 6064.73 MB/s
[xDuff    Memory Copy]     Time : 0.085610 sec  Rate : 11961.28 MB/s
[SIMD     Memory Copy]     Time : 0.337819 sec  Rate : 3031.21 MB/s
------------------- Memory Set --------------------
[Standard Memory Set]      Time : 0.127251 sec  Rate : 8047.12 MB/s
[ForLooop Memory Set]      Time : 0.126776 sec  Rate : 8077.26 MB/s
[xDuff    Memory Set]      Time : 0.063646 sec  Rate : 16088.99 MB/s
[SIMD     Memory Set]      Time : 0.126390 sec  Rate : 8101.89 MB/s
----------------- Memory Compare ------------------
[Standard Memory Compare]  Time : 0.116617 sec  Rate : 8780.90 MB/s
[ForLooop Memory Compare]  Time : 0.488327 sec  Rate : 2096.95 MB/s
[xDuff    Memory Compare]  Time : 0.063252 sec  Rate : 16189.28 MB/s
[SIMD     Memory Compare]  Time : 0.116520 sec  Rate : 8788.20 MB/s

```
根據實驗，在`O3`的情況下，執行效率比較如下:
1. 記憶體複製 : `xDuff >> ForLoop >> SIMD   >  memcpy`
2. 記憶體設置 : `xDuff >> SIMD    >  memset >  ForLoop`
3. 記憶體比較 : `xDuff >> SIMD    >  memcmp >> ForLoop`

在 `O0` 的情況下
``` shell
------------------- Memory Copy -------------------
[Standard Memory Copy]     Time : 0.418578 sec  Rate : 2446.38 MB/s
[ForLooop Memory Copy]     Time : 1.092280 sec  Rate : 937.49 MB/s
[xDuff    Memory Copy]     Time : 0.085735 sec  Rate : 11943.81 MB/s
[SIMD     Memory Copy]     Time : 1.279643 sec  Rate : 800.22 MB/s
------------------- Memory Set --------------------
[Standard Memory Set]      Time : 0.126735 sec  Rate : 8079.84 MB/s
[ForLooop Memory Set]      Time : 0.609588 sec  Rate : 1679.82 MB/s
[xDuff    Memory Set]      Time : 0.063856 sec  Rate : 16036.11 MB/s
[SIMD     Memory Set]      Time : 0.125780 sec  Rate : 8141.23 MB/s
----------------- Memory Compare ------------------
[Standard Memory Compare]  Time : 0.116397 sec  Rate : 8797.44 MB/s
[ForLooop Memory Compare]  Time : 1.478592 sec  Rate : 692.55 MB/s
[xDuff    Memory Compare]  Time : 0.063712 sec  Rate : 16072.27 MB/s
[SIMD     Memory Compare]  Time : 0.197140 sec  Rate : 5194.28 MB/s

```
根據實驗，在`O0`的情況下，執行效率比較如下:
1. 記憶體複製 : `xDuff >> memcpy >> ForLoop > SIMD`
2. 記憶體設置 : `xDuff >> SIMD   >  memset  > ForLoop`
3. 記憶體比較 : `xDuff >> memcmp >> SIMD    > ForLoop`

#### [範例二]
1. 演示使用 `xDuff` 高效能矩陣運算
2. 演示內容包含矩陣加法、減法、乘法、點積、縮放、轉置功能

```c
//[Variable Declare]
static DBL *MTX_A = NULL;
static DBL *MTX_B = NULL;
static DBL *MTX_C = NULL;

static DBL *MTX_SA = NULL;
static DBL *MTX_SB = NULL;
static DBL *MTX_SC = NULL;

//Main Code
int main(void)
{
  MTX_A  = (DBL*)malloc(MATRIX_LEN * sizeof(DBL));
  MTX_B  = (DBL*)malloc(MATRIX_LEN * sizeof(DBL));
  MTX_C  = (DBL*)malloc(MATRIX_LEN * sizeof(DBL));
  if(!MTX_A || !MTX_B || !MTX_C)
  {
    printf("[Error]: Memory Allocate Fail!\n");
    return -1;
  }

  MTX_SA = (DBL*)malloc(MATRIX_SLEN * sizeof(DBL));
  MTX_SB = (DBL*)malloc(MATRIX_SLEN * sizeof(DBL));
  MTX_SC = (DBL*)malloc(MATRIX_SLEN * sizeof(DBL));
  if(!MTX_SA || !MTX_SB || !MTX_SC)
  {
    printf("[Error]: Memory Allocate Fail!\n");
    return -1;
  }
  
  //Matrix_Add
  printf("\n--------------------------------------- Add ---------------------------------------\n");
  Matrix_Init(2,1);   PERF_TEST("STD  Matrix ADD",MATRIX_LEN + MATRIX_SLEN,TEST_STD_MatAdd());
  Matrix_Init(2,1);   PERF_TEST("Duff Matrix ADD",MATRIX_LEN + MATRIX_SLEN,TEST_Duff_MatAdd());
  Matrix_Init(2,1);   PERF_TEST("SIMD Matrix ADD",MATRIX_LEN + MATRIX_SLEN,TEST_SIMD_MatAdd());

  //Matrix Sub
  printf("\n--------------------------------------- Sub ---------------------------------------\n");
  Matrix_Init(2,1);   PERF_TEST("STD  Matrix SUB",MATRIX_LEN + MATRIX_SLEN,TEST_STD_MatSub());
  Matrix_Init(2,1);   PERF_TEST("Duff Matrix SUB",MATRIX_LEN + MATRIX_SLEN,TEST_Duff_MatSub());
  Matrix_Init(2,1);   PERF_TEST("SIMD Matrix SUB",MATRIX_LEN + MATRIX_SLEN,TEST_SIMD_MatSub());

  //Matrix Mul
  printf("\n--------------------------------------- Mul ---------------------------------------\n");
  Matrix_Init(1,0);   PERF_TEST("STD  Matrix MUL",MATRIX_LEN + MATRIX_SLEN,TEST_STD_MatMul());
  Matrix_Init(1,0);   PERF_TEST("Duff Matrix MUL",MATRIX_LEN + MATRIX_SLEN,TEST_Duff_MatMul());
  Matrix_Init(1,0);   PERF_TEST("SIMD Matrix MUL",MATRIX_LEN + MATRIX_SLEN,TEST_SIMD_MatMul());

  //Dot Product
  printf("\n--------------------------------------- Dot ---------------------------------------\n");
  Matrix_Init(2,1);   PERF_TEST("STD  Matrix DOT",MATRIX_LEN + MATRIX_SLEN,TEST_STD_MatDot());
  Matrix_Init(2,1);   PERF_TEST("Duff Matrix DOT",MATRIX_LEN + MATRIX_SLEN,TEST_Duff_MatDot());
  Matrix_Init(2,1);   PERF_TEST("SIMD Matrix DOT",MATRIX_LEN + MATRIX_SLEN,TEST_SIMD_MatDot());

  //Matrix Scale
  printf("\n--------------------------------------- Scl ---------------------------------------\n");
  Matrix_Init(2,1);   PERF_TEST("STD  Matrix SCL",MATRIX_LEN + MATRIX_SLEN,TEST_STD_MatScale());
  Matrix_Init(2,1);   PERF_TEST("Duff Matrix SCL",MATRIX_LEN + MATRIX_SLEN,TEST_Duff_MatScale());
  Matrix_Init(2,1);   PERF_TEST("SIMD Matrix SCL",MATRIX_LEN + MATRIX_SLEN,TEST_SIMD_MatScale());

  //Matrix TPose
  printf("\n-------------------------------------- TPose --------------------------------------\n");
  Matrix_Init(2,1);   PERF_TEST("STD  Matrix SCL",MATRIX_LEN + MATRIX_SLEN,TEST_STD_MatTPose());
  Matrix_Init(2,1);   PERF_TEST("Duff Matrix SCL",MATRIX_LEN + MATRIX_SLEN,TEST_Duff_MatTPose());
  Matrix_Init(2,1);   PERF_TEST("SIMD Matrix SCL",MATRIX_LEN + MATRIX_SLEN,TEST_SIMD_MatTPose());

  //Destroy
  SAFE_DESTROY(MTX_A);
  SAFE_DESTROY(MTX_B);
  SAFE_DESTROY(MTX_C);

  SAFE_DESTROY(MTX_SA);
  SAFE_DESTROY(MTX_SB);
  SAFE_DESTROY(MTX_SC);
  return 0;
}
```
#### 範例-2 函數效率
在 `O3` 的情況下
```shell
--------------------------------------- Add ---------------------------------------
[STD  Matrix ADD]  Time : 0.001942 sec  Rate : 491.02 MB/s
[Duff Matrix ADD]  Time : 0.001940 sec  Rate : 491.54 MB/s
[SIMD Matrix ADD]  Time : 0.001957 sec  Rate : 487.30 MB/s
--------------------------------------- Sub ---------------------------------------
[STD  Matrix SUB]  Time : 0.001931 sec  Rate : 494.01 MB/s
[Duff Matrix SUB]  Time : 0.001972 sec  Rate : 483.56 MB/s
[SIMD Matrix SUB]  Time : 0.001949 sec  Rate : 489.21 MB/s
--------------------------------------- Mul ---------------------------------------
[STD  Matrix MUL]  Time : 4.211504 sec  Rate : 0.23 MB/s
[Duff Matrix MUL]  Time : 0.510295 sec  Rate : 1.87 MB/s
[SIMD Matrix MUL]  Time : 0.388760 sec  Rate : 2.45 MB/s
--------------------------------------- Dot ---------------------------------------
[STD  Matrix DOT]  Time : 0.001360 sec  Rate : 701.01 MB/s
[Duff Matrix DOT]  Time : 0.001358 sec  Rate : 702.37 MB/s
[SIMD Matrix DOT]  Time : 0.001203 sec  Rate : 792.79 MB/s
--------------------------------------- Scl ---------------------------------------
[STD  Matrix SCL]  Time : 0.000982 sec  Rate : 971.06 MB/s
[Duff Matrix SCL]  Time : 0.000939 sec  Rate : 1015.20 MB/s
[SIMD Matrix SCL]  Time : 0.000971 sec  Rate : 982.42 MB/s
-------------------------------------- TPose --------------------------------------
[STD  Matrix SCL]  Time : 0.002565 sec  Rate : 371.86 MB/s
[Duff Matrix SCL]  Time : 0.001455 sec  Rate : 655.33 MB/s
[SIMD Matrix SCL]  Time : 0.001708 sec  Rate : 558.24 MB/s
```

根據實驗，在`O3`的情況下，執行效率比較如下:
1. 矩陣加法 : `xDuff > STD   > SIMD  (幾乎沒差異)`
2. 矩陣減法 : `STD   > SIMD  > xDuff (幾乎沒差異)`
3. 矩陣乘法 : `SIMD  > xDuff > STD`
4. 矩陣內積 : `SIMD  > xDuff > STD   (差異小)`
4. 矩陣內積 : `SIMD  > xDuff > STD   (差異小)`
4. 矩陣內積 : `SIMD  > xDuff > STD   (差異小)`


在 `O0` 的情況下
``` shell
--------------------------------------- Add ---------------------------------------
[STD  Matrix ADD]  Time : 0.002122 sec  Rate : 449.49 MB/s
[Duff Matrix ADD]  Time : 0.001945 sec  Rate : 490.31 MB/s
[SIMD Matrix ADD]  Time : 0.002068 sec  Rate : 461.09 MB/s
--------------------------------------- Sub ---------------------------------------
[STD  Matrix SUB]  Time : 0.002132 sec  Rate : 447.24 MB/s
[Duff Matrix SUB]  Time : 0.001955 sec  Rate : 487.85 MB/s
[SIMD Matrix SUB]  Time : 0.002065 sec  Rate : 461.88 MB/s
--------------------------------------- Mul ---------------------------------------
[STD  Matrix MUL]  Time : 5.025502 sec  Rate : 0.19 MB/s
[Duff Matrix MUL]  Time : 0.513272 sec  Rate : 1.86 MB/s
[SIMD Matrix MUL]  Time : 1.079165 sec  Rate : 0.88 MB/s
--------------------------------------- Dot ---------------------------------------
[STD  Matrix DOT]  Time : 0.003342 sec  Rate : 285.39 MB/s
[Duff Matrix DOT]  Time : 0.001305 sec  Rate : 731.06 MB/s
[SIMD Matrix DOT]  Time : 0.001660 sec  Rate : 574.69 MB/s
--------------------------------------- Scl ---------------------------------------
[STD  Matrix SCL]  Time : 0.001377 sec  Rate : 692.59 MB/s
[Duff Matrix SCL]  Time : 0.000928 sec  Rate : 1027.57 MB/s
[SIMD Matrix SCL]  Time : 0.001323 sec  Rate : 720.62 MB/s
-------------------------------------- TPose --------------------------------------
[STD  Matrix SCL]  Time : 0.002577 sec  Rate : 370.04 MB/s
[Duff Matrix SCL]  Time : 0.001436 sec  Rate : 664.33 MB/s
[SIMD Matrix SCL]  Time : 0.002375 sec  Rate : 401.51 MB/s
```
根據實驗，在`O0`的情況下，執行效率比較如下:
1. 矩陣加法 : `xDuff > SIMD > STD`
2. 矩陣減法 : `xDuff > SIMD > STD`
3. 矩陣乘法 : `xDuff > SIMD > STD`
4. 矩陣內積 : `xDuff > SIMD > STD`
5. 矩陣縮放 : `xDuff > SIMD > STD`
6. 矩陣轉置 : `xDuff > SIMD > STD`

#### [範例三]
1. 演示如何快速對陣列進行批次算術運算與校驗和計算

```c
int main(void)
{
  int Value[10] = {0};
  int *pVal = NULL;
  int  Size = ASIZE(Value);

  //Initial
  for(int i=0;i<10;i++)
    Value[i] = i;

  int ChkSum1 = 0;
  int ChkSum2 = 0;

  pVal = Value;   xDUFF_ADD(pVal,10  ,Size);   Show_Array(Value,Size);
  pVal = Value;   xDUFF_SUB(pVal,5   ,Size);   Show_Array(Value,Size);
  pVal = Value;   xDUFF_MUL(pVal,10  ,Size);   Show_Array(Value,Size);
  pVal = Value;   xDUFF_DIV(pVal,2   ,Size);   Show_Array(Value,Size);
  pVal = Value;   xDUFF_MOD(pVal,7   ,Size);   Show_Array(Value,Size);
  pVal = Value;   xDUFF_OR (pVal,0xF0,Size);   Show_Array(Value,Size);
  pVal = Value;   xDUFF_AND(pVal,0x30,Size);   Show_Array(Value,Size);
  pVal = Value;   xDUFF_XOR(pVal,0x99,Size);   Show_Array(Value,Size);
  pVal = Value;   xDUFF_NOT(pVal,Size);        Show_Array(Value,Size);

  //Check Sum
  //Initial
  for(int i=0;i<10;i++)
    Value[i] = i;

  pVal = Value;   xDUFF_ADD_SUM(pVal,ChkSum1,Size);
  pVal = Value;   xDUFF_XOR_SUM(pVal,ChkSum2,Size);
  printf("CheckSum-1[ADD]: 0x%02x\n",ChkSum1);
  printf("CheckSum-2[XOR]: 0x%02x\n",ChkSum2);
  return 0;
}
```

#### [範例四]
1.演示如何在單執行緒環境下，模擬多個並發任務

```c
int main(void)
{
  xDuff_Coro CO_LED1     = {0,0};
  xDuff_Coro CO_LED2     = {0,0};
  xDuff_Coro CO_ALARM    = {0,0};
  xDuff_Coro CO_PRODUCER = {0,0};
  xDuff_Coro CO_CUSTOMER = {0,0};
  xDuff_Coro CO_PRINTERA = {0,0};
  xDuff_Coro CO_PRINTERB = {0,0};
  xDuff_Coro CO_CARPARK1 = {0,0};
  xDuff_Coro CO_CARPARK2 = {0,0};
  xDuff_Coro CO_CARPARK3 = {0,0};
  xDuff_Coro CO_CARPARK4 = {0,0};
  xDuff_Coro CO_SMLIGHT  = {0,0};
  xDuff_Coro CO_BGLOG    = {0,0};

  for(int Tick = 0;Tick <= 20;Tick++)
  {
    printf("\n\n[Tick]: %d\n",Tick);
    Coro_LED1 (&CO_LED1);
    Coro_LED2 (&CO_LED2);
    Coro_Alram(&CO_ALARM);
    Coro_Producer(&CO_PRODUCER);
    Coro_Consumer(&CO_CUSTOMER);
    Coro_PrintA(&CO_PRINTERA);
    Coro_PrintB(&CO_PRINTERB);
    Coro_CarPark(&CO_CARPARK1,1);
    Coro_CarPark(&CO_CARPARK2,2);
    Coro_CarPark(&CO_CARPARK3,3);
    Coro_CarPark(&CO_CARPARK4,4);
    Coro_SmartLight(&CO_SMLIGHT);
    Coro_BGLog(&CO_BGLOG);

    usleep(1000000);
  }
  printf("\n");
  return 0;
}
```

## 授權條款
本專案採用 `MIT License` 授權使用
