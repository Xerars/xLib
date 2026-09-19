#ifndef __XSIM_INT_H__  //__XSIM_INT_H__
#define __XSIM_INT_H__  //__XSIM_INT_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
#define xSIM_INT_CH_MAX           16          //Max Interrupt Channels
#define xSIM_INT_NAME_SIZE        32          //Max Name Size
#define xSIM_INT_LOG_CAPACITY     (4 * 1024)  //4KB Default Log Capacity

//[Enum Declare]
typedef enum _xSIM_INT_EDGE
{
  xSIM_INT_EDGE_NONE            = 0x00,       //No Interrupt
  xSIM_INT_EDGE_RISING          = 0x01,       //Low  -> High
  xSIM_INT_EDGE_FALLING         = 0x02,       //High -> Low
  xSIM_INT_EDGE_BOTH            = 0x03,       //Both Low -> High & High -> Low
} xSIM_INT_EDGE;


//[Callback Function Declare]
typedef void (*xSim_Int_CB)(U8 Channel,U8 Level);

//[Struct Declare]
//Interrupt
typedef struct _xSim_Int
{
  U8            Used;                         //Is Used
  U8            Channel;                      //Channel ID
  char          Name[xSIM_INT_NAME_SIZE];     //Interrupt Name
  xSIM_INT_EDGE Edge;                         //Trigger Edge Type
  U8            Last;                         //Last Sample Level
  xSim_Int_CB   ISR;                          //ISR Callback
  U32           Stamp;                        //Interrupt Stamp
} xSim_Int;

//Log
typedef struct _xSim_INT_Log
{
  char         *Buf;                          //Interrupt Buffer
  U32           Capacity;                     //Interrupt Capacity
  U32           Size;                         //Interrupt Size
} xSim_INT_Log;



#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Init
void xSim_INT_Init(U8 LogEn);
void xSim_INT_Destroy(void);

//Regist
void xSim_INT_Regist(U8 Channel,CCHAR *Name,xSIM_INT_EDGE Edge,xSim_Int_CB CB);
void xSim_INT_UnRegist(U8 Channel);

//Set
void xSim_INT_SetEdge(U8 Channel,xSIM_INT_EDGE Edge);
void xSim_INT_SetTrigger(U8 Channel,U8 Cur);

//Dump
void xSim_INT_Dump(CCHAR *FileName);

#ifdef __cplusplus
}
#endif

#endif  //__XSIM_INT_H__
