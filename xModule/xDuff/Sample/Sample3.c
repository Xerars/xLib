//Demo the xDuff Lib about Matrix Calculate

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xDuff.h"

//[Prototype Declare]
void Show_Array(int *Arr,int N);

//Main Code
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


///@Function: Show_Array
///@Descript: Show Array Data
void Show_Array(int *Arr,int N)
{
  for(int i=0;i<N;i++)
    printf("[%02X] ",Arr[i]);
  printf("\n");
}
