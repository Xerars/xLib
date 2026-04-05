//Demo the xDuff Lib about Matrix Calculate

#ifndef _WIN32
  #define _POSIX_C_SOURCE 199309L
#endif

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
  #include <windows.h>
#endif

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xDuff.h"

//[SIMD Lib Include]
#include <immintrin.h>

//[Macro Declare]
//Large Matrix
#define MATRIX_SIZE       1000
#define MATRIX_LEN        (MATRIX_SIZE * MATRIX_SIZE)

//Small Matrix
#define MATRIX_SSIZE      5
#define MATRIX_SLEN       (MATRIX_SSIZE * MATRIX_SSIZE)

static inline double GetTimeSec(void);
#define PERF_TEST(NAME,BYTES,CODE)                    \
do                                                    \
{                                                     \
  double StartTime = GetTimeSec();                    \
  CODE;                                               \
  double EndTime   = GetTimeSec();                    \
  double Sec  = EndTime - StartTime;                  \
  double MB   = (double)(BYTES)/(1024.0*1024.0);      \
  double Rate = (Sec>0)?(MB/Sec):0;                   \
  printf("[%s]\n",NAME);                              \
  printf("  Time : %.6f sec\n",Sec);                  \
  printf("  Rate : %.2f MB/s\n\n",Rate);              \
} while (0)

//[Prototype Declare]
void Matrix_Init(DBL A,DBL B);
void Show_Result(void);

//Add
void TEST_STD_MatAdd(void);
void TEST_Duff_MatAdd(void);
void TEST_SIMD_MatAdd(void);

//Sub
void TEST_STD_MatSub(void);
void TEST_Duff_MatSub(void);
void TEST_SIMD_MatSub(void);

//Mul
void TEST_STD_MatMul(void);
void TEST_Duff_MatMul(void);
void TEST_SIMD_MatMul(void);

//Dot
void TEST_STD_MatDot(void);
void TEST_Duff_MatDot(void);
void TEST_SIMD_MatDot(void);

//Scale
void TEST_STD_MatScale(void);
void TEST_Duff_MatScale(void);
void TEST_SIMD_MatScale(void);

//TPose
void TEST_STD_MatTPose(void);
void TEST_Duff_MatTPose(void);
void TEST_SIMD_MatTPose(void);


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


///@Function: TEST_STD_MatAdd
///@Descript: TEST Standard Matrix Add
void TEST_STD_MatAdd(void)
{
  for(int i = 0;i < MATRIX_LEN;i++)   MTX_C[i]  = MTX_A[i]  + MTX_B[i];
  for(int i = 0;i < MATRIX_SLEN;i++)  MTX_SC[i] = MTX_SA[i] + MTX_SB[i];
  Show_Result();
}


///@Function: TEST_Duff_MatAdd
///@Descript: TEST Duff's Matrix Add
void TEST_Duff_MatAdd(void)
{
  xDuff_MatAdd(MTX_A,MTX_B,MTX_C,MATRIX_LEN);
  xDuff_MatAdd(MTX_SA,MTX_SB,MTX_SC,MATRIX_SLEN);
  Show_Result();
}


///@Function: TEST_SIMD_MatAdd
///@Descript: TEST SIMD Matrix Add
void TEST_SIMD_MatAdd(void)
{
  int i = 0;
  for(;i <= MATRIX_LEN-4;i += 4)
  {
    __m256d A   = _mm256_loadu_pd(&MTX_A[i]); 
    __m256d B   = _mm256_loadu_pd(&MTX_B[i]);
    __m256d Ret = _mm256_add_pd(A,B);
    _mm256_storeu_pd(&MTX_C[i],Ret); 
  }
  for(;i < MATRIX_LEN;i++)  //Process Remain Data
    MTX_C[i] = MTX_A[i] + MTX_B[i];

  int j = 0;
  for(;j <= MATRIX_SLEN - 4;j += 4)
  {
    __m256d SA   = _mm256_loadu_pd(&MTX_SA[j]);
    __m256d SB   = _mm256_loadu_pd(&MTX_SB[j]);
    __m256d SRet = _mm256_add_pd(SA,SB);
    _mm256_storeu_pd(&MTX_SC[j],SRet);
  }
  for(;j < MATRIX_SLEN;j++) //Process Remain Data
    MTX_SC[j] = MTX_SA[j] + MTX_SB[j];

  Show_Result();
}


///@Function: TEST_STD_MatSub
///@Descript: TEST Standard Matrix Sub
void TEST_STD_MatSub(void)
{
  for(int i = 0;i < MATRIX_LEN;i++)   MTX_C[i]  = MTX_A[i]  - MTX_B[i];
  for(int i = 0;i < MATRIX_SLEN;i++)  MTX_SC[i] = MTX_SA[i] - MTX_SB[i];
  Show_Result();
}


