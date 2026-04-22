#ifndef __XTCA9555_H__  //__XTCA9555_H__
#define __XTCA9555_H__  //__XTCA9555_H__

//Author  : William Hsiao
//Descript: TCA9555 Device Driver
//Version : 1.0.0

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
//Slave ID
#define xTCA_SLAVE_ADDR(A2,A1,A0)       (0x20|(A2<<2)|(A1<<1)|(A0))       //Device Slave ID

#define xTCA_MAX_PIN                    16          //Max Pin Num


//[Register Map]
#define REG_TCA_IN_PORT0                0x00        //Input  Port 0
#define REG_TCA_IN_PORT1                0x01        //Input  Port 1
#define REG_TCA_OUT_PORT0               0x02        //Output Port 0
#define REG_TCA_OUT_PORT1               0x03        //Output Port 1
#define REG_TCA_POLAR_INV_PORT0         0x04        //Polarity Inversion Port 0
#define REG_TCA_POLAR_INV_PORT1         0x05        //Polarity Inversion Port 1
#define REG_TCA_CONF_PORT0              0x06        //Configuration Port 0
#define REG_TCA_CONF_PORT1              0x07        //Configuration Port 1

//[Enum Declare]
//Level
typedef enum _xTCA_LEVEL
{
  xTCA_LEVEL_LOW   = 0,           //Level Low
  xTCA_LEVEL_HIGH  = 1,           //Level High

} xTCA_LEVEL;

//Direct
typedef enum _xTCA_DIR
{
  xTCA_DIR_OUT    = 0,            //Output
  xTCA_DIR_IN     = 1,            //Input
} xTCA_DIR;

//Pin
typedef enum _xTCA_PIN
{
  //Port 0
  TCA_PIN_NONE    = 0x0000,       //None
  TCA_PIN_P00     = 0x0001,       //P0.0
  TCA_PIN_P01     = 0x0002,       //P0.1
  TCA_PIN_P02     = 0x0004,       //P0.2
  TCA_PIN_P03     = 0x0008,       //P0.3
  TCA_PIN_P04     = 0x0010,       //P0.4
  TCA_PIN_P05     = 0x0020,       //P0.5
  TCA_PIN_P06     = 0x0040,       //P0.6
  TCA_PIN_P07     = 0x0080,       //P0.7
  //Port 1
  TCA_PIN_P10     = 0x0100,       //P1.0
  TCA_PIN_P11     = 0x0200,       //P1.1
  TCA_PIN_P12     = 0x0400,       //P1.2
  TCA_PIN_P13     = 0x0800,       //P1.3
  TCA_PIN_P14     = 0x1000,       //P1.4
  TCA_PIN_P15     = 0x2000,       //P1.5
  TCA_PIN_P16     = 0x4000,       //P1.6
  TCA_PIN_P17     = 0x8000,       //P1.7
} xTCA_PIN;


//[Callback Function Declare]
typedef void (*xTCA_I2C_Write_CB)(U8 Addr,U8 Reg,U8 *pData,U32 Len);
typedef void (*xTCA_I2C_Read_CB) (U8 Addr,U8 Reg,U8 *pData,U32 Len);


//[Struct Declare]
typedef struct _xTCA_Port
{
  U8   I2C_ID;                    //I2C Dev ID
  U32  I2C_Speed;                 //I2C Speed
  xTCA_I2C_Write_CB Write;        //I2C Write Method
  xTCA_I2C_Read_CB  Read;         //I2C Read  Method
} xTCA_Port;


typedef struct _xTCA
{
  xTCA_Port Port;                 //TCA Port
  U16       Dir;                  //Direct Shadow
  U16       Inv;                  //Invert Shadow
  U16       Level;                //Lveel  Shadow
} xTCA;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Handle
xTCA* xTCA_GetHandle(void);
void  xTCA_SetHandle(xTCA *pTCA);

//Init
void xTCA_Init(xTCA *pTCA,xTCA_Port *Port);
void xTCA_Reset(void);

//Direct
void xTCA_SetDir(U16 Pin, xTCA_DIR Dir);

//Output
void xTCA_WritePin(U16 Pin,xTCA_LEVEL Level);
void xTCA_TogglePin(U16 Pin);

//Invert
U16 xTCA_ReadPort(void);
xTCA_LEVEL xTCA_ReadPin(xTCA_PIN Pin);

//Invert
void xTCA_SetInvert(U16 Pin,U8 Invert);

//I2C
void xTCA_I2C_Write(U8 Reg,U8 *pData,U32 Len);
void xTCA_I2C_Read(U8 Reg,U8 *pData,U32 Len);
#ifdef __cplusplus
}
#endif

#endif  //__XTCA9555_H__
