//[xLib Include]
#include "xDuff.h"

//Author  : William Hsiao
//Descript: Duff's Device-based High-Performance Computing and Coroutine Library
//Version : 1.0.0

///@Function: xDuff_MemCopy
///@Descript: Memory Copy for Duff's Device Data Copy
void xDuff_MemCopy(void *Dst,const void *Src,int n)
{
  if(n <= 0)
    return;
#if 0   //Basic
  int Count = (n+7)>>3;       //(N+7)/8
  switch(n%8)
  {
    case 0: do {  *Dst++ = *Src++;    //Fallthrough
    case 7:       *Dst++ = *Src++;    //Fallthrough
    case 6:       *Dst++ = *Src++;    //Fallthrough
    case 5:       *Dst++ = *Src++;    //Fallthrough
    case 4:       *Dst++ = *Src++;    //Fallthrough
    case 3:       *Dst++ = *Src++;    //Fallthrough
    case 2:       *Dst++ = *Src++;    //Fallthrough
    case 1:       *Dst++ = *Src++;    //Fallthrough
              } while(--Count>0);
  }
#else
  int Words = n >> 3;    //n / 8
  int Rem   = n & 7;     //n % 8 (Remain)

  U32 *D32 = (U32 *)Dst;
  U32 *S32 = (U32 *)Src;
  if(Words > 0)
  {
    int Count = (Words + 7) >> 3;
    switch (Words % 8)
    {
      case 0: do { *D32++ = *S32++;    //Fallthrough
      case 7:      *D32++ = *S32++;    //Fallthrough
      case 6:      *D32++ = *S32++;    //Fallthrough
      case 5:      *D32++ = *S32++;    //Fallthrough
      case 4:      *D32++ = *S32++;    //Fallthrough
      case 3:      *D32++ = *S32++;    //Fallthrough
      case 2:      *D32++ = *S32++;    //Fallthrough
      case 1:      *D32++ = *S32++;    //Fallthrough
                 } while (--Count > 0);
    }
  }
  //Remain
  U8 *D8 = (U8 *)D32;
  U8 *S8 = (U8 *)S32;
  while(Rem--)
    *D8++ = *S8++;
#endif
}

///@Function: xDuff_MemSet
///@Descript: Memory Set for Duff's Device Data Set
void xDuff_MemSet(void *Dst,int Value,int n)
{
  if(n <= 0)
    return;
#if 0   //Basic
  int Count = (n+7)>>3;       //(N+7)/8
  switch(n%8)
  {
    case 0: do {  *Dst++ = Value;     //Fallthrough
    case 7:       *Dst++ = Value;     //Fallthrough
    case 6:       *Dst++ = Value;     //Fallthrough
    case 5:       *Dst++ = Value;     //Fallthrough
    case 4:       *Dst++ = Value;     //Fallthrough
    case 3:       *Dst++ = Value;     //Fallthrough
    case 2:       *Dst++ = Value;     //Fallthrough
    case 1:       *Dst++ = Value;     //Fallthrough
              } while(--Count>0);
  }
#else
  U32 V32 = Value;
  V32 |= (V32 << 8);
  V32 |= (V32 << 16);

  U32 *p32 = (U32 *)Dst;
  int Words = n >> 3;
  int Rem   = n & 7;
  if(Words > 0)
  {
    int Count = (Words + 7) >> 3;
    switch (Words % 8)
    {
      case 0: do {  *p32++ = V32;     //Fallthrough
      case 7:       *p32++ = V32;     //Fallthrough
      case 6:       *p32++ = V32;     //Fallthrough
      case 5:       *p32++ = V32;     //Fallthrough
      case 4:       *p32++ = V32;     //Fallthrough
      case 3:       *p32++ = V32;     //Fallthrough
      case 2:       *p32++ = V32;     //Fallthrough
      case 1:       *p32++ = V32;     //Fallthrough
                  } while(--Count > 0);
    }
  }
  //Remain
  U8 *p8 = (U8 *)p32;
  while(Rem--)
    *p8++ = Value;
#endif
}


