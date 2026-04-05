#ifndef __XDUFF_H__ //__XDUFF_H__
#define __XDUFF_H__ //__XDUFF_H__

//Author  : William Hsiao
//Descript: Duff's Device-based High-Performance Computing and Coroutine Library
//Version : 1.0.0

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Struct Declare]
//Duff Coro
typedef struct _xDuff_Coro
{
  int State;    //Coroutine State
  int Done;     //Coroutine Done
} xDuff_Coro;


//Duff Mutex
typedef struct _xDuff_Locker
{
  int Locked;   //0:UnLock  / 1:Lock
} xDuff_Locker;


//Duff Semaphore
typedef struct _xDuff_Sem
{
  int Count;    //Semaphore
} xDuff_Sem;

#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Memory
void xDuff_MemCopy(void *Dst,const void *Src ,int n);
void xDuff_MemSet (void *Dst,int  Value,int n);
int  xDuff_MemCmp (const void *ptr1,const void *ptr2,int n);

//Matrix
void xDuff_MatAdd(DBL *A,DBL *B,DBL *C,int n);
void xDuff_MatSub(DBL *A,DBL *B,DBL *C,int n);
void xDuff_MatMul(DBL *A,DBL *B,DBL *C,int M,int N,int K);
DBL  xDuff_MatDot(DBL *A,DBL *B,int n);
void xDuff_MatScale(DBL *A,DBL Factor,int n);
void xDuff_MatTPose(DBL *A,int n);
#ifdef __cplusplus
}
#endif
//[Macro Function Declare]
//Memory
#define xDUFF_STRCPY(DST,SRC,N)       xDuff_MemCopy(DST,SRC,N)
#define xDUFF_STRSET(DST,V,N)         xDuff_MemSet (DST,V,N)
#define xDUFF_STRCMP(P1,P2,N)         xDuff_MemCmp (P1,P2,N)

//Matrix
#define xDUFF_MAT_ADD(A,B,C,N)        xDuff_MatAdd(A,B,C,N)
#define xDUFF_MAT_SUB(A,B,C,N)        xDuff_MatSub(A,B,C,N)
#define xDUFF_MAT_MUL(A,B,C,M,N,K)    xDuff_MatMul(A,B,C,M,N,K)
#define xDUFF_MAT_DOT(A,B,N)          xDuff_MatDot(A,B,N)
#define xDUFF_MAT_SCALE(A,FACTOR,N)   xDuff_MatScale(A,FACTOR,N)
#define xDUFF_MAT_TPOSE(A,N)          xDuff_MatTPose(A,N)

//Calculate
#define xDUFF_ITER(COUNT,ACTION)            \
do                                          \
{                                           \
  int _n = ((COUNT)+7)>>3;                  \
  switch((COUNT)%8)                         \
  {                                         \
    case 0: do { ACTION; /* Fallthrough */  \
    case 7:      ACTION; /* Fallthrough */  \
    case 6:      ACTION; /* Fallthrough */  \
    case 5:      ACTION; /* Fallthrough */  \
    case 4:      ACTION; /* Fallthrough */  \
    case 3:      ACTION; /* Fallthrough */  \
    case 2:      ACTION; /* Fallthrough */  \
    case 1:      ACTION; /* Fallthrough */  \
               } while(--_n>0);             \
  }                                         \
} while(0)

