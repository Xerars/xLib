#ifndef __APP_H__  //__APP_H__
#define __APP_H__  //__APP_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Init
void App_Init(void);                                             //Initialize xSTM Flash Sample

//Service
void App_Service(void);                                          //Run xSTM Flash Sample Service

#ifdef __cplusplus
}
#endif

#endif  //__APP_H__