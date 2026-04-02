#ifndef __MODULE_H__  //__MODULE_H__ 
#define __MODULE_H__  //__MODULE_H__

//[STD Lib Include]
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
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


#ifdef __cplusplus
extern "C" {
#endif
//[Variable Declare]
extern int Round;
extern float Version;
extern char* Data;

//[Prototype Declare]
int  Calculate(int X1,int X2);
void PrintData(char *Str);
void Slogan(void);
int  GetRound(void);
void Module_Config(Module_t Mod,MOD_U8 Data);

#ifdef __cplusplus
}
#endif
//[Macro Function Declare]
#define SHOW_USER()           printf("[USER]: %s\n",MODULE_USER)
#define SHOW_INFO()           printf("[INFO]: %s\n",MODULE_INFO)
#define SHOW_DATE()           printf("[DATE]: %s\n",MODULE_DATE)
#define SHOW_VERSION()        printf("[VER] : %1.1f\n",MODULE_VERSION)

#endif //__MODULE_H__
