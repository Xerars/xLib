#ifndef __MODULE_DPORT_H__  //__MODULE_DPORT_H__
#define __MODULE_DPORT_H__  //__MODULE_DPORT_H__

//[STD Lib Include]
#include <stdio.h>

//[xLib Include]
#include "xDLoad.h"

//[Callback Function Declare]
typedef int   (*Calculate_CB)  (int,int);
typedef void  (*PrintData_CB)  (char*);
typedef void  (*Slogan_CB)     (void);
typedef int   (*GetRound_CB)   (void);

//[Struct Declare]
typedef struct _Module_DPort
{
  //Function
  Calculate_CB    Calculate;
  PrintData_CB    PrintData;
  Slogan_CB       Slogan;
  GetRound_CB     GetRound;

  //Variable
  int* Round;
} Module_DPort;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
//[Macro Function Declare]
#define XDLIB_MODULE_GET(LIB,DPORT)                             \
do                                                              \
{                                                               \
  /* Function Bind */                                           \
  xDLOAD_BIND(LIB,Calculate_CB,Calculate);                      \
  xDLOAD_BIND(LIB,PrintData_CB,PrintData);                      \
  xDLOAD_BIND(LIB,Slogan_CB   ,Slogan);                         \
  xDLOAD_BIND(LIB,GetRound_CB ,GetRound);                       \
  /* Variable Bind */                                           \
  xDLOAD_BIND(LIB,int* ,Round);                                 \
  /* Check */                                                   \
  if(!Calculate)  printf("[ERROR]: Calculate Bind Failed!\n");  \
  if(!PrintData)  printf("[ERROR]: PrintData Bind Failed!\n");  \
  if(!Slogan)     printf("[ERROR]: Slogan Bind Failed!\n");     \
  if(!GetRound)   printf("[ERROR]: GetRound Bind Failed!\n");   \
  if(!Round)      printf("[ERROR]: Round Bind Failed!\n");      \
  /* Regist */                                                  \
  DPORT.Calculate = Calculate;                                  \
  DPORT.PrintData = PrintData;                                  \
  DPORT.Slogan    = Slogan;                                     \
  DPORT.GetRound  = GetRound;                                   \
  DPORT.Round     = Round;                                      \
} while(0)

#endif  //__MODULE_DPORT_H__
