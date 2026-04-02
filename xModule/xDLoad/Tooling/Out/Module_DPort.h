#ifndef __MODULE_DPORT_DPORT_H__  //__MODULE_DPORT_DPORT_H__
#define __MODULE_DPORT_DPORT_H__  //__MODULE_DPORT_DPORT_H__

//**************************************************
//  @File   : Module_DPort.h DPort Header
//  @Author : DLoad Tool
//  @Date   : 2026-03-30 23:49:30
//  @Brief  : DPort Interface Definition
//**************************************************

//[Include Declare]
#include <stdio.h>

//[Typedef Declare]
//None

//[Macro Declare]
//None

//[Enum Declare]
//None

//[Callback Function Declare]

//Generate Callback
typedef int   (*Calculate_CB)(int, int);
typedef void  (*PrintData_CB)(char);
typedef void  (*Slogan_CB)   (void);
typedef int   (*GetRound_CB) (void);

//[Struct Declare]

//Generate Struct
typedef struct _Module_DPort
{
  //Function
  Calculate_CB    Calculate;
  PrintData_CB    PrintData;
  Slogan_CB       Slogan;
  GetRound_CB     GetRound;

  //Variable
  int        *Round;
} Module_DPort;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

//[Variable Declare]
//None
//[Prototype Declare]
//None
#ifdef __cplusplus
}
#endif  // __cplusplus
//[Macro Function Declare]
#define XDLIB_MODULE_GET(LIB,DPORT)                                             \
do                                                                              \
{                                                                               \
  /* Function Bind */                                                           \
  xDLOAD_BIND(LIB,Calculate_CB,Calculate);                                      \
  xDLOAD_BIND(LIB,PrintData_CB,PrintData);                                      \
  xDLOAD_BIND(LIB,Slogan_CB   ,Slogan);                                         \
  xDLOAD_BIND(LIB,GetRound_CB ,GetRound);                                       \
  /* Variable Bind */                                                           \
  xDLOAD_BIND(LIB,int*    ,Round);                                              \
  /* Check */                                                                   \
  if(!Round)      printf("[ERROR]: Round Bind Failed!\n");                      \
  if(!Calculate)  printf("[ERROR]: Calculate Bind Failed!\n");                  \
  if(!PrintData)  printf("[ERROR]: PrintData Bind Failed!\n");                  \
  if(!Slogan)     printf("[ERROR]: Slogan Bind Failed!\n");                     \
  if(!GetRound)   printf("[ERROR]: GetRound Bind Failed!\n");                   \
  /* Regist */                                                                  \
  DPORT.Round      = Round;                                                     \
  DPORT.Calculate  = Calculate;                                                 \
  DPORT.PrintData  = PrintData;                                                 \
  DPORT.Slogan     = Slogan;                                                    \
  DPORT.GetRound   = GetRound;                                                  \
} while(0)

#endif //__MODULE_DPORT_DPORT_H__

