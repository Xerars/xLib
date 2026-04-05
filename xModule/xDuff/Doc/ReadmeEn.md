# xDuff

> **Project** : xDuff
> **Author**  : William Hsiao
> **Descript**: High-performance computing and lightweight coroutine library based on Duff devices

## Introduction
xDuff is a tool library developed using the classic Duff device syntax of the C language.
It provides two core functionalities:
* Extreme computational optimization: Significantly improves the execution efficiency of memory operations and matrix operations through loop unrolling technology.
* Lightweight coroutines: Provides stack-free concurrency control, supports synchronization mechanisms such as mutexes and semaphores, and is suitable for resource-constrained embedded systems.

## Features
1. C/C++ compatible
2. Supports C99
3. High-performance utilization of Duff devices to reduce jump overhead
4. Covers memory control, matrix operations, coroutines, and synchronization locks

## API
#### [Type Definitions]
1. `xDuff_Coro`: Coroutine Controller
2. `xDuff_Locker`: Mutex
3. `xDuff_Sem`: Semaphore

#### [Core Functions]
Memory Control
1. `xDuff_MemCopy` : Copy data from the source address to the target address.
2. `xDuff_MemSet ` : Fill the entire specified range of memory with the same value.
3. `xDuff_MemCmp ` : Compare the contents of the two memory blocks to ensure they are identical.

Matrix calculation
1. `xDuff_MatAdd  `: Add corresponding elements of two matrices of the same dimension ($A_{ij} + B_{ij}$)
2. `xDuff_MatSub  `: Subtract corresponding elements of two matrices of the same dimension ($A_{ij} - B_{ij}$)
3. `xDuff_MatMul  `: Standard linear algebra multiplication
4. `xDuff_MatDot  `: Calculate $\sum (a_i \times b_i)$
5. `xDuff_MatScale`: Multiply each element of the matrix by the same constant $k$ ($k \times A_{ij}$)
6. `xDuff_MatTPose`: Interchange the columns and rows of the matrix ($A_{ij} \rightarrow A_{ji}$)

#### [Core Macro Functions - Operations]
1. `xDUFF_STRCPY    `: Copy the first N elements of SRC to DST.
2. `xDUFF_STRSET    `: Set the first N elements of DST to the same value V.
3. `xDUFF_STRCMP    `: Compare the first N bytes of the two memory blocks to see if they are consistent.

1. `xDUFF_MAT_ADD   `: Element-wise addition of matrices
2. `xDUFF_MAT_SUB   `: Element-wise subtraction of matrices
3. `xDUFF_MAT_MUL   `: Standard matrix multiplication: $C_{M \times K} = A_{M \times N} \times B_{N \times K}$
4. `xDUFF_MAT_DOT   `: Vector dot product
5. `xDUFF_MAT_SCALE `: Scaling operation
6. `xDUFF_MAT_TPOSE `: Matrix transpose

1. `xDUFF_ITER      `: Core Iterator
2. `xDUFF_ADD       `: Adds each element of the array to the scalar
3. `xDUFF_SUB       `: Subtracts each element of the array from the scalar
4. `xDUFF_MUL       `: Multiplys each element of the array to the scalar
5. `xDUFF_DIV       `: Divides each element of the array to the scalar
6. `xDUFF_MOD       `: Calculates the remainder of each element of the array to the scalar
7. `xDUFF_OR        `: ORs each element of the array to the scalar
8. `xDUFF_AND       `: ANDs each element of the array to the scalar
9. `xDUFF_XOR       `: Performs a mutually exclusive OR operation on each element of the array to the scalar
10. `xDUFF_NOT      `: Performs a NOT operation on each element of the array to the scalar
11. `xDUFF_ADD_SUM  `: Adds a checksum to each element of the array to the scalar
12. `xDUFF_XOR_SUM  `: Performs a mutually exclusive OR operation on each element of the array to the scalar

