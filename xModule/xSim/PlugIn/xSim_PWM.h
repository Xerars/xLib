#ifndef __XSIM_PWM_H__  //__XSIM_PWM_H__
#define __XSIM_PWM_H__  //__XSIM_PWM_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
#define xSIM_PWM_CH_MAX         8           //Max PWM Channels
#define xSIM_PWM_NAME_SIZE      32          //Max Name Size
#define xSIM_PWM_LOG_CAPACITY   (4 * 1024)  //4KB Default Log Capacity

//[Struct Declare]
//PWM
typedef struct _xSim_PWM
{
  U8            Used;                       //Is Used
  U8            Channel;                    //Channel ID
  char          Name[xSIM_PWM_NAME_SIZE];   //PWM Name
  U8            En;                         //Enable State (0/1)
  U32           Freq;                       //Frequency (Hz)
  U8            Rate;                       //Duty Cycle Rate (0-100%)
  U8            Running;                    //Running State (Start/Stop)
  U32           Stamp;                      //Timestamp
} xSim_PWM;

//Log
typedef struct _xSim_PWM_Log
{
  char          *Buf;                       //PWM Buffer
  U32           Capacity;                   //PWM Capacity
  U32           Size;                       //PWM Size
} xSim_PWM_Log;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Init
void xSim_PWM_Init(U8 LogEn);
void xSim_PWM_Destroy(void);

//Regist
void xSim_PWM_Regist(U8 Channel,CCHAR *Name,U8 En,U32 Freq,U8 Rate);
void xSim_PWM_UnRegist(U8 Channel);

//Set
void xSim_PWM_SetEnable(U8 Channel,U8 En);
void xSim_PWM_SetFreq(U8 Channel,U32 Freq);
void xSim_PWM_SetDuty(U8 Channel,U8 Rate);

//Control
void xSim_PWM_Start(U8 Channel);
void xSim_PWM_Stop(U8 Channel);

//Dump
void xSim_PWM_Dump(CCHAR *FileName);

#ifdef __cplusplus
}
#endif

#endif  //__XSIM_PWM_H__
