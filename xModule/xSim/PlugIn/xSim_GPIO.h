#ifndef __XSIM_GPIO_H__ //__XSIM_GPIO_H__
#define __XSIM_GPIO_H__ //__XSIM_GPIO_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
//GPIO Table Size
#define xSIM_GPI_MAX              20        //GPI Max Table Size
#define xSIM_GPO_MAX              20        //GPO Max Table Size

//GPIO Name Size
#define xSIM_GPIO_NAME_SIZE       32        //GPIO Name Size

//GPIO Log Capacity
#define xSIM_GPIO_LOG_CAPACITY    4096      //4KB


//[Enum Declare]
//GPIO Status
typedef enum _xSIM_GPIO_STATE
{
  xSIM_GPIO_OFF                 = 0,        //GPIO Off
  xSIM_GPIO_ON                  = 1,        //GPIO On
} xSIM_GPIO_STATE;


//GPIO Direction
typedef enum _xSIM_GPIO_DIR
{
  xSIM_GPIO_DIR_IN              = 0,        //Direction: Input
  xSIM_GPIO_DIR_OUT             = 1,        //Direction: Output
} xSIM_GPIO_DIR;


//[Struct Declare]
//GPIO Output
typedef struct _xSim_GPI
{
  char  Name[xSIM_GPIO_NAME_SIZE];          //GPIO In Name
  U8    Dir;                                //GPIO In Direction
  U8    ID;                                 //GPIO In ID
  U8    Used;                               //GPIO In Used
  U8    Status;                             //GPIO In Status
  U8    Last;                               //GPIO In Last Status
  U32   Stamp;                              //GPIO In Stamp
} xSim_GPI;


//GPIO Output
typedef struct _xSim_GPO
{
  char  Name[xSIM_GPIO_NAME_SIZE];          //GPIO Out Name
  U8    Dir;                                //GPIO Out Direction
  U8    ID;                                 //GPIO Out ID
  U8    Used;                               //GPIO Out Used
  U8    Status;                             //GPIO Out Status
  U32   Stamp;                              //GPIO Out Stamp
} xSim_GPO;


//GPIO Log
typedef struct _xSim_GPIO_Log
{
  char *Buf;                                //GPIO Buffer
  U32   Capacity;                           //GPIO Capacity
  U32   Size;                               //GPIO Size
} xSim_GPIO_Log;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Configure
void xSim_GPI_Regist(U8 ID,CCHAR *Name);
void xSim_GPO_Regist(U8 ID,CCHAR *Name);
void xSim_GPI_UnRegist(U8 ID);
void xSim_GPO_UnRegist(U8 ID);
void xSim_GPIO_Init(U8 LogEn);

//Control
void xSim_GPI_Set(U8 ID,U8 Level);
U8   xSim_GPI_Read(U8 ID);
void xSim_GPO_Write(U8 ID,U8 Level);

//Dump
void xSim_GPIO_Dump(CCHAR *FileName);

#ifdef __cplusplus
}
#endif

#endif  //__XSIM_GPIO_H__
