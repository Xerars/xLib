//Demo the xVector Lib Macro Function

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xVector.h"

//[Struct Declare]
typedef struct _Student
{
  int  ID;
  char Name[10];
  int  Score;
} Student;

XVEC_STRUCT(int  ,INT);
XVEC_STRUCT(DBL  ,DBL);
XVEC_STRUCT(char ,CHAR);
XVEC_STRUCT(char*,STR);
XVEC_STRUCT(Student,STU);

//[Function Declare]
XVEC_IMPL(int ,INT);
XVEC_IMPL(DBL ,DBL);
XVEC_IMPL(char,CHAR);
XVEC_IMPL(char*,STR);
XVEC_IMPL(Student,STU);

//[Prototype Declare]
static void TEST_INT_VECTOR (void);
static void TEST_DBL_VECTOR (void);
static void TEST_CHAR_VECTOR(void);
static void TEST_STR_VECTOR (void);
static void TEST_STU_VECTOR (void);

static void Show_INT_Data (xCC *Name,xVec_INT  *Vec);
static void Show_DBL_Data (xCC *Name,xVec_DBL  *Vec);
static void Show_CHAR_Data(xCC *Name,xVec_CHAR *Vec);
static void Show_STR_Data (xCC *Name,xVec_STR  *Vec);
static void Show_STU_Data (xCC *Name,xVec_STU  *Vec);

static void Show_INT_Result (xCC *Name,xVec_INT  *V1,xVec_INT  *V2);
static void Show_DBL_Result (xCC *Name,xVec_DBL  *V1,xVec_DBL  *V2);
static void Show_CHAR_Result(xCC *Name,xVec_CHAR *V1,xVec_CHAR *V2);
static void Show_STR_Result (xCC *Name,xVec_STR  *V1,xVec_STR  *V2);
static void Show_STU_Result (xCC *Name,xVec_STU  *V1,xVec_STU  *V2);

static void Add_Shallow_STR_Data(xVec_STR *Vec,xCC *In);
static void Add_Deep_STR_Data(xVec_STR *Vec,xCC *In);
static void Demo_Copy(void);

//[Variable Declare]
char gBuf[100] = {0};

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


///@Function: TEST_DBL_VECTOR
///@Descript: Test double Vector
static void TEST_DBL_VECTOR(void)
{
  xVec_DBL V1;
  xVec_DBL V2;

  xVec_DBL_Init(&V1,5);
  xVec_DBL_Init(&V2,5);
  for(int i=0;i<5;i++)
  {
    xVec_DBL_Push(&V1,i+0.5);
    xVec_DBL_Push(&V2,5.5-i);
  }
  Show_DBL_Result("PUSH",&V1,&V2);

  xVec_DBL_Pop(&V1);
  xVec_DBL_Pop(&V2);
  Show_DBL_Result("POP",&V1,&V2);

  printf("[AT]\n");
  printf("V1[2] = %f\n"  ,xVec_DBL_At(&V1,2));
  printf("V2[2] = %f\n\n",xVec_DBL_At(&V2,2));

  xVec_DBL_Insert(&V1,3,10.5);
  xVec_DBL_Insert(&V2,3,10.5);
  Show_DBL_Result("INSERT",&V1,&V2);

  xVec_DBL_Remove(&V1,4);
  xVec_DBL_Remove(&V2,4);
  Show_DBL_Result("REMOVE",&V1,&V2);

  xVec_DBL_Update(&V1,2,10.5);
  xVec_DBL_Update(&V2,2,10.5);
  Show_DBL_Result("UPDATE",&V1,&V2);

  xVec_DBL_Reverse(&V1);      Show_DBL_Result("REVERSE",&V1,&V2);
  xVec_DBL_Merge(&V1,&V2);    Show_DBL_Result("MERGE",&V1,&V2);

  xVec_DBL_Clear(&V2);
  xVec_DBL_Push(&V1,100.5);
  Show_DBL_Result("CLEAR",&V1,&V2);

  xVec_DBL_Destroy(&V1);
  xVec_DBL_Destroy(&V2);
}