///@Function: xDuff_MemCmp
///@Descript: Memory Compare with Duff's Device Data Compare
int xDuff_MemCmp(const void *ptr1,const void *ptr2,int n)
{
  if(n <= 0)
    return 0;
#if 0   //Basic
  const U8 *p1 = (const U8 *)ptr1;
  const U8 *p2 = (const U8 *)ptr2;
  int Diff  = 0;
  int Count = (n+7)>>3;       //(N+7)/8
  switch(n % 8)
  {
    case 0: do {  if((Diff = *p1++ - *p2++) != 0) return Diff;    //Fallthrough
    case 7:       if((Diff = *p1++ - *p2++) != 0) return Diff;    //Fallthrough
    case 6:       if((Diff = *p1++ - *p2++) != 0) return Diff;    //Fallthrough
    case 5:       if((Diff = *p1++ - *p2++) != 0) return Diff;    //Fallthrough
    case 4:       if((Diff = *p1++ - *p2++) != 0) return Diff;    //Fallthrough
    case 3:       if((Diff = *p1++ - *p2++) != 0) return Diff;    //Fallthrough
    case 2:       if((Diff = *p1++ - *p2++) != 0) return Diff;    //Fallthrough
    case 1:       if((Diff = *p1++ - *p2++) != 0) return Diff;    //Fallthrough
               } while(--Count > 0);
  }
  return 0;
#else
  const U32 *p1_32 = (const U32 *)ptr1;
  const U32 *p2_32 = (const U32 *)ptr2;

  int Words = n >> 3;   //n / 8
  int Rem   = n & 7;    //n % 8
  if(Words > 0)
  {
    int Count = (Words + 7) >> 3;
    switch (Words % 8)
    {
      case 0: do {  if(*p1_32 != *p2_32)  goto _FIND_DIFF;  p1_32++;  p2_32++;  //Fallthrough
      case 7:       if(*p1_32 != *p2_32)  goto _FIND_DIFF;  p1_32++;  p2_32++;  //Fallthrough
      case 6:       if(*p1_32 != *p2_32)  goto _FIND_DIFF;  p1_32++;  p2_32++;  //Fallthrough
      case 5:       if(*p1_32 != *p2_32)  goto _FIND_DIFF;  p1_32++;  p2_32++;  //Fallthrough
      case 4:       if(*p1_32 != *p2_32)  goto _FIND_DIFF;  p1_32++;  p2_32++;  //Fallthrough
      case 3:       if(*p1_32 != *p2_32)  goto _FIND_DIFF;  p1_32++;  p2_32++;  //Fallthrough
      case 2:       if(*p1_32 != *p2_32)  goto _FIND_DIFF;  p1_32++;  p2_32++;  //Fallthrough
      case 1:       if(*p1_32 != *p2_32)  goto _FIND_DIFF;  p1_32++;  p2_32++;  //Fallthrough
                 } while (--Count > 0);
    }
  }

  const U8 *s1 = (const U8 *)p1_32;
  const U8 *s2 = (const U8 *)p2_32;
  int Diff;
  switch(Rem)
  {
    case 3: if((Diff = *s1++ - *s2++) != 0) return Diff;  //Fallthrough
    case 2: if((Diff = *s1++ - *s2++) != 0) return Diff;  //Fallthrough
    case 1: if((Diff = *s1++ - *s2++) != 0) return Diff;  //Fallthrough
  }
  return 0;

_FIND_DIFF:
  const U8 *b1 = (const U8 *)p1_32;
  const U8 *b2 = (const U8 *)p2_32;
  for(int i=0;i<3;i++)
    if(b1[0] != b2[0])
      return (int)b1[0] - (int)b2[0];
  return (int)b1[3] - (int)b2[3];
#endif
}



///@Function: xDuff_MatAdd
///@Descript: Matrix Addition (C = A + B) Using Duff' Device
void xDuff_MatAdd(DBL *A,DBL *B,DBL *C,int n)
{
  if(n<=0)
    return;  
  DBL *pA = A;
  DBL *pB = B;
  DBL *pC = C;
  int Count = (n+7)>>3;     //(N+7)/8
  switch(n%8)
  {
    case 0: do {  *pC++ = *pA++ + *pB++;  //Fallthrough
    case 7:       *pC++ = *pA++ + *pB++;  //Fallthrough
    case 6:       *pC++ = *pA++ + *pB++;  //Fallthrough
    case 5:       *pC++ = *pA++ + *pB++;  //Fallthrough
    case 4:       *pC++ = *pA++ + *pB++;  //Fallthrough
    case 3:       *pC++ = *pA++ + *pB++;  //Fallthrough
    case 2:       *pC++ = *pA++ + *pB++;  //Fallthrough
    case 1:       *pC++ = *pA++ + *pB++;  //Fallthrough
               } while(--Count > 0);
  }
}


///@Function: xDuff_MatSub
///@Descript: Matrix Subtraction (C = A - B) Using Duff's Device
void xDuff_MatSub(DBL *A,DBL *B,DBL *C,int n)
{
  if(n<=0)
    return;
  
  DBL *pA = A;
  DBL *pB = B;
  DBL *pC = C;
  int Count = (n+7)>>3;     //(N+7)/8
  switch(n%8)
  {
    case 0: do {  *pC++ = *pA++ - *pB++;  //Fallthrough
    case 7:       *pC++ = *pA++ - *pB++;  //Fallthrough
    case 6:       *pC++ = *pA++ - *pB++;  //Fallthrough
    case 5:       *pC++ = *pA++ - *pB++;  //Fallthrough
    case 4:       *pC++ = *pA++ - *pB++;  //Fallthrough
    case 3:       *pC++ = *pA++ - *pB++;  //Fallthrough
    case 2:       *pC++ = *pA++ - *pB++;  //Fallthrough
    case 1:       *pC++ = *pA++ - *pB++;  //Fallthrough
               } while(--Count > 0);
  }
}


