#ifndef __XSIM_ADC_H__  //__XSIM_ADC_H__
#define __XSIM_ADC_H__  //__XSIM_ADC_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
#define xSIM_ADC_MAX              20        //GPI Max Table Size
#define xSIM_ADC_LOG_CAPACITY     4096      //4KB

//[Enum Declare]
typedef enum _xSIM_DATA_TYPE
{
  xSIM_DATA_TYPE_RANDOM         = 0,        //Radom   Value
  xSIM_DATA_TYPE_ONESHOT        = 1,        //OneShot Value
} xSIM_DATA_TYPE;


//[Struct Declare]
//Simulate ADC
typedef struct _xSim_ADC
{
  U8              Channel;                  //Channel
  U8              Used;                     //Used
  U8              nBit;                     //Num of Bit
  xSIM_DATA_TYPE  Type;                     //Data Type
  U32             Value;                    //Value
  U32             Min;                      //Min Limit
  U32             Max;                      //Max Limit
  U32             Stamp;                    //Stamp
} xSim_ADC;


//Simulate ADC Log
typedef struct _xSim_ADC_Log
{
  char           *Buf;                      //Buffer
  U32             Capacity;                 //Capacity
  U32             Size;                     //Used Size
} xSim_ADC_Log;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Configure
void xSim_ADC_Regist(U8 Channel,U8 nBit);
void xSim_ADC_UnRegist(U8 Channel);
void xSim_ADC_Init(U8 LogEn);

//Get
U32  xSim_ADC_GetValue(U8 Channel);

//Set
void xSim_ADC_SetValue(U8 Channel,U32 Value);
void xSim_ADC_SetRange(U8 Channel,U32 Min,U32 Max);

//Dump
void xSim_ADC_Dump(const char *FileName);

#ifdef __cplusplus
}
#endif

#endif  //__XSIM_ADC_H__
