#ifndef __XLEAKCHECK_H__   //__XLEAKCHECK_H__
#define __XLEAKCHECK_H__   //__XLEAKCHECK_H__

//Author  : William Hsiao
//Descript: Lightweight Memory Leak Detection
//Version : 1.1.1

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
#define xLEAK_CHECK_FILE        __FILE__        //File Name
#define xLEAK_CHECK_LINE        __LINE__        //Line
#define xLEAK_CHECK_FUNC        __func__        //Function

#undef malloc                                   //Undefine Malloc
#undef calloc                                   //Undefine Calloc
#undef realloc                                  //Undefine Realloc
#undef free                                     //Undefine Free

#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
void* xLeak_Malloc (size_t Size ,char* FileName,xCC* FuncName,size_t Line);
void* xLeak_Calloc (size_t Count,size_t Size,char* FileName,xCC* FuncName,size_t Line);
void* xLeak_Realloc(void *Addr  ,size_t Size,char* FileName,xCC* FuncName,size_t Line);
void  xLeak_Free   (void *Addr);
int   xLeak_MemInfo(void);

#ifdef __cplusplus
}
#endif
//[Macro Function Declare]
#define malloc(S)           xLeak_Malloc(   S,xLEAK_CHECK_FILE,xLEAK_CHECK_FUNC,xLEAK_CHECK_LINE)
#define calloc(C,S)         xLeak_Calloc(C, S,xLEAK_CHECK_FILE,xLEAK_CHECK_FUNC,xLEAK_CHECK_LINE)
#define realloc(P,S)        xLeak_Realloc(P,S,xLEAK_CHECK_FILE,xLEAK_CHECK_FUNC,xLEAK_CHECK_LINE)
#define free(P)             xLeak_Free(P)

//Leak Memory 
#define Leak_Malloc(S)      xLeak_Malloc(   S,xLEAK_CHECK_FILE,xLEAK_CHECK_FUNC,xLEAK_CHECK_LINE)
#define Leak_Calloc(C,S)    xLeak_Calloc(C ,S,xLEAK_CHECK_FILE,xLEAK_CHECK_FUNC,xLEAK_CHECK_LINE)
#define Leak_Realloc(P,S)   xLeak_Realloc(P,S,xLEAK_CHECK_FILE,xLEAK_CHECK_FUNC,xLEAK_CHECK_LINE)
#define Leak_Free(P)        xLeak_Free(P)

#endif  //__XLEAKCHECK_H__