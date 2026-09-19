#ifndef __XSIM_REG_H__  //__XSIM_REG_H__
#define __XSIM_REG_H__  //__XSIM_REG_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
#define xSIM_REGDEV_MAX         5           //Max Reg Device
#define xSIM_REG_LOG_CAPACITY   4096        //4KB

//[Enum Declare]
//Attribute
typedef enum _xSIM_ATTR
{
  xSIM_ATTR_RO                = 0,          //Read  Only
  xSIM_ATTR_WO                = 1,          //Write Only
  xSIM_ATTR_WR                = 2,          //Read and Write
} xSIM_ATTR;


//Type
typedef enum _xSIM_TYPE
{
  xSIM_TYPE_REGUALR           = 0,          //Regular Type
  xSIM_TYPE_ONESHOT           = 1,          //One Shot Value
  xSIM_TYPE_RANDOM            = 2,          //Random Value
} xSIM_TYPE;


//[Struct Declare]
//Reg
typedef struct _xSim_Reg
{
  U32             Reg;                      //Register
  U32             Value;                    //Value
  U8              En;                       //Enable
  xSIM_ATTR       Attr;                     //Attribute
  xSIM_TYPE       Type;                     //Type
  U32             Min;                      //Min Value
  U32             Max;                      //Max Value
} xSim_Reg;


//Reg Device
typedef struct _xSim_RegDevice
{
  U32             Addr;                     //Address
  xSim_Reg       *Table;                    //Table
  U32             Count;                    //Count
  U32             Stamp;                    //Stamp
} xSim_RegDevice;

//Simulate Reg Log
typedef struct _xSim_Reg_Log
{
  char           *Buf;                      //Buffer
  U32             Capacity;                 //Capacity
  U32             Size;                     //Used Size
} xSim_Reg_Log;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Regist
void xSim_RegDevice_Regist(U8 ID,U8 Addr,xSim_Reg *RegTable,U32 Count);
void xSim_RegDevice_UnRegist(U8 ID);
void xSim_Reg_Init(U8 LogEn);

//Operate
void xSim_RegWrite(U32 Addr,U32 Reg,U32 *Value,U32 Len);
void xSim_RegRead(U32 Addr,U32 Reg,U32 *Value,U32 Len);

//Set Data
void xSim_Reg_SetValue(U32 Addr,U32 Reg,U32 Value);
void xSim_Reg_SetRange(U32 Addr,U32 Reg,U32 Min,U32 Max);

//Dump
void xSim_Reg_Dump(const char *FileName);

#ifdef __cplusplus
}
#endif

#endif  //__XSIM_REG_H__
