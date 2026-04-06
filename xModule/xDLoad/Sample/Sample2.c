//Demo the DLoad Lib and the Generate Port Interface Operate

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xDLoad.h"

//[Port Include]
#include "Module_DPort.h"

//[Macro Declare]
#ifdef _WIN32
  #define DLIB_NAME         "./Lib/Module.dll"
#else
  #define DLIB_NAME         "./Lib/libModule.so"
#endif

//[Prototype Declare]
void Run_Test(void);

//[Variable Declare]
xDLib Lib;
Module_DPort *pDPort = NULL;

//Main Code
int main(void)
{
  Module_DPort DPort;
  pDPort = &DPort;

  Lib = xDLOAD_OPEN(DLIB_NAME);   //Open DLib
  XDLIB_MODULE_GET(Lib,DPort);    //Get Module
  Run_Test();                     //Run Test
  xDLOAD_CLOSE(Lib);              //Close DLib
  return 0;
}


///@Function: Run_Test
///@Descript: Run Test Module
void Run_Test(void)
{
  //TEST PrintData
  pDPort->PrintData("DLOAD Function TEST!!\n");

  //TEST Calculate
  int r =  pDPort->Calculate(3,5);
  printf("Calculate(3,5) = %d\n",r);

  //TEST Slogan
   pDPort->Slogan();

  //TEST Round
  printf("Round(1)   = %d\n",*pDPort->Round);
  printf("GetRound() = %d\n", pDPort->GetRound());
  printf("GetRound() = %d\n", pDPort->GetRound());
  printf("GetRound() = %d\n", pDPort->GetRound());
}