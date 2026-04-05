#ifndef __XLOAD_H__ //__XLOAD_H__
#define __XLOAD_H__ //__XLOAD_H__

//Author  : William Hsiao
//Descript: Cross-Platform Dynamic Library Loading Function Library
//Version : 1.0.1

//[xLib Inlcude]
#include "xType.h"
#include "xMeta.h"

//[OS Lib Include]
#ifdef _WIN32
  #include <windows.h>        //Dynamic Load
#else
  #include <dlfcn.h>          //Dynamic Load
#endif


//[Typedef Declare]
typedef void* xDLib;         //DLib Handler

#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
xDLib xDLIB_Load(CCHAR* Path);
void  xDLIB_Close(xDLib Handle);
void* xDLIB_Get(xDLib Handle,CCHAR* FName);

#ifdef __cplusplus
}
#endif
//[Macro Function Declare]
#define xDLOAD_OPEN(NAME)                 xDLIB_Load(NAME)
#define xDLOAD_CLOSE(LIB)                 xDLIB_Close(LIB)
#define xDLOAD_BIND(LIB,TYPE,NAME)        TYPE NAME = (TYPE)xDLIB_Get(LIB,#NAME)

#endif  //__XLOAD_H__