///@Function: TEST_CHAR_VECTOR
///@Descript: Test Char Vector
static void TEST_CHAR_VECTOR(void)
{
  xVec_CHAR V1;
  xVec_CHAR V2;

  xVec_CHAR_Init(&V1,5);
  xVec_CHAR_Init(&V2,5);
  for(int i='A';i<'F';i++)
  {
    xVec_CHAR_Push(&V1,i);
    xVec_CHAR_Push(&V2,i+32);
  }
  Show_CHAR_Result("PUSH",&V1,&V2);

  xVec_CHAR_Pop(&V1);
  xVec_CHAR_Pop(&V2);
  Show_CHAR_Result("POP",&V1,&V2);

  printf("[AT]\n");
  printf("V1[2] = %c\n"  ,xVec_CHAR_At(&V1,2));
  printf("V2[2] = %c\n\n",xVec_CHAR_At(&V2,2));

  xVec_CHAR_Insert(&V1,3,'Z');
  xVec_CHAR_Insert(&V2,3,'z');
  Show_CHAR_Result("INSERT",&V1,&V2);

  xVec_CHAR_Remove(&V1,4);
  xVec_CHAR_Remove(&V2,4);
  Show_CHAR_Result("REMOVE",&V1,&V2);

  xVec_CHAR_Update(&V1,2,'X');
  xVec_CHAR_Update(&V2,2,'x');
  Show_CHAR_Result("UPDATE",&V1,&V2);

  xVec_CHAR_Reverse(&V1);     Show_CHAR_Result("REVERSE",&V1,&V2);
  xVec_CHAR_Merge(&V1,&V2);   Show_CHAR_Result("MERGE",&V1,&V2);

  xVec_CHAR_Clear(&V2);
  xVec_CHAR_Push(&V1,'V');
  Show_CHAR_Result("CLEAR",&V1,&V2);

  xVec_CHAR_Destroy(&V1);
  xVec_CHAR_Destroy(&V2);
}


///@Function: TEST_STR_VECTOR
///@Descript: Test String Vector
static void TEST_STR_VECTOR(void)
{
  xVec_STR V1;
  xVec_STR V2;

  xVec_STR_Init(&V1, 5);
  xVec_STR_Init(&V2, 5);

  xVec_STR_Push(&V1, "Hello");
  xVec_STR_Push(&V1, "World");
  xVec_STR_Push(&V1, "C-Language");

  xVec_STR_Push(&V2, "Gemini");
  xVec_STR_Push(&V2, "AI");
  xVec_STR_Push(&V2, "xLib");
  Show_STR_Result("PUSH",&V1,&V2);

  printf("[AT]\n");
  printf("V1[1] = %s\n"  ,xVec_STR_At(&V1,1));
  printf("V2[0] = %s\n\n",xVec_STR_At(&V2,0));

  xVec_STR_Insert(&V1,1,"INSERTED");    Show_STR_Result("INSERT",&V1,&V2);
  xVec_STR_Update(&V1,0,"New-Hello");   Show_STR_Result("UPDATE",&V1,&V2);
  xVec_STR_Reverse(&V1);                Show_STR_Result("REVERSE",&V1,&V2);
  xVec_STR_Merge(&V1,&V2);              Show_STR_Result("MERGE",&V1,&V2);

  xVec_STR_Clear(&V2);
  xVec_STR_Push(&V1,"GoodBye");
  Show_STR_Result("CLEAR",&V1,&V2);

  xVec_STR_Destroy(&V1);
  xVec_STR_Destroy(&V2);
}


