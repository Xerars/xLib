#ifndef __XVECTOR_H__ //__XVECTOR_H__
#define __XVECTOR_H__ //__XVECTOR_H__

//Author  : William Hsiao
//Descript: Macro-Based Type-Safe Dynamic Array (Vector) Library
//Version : 1.0.5

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
//Struct Type
#define XVEC_STRUCT(TYPE,NAME)    \
typedef struct _xVec_##NAME       \
{                                 \
  TYPE *Data;                     \
  int   Size;                     \
  int   Capacity;                 \
} xVec_##NAME;

//Prototype Type


//[Struct Declare]
typedef struct _xVector
{
  int *Data;            //Vector Data
  int  Size;            //Vector Size
  int  Capacity;        //Vector Capacity
} xVector;

#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Init
void xVector_Init   (xVector *Vec,int Capacity);
void xVector_Destroy(xVector *Vec);
void xVector_Resize (xVector *Vec,int NewCapacity);

//Data
void xVector_Push   (xVector *Vec,int Value);
void xVector_Pop    (xVector *Vec);
int  xVector_At     (xVector *Vec,int Idx);
void xVector_Insert (xVector *Vec,int Idx,int Value);
void xVector_Remove (xVector *Vec,int Idx);
void xVector_Update (xVector *Vec,int Idx,int Value);

//Utils
void xVector_Clear  (xVector *Vec);
void xVector_Merge  (xVector *Vec1,xVector *Vec2);
void xVector_Reverse(xVector *Vec);

//Math
int  xVector_Sum    (xVector *Vec);
DBL  xVector_Average(xVector *Vec);
void xVector_Scale  (xVector *Vec,int Factor);
int  xVector_FindMax(xVector *Vec);
int  xVector_FindMin(xVector *Vec);
#ifdef __cplusplus
}
#endif
//[Macro Declare]
//Generic
#define XVEC_IMPL(TYPE,NAME)                                                    \
  XVEC_IMPL_INIT(TYPE,NAME)                                                     \
  XVEC_IMPL_DESTROY(NAME)                                                       \
  XVEC_IMPL_RESIZE(TYPE,NAME)                                                   \
  XVEC_IMPL_PUSH(TYPE,NAME)                                                     \
  XVEC_IMPL_POP(NAME)                                                           \
  XVEC_IMPL_AT(TYPE,NAME)                                                       \
  XVEC_IMPL_INSERT(TYPE,NAME)                                                   \
  XVEC_IMPL_REMOVE(NAME)                                                        \
  XVEC_IMPL_UPDATE(TYPE,NAME)                                                   \
  XVEC_IMPL_CLEAR(NAME)                                                         \
  XVEC_IMPL_MERGE(TYPE,NAME)                                                    \
  XVEC_IMPL_REVERSE(TYPE,NAME)

//void xVec_xxxx_Init(xVec_xxxx *Vec,int Capacity)
#define XVEC_IMPL_INIT(TYPE,NAME)                                               \
void xVec_##NAME##_Init(xVec_##NAME *Vec,int Capacity)                          \
{                                                                               \
  Vec->Size     = 0;                                                            \
  Vec->Capacity = Capacity;                                                     \
  Vec->Data     = (TYPE*)malloc(Capacity * sizeof(TYPE));                       \
  if(!Vec->Data)                                                                \
    return;                                                                     \
}

//void xVec_xxxx_Destroy(xVec_xxxx *Vec)
#define XVEC_IMPL_DESTROY(NAME)                                                 \
void xVec_##NAME##_Destroy(xVec_##NAME *Vec)                                    \
{                                                                               \
  if(Vec->Data)                                                                 \
  {                                                                             \
    free(Vec->Data);                                                            \
    Vec->Data = NULL;                                                           \
  }                                                                             \
  Vec->Size     = 0;                                                            \
  Vec->Capacity = 0;                                                            \
}

//void xVec_xxxx_Resize(xVec_xxxx *Vec,int NewCapacity)
#define XVEC_IMPL_RESIZE(TYPE,NAME)                                             \
void xVec_##NAME##_Resize(xVec_##NAME *Vec,int NewCapacity)                     \
{                                                                               \
  TYPE *NewData  = (TYPE*)realloc(Vec->Data,sizeof(TYPE) * NewCapacity);        \
  if(!NewData)                                                                  \
    return;                                                                     \
  Vec->Data     = NewData;                                                      \
  Vec->Capacity = NewCapacity;                                                  \
}

//void xVec_xxxx_Push(xVec_xxxx *Vec,int Value)
#define XVEC_IMPL_PUSH(TYPE,NAME)                                               \
void xVec_##NAME##_Push(xVec_##NAME *Vec,TYPE Value)                            \
{                                                                               \
  if(Vec->Size == Vec->Capacity)                                                \
    xVec_##NAME##_Resize(Vec,Vec->Capacity<<1);                                 \
  Vec->Data[Vec->Size] = Value;                                                 \
  Vec->Size++;                                                                  \
}