#### [Core Macro Functions - Coroutines]
1. `xDUFF_CORO_BEGIN       `: Mark the start of the coroutine function.
2. `xDUFF_CORO_YIELD       `: Pause the current progress and resume from here on the next call.
3. `xDUFF_CORO_END         `: Mark the end of the coroutine.
4. `xDUFF_CORO_RESET       `: Reset the coroutine's state machine counter.
5. `xDUFF_CORO_MUTEX_LOCK  `: Lock the mutex at the coroutine level.
6. `xDUFF_CORO_MUTEX_UNLOCK`: Unlock the mutex at the coroutine level.
7. `xDUFF_CORO_SEM_WAIT    `: Wait on the coroutine semaphore.
8. `xDUFF_CORO_SEM_SIGNAL  `: Signal the coroutine semaphore.
9. `xDUFF_CORO_WAIT_UNTIL  `: Block and wait until the condition is met.
10. `xDUFF_CORO_DELAY      `: Pause the coroutine for a specified time.
11. `xDUFF_CORO_EVERY      `: Periodically execute the task.

## Library Information
1. xDuff library size: 3.853KB
```c
xDuff_MatAdd      // Occupies 308 Bytes
xDuff_MatDot      // Occupies 344 Bytes
xDuff_MatMul      // Occupies 795 Bytes
xDuff_MatScale    // Occupies 205 Bytes
xDuff_MatSub      // Occupies 308 Bytes
xDuff_MatTPose    // Occupies 313 Bytes
xDuff_MemCmp      // Occupies 285 Bytes
xDuff_MemCopy     // Occupies 427 Bytes
xDuff_MemSet      // Occupies 205 Bytes
```

## Compilation Dependencies
##### [Header Dependencies]
1. `xMeta.h`
2. `xType.h`

##### [Compilation]
Use the command `make all` in the `xDuff` folder

```shell
make all

```
## Example
Use the command `make all` in the `Sample` folder

```shell
make all
```

#### [Example 1]
1. Demonstrates the memory control functionality using `xDLoad`
2. Includes computational efficiency calculations and a comparison with `memcpy`, `memset`, and `memcmp`.

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

##### Example-1 Function Efficiency
In the case of `O3`
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
Based on experiments, the execution efficiency comparison under `O3` conditions is as follows:
1. Memory copying   : `xDuff >> ForLoop >> SIMD   > memcpy`
2. Memory setting   : `xDuff >> SIMD    >  memset > ForLoop`
3. Memory comparison: `xDuff >> SIMD    >  memcmp >> ForLoop`

Under `O0` conditions
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
Based on experiments, the execution efficiency comparison under the `00` condition is as follows:
1. Memory copying   : `xDuff >> memcpy >> ForLoop > SIMD`
2. Memory setting   : `xDuff >> SIMD   > memset   > ForLoop`
3. Memory comparison: `xDuff >> memcmp >> SIMD    > ForLoop`

#### [Example 2]
1. Demonstration of using `xDuff` for high-performance matrix operations
2. Demonstration includes matrix addition, subtraction, multiplication, dot product, scaling, and transpose functions.

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
#### Example-2 Function Efficiency
In the case of `O3`
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

According to experiments, under `O3` optimization, the execution efficiency comparison is as follows:
1. Matrix Addition      : `xDuff > STD   > SIMD  (Almost no difference)`
2. Matrix Subtraction   : `STD   > SIMD  > xDuff (Almost no difference)`
3. Matrix Multiplication: `SIMD  > xDuff > STD`
4. Matrix Dot Product   : `SIMD  > xDuff > STD   (Small differences)`
5. Matrix Scaling:      : `SIMD  > xDuff > STD   (Small differences)`
6. Matrix Transposition : `SIMD  > xDuff > STD   (Small differences)`


In the case of `O0`
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
According to experiments, under `O0` optimization, the execution efficiency comparison is as follows:
1. Matrix Addition      : `xDuff > SIMD > STD`
2. Matrix Subtraction   : `xDuff > SIMD > STD`
3. Matrix Multiplication: `xDuff > SIMD > STD`
4. Matrix Dot Product   : `xDuff > SIMD > STD`
5. Matrix Scaling:      : `xDuff > SIMD > STD`
6. Matrix Transposition : `xDuff > SIMD > STD`

#### [Sample-3]
1. Demonstrates how to quickly perform batch arithmetic and checksum calculations on an array.

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

#### [Sample-4]
1.Demonstrates how to simulate multiple concurrent tasks (such as LED blinking and parking management) within a single-threaded environment.

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

## License
This project is licensed under the  `MIT` License.