///@Function: TEST_STU_VECTOR
///@Descript: Test struct Student Vector
static void TEST_STU_VECTOR(void)
{
  xVec_STU V1;
  xVec_STU V2;

  xVec_STU_Init(&V1,5);
  xVec_STU_Init(&V2,5);

  xVec_STU_Push(&V1,(Student){101,"William",99});
  xVec_STU_Push(&V1,(Student){102,"Charile",72});
  xVec_STU_Push(&V1,(Student){103,"Frankie",88});
  xVec_STU_Push(&V1,(Student){104,"Charlie",87});

  xVec_STU_Push(&V2,(Student){201,"Stacy"  ,87});
  xVec_STU_Push(&V2,(Student){202,"Kelly"  ,68});
  xVec_STU_Push(&V2,(Student){203,"Bunny"  ,78});
  xVec_STU_Push(&V2,(Student){204,"Ruby"   ,56});
  Show_STU_Result("PUSH",&V1,&V2);

  xVec_STU_Pop(&V1);
  xVec_STU_Pop(&V2);
  Show_STU_Result("POP",&V1,&V2);


  printf("[AT]\n");
  Student S1 = xVec_STU_At(&V1, 2);
  Student S2 = xVec_STU_At(&V2, 2);
  printf("V1[2] -> ID:%d, Name:%s, Score:%d\n"  ,S1.ID,S1.Name,S1.Score);
  printf("V2[2] -> ID:%d, Name:%s, Score:%d\n\n",S2.ID,S2.Name,S2.Score);

  xVec_STU_Insert(&V1,2,(Student){888,"Mark" ,60});
  xVec_STU_Insert(&V2,2,(Student){888,"Sunny",60});
  Show_STU_Result("INSERT",&V1,&V2);

  xVec_STU_Remove(&V1,4);
  xVec_STU_Remove(&V2,4);
  Show_STU_Result("REMOVE",&V1,&V2);

  xVec_STU_Update(&V1,2,(Student){103,"Frank-V2",0});
  xVec_STU_Update(&V2,2,(Student){203,"Bunny-V2",0});
  Show_STU_Result("UPDATE",&V1,&V2);

  xVec_STU_Reverse(&V1);      Show_STU_Result("REVERSE",&V1,&V2);
  xVec_STU_Merge(&V1,&V2);    Show_STU_Result("MERGE",&V1,&V2);
  xVec_STU_Clear(&V2);        Show_STU_Result("CLEAR",&V1,&V2);

  xVec_STU_Destroy(&V1);
  xVec_STU_Destroy(&V2);
}


///@Function: Show_INT_Data
///@Descript: Show Vector Integer Data
static void Show_INT_Data(xCC *Name,xVec_INT *Vec)
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


///@Function: Show_INT_Result
///@Descript: Show Vec1 & Vec2 Result
static void Show_INT_Result(xCC *Name,xVec_INT *V1,xVec_INT *V2)
{
  printf("[%s]\n",Name);
  Show_INT_Data("Vec1",V1);
  Show_INT_Data("Vec2",V2);
  printf("\n");

}


///@Function: Show_DBL_Data
///@Descript: Show Vector Double Data
static void Show_DBL_Data(xCC *Name,xVec_DBL *Vec)
{
  printf("[%s]: %d/%d (Size/Capacity) => ",Name,Vec->Size,Vec->Capacity);
  for(int i=0;i<Vec->Size;i++)
  {
    printf("%3.2f ",Vec->Data[i]);
    if(i!=Vec->Size-1)
      printf("-> ");
  }
  printf("\n");
}


///@Function: Show_DBL_Result
///@Descript: Show Vec1 & Vec2 Result
static void Show_DBL_Result(xCC *Name,xVec_DBL *V1,xVec_DBL *V2)
{
  printf("[%s]\n",Name);
  Show_DBL_Data("Vec1",V1);
  Show_DBL_Data("Vec2",V2);
  printf("\n");
}


///@Function: Show_CHAR_Data
///@Descript: Show Vector Double Data
static void Show_CHAR_Data(xCC *Name,xVec_CHAR *Vec)
{
  printf("[%s]: %d/%d (Size/Capacity) => ",Name,Vec->Size,Vec->Capacity);
  for(int i=0;i<Vec->Size;i++)
  {
    printf("'%c' ",Vec->Data[i]);
    if(i!=Vec->Size-1)
      printf("-> ");
  }
  printf("\n");
}


///@Function: Show_CHAR_Result
///@Descript: Show Vec1 & Vec2 Result
static void Show_CHAR_Result(xCC *Name,xVec_CHAR *V1,xVec_CHAR *V2)
{
  printf("[%s]\n",Name);
  Show_CHAR_Data("Vec1",V1);
  Show_CHAR_Data("Vec2",V2);
  printf("\n");
}


///@Function: Show_STR_Data
///@Descript:  Show Vector String Data
static void Show_STR_Data(xCC *Name,xVec_STR *Vec)
{
  printf("[%s]: %d/%d (Size/Capacity) => ",Name,Vec->Size,Vec->Capacity);
  for(int i=0; i < Vec->Size; i++)
  {
    printf("[%s] ", Vec->Data[i]);
    if(i != Vec->Size-1)
      printf("-> ");
  }
  printf("\n");
}