//void xVec_xxxx_Pop(xVec_xxxx *Vec)
#define XVEC_IMPL_POP(NAME)                                                     \
void xVec_##NAME##_Pop(xVec_##NAME *Vec)                                        \
{                                                                               \
  if(Vec->Size > 0)                                                             \
    Vec->Size--;                                                                \
}

//int xVec_xxxx_At(xVec_xxxx *Vec,int Idx)
#define XVEC_IMPL_AT(TYPE,NAME)                                                 \
TYPE xVec_##NAME##_At(xVec_##NAME *Vec,int Idx)                                 \
{                                                                               \
  if(Idx >= 0 && Idx < Vec->Size)                                               \
    return Vec->Data[Idx];                                                      \
  /* @@ Static Zero: Solvw Non-Scale Type Request*/                             \
  static TYPE xVec_##NAME##_Zero = {0};                                         \
  return xVec_##NAME##_Zero;                                                    \
}

//void xVec_xxxx_Insert(xVec_xxxx *Vec,int Idx,int Value)
#define XVEC_IMPL_INSERT(TYPE,NAME)                                             \
void xVec_##NAME##_Insert(xVec_##NAME *Vec,int Idx,TYPE Value)                  \
{                                                                               \
  if(Idx < 0 || Idx > Vec->Size)                                                \
    return;                                                                     \
  if(Vec->Size == Vec->Capacity)                                                \
    xVec_##NAME##_Resize(Vec,Vec->Capacity<<1);                                 \
  for(int i=Vec->Size;i>Idx;i--)                                                \
    Vec->Data[i] = Vec->Data[i-1];                                              \
  Vec->Data[Idx] = Value;                                                       \
  Vec->Size++;                                                                  \
}

//void xVec_xxxx_Remove(xVec_xxxx *Vec,int Idx)
#define XVEC_IMPL_REMOVE(NAME)                                                  \
void xVec_##NAME##_Remove(xVec_##NAME *Vec,int Idx)                             \
{                                                                               \
  if(Idx < 0 || Idx >= Vec->Size)                                               \
    return;                                                                     \
  for(int i=Idx;i<Vec->Size-1;i++)                                              \
    Vec->Data[i] = Vec->Data[i+1];                                              \
  Vec->Size--;                                                                  \
}

//void xVec_xxxx_Update(xVec_xxxx *Vec,int Idx,int Value)
#define XVEC_IMPL_UPDATE(TYPE,NAME)                                             \
void xVec_##NAME##_Update(xVec_##NAME *Vec,int Idx,TYPE Value)                  \
{                                                                               \
  if(Idx < 0 || Idx >= Vec->Size)                                               \
    return;                                                                     \
  Vec->Data[Idx] = Value;                                                       \
}

//void xVec_xxxx_Clear(xVec_xxxx *Vec)
#define XVEC_IMPL_CLEAR(NAME)                                                   \
void xVec_##NAME##_Clear(xVec_##NAME *Vec)                                      \
{                                                                               \
  Vec->Size = 0;                                                                \
}

//void xVec_xxxx_Merge(xVec_xxxx *Vec,xVec_xxxx *Vec2)
#define XVEC_IMPL_MERGE(TYPE,NAME)                                              \
void xVec_##NAME##_Merge(xVec_##NAME *Vec1,xVec_##NAME *Vec2)                   \
{                                                                               \
  int NewSize = Vec1->Size + Vec2->Size;                                        \
  Vec1->Data = (TYPE*)realloc(Vec1->Data,NewSize * sizeof(TYPE));               \
  for(int i=0;i<Vec2->Size;i++)                                                 \
    Vec1->Data[Vec1->Size+i] = Vec2->Data[i];                                   \
  Vec1->Size     = NewSize;                                                     \
  Vec1->Capacity = NewSize;                                                     \
}

//void xVec_xxxx_Reverse(xVec_xxxx *Vec)
#define XVEC_IMPL_REVERSE(TYPE,NAME)                                            \
void xVec_##NAME##_Reverse(xVec_##NAME *Vec)                                    \
{                                                                               \
  int Start = 0;                                                                \
  int End   = Vec->Size - 1;                                                    \
  while(Start < End)                                                            \
  {                                                                             \
    TYPE tmp = Vec->Data[Start];                                                \
    Vec->Data[Start] = Vec->Data[End];                                          \
    Vec->Data[End] = tmp;                                                       \
    Start++;                                                                    \
    End--;                                                                      \
  }                                                                             \
}

#endif  //__XVECTOR_H__
