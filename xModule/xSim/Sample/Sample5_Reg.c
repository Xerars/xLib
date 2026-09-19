//Demostrating How to Use the xSim_Reg Module to Simulate Register

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xSim_Reg.h"
#include "xSim_Timer.h"

//[Macro Declare]
#define SIM_REG_LOG           "./SIM_REG_LOG.LOG"


//Sensor-1 Device
#define SENSOR1_I2C_ADDR      0x50      //I2C Device ID
#define SENSOR1_DEV_ID        0         //Device ID

//Sensor-1
#define REG_TEMP_DEV_ID       0x00      //[RO]
#define REG_TEMP_CTRL         0x01      //[RW]
#define REG_TEMP_DATA         0x02      //[RO]
#define REG_TEMP_ONESHOT      0x03      //[RW]
#define SENSOR1_REG_COUNT     (sizeof(SimSensor1) / sizeof(xSim_Reg))

//Sensor-2 Device
#define SENSOR2_I2C_ADDR      0x38      //I2C Device ID
#define SENSOR2_DEV_ID        1         //Device ID

//Sensor-2
#define REG_AMB_DEV_ID        0x00      //[RO]
#define REG_AMB_CONF          0x01      //[RW]
#define REG_AMB_HLIGHT        0x02      //[RO]
#define REG_AMB_LLIGHT        0x03      //[RO]
#define SENSOR2_REG_COUNT     (sizeof(SimSensor2) / sizeof(xSim_Reg))

//[Variable Declare]
static xSim_Reg SimSensor1[] = 
{
//     Reg            Value  En      Attr          Type          Min  Max
  { REG_TEMP_DEV_ID , 0x68,  1,  xSIM_ATTR_RO, xSIM_TYPE_REGUALR, 0, 0xFF},
  { REG_TEMP_CTRL   , 0x00,  1,  xSIM_ATTR_WR, xSIM_TYPE_REGUALR, 0, 0xFF},
  { REG_TEMP_DATA   , 25  ,  1,  xSIM_ATTR_RO, xSIM_TYPE_RANDOM,  0, 0xFF},
  { REG_TEMP_ONESHOT, 50  ,  1,  xSIM_ATTR_RO, xSIM_TYPE_RANDOM,  0, 64, },
};


static xSim_Reg SimSensor2[] = 
{
//     Reg           Value  En      Attr          Type          Min  Max 
  { REG_AMB_DEV_ID  , 0x33, 1,  xSIM_ATTR_RO, xSIM_TYPE_REGUALR, 0, 0xFF},
  { REG_AMB_CONF    , 0x02, 1,  xSIM_ATTR_WR, xSIM_TYPE_REGUALR, 0, 0x0F},
  { REG_AMB_HLIGHT  , 0x00, 1,  xSIM_ATTR_RO, xSIM_TYPE_RANDOM , 0, 0xFF},
  { REG_AMB_LLIGHT  , 0x00, 1,  xSIM_ATTR_RO, xSIM_TYPE_RANDOM , 0, 0xFF},
};

//Main Code
int main(void)
{
  //Initial
  xSim_Reg_Init(1);   //Enable Log

  //Regist
  xSim_RegDevice_Regist(SENSOR1_DEV_ID,
                        SENSOR1_I2C_ADDR,
                        SimSensor1,
                        SENSOR1_REG_COUNT);
  xSim_RegDevice_Regist(SENSOR2_DEV_ID,
                        SENSOR2_I2C_ADDR,
                        SimSensor2,
                        SENSOR2_REG_COUNT);
  U32 rValue = 0;
  U32 wValue = 0;
  //Sensor-1 Operate
  printf("\n[1]\n");  xSim_DelayMS(100);
  xSim_RegRead (SENSOR1_I2C_ADDR,REG_TEMP_DEV_ID,&rValue,1);
  xSim_RegWrite(SENSOR1_I2C_ADDR,REG_TEMP_DEV_ID,&wValue,1);    //Write(Fault Operate)

  printf("\n[2]\n");  xSim_DelayMS(100);
  wValue = 0x15;
  xSim_RegRead (SENSOR1_I2C_ADDR,REG_TEMP_CTRL,&rValue,1);
  xSim_RegWrite(SENSOR1_I2C_ADDR,REG_TEMP_CTRL,&wValue,1);
  xSim_RegRead (SENSOR1_I2C_ADDR,REG_TEMP_CTRL,&rValue,1);

  printf("\n[3]\n");  xSim_DelayMS(100);
  for(int i=0;i<5;i++)
      xSim_RegRead(SENSOR1_I2C_ADDR,REG_TEMP_DATA,&rValue,1);

  printf("\n[4]\n");  xSim_DelayMS(100);
  xSim_Reg_SetValue(SENSOR1_I2C_ADDR,REG_TEMP_ONESHOT,0x11);      //Test Set Value
  xSim_RegRead(SENSOR1_I2C_ADDR,REG_TEMP_ONESHOT,&rValue,1);

  printf("\n[5]\n");  xSim_DelayMS(100);
  xSim_Reg_SetRange(SENSOR1_I2C_ADDR,REG_TEMP_ONESHOT,0x30,0x40); //Test Set Range
  for(int i=0;i<5;i++)
      xSim_RegRead(SENSOR1_I2C_ADDR,REG_TEMP_ONESHOT,&rValue,1);


  //Sensor-2 Operate
  printf("\n[6]\n");  xSim_DelayMS(100);
  xSim_RegRead (SENSOR2_I2C_ADDR,REG_AMB_DEV_ID,&rValue,1);
  xSim_RegWrite(SENSOR2_I2C_ADDR,REG_AMB_DEV_ID,&wValue,1);       //Write(Fault Operate)

  printf("\n[7]\n");  xSim_DelayMS(100);
  xSim_RegRead (SENSOR2_I2C_ADDR,REG_AMB_CONF,&rValue,1);
  xSim_RegWrite(SENSOR2_I2C_ADDR,REG_AMB_CONF,&wValue,1);
  xSim_RegRead (SENSOR2_I2C_ADDR,REG_AMB_CONF,&rValue,1);

  U32 r2Value[2] = {0};
  printf("\n[8]\n");  xSim_DelayMS(100);
  for(int i=0;i<5;i++)
    xSim_RegRead(SENSOR2_I2C_ADDR,REG_AMB_HLIGHT,r2Value,2);      //Test Read N-Byte

  //Dump
  xSim_Reg_Dump(SIM_REG_LOG);    //Dump

  //UnRegist
  xSim_RegDevice_UnRegist(SENSOR1_DEV_ID);
  xSim_RegDevice_UnRegist(SENSOR2_DEV_ID);
  return 0;
}