///@Function: TEST_Duff_MatSub
///@Descript: TEST Duff's Device Matrix Sub
void TEST_Duff_MatSub(void)
{
  xDuff_MatSub(MTX_A ,MTX_B ,MTX_C ,MATRIX_LEN);
  xDuff_MatSub(MTX_SA,MTX_SB,MTX_SC,MATRIX_SLEN);
  Show_Result();
}


///@Function: TEST_SIMD_MatSub
///@Descript: TEST SIMD Matrix Sub
void TEST_SIMD_MatSub(void)
{
  int i = 0;
  for(;i <= MATRIX_LEN-4;i += 4)
  {
    __m256d A   = _mm256_loadu_pd(&MTX_A[i]);
    __m256d B   = _mm256_loadu_pd(&MTX_B[i]);
    __m256d Ret = _mm256_sub_pd(A,B);
    _mm256_storeu_pd(&MTX_C[i],Ret);
  }
  for(;i < MATRIX_LEN;i++)  //Process Remain Data
    MTX_C[i] = MTX_A[i] - MTX_B[i];

  int j = 0;
  for(;j <= MATRIX_SLEN - 4;j += 4)
  {
    __m256d SA   = _mm256_loadu_pd(&MTX_SA[j]);
    __m256d SB   = _mm256_loadu_pd(&MTX_SB[j]);
    __m256d SRet = _mm256_sub_pd(SA,SB);
    _mm256_storeu_pd(&MTX_SC[j],SRet);
  }
  for(;j < MATRIX_SLEN;j++) //Process Remain Data
    MTX_SC[j] = MTX_SA[j] - MTX_SB[j];
  Show_Result();
}


///@Function: TEST_STD_MatMul
///@Descript: TEST Standard Matrix Mutiple
void TEST_STD_MatMul(void)
{
  for(int i = 0;i < MATRIX_SIZE;i++)
    for(int j = 0;j < MATRIX_SIZE;j++)
    {
      U32 Sum = 0;
      for(int k = 0;k < MATRIX_SIZE;k++)
        Sum += MTX_A[i * MATRIX_SIZE + k] * MTX_B[k * MATRIX_SIZE + j];       //A[i][k] * B[k][j]
      MTX_C[i * MATRIX_SIZE + j] = Sum;
    }

  for(int i = 0;i < MATRIX_SSIZE;i++)
    for(int j = 0;j < MATRIX_SSIZE;j++)
    {
      U32 Sum = 0;
      for(int k = 0;k < MATRIX_SSIZE;k++)
        Sum += MTX_SA[i * MATRIX_SSIZE + k] * MTX_SB[k * MATRIX_SSIZE + j];   //A[i][k] * B[k][j]
      MTX_SC[i * MATRIX_SSIZE + j] = Sum;
   }
  Show_Result();
}


///@Function: TEST_Duff_MatMul
///@Descript: TEST Duff's Device Matrix Mutiple
void TEST_Duff_MatMul(void)
{
  xDuff_MatMul(MTX_A ,MTX_B ,MTX_C ,MATRIX_SIZE ,MATRIX_SIZE ,MATRIX_SIZE);
  xDuff_MatMul(MTX_SA,MTX_SB,MTX_SC,MATRIX_SSIZE,MATRIX_SSIZE,MATRIX_SSIZE);
  Show_Result();
}


///@Function: TEST_SIMD_MatMul
///@Descript: TEST SIMD Matrix Mutiple
void TEST_SIMD_MatMul(void)
{
  for(int i = 0; i < MATRIX_SIZE; i++)
    for(int k = 0; k < MATRIX_SIZE; k++)
    {
      __m256d AVal = _mm256_set1_pd(MTX_A[i * MATRIX_SIZE + k]);
      for(int j = 0; j <= MATRIX_SIZE - 8; j += 8)
      {
        __m256d BRow   = _mm256_loadu_pd(&MTX_B[k * MATRIX_SIZE + j]);
        __m256d COrg   = _mm256_loadu_pd(&MTX_C[i * MATRIX_SIZE + j]);
        __m256d MulRet = _mm256_mul_pd(AVal, BRow);
        __m256d AddRet = _mm256_add_pd(MulRet, COrg);
        _mm256_storeu_pd(&MTX_C[i * MATRIX_SIZE + j],AddRet);
      }
    }

  for(int i = 0;i < MATRIX_SSIZE;i++)
    for(int k = 0;k < MATRIX_SSIZE;k++)
    {
      U32 AVal = MTX_SA[i * MATRIX_SSIZE + k];
      for(int j = 0;j < MATRIX_SSIZE;j++)
        MTX_SC[i * MATRIX_SSIZE + j] += AVal * MTX_SB[k * MATRIX_SSIZE + j];
    }
  Show_Result();
}


