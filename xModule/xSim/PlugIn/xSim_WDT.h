#ifndef __XSIM_WDT_H__ //__XSIM_WDT_H__
#define __XSIM_WDT_H__ //__XSIM_WDT_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"


//[Struct Declare]
typedef struct _xSim_WDT
{
  U8  En;               //Enable
  U32 TimeOut;          //TimeOut
  U32 Counter;          //Couter
  U8  Exit;             //Exit the Program
} xSim_WDT;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Init
void xSim_WDT_Regist(U32 TimeOut);
void xSim_WDT_UnRegist(void);
void xSim_WDT_Init(void);

//Feed
void xSim_WDT_Feed(void);

//Setting
void xSim_WDT_SetTimeOut(U32 TimeOut);
void xSim_WDT_SetEn(U8 En);
void xSim_WDT_SetExit(U8 Exit);


#ifdef __cplusplus
}
#endif

#endif  //__XSIM_WDT_H__
