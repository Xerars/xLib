//Demo the xDuff Lib about Memory Copy and Memory Set

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
#define TEST_DATA_SIZE        (1024 * 1024 * 1024)       //1GB

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
static void TEST_STD_Copy (void);
static void TEST_For_Copy (void);
static void TEST_Duff_Copy(void);
static void TEST_SIMD_Copy(void);

static void TEST_STD_Set (void);
static void TEST_For_Set (void);
static void TEST_Duff_Set(void);
static void TEST_SIMD_Set(void);

static void TEST_STD_Cmp(void);
static void TEST_For_Cmp(void);
static void TEST_Duff_Cmp(void);
static void TEST_SIMD_Cmp(void);

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


///@Function: TEST_STD_Copy
///@Descript: Memory Copy for Function Memcpy
static void TEST_STD_Copy(void)
{
  if(gSrc && gDst)
    memcpy(gDst,gSrc,TEST_DATA_SIZE);
}


///@Function: TEST_For_Copy
///@Descript: Memory Copy for For Loop Copy
static void TEST_For_Copy(void)
{
  if(gSrc && gDst)
    for(int long i = 0;i<TEST_DATA_SIZE;i++)
      gDst[i] = gSrc[i];
}


///@Function: TEST_Duff_Copy
///@Descript: Memory Copy for Duff Device Copy
static void TEST_Duff_Copy(void)
{
  if(gSrc && gDst)
    xDuff_MemCopy(gDst,gSrc,TEST_DATA_SIZE);
}


///@Function: TEST_SIMD_Copy
///@Descript: Memory Copy for SIMD Copy
static void TEST_SIMD_Copy(void)
{
  if(gSrc && gDst)
  {
    for(int i=0;(i+32) <= TEST_DATA_SIZE;i+=32)
    {
      __m256i Data = _mm256_loadu_si256((__m256i*)&gSrc[i]);
      _mm256_storeu_si256((__m256i*)&gDst[i],Data);
    }

    for(int i=0;i < TEST_DATA_SIZE;i++)    //Process the Remain Portion Less than 32 Bytes
      gDst[i] = gSrc[i];
  }
}


///@Function: TEST_STD_Set
///@Descript: Memory Set for Function Memset
static void TEST_STD_Set(void)
{
  if(gDst)
    memset(gDst,0x55,TEST_DATA_SIZE);
}


///@Function: TEST_For_Set
///@Descript: Memory Set for For Loop Set
static void TEST_For_Set(void)
{
  if(gDst)
    for(int i=0;i<TEST_DATA_SIZE;i++)
      gDst[i] = 0x55;
}


///@Function: TEST_Duff_Set
///@Descript: Memory Set for Duff Device Set
static void TEST_Duff_Set(void)
{
  if(gDst)
    xDuff_MemSet(gDst,0x55,TEST_DATA_SIZE);
}


///@Function: TEST_SIMD_Set
///@Descript: Memory Set for SIMD Set
static void TEST_SIMD_Set(void)
{
  if(gDst)
  {
    int i  = 0;
    U8 Val = 0x55;
    __m256i Data = _mm256_set1_epi8((char)Val);
    for(;(i+32) <= TEST_DATA_SIZE;i+=32)
      _mm256_storeu_si256((__m256i*)&gDst[i],Data);
    for(;i<TEST_DATA_SIZE;i++)    //Process the Remain Portion Less than 32 Bytes
      gDst[i] = Val;
  }
}


///@Function: TEST_STD_Cmp
///@Descript: Memory Compare for Function memcmp
static void TEST_STD_Cmp(void)
{
  if(gSrc && gDst)
  {
    int Ret = memcmp(gSrc,gDst,TEST_DATA_SIZE);
    printf("Return Value: %d\n",Ret);
  }
}


///@Function: TEST_For_Cmp
///@Descript: Memory Compare for For Loop Compare
static void TEST_For_Cmp(void)
{
  if(gSrc && gDst)
  {
    int Ret = 0;
    for(int i = 0;i<TEST_DATA_SIZE;i++)
      if(gSrc[i] != gDst[i])
      {
        Ret = gSrc[i] - gDst[i];
        break;
      }
    printf("Return Value: %d\n",Ret);
  }
}


///@Function: TEST_Duff_Cmp
///@Descript: Memory Compare for Duff Device Compare
static void TEST_Duff_Cmp(void)
{
  if(gSrc && gDst)
  {
    int Ret = xDuff_MemCmp(gSrc,gDst,TEST_DATA_SIZE);
    printf("Return Value: %d\n",Ret);
  }
}

///@Function: TEST_SIMD_Cmp
///@Descript: Memory Compare for SIMD Compare
static void TEST_SIMD_Cmp(void)
{
  if(gSrc && gDst)
  {
    int Ret = 0;
    int i = 0;

    for(;(i+32) <= TEST_DATA_SIZE;i+=32)
    {
      __m256i V1  = _mm256_loadu_si256((__m256i const*)&gSrc[i]);
      __m256i V2  = _mm256_loadu_si256((__m256i const*)&gDst[i]);
      __m256i Cmp = _mm256_cmpeq_epi8(V1,V2);
      U32    Mask = _mm256_movemask_epi8(Cmp);

      if(Mask != 0xFFFFFFFF)
      {
        for(int j=0;j<32;j++)
          if(gSrc[i+j] != gDst[i+j])
          {
            Ret = gSrc[i] - gDst[i];
            break;
          }
        goto END;
      }
    }

    for(;i<TEST_DATA_SIZE;i++)    //Process the Remain Portion Less than 32 Bytes
      if(gSrc[i] != gDst[i])
      {
        Ret = gSrc[i] - gDst[i];
        break;
      }
END:
    printf("Return Value: %d\n",Ret);
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
