//Demo the xVector Lib Integer Vector Operate

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xVector.h"

//[Prototype Declare]
void ShowData(CCHAR *Name,xVector *Vec);

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

  printf("[PUSH]\n");
  ShowData("Vec1",&Vec1);
  ShowData("Vec2",&Vec2);
  printf("\n");

  //At
  int V1 = xVector_At(&Vec1,2);
  int V2 = xVector_At(&Vec1,2);
  printf("[AT]\n");
  printf("V1[2] = %d\n",V1);
  printf("V2[2] = %d\n",V2);
  printf("\n");

  //Insert
  xVector_Insert(&Vec1,1,99);
  xVector_Insert(&Vec2,1,99);
  printf("[INSERT]\n");
  ShowData("Vec1",&Vec1);
  ShowData("Vec2",&Vec2);
  printf("\n");

  //Update
  xVector_Update(&Vec1,0,100);
  xVector_Update(&Vec2,0,100);
  printf("[UPDATE]\n");
  ShowData("Vec1",&Vec1);
  ShowData("Vec2",&Vec2);
  printf("\n");

  //Remove
  xVector_Remove(&Vec1,3);
  xVector_Remove(&Vec2,3);
  printf("[REMOVE]\n");
  ShowData("Vec1",&Vec1);
  ShowData("Vec2",&Vec2);
  printf("\n");

  //Math
  xVector_Scale(&Vec1,2);
  printf("[SCALE]\n");
  ShowData("Vec1",&Vec1);
  ShowData("Vec2",&Vec2);
  printf("\n");

  int Sum = xVector_Sum(&Vec1);
  DBL Avg = xVector_Average(&Vec1);
  int Max = xVector_FindMax(&Vec1);
  int Min = xVector_FindMin(&Vec1);
  printf("[VEC1]: [SUM]:%d [AVG]:%f [MAX]:%d [MIN]:%d\n",Sum,Avg,Max,Min);

  //Utils
  xVector_Reverse(&Vec2);
  printf("[REVERSE]\n");
  ShowData("Vec1",&Vec1);
  ShowData("Vec2",&Vec2);
  printf("\n");

  xVector_Merge(&Vec1,&Vec2);
  printf("[MERGE]\n");
  ShowData("Vec1",&Vec1);
  ShowData("Vec2",&Vec2);
  printf("\n");

  xVector_Clear(&Vec2);
  printf("[CLEAR]\n");
  ShowData("Vec1",&Vec1);
  ShowData("Vec2",&Vec2);
  printf("\n");

  //Destroy
  xVector_Destroy(&Vec1);
  xVector_Destroy(&Vec2);
  return 0;
}


///@Function: ShowData
///@Descript: Show Vector Data
void ShowData(CCHAR *Name,xVector *Vec)
{
  printf("[%s]: %d/%d (Size/Capacity) => ",Name,Vec->Size,Vec->Capacity);
  for(int i=0;i<Vec->Size;i++)
  {
    printf("%d ",Vec->Data[i]);
    if(i!=Vec->Size-1)
      printf("-> ");
  }
  printf("\n");
}