///@Function: Show_STR_Result
///@Descript: Show Vec1 & Vec2 Result
static void Show_STR_Result(xCC *Name,xVec_STR *V1,xVec_STR *V2)
{
  printf("[%s]\n",Name);
  Show_STR_Data("Vec1",V1);
  Show_STR_Data("Vec2",V2);
  printf("\n");
}


///@Function: Show_STU_Data
///@Descript: Show Vector Student Struct Data
static void Show_STU_Data(xCC *Name,xVec_STU *Vec)
{
  printf("[%s]: %d/%d (Size/Capacity)\n",Name,Vec->Size,Vec->Capacity);
  printf("-> ");
  for(int i = 0;i<Vec->Size;i++)
  {
    printf("[%d] ID:%d [%-7s]:(%d)",i,
      Vec->Data[i].ID,
      Vec->Data[i].Name,
      Vec->Data[i].Score);
    if(i != Vec->Size-1)
      printf("-> ");
  }
  printf("\n");
}


///@Function: Show_STU_Result
///@Descript: Show Student Vec1 & Vec2 Result
static void Show_STU_Result(xCC *Name,xVec_STU *V1,xVec_STU *V2)
{
  printf("[%s]\n",Name);
  Show_STU_Data("Vec1",V1);
  Show_STU_Data("Vec2",V2);
  printf("\n");
}

///@Function: Add_Shallow_STR_Data
///@Descript: Add Shallow Str Data
static void Add_Shallow_STR_Data(xVec_STR *Vec,xCC *In)
{
  xVec_STR_Push(Vec,(char*)In);      //Push Data
}

///@Function: Add_Deep_STR_Data
///@Descript: Add Deep Str Data
static void Add_Deep_STR_Data(xVec_STR *Vec,xCC *In)
{
  int Len = strlen(In) + 1;
  char *DeepCopy = (char*)malloc(sizeof(char)*Len);
  strcpy(DeepCopy,In);
  xVec_STR_Push(Vec,DeepCopy);      //Push Data
}

///@Function: Demo_Copy
///@Descript: Demo Shallow Copy & Deep Copy
static void Demo_Copy(void)
{
  xVec_STR SC1;
  xVec_STR SC2;
  xVec_STR_Init(&SC1,5);
  xVec_STR_Init(&SC2,5);

  //Shallow Copy
  {
    sprintf(gBuf,"Apple");          Add_Shallow_STR_Data(&SC1,gBuf);
    sprintf(gBuf,"Banana");         Add_Shallow_STR_Data(&SC1,gBuf);
    sprintf(gBuf,"Grape");          Add_Shallow_STR_Data(&SC1,gBuf);
    sprintf(gBuf,"StrawBerry");     Add_Shallow_STR_Data(&SC1,gBuf);
  }

  //Deep Copy
  {
    sprintf(gBuf,"Apple");          Add_Deep_STR_Data(&SC2,gBuf);
    sprintf(gBuf,"Banana");         Add_Deep_STR_Data(&SC2,gBuf);
    sprintf(gBuf,"Grape");          Add_Deep_STR_Data(&SC2,gBuf);
    sprintf(gBuf,"StrawBerry");     Add_Deep_STR_Data(&SC2,gBuf);
  }

  printf("[SHALLOW]: %s\n",xVec_STR_At(&SC1,0));
  printf("[SHALLOW]: %s\n",xVec_STR_At(&SC1,1));
  printf("[SHALLOW]: %s\n",xVec_STR_At(&SC1,2));
  printf("[SHALLOW]: %s\n",xVec_STR_At(&SC1,3));

  printf("[DEEP]   : %s\n",xVec_STR_At(&SC2,0));
  printf("[DEEP]   : %s\n",xVec_STR_At(&SC2,1));
  printf("[DEEP]   : %s\n",xVec_STR_At(&SC2,2));
  printf("[DEEP]   : %s\n",xVec_STR_At(&SC2,3));


  //Release Deep Copy Memory
  for(int i = 0;i < SC2.Size;i++)
  {
    char *ptr = xVec_STR_At(&SC2, i);
    SAFE_DESTROY(ptr);
  }

  //Destroy
  xVec_STR_Destroy(&SC1);
  xVec_STR_Destroy(&SC2);
}