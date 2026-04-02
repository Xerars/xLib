#ifndef __MODULE_H__  //__MODULE_H__ 
#define __MODULE_H__  //__MODULE_H__

//[STD Lib Include]
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
//[Variable Declare]
extern int Round;

//[Prototype Declare]
int  Calculate(int X1,int X2);
void PrintData(char *Str);
void Slogan(void);
int  GetRound(void);

#ifdef __cplusplus
}
#endif

#endif //__MODULE_H__
