#ifndef __MODULEPLUS_DPORT_DPORT_H__  //__MODULEPLUS_DPORT_DPORT_H__
#define __MODULEPLUS_DPORT_DPORT_H__  //__MODULEPLUS_DPORT_DPORT_H__

//**************************************************
//  @File   : ModulePlus_DPort.h DPort Header
//  @Author : DLoad Tool
//  @Date   : 2026-03-30 23:49:48
//  @Brief  : DPort Interface Definition
//**************************************************

//[Include Declare]
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xType.h"
#include "xMeta.h"

//[Typedef Declare]
typedef unsigned char         MOD_U8;
typedef unsigned short        MOD_U16;
typedef unsigned int          MOD_U32;
typedef signed char           MOD_S8;
typedef signed short          MOD_S16;
typedef signed int            MOD_S32;

//[Macro Declare]
#define MODULE_USER           "William Hsiao"               //User
#define MODULE_INFO           "TEST Module for Convert"     //Info
#define MODULE_DATE           "2026/03/29"                  //Date
#define MODULE_VERSION        1.2                           //Version

//[Enum Declare]
typedef enum _MODULE_TYPE
{
  MODULE_START   = 0,         //Module Start
  MODULE_PROCESS = 1,         //Module Process
  MODULE_FINISH  = 2,         //Module Finish
} MODULE_TYPE;

enum _MODULE_LEVEL
{
  MODULE_LEVEL1  = 0,         //Module Level 1
  MODULE_LEVEL2  = 1,         //Module Level 2
  MODULE_LEVEL3  = 2,         //Module Level 3
};


//[Callback Function Declare]
typedef void (*Regist)(int Value);

//Generate Callback
typedef int   (*Calculate_CB)    (int, int);
typedef void  (*PrintData_CB)    (char);
typedef void  (*Slogan_CB)       (void);
typedef int   (*GetRound_CB)     (void);
typedef void  (*Module_Config_CB)(Module_t, MOD_U8);

//[Struct Declare]
typedef struct _DL_Point
{
  int X;                      //X
  int Y;                      //Y
} DL_Point;

typedef struct _DL_Size
{
  int Width;                  //Width
  int Height;                 //Height
} DL_Size;

typedef struct _Module
{
  char *Author;               //Author
  char *Date;                 //Date
  char *Info;                 //Information
  float Version;              //Version
  MODULE_TYPE Type;           //Type
  enum _MODULE_LEVEL Level;   //Level
  Regist Reg;                 //Reg
  DL_Point Point;             //Point
  DL_Size  Size;              //Size
} Module_t;


//Generate Struct
typedef struct _ModulePlus_DPort
{
  //Function
  Calculate_CB    Calculate;
  PrintData_CB    PrintData;
  Slogan_CB       Slogan;
  GetRound_CB     GetRound;
  Module_Config_CB Module_Config;

  //Variable
  int        *Round;
  float      *Version;
  char       **Data;
} ModulePlus_DPort;

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
#define XDLIB_MODULEPLUS_GET(LIB,DPORT)                                         \
do                                                                              \
{                                                                               \
  /* Function Bind */                                                           \
  xDLOAD_BIND(LIB,Calculate_CB,Calculate);                                      \
  xDLOAD_BIND(LIB,PrintData_CB,PrintData);                                      \
  xDLOAD_BIND(LIB,Slogan_CB   ,Slogan);                                         \
  xDLOAD_BIND(LIB,GetRound_CB ,GetRound);                                       \
  xDLOAD_BIND(LIB,Module_Config_CB,Module_Config);                              \
  /* Variable Bind */                                                           \
  xDLOAD_BIND(LIB,int*    ,Round);                                              \
  xDLOAD_BIND(LIB,float*  ,Version);                                            \
  xDLOAD_BIND(LIB,char**  ,Data);                                               \
  /* Check */                                                                   \
  if(!Round)      printf("[ERROR]: Round Bind Failed!\n");                      \
  if(!Version)    printf("[ERROR]: Version Bind Failed!\n");                    \
  if(!Data)       printf("[ERROR]: Data Bind Failed!\n");                       \
  if(!Calculate)  printf("[ERROR]: Calculate Bind Failed!\n");                  \
  if(!PrintData)  printf("[ERROR]: PrintData Bind Failed!\n");                  \
  if(!Slogan)     printf("[ERROR]: Slogan Bind Failed!\n");                     \
  if(!GetRound)   printf("[ERROR]: GetRound Bind Failed!\n");                   \
  if(!Module_Config)      printf("[ERROR]: Module_Config Bind Failed!\n");      \
  /* Regist */                                                                  \
  DPORT.Round      = Round;                                                     \
  DPORT.Version    = Version;                                                   \
  DPORT.Data       = Data;                                                      \
  DPORT.Calculate  = Calculate;                                                 \
  DPORT.PrintData  = PrintData;                                                 \
  DPORT.Slogan     = Slogan;                                                    \
  DPORT.GetRound   = GetRound;                                                  \
  DPORT.Module_Config = Module_Config;                                          \
} while(0)

#endif //__MODULEPLUS_DPORT_DPORT_H__