///@Function: TEST_STD_MatDot
///@Descript: TEST Standard Matrix Dot Product
void TEST_STD_MatDot(void)
{
  DBL Sum1 = 0;
  DBL Sum2 = 0;
  for(int i = 0;i < MATRIX_LEN;i++)
    Sum1 += MTX_A[i] * MTX_B[i];
  for(int i = 0;i < MATRIX_SLEN;i++)
    Sum2 += MTX_SA[i] * MTX_SB[i];
  printf("[SUM1]: %3.2f [SUM2]: %3.2f\n",Sum1,Sum2);
}


///@Function: TEST_Duff_MatDot
///@Descript: TEST Duff's Device Matrix Dot Product
void TEST_Duff_MatDot(void)
{
  DBL Sum1 = xDuff_MatDot(MTX_A ,MTX_B ,MATRIX_LEN);
  DBL Sum2 = xDuff_MatDot(MTX_SA,MTX_SB,MATRIX_SLEN);
  printf("[SUM1]: %3.2f [SUM2]: %3.2f\n",Sum1,Sum2);
}


///@Function: TEST_SIMD_MatDot
///@Descript: TEST SIMD Matrix Dot Product
void TEST_SIMD_MatDot(void)
{
  DBL Sum1 = 0;
  DBL Sum2 = 0;
  int i = 0;
  __m256d vSum1 = _mm256_setzero_pd();
  for(;i <= MATRIX_LEN - 4;i += 4)
  {
    __m256d A = _mm256_loadu_pd(&MTX_A[i]);
    __m256d B = _mm256_loadu_pd(&MTX_B[i]);
    vSum1     = _mm256_add_pd(vSum1,_mm256_mul_pd(A,B));
  }
  
  double Tmp1[4];
  _mm256_storeu_pd(Tmp1,vSum1);
  Sum1 = Tmp1[0] + Tmp1[1] + Tmp1[2] + Tmp1[3];

  for(;i < MATRIX_LEN;i++)
    Sum1 += MTX_A[i] * MTX_B[i];

  int j = 0;
  __m256d vSum2 = _mm256_setzero_pd();
  for(;j <= MATRIX_SLEN - 4;j += 4)
  {
    __m256d SA = _mm256_loadu_pd(&MTX_SA[j]);
    __m256d SB = _mm256_loadu_pd(&MTX_SB[j]);
    vSum2 = _mm256_add_pd(vSum2,_mm256_mul_pd(SA,SB));
  }

  double Tmp2[4];
  _mm256_storeu_pd(Tmp2,vSum2);
  Sum2 = Tmp2[0] + Tmp2[1] + Tmp2[2] + Tmp2[3];

  for(;j < MATRIX_SLEN;j++)
    Sum2 += MTX_SA[j] * MTX_SB[j];
  printf("[SUM1]: %3.2f [SUM2]: %3.2f\n",Sum1,Sum2);
}


///@Function: TEST_STD_MatScale
///@Descript: TEST Standard Matrix Scale
void TEST_STD_MatScale(void)
{
  const DBL Factor = 2.0;
  for(int i = 0;i < MATRIX_LEN;i++)     MTX_A[i]  = MTX_A[i]  * Factor;
  for(int i = 0;i < MATRIX_SLEN;i++)    MTX_SA[i] = MTX_SA[i] * Factor;
    
  Show_Result();
}

///@Function: TEST_Duff_MatScale
///@Descript: TEST Duff's Device Matrix Scale
void TEST_Duff_MatScale(void)
{
  const DBL Factor = 2.0;
  xDuff_MatScale(MTX_A ,Factor,MATRIX_LEN);
  xDuff_MatScale(MTX_SA,Factor,MATRIX_SLEN);
  Show_Result();
}


///@Function: TEST_SIMD_MatScale
///@Descript: TEST SIMD Matrix Scale
void TEST_SIMD_MatScale(void)
{
  const DBL Factor = 2.0;  
  __m256d vFac = _mm256_set1_pd(Factor);    
  int i = 0;
  for(;i <= MATRIX_LEN - 4;i += 4)
  {
    __m256d vSrc = _mm256_loadu_pd(&MTX_A[i]);
    __m256d vRet = _mm256_mul_pd(vSrc,vFac);
    _mm256_storeu_pd(&MTX_A[i],vRet);
  }
    
  for(; i < MATRIX_LEN; i++)   //Process Remain Data
    MTX_A[i]  = MTX_A[i] * Factor;
  
  for(int j = 0; j < MATRIX_SLEN; j++)
    MTX_SA[j] = MTX_SA[j] * Factor;
  Show_Result();
}


