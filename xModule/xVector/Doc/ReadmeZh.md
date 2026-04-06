# xDuff

> **Project** : xVector
> **Author**  : William Hsiao
> **Descript**: 基於宏高彈性、動態泛型向量庫

## 簡介
`xVector` 是一個輕量級的 `C` 語言函式庫，旨在為純 C 環境提供類似 `C++ std::vector` 的動態陣列功能。
透過強大的`宏分發`技術，它支援：

* 偽泛型支援  : 只需一行宏，即可為自定義結構或基本型別產生專屬的 `Vector` 實作。
* 自動擴容機制: 內建倍增式隨機存取記憶體管理，減少頻繁 `realloc` 的開銷。
* 類型安全    : 生成的函數帶有類型名稱`(如 xVec_Int_Push)`，有效避免型別誤用。


## 特性
1. `C/C++` 兼容
2. 支持 `C99`
3. 不使用 `void*`，保留編譯器對具體型別的優化能力。
4. 極簡依賴
5. 完整生命週期管理：涵蓋初始化、動態縮放、插入、刪除及基礎運算。

## API
#### [類型定義]
1. `xVector`               : 預設的 int 型別向量結構
2. `XVEC_STRUCT(TYPE,NAME)`: 核心宏，用於宣告特定型別的向量結構體。

#### [核心函數]
1.  `xVector_Init   `     : 初始化向量，預配指定容量
2.  `xVector_Destroy`     : 放內部數據空間並重置狀態
3.  `xVector_Resize `     : 手動調整向量容量
4.  `xVector_Push   `     : 於末端新增元素(容量不足時自動翻倍)
5.  `xVector_Pop    `     : 移除末端元素
6.  `xVector_At     `     : 隨機存取指定索引元素(含邊界檢查與靜態零值保護)
7.  `xVector_Insert `     : 在指定位置插入元素，後方元素自動後移
8.  `xVector_Remove `     : 移除指定位置元素，後方元素自動前移
9.  `xVector_Update `     : 更新指定位置的元素內容
10. `xVector_Clear  `     : 清空所有資料(保留容量)
11. `xVector_Merge  `     : 合併兩個相同型別的向量
12. `xVector_Reverse`     : 將向量內的元素順序反轉
13. `xVector_Sum    `     : 計算向量和
14. `xVector_Average`     : 計算向量平均值
15. `xVector_Scale  `     : 向量縮放
16. `xVector_FindMax`     : 取得向量最大值
17. `xVector_FindMin`     : 取得向量最小值

#### [核心宏函數]
1.  `XVEC_IMPL(TYPE,NAME)`: 一鍵生成該型別所有的操作函數實作
2.  `xVec_NAME_Init      `: 初始化向量，預配指定容量
3.  `xVec_NAME_Destroy   `: 釋放內部數據空間並重置狀態
4.  `xVec_NAME_Resize    `: 手動調整向量容量
5.  `xVec_NAME_Push      `: 於末端新增元素(容量不足時自動翻倍)
6.  `xVec_NAME_Pop       `: 移除末端元素
7.  `xVec_NAME_At        `: 隨機存取指定索引元素(含邊界檢查與靜態零值保護)
8.  `xVec_NAME_Insert    `: 在指定位置插入元素，後方元素自動後移
9.  `xVec_NAME_Remove    `: 移除指定位置元素，後方元素自動前移
10. `xVec_NAME_Update    `: 更新指定位置的元素內容
11. `xVec_NAME_Clear     `: 清空所有資料(保留容量)
12. `xVec_NAME_Merge     `: 合併兩個相同型別的向量
13. `xVec_NAME_Reverse   `: 將向量內的元素順序反轉



## 庫資訊
1. `xVector` 庫大小: `1.975KB`->`1.916KB`(-2.98%)
```c
xVector_FindMax   // 佔用 250->230(-8.00%)  Bytes
xVector_FindMin   // 佔用 247->227(-8.09%)  Bytes
xVector_Sum       // 佔用 159->143(-10.06%) Bytes
xVector_Insert    // 佔用 141->124(-12.06%) Bytes
xVector_Merge     // 佔用 115 Bytes
xVector_Push      // 佔用 62 Bytes
xVector_Remove    // 佔用 57 Bytes
xVector_Resize    // 佔用 49 Bytes
xVector_Reverse   // 佔用 49 Bytes
xVector_Average   // 佔用 48 Bytes
xVector_Init      // 佔用 45 Bytes
xVector_Destroy   // 佔用 38 Bytes
xVector_Scale     // 佔用 35 Bytes
xVector_At        // 佔用 26 Bytes
xVector_Update    // 佔用 23 Bytes
xVector_Pop       // 佔用 18 Bytes
xVector_Clear     // 佔用 12 Bytes
```