#define xDUFF_ADD(ARY,VAL,CNT)        xDUFF_ITER(CNT,(*(ARY)++ += (VAL)))
#define xDUFF_SUB(ARY,VAL,CNT)        xDUFF_ITER(CNT,(*(ARY)++ -= (VAL)))
#define xDUFF_MUL(ARY,VAL,CNT)        xDUFF_ITER(CNT,(*(ARY)++ *= (VAL)))
#define xDUFF_DIV(ARY,VAL,CNT)        xDUFF_ITER(CNT,(*(ARY)++ /= (VAL)))
#define xDUFF_MOD(ARY,VAL,CNT)        xDUFF_ITER(CNT,(*(ARY)++ %= (VAL)))
#define xDUFF_OR(ARY,VAL,CNT)         xDUFF_ITER(CNT,(*(ARY)++ |= (VAL)))
#define xDUFF_AND(ARY,VAL,CNT)        xDUFF_ITER(CNT,(*(ARY)++ &= (VAL)))
#define xDUFF_XOR(ARY,VAL,CNT)        xDUFF_ITER(CNT,(*(ARY)++ ^= (VAL)))
#define xDUFF_NOT(ARY,CNT)            xDUFF_ITER(CNT,(*(ARY) = ~(*(ARY)),(ARY)++))
#define xDUFF_ADD_SUM(ARY,RET,CNT)    xDUFF_ITER(CNT,((RET) += *(ARY)++))
#define xDUFF_XOR_SUM(ARY,RET,CNT)    xDUFF_ITER(CNT,((RET) ^= *(ARY)++))

//Coroutine
//Coro Start
#define xDUFF_CORO_BEGIN(C)                         \
  switch((C)->State)  { case 0:


//Coro Yield
#define xDUFF_CORO_YIELD(C,Value)                   \
do                                                  \
{                                                   \
  (C)->State = __LINE__;                            \
  return (Value);                                   \
  case __LINE__:;                                   \
} while (0)


//Coro End
#define xDUFF_CORO_END(C)                           \
  (C)->Done  = 1;                                   \
  (C)->State = 0;                                   \
}


//Coro Reset
#define xDUFF_CORO_RESET(C)                         \
do                                                  \
{                                                   \
  (C)->State = 0;                                   \
  (C)->Done  = 0;                                   \
} while(0)


//Mutex Lock
#define xDUFF_CORO_MUTEX_LOCK(C,MTX)                \
do                                                  \
{                                                   \
  if((MTX)->Locked)                                 \
    return 0;                                       \
  (MTX)->Locked = 1;                                \
  (C)->State = __LINE__; /* Fallthrough */          \
  case __LINE__:;                                   \
} while(0)


//Mutex UnLock              
#define xDUFF_CORO_MUTEX_UNLOCK(MTX)                \
do                                                  \
{                                                   \
  (MTX)->Locked = 0;                                \
} while(0)


//Semaphore Wait              
#define xDUFF_CORO_SEM_WAIT(C,SEM)                  \
do                                                  \
{                                                   \
  (C)->State = __LINE__; /* Fallthrough */          \
  case __LINE__:                                    \
    if((SEM)->Count <= 0)                           \
      return 0;                                     \
    (SEM)->Count--;                                 \
} while(0)


//Semaphore Signal              
#define xDUFF_CORO_SEM_SIGNAL(SEM)                  \
do                                                  \
{                                                   \
  (SEM)->Count++;                                   \
} while(0)


//Wait Until
#define xDUFF_CORO_WAIT_UNTIL(C,COND)               \
do                                                  \
{                                                   \
  (C)->State = __LINE__; /* Fallthrough */          \
  case __LINE__:                                    \
    if(!(COND))                                     \
      return 0;                                     \
} while(0)


//Delay
#define xDUFF_CORO_DELAY(C,TICK,DELAY)              \
do                                                  \
{                                                   \
  (C)->State = __LINE__; /* Fallthrough */          \
  case __LINE__:                                    \
    if((TICK++)<(DELAY))                            \
      return 0;                                     \
    TICK = 0;                                       \
} while(0)


//Every
#define xDUFF_CORO_EVERY(TICK,DELAY,ACTION)         \
do                                                  \
{                                                   \
  if((TICK++) >= (DELAY))                           \
  {                                                 \
    ACTION;                                         \
    (TICK) = 0;                                     \
  }                                                 \
} while(0)

#endif  //__XDUFF_H__
