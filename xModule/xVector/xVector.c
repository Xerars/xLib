//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//Author  : William Hsiao
//Descript: Macro-Based Type-Safe Dynamic Array (Vector) Library
//Version : 1.0.4

//[xLib Include]
#include "xVector.h"

///@Function: xVector_Init
///@Descript: Initialize a Vector with a Specified Capacity
void xVector_Init(xVector *Vec,int Capacity)
{
  Vec->Size     = 0;
  Vec->Capacity = Capacity; 
  Vec->Data     = (Capacity>0)?(int*)malloc(Capacity * sizeof(int)):NULL;
}


///@Function: xVector_Destroy
///@Descript: Destroy the Memory for the Vector's Data and Reset Size and Capacity
void xVector_Destroy(xVector *Vec)
{
  SAFE_DESTROY(Vec->Data);
  Vec->Size     = 0;
  Vec->Capacity = 0;
}


///@Function: xVector_Resize
///@Descript: Resize the Vector to a New Capacity
void xVector_Resize(xVector *Vec,int NewCapacity)
{
  int *NewData  = (int*)realloc(Vec->Data,sizeof(int) * NewCapacity);
  if(!NewData)
    return;
  Vec->Data     = NewData;
  Vec->Capacity = NewCapacity;
}


///@Function: xVector_Push
///@Descript: Add a New Value to the End of the Vector
void xVector_Push(xVector *Vec,int Value)
{
  if(Vec->Size == Vec->Capacity)    //Full -> Resize
    xVector_Resize(Vec,Vec->Capacity<<1);    //Size * 2

  //Set Data
  Vec->Data[Vec->Size] = Value;
  Vec->Size++;
}


///@Function: xVector_Pop
///@Descript: Remove the Last Element from the Vector
void xVector_Pop(xVector *Vec)
{
  if(Vec->Size > 0)
    Vec->Size--;
}


///@Function: xVector_At
///@Descript: Return the Element at the Specified Index
int xVector_At(xVector *Vec,int Idx)
{
  if(Idx >= 0 && Idx < Vec->Size)
    return Vec->Data[Idx];
  return 0;
}


///@Function: xVector_Insert
///@Descript: Insert a New Value at the Specified Index in the Vector
void xVector_Insert(xVector *Vec,int Idx,int Value)
{
#if 0 //V1.1 Remove
  if(Idx < 0 || Idx > Vec->Size)
    return;
  if(Vec->Size == Vec->Capacity)
    xVector_Resize(Vec,Vec->Capacity<<1);   //Size * 2
  
  for(int i=Vec->Size;i>Idx;i--)
    Vec->Data[i] = Vec->Data[i-1];

  Vec->Data[Idx] = Value;
  Vec->Size++;
#endif
  if(Idx < 0 || Idx > Vec->Size)
    return;
  if(Vec->Size == Vec->Capacity)
    xVector_Resize(Vec, Vec->Capacity << 1);

  int *p = Vec->Data + Vec->Size;
  int  n = Vec->Size - Idx;
  while(n--)
  {
    *p = *(p-1);
    p--;
  }
  *p = Value;
  Vec->Size++;
}


///@Function: xVector_Remove
///@Descript: Remove the Element at the Specified Index from the Vector
void xVector_Remove(xVector *Vec,int Idx)
{
  if(Idx < 0 || Idx >= Vec->Size)
    return;
  for(int i=Idx;i<Vec->Size-1;i++)
    Vec->Data[i] = Vec->Data[i+1];
  Vec->Size--;
}


///@Function: xVector_Update
///@Descript: Update the Value of the Element at the Specified Index in the Vector
void xVector_Update(xVector *Vec,int Idx,int Value)
{
  if(Idx < 0 || Idx >= Vec->Size)
    return;
  Vec->Data[Idx] = Value;
}


///@Function: xVector_Clear
///@Descript: Clear All Elements in the Vector By Setting Size to 0
void xVector_Clear(xVector *Vec)
{
  Vec->Size = 0;
}


///@Function: xVector_Merge
///@Descript: Merge 2 Vector By Appending the Elements of the Second Vector to the First
void xVector_Merge(xVector *Vec1,xVector *Vec2)
{
  int NewSize = Vec1->Size + Vec2->Size;
  Vec1->Data = (int*)realloc(Vec1->Data,NewSize * sizeof(int));
  
  for(int i=0;i<Vec2->Size;i++)
    Vec1->Data[Vec1->Size+i] = Vec2->Data[i];
  Vec1->Size     = NewSize;
  Vec1->Capacity = NewSize;
}


///@Function: xVector_Reverse
///@Descript: Reverse the Order of Elements in the Vector
void xVector_Reverse(xVector *Vec)
{
  int Start = 0;
  int End   = Vec->Size - 1;
  while(Start < End)
  {
    SAFE_SWAP(int,Vec->Data[Start],Vec->Data[End]);
    Start++;
    End--;
  }
}


///@Function: xVector_Sum
///@Descript: Calculate the Sum of All Elements in the Vecotr
int xVector_Sum(xVector *Vec)
{
#if 0 //V1.1 Remove
  int Sum = 0;
  for(int i=0;i<Vec->Size;i++)
    Sum += Vec->Data[i];
  return Sum;
#endif
  int Sum = 0;
  int *p  = Vec->Data;
  int n   = Vec->Size;

  while(n--)
    Sum += *p++;
  return Sum;
}


///@Function: xVector_Average
///@Descript: Calculate the Average of All Elements in the Vector
DBL xVector_Average(xVector *Vec)
{
  if(Vec->Size == 0)
    return 0.0f;
  return (DBL)xVector_Sum(Vec)/(DBL)Vec->Size;
}


///@Function: xVector_Scale
///@Descript: Mutiple Each Element in the Vecotr By the Factor
void xVector_Scale(xVector *Vec,int Factor)
{
  for(int i=0;i<Vec->Size;i++)
    Vec->Data[i] *= Factor;
}


///@Function: xVector_FindMax
///@Descript: Find the Maximum Value in the Vector
int xVector_FindMax(xVector *Vec)
{
#if 0 //V1.1 Remove
  if(Vec->Size == 0)
    return -1;

  int Max = Vec->Data[0];
  for(int i=1;i<Vec->Size;i++)
    if(Vec->Data[i] > Max)
      Max = Vec->Data[i];
  return Max;
#endif
  int n = Vec->Size;
  if(n <= 0)
    return -1;

  int *p  = Vec->Data;
  int Max = *p++;
  while(--n > 0) 
  {
    if(*p > Max)
      Max = *p;
    p++;
  }
  return Max;
}


///@Function: xVector_FindMin
///@Descript: Find the Minmum Value in the Vector
int xVector_FindMin(xVector *Vec)
{
#if 0 //V1.1 Remove
  if(Vec->Size == 0)
    return -1;
  
  int Min = Vec->Data[0];
  for(int i=1;i<Vec->Size;i++)
    if(Vec->Data[i] < Min)
      Min = Vec->Data[i];
  return Min;
#endif
  int n = Vec->Size;
  if(n <= 0)
    return -1;

  int *p  = Vec->Data;
  int Min = *p++;
  while(--n > 0) 
  {
    if(*p < Min)
      Min = *p;
    p++;
  }
  return Min;
}