///@Function: TEST_STD_MatTPose
///@Descript: TEST Standard Matrix T-Pose
void TEST_STD_MatTPose(void)
{
  for(int i = 0;i < MATRIX_SIZE;i++)
    for(int j = 0;j < MATRIX_SIZE;j++)
      MTX_C[j * MATRIX_SIZE + i] = MTX_A[i * MATRIX_SIZE + j];
  for(int i = 0;i < MATRIX_SSIZE;i++)
    for(int j = 0;j < MATRIX_SSIZE;j++)
      MTX_SC[j * MATRIX_SSIZE + i] = MTX_SA[i * MATRIX_SSIZE + j];
  Show_Result();
}


///@Function: TEST_Duff_MatTPose
///@Descript: TEST Duff' Device Matrix T-Pose
void TEST_Duff_MatTPose(void)
{
  xDuff_MatTPose(MTX_A ,MATRIX_SIZE);
  xDuff_MatTPose(MTX_SA,MATRIX_SSIZE);
  Show_Result();
}


///@Function: TEST_SIMD_MatTPose
///@Descript: TEST SIMD Matrix T-Pose
void TEST_SIMD_MatTPose(void)
{
  for(int i = 0;i < MATRIX_SIZE;i += 4)
  {
    for (int j = 0;j < MATRIX_SIZE;j += 4)
    {
      __m256d r0 = _mm256_loadu_pd(&MTX_A[(i+0)*MATRIX_SIZE+j]);
      __m256d r1 = _mm256_loadu_pd(&MTX_A[(i+1)*MATRIX_SIZE+j]);
      __m256d r2 = _mm256_loadu_pd(&MTX_A[(i+2)*MATRIX_SIZE+j]);
      __m256d r3 = _mm256_loadu_pd(&MTX_A[(i+3)*MATRIX_SIZE+j]);

      __m256d t0 = _mm256_unpacklo_pd(r0,r1);
      __m256d t1 = _mm256_unpackhi_pd(r0,r1);
      __m256d t2 = _mm256_unpacklo_pd(r2,r3);
      __m256d t3 = _mm256_unpackhi_pd(r2,r3);

      __m256d res0 = _mm256_permute2f128_pd(t0,t2,0x20);
      __m256d res1 = _mm256_permute2f128_pd(t1,t3,0x20);
      __m256d res2 = _mm256_permute2f128_pd(t0,t2,0x31);
      __m256d res3 = _mm256_permute2f128_pd(t1,t3,0x31);

      _mm256_storeu_pd(&MTX_C[(j+0)*MATRIX_SIZE+i],res0);
      _mm256_storeu_pd(&MTX_C[(j+1)*MATRIX_SIZE+i],res1);
      _mm256_storeu_pd(&MTX_C[(j+2)*MATRIX_SIZE+i],res2);
      _mm256_storeu_pd(&MTX_C[(j+3)*MATRIX_SIZE+i],res3);
    }
  }

  for(int i = 0;i < MATRIX_SSIZE;i++)
    for(int j = 0;j < MATRIX_SSIZE;j++)
      MTX_SA[j * MATRIX_SSIZE + i] = MTX_SA[i * MATRIX_SSIZE + j];
  Show_Result();
}


///@Function: Matrix_Init
///@Descript: Matrix Initial Value
void Matrix_Init(DBL A,DBL B)
{
  for(int i = 0; i < MATRIX_LEN; i++)
  {
    MTX_A[i] = A+i-1;
    MTX_B[i] = B+i-1;
    MTX_C[i] = 0;
  }

  for(int i = 0;i < MATRIX_SLEN;i++)
  {
    MTX_SA[i] = A+i-1;
    MTX_SB[i] = B+i-1;
    MTX_SC[i] = 0;
  }
}

///@Function: Show_Result
///@Descript: Show Matrix Calculate Result
void Show_Result(void)
{
  for(int i=0;i<MATRIX_SSIZE;i++)
  {
    for(int j=0;j<MATRIX_SSIZE;j++)
      printf("[%4.1f] ",MTX_SC[i*MATRIX_SSIZE+j]);
    printf("  ");
    for(int j=0;j<MATRIX_SSIZE;j++)
      printf("[%4.1f] ",MTX_SA[i*MATRIX_SSIZE+j]);
    printf("  ");
    for(int j=0;j<MATRIX_SSIZE;j++)
    printf("[%4.1f] ",MTX_SB[i*MATRIX_SSIZE+j]);
      printf("  ");
    printf("\n");
  } 
}


///@Function: GetTimeSec
///@Descript: Get Time Second (Support Windows/Linux)
static inline double GetTimeSec(void)
{
#ifdef _WIN32
  LARGE_INTEGER freq, counter;
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&counter);
  return (double)counter.QuadPart / freq.QuadPart;
#else
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
#endif
}