///@Function: xDuff_MatMul
///@Descript: Matrix Multiplication (C = A * B) Using Duff's Device
void xDuff_MatMul(DBL *A,DBL *B,DBL *C,int M,int N,int K)
{
  if(M<=0 || N<=0 || K<=0)
    return;

  for(int i = 0;i < M;i++)
    for(int k = 0;k < K;k++)
    {
      DBL AVal = A[i * K + k];
      DBL *pB = &B[k * N];
      DBL *pC = &C[i * N];
            
      int Count = (N + 7) >> 3;
      switch(N % 8)
      {
        case 0: do { *pC++ += AVal * (*pB++);    //Fallthrough
        case 7:      *pC++ += AVal * (*pB++);    //Fallthrough
        case 6:      *pC++ += AVal * (*pB++);    //Fallthrough
        case 5:      *pC++ += AVal * (*pB++);    //Fallthrough
        case 4:      *pC++ += AVal * (*pB++);    //Fallthrough
        case 3:      *pC++ += AVal * (*pB++);    //Fallthrough
        case 2:      *pC++ += AVal * (*pB++);    //Fallthrough
        case 1:      *pC++ += AVal * (*pB++);    //Fallthrough
                   } while(--Count>0);
      }
    }
}


///@Function: xDuff_MatDot
///@Descript: Vector Dot Product (C = Sum(A*B)) Using Duff's Device
DBL xDuff_MatDot(DBL *A,DBL *B,int n)
{
  DBL Sum = 0;
  if(n <= 0)
    return 0;
  
  int Count = (n+7)>>3;
  switch(n%8)
  {
    case 0: do { Sum += (*A++)*(*B++);    //Fallthrough
    case 7:      Sum += (*A++)*(*B++);    //Fallthrough
    case 6:      Sum += (*A++)*(*B++);    //Fallthrough
    case 5:      Sum += (*A++)*(*B++);    //Fallthrough
    case 4:      Sum += (*A++)*(*B++);    //Fallthrough
    case 3:      Sum += (*A++)*(*B++);    //Fallthrough
    case 2:      Sum += (*A++)*(*B++);    //Fallthrough
    case 1:      Sum += (*A++)*(*B++);    //Fallthrough
               } while(--Count > 0);
  }
  return Sum;
}


///@Function: xDuff_MatScale
///@Descript: Matrix Scalar Multiplication (A = A * Factor) Using Duff's Device
void xDuff_MatScale(DBL *A,DBL Factor,int n)
{
  if(n <= 0)
    return;

  int Count = (n+7)>>3;
  switch(n%8)
  {
    case 0: do { *A++ *= Factor;          //Fallthrough
    case 7:      *A++ *= Factor;          //Fallthrough
    case 6:      *A++ *= Factor;          //Fallthrough
    case 5:      *A++ *= Factor;          //Fallthrough
    case 4:      *A++ *= Factor;          //Fallthrough
    case 3:      *A++ *= Factor;          //Fallthrough
    case 2:      *A++ *= Factor;          //Fallthrough
    case 1:      *A++ *= Factor;          //Fallthrough
               } while(--Count > 0);
  }
}


///@Function: xDuff_MatTPose
///@Descript: Matrix Transpose (A = A^T) Using Duff' Device
void xDuff_MatTPose(DBL *A,int n)
{
  if(n<=1)
    return;

  for(int i=0;i<n-1;i++)
  {
    DBL *pRow = &A[i*n+(i+1)];
    DBL *pCol = &A[(i+1)*n+i];
    int Count = n-1-i;
    int Dist  = (Count + 7)>>3;

    switch(Count%8)
    {
      case 0: do {  SAFE_SWAP(DBL,*pRow,*pCol); pRow++; pCol+=n;  //Fallthrough
      case 7:       SAFE_SWAP(DBL,*pRow,*pCol); pRow++; pCol+=n;  //Fallthrough
      case 6:       SAFE_SWAP(DBL,*pRow,*pCol); pRow++; pCol+=n;  //Fallthrough
      case 5:       SAFE_SWAP(DBL,*pRow,*pCol); pRow++; pCol+=n;  //Fallthrough
      case 4:       SAFE_SWAP(DBL,*pRow,*pCol); pRow++; pCol+=n;  //Fallthrough
      case 3:       SAFE_SWAP(DBL,*pRow,*pCol); pRow++; pCol+=n;  //Fallthrough
      case 2:       SAFE_SWAP(DBL,*pRow,*pCol); pRow++; pCol+=n;  //Fallthrough
      case 1:       SAFE_SWAP(DBL,*pRow,*pCol); pRow++; pCol+=n;  //Fallthrough
                 } while(--Dist>0);
    }
  }
}