## 編譯依賴
##### [標頭依賴]
1. `xMeta.h`
2. `xType.h`

##### [編譯]
在 `xVector` 資料夾內使用指令 `make all`

```shell
make all
```

## 範例
在 `Sample` 資料夾內使用指令 `make all`

```shell
make all
```
#### [範例一]
1. 演示使用`xVector`整數的動態陣列運算

```c
//Main Code
int main(void)
{
  xVector Vec1;
  xVector Vec2;

  //Init
  xVector_Init(&Vec1,5);
  xVector_Init(&Vec2,5);

  //Push Data
  xVector_Push(&Vec1,1);
  xVector_Push(&Vec1,3);
  xVector_Push(&Vec1,5);

  xVector_Push(&Vec2,2);
  xVector_Push(&Vec2,4);
  xVector_Push(&Vec2,6);

  //At
  int V1 = xVector_At(&Vec1,2);
  int V2 = xVector_At(&Vec1,2);

  //Insert
  xVector_Insert(&Vec1,1,99);
  xVector_Insert(&Vec2,1,99);

  //Update
  xVector_Update(&Vec1,0,100);
  xVector_Update(&Vec2,0,100);

  //Remove
  xVector_Remove(&Vec1,3);
  xVector_Remove(&Vec2,3);

  //Math
  xVector_Scale(&Vec1,2);

  int Sum = xVector_Sum(&Vec1);
  DBL Avg = xVector_Average(&Vec1);
  int Max = xVector_FindMax(&Vec1);
  int Min = xVector_FindMin(&Vec1);

  //Utils
  xVector_Reverse(&Vec2);
  xVector_Merge(&Vec1,&Vec2);
  xVector_Clear(&Vec2);

  //Destroy
  xVector_Destroy(&Vec1);
  xVector_Destroy(&Vec2);
  return 0;
}
```

#### [範例二]
1. 演示使用 `xVector` 宏函數應用於不同型態的使用
2. 演示使用宏函數處理 `int   ` 宣告
3. 演示使用宏函數處理 `double` 宣告
3. 演示使用宏函數處理 `char  ` 宣告
4. 演示使用宏函數處理 `char* ` 宣告
5. 演示使用宏函數處理 `struct ` 宣告
6. 演示使用宏函數處理 `char*` 用`深複製`與`淺複製`的差異
7. 
```c
XVEC_STRUCT(int  ,INT);
XVEC_IMPL(int ,INT);

//Main Code
int main(void)
{
  TEST_INT_VECTOR();    //TEST Integer   Vector
  TEST_DBL_VECTOR();    //TEST Double    Vector
  TEST_CHAR_VECTOR();   //TEST Character Vector
  TEST_STR_VECTOR();    //TEST String    Vector
  TEST_STU_VECTOR();    //TEST Struct    Vector
  
  //Demo Copy
  Demo_Copy();          //Deep Copy vs Shallow Copy
  return 0;
}

///@Function: TEST_INT_VECTOR
///@Descript: Test Integer Vector
static void TEST_INT_VECTOR(void)
{
  xVec_INT V1;
  xVec_INT V2;

  xVec_INT_Init(&V1,5);
  xVec_INT_Init(&V2,5);
  for(int i=0;i<5;i++)
  {
    xVec_INT_Push(&V1,i);
    xVec_INT_Push(&V2,5-i);
  }
  Show_INT_Result("PUSH",&V1,&V2);

  xVec_INT_Pop(&V1);
  xVec_INT_Pop(&V2);
  Show_INT_Result("POP",&V1,&V2);

  printf("[AT]\n");
  printf("V1[2] = %d\n"  ,xVec_INT_At(&V1,2));
  printf("V2[2] = %d\n\n",xVec_INT_At(&V2,2));

  xVec_INT_Insert(&V1,3,10);
  xVec_INT_Insert(&V2,3,10);
  Show_INT_Result("INSERT",&V1,&V2);

  xVec_INT_Remove(&V1,4);
  xVec_INT_Remove(&V2,4);
  Show_INT_Result("REMOVE",&V1,&V2);

  xVec_INT_Update(&V1,2,10);
  xVec_INT_Update(&V2,2,10);
  Show_INT_Result("UPDATE",&V1,&V2);

  xVec_INT_Reverse(&V1);    Show_INT_Result("REVERSE",&V1,&V2);
  xVec_INT_Merge(&V1,&V2);  Show_INT_Result("MERGE",&V1,&V2);

  xVec_INT_Clear(&V2);
  xVec_INT_Push(&V1,100);
  Show_INT_Result("CLEAR",&V1,&V2);

  xVec_INT_Destroy(&V1);
  xVec_INT_Destroy(&V2);
}

```

## 授權條款
本專案採用 `MIT License` 授權使用
