//Demo the DLoad Lib to Dynamically Load and Use Function

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xDLoad.h"

//[Macro Declare]
#ifdef _WIN32
  #define DLIB_NAME         "../lib/Module.dll"
#else
  #define DLIB_NAME         "../lib/libModule.so"
#endif

//[Callback Function Declare]
typedef int  (*MOD_Calculate)(int,int);
typedef void (*MOD_PrintData)(char*);
typedef void (*MOD_Slogan)   (void);
typedef int  (*MOD_GetRound) (void);

//[Prototype Declare]
void Run_Test(void);

//[Variable Declare]
//Function
MOD_Calculate Calculate = NULL;
MOD_PrintData PrintData = NULL;
MOD_Slogan    Slogan    = NULL;
MOD_GetRound  GetRound  = NULL;

//Var
int *pRound = NULL;

//DLib
xDLib Lib   = NULL;

//Main Code
int main(void)
{
  //Load DLib
  Lib = xDLIB_Load(DLIB_NAME);

  if(!Lib)
  {
  	printf("Load Module Lib Failed!\n");
  	return -1;
  }
  
  //Get Function
  Calculate = (MOD_Calculate) xDLIB_Get(Lib,"Calculate");
  PrintData = (MOD_PrintData) xDLIB_Get(Lib,"PrintData");
  Slogan    = (MOD_Slogan)    xDLIB_Get(Lib,"Slogan");
  GetRound  = (MOD_GetRound)  xDLIB_Get(Lib,"GetRound");
  
  //Get Variable
  xDLOAD_BIND(Lib,int*,Round);         //Demo Macro Function
  pRound = Round;

  //Run Test
  Run_Test();
  
  //Close Lib
  xDLIB_Close(Lib);
  return 0;
}


///@Function: Run_Test
///@Descript: Run Test Module
void Run_Test(void)
{
  //TEST PrintData
  PrintData("DLOAD Function TEST!!\n");

  //TEST Calculate
  int r = Calculate(3,5);
  printf("Calculate(3,5) = %d\n",r);
  
  //TEST Slogan
  Slogan();

  //TEST Round
  printf("Round(1)   = %d\n",*pRound);
  printf("GetRound() = %d\n",GetRound());
  printf("GetRound() = %d\n",GetRound());
  printf("GetRound() = %d\n",GetRound());
}