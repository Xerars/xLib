//Demostrating How to Use the xSim_GPIO Module to Simulate GPIO

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//[xLib Include]
#include "xSim_GPIO.h"
#include "xSim_Timer.h"

//[Macro Declare]
#define SIM_GPIO_LOG           "./SIM_GPIO_LOG.LOG"

//Main Code
int main(void)
{
  //Init
  xSim_GPIO_Init(1);

  //Regist
  xSim_GPI_Regist(0,"BTN1");
  xSim_GPI_Regist(1,"BTN2");
  xSim_GPO_Regist(0,"LED1");
  xSim_GPO_Regist(1,"LED2");

  //TEST GPIO Output
  printf("\nTEST GPO Output\n");
  xSim_GPO_Write(0,xSIM_GPIO_ON);  xSim_DelayMS(100);
  xSim_GPO_Write(1,xSIM_GPIO_ON);  xSim_DelayMS(100);
  xSim_GPO_Write(0,xSIM_GPIO_OFF);
  xSim_GPO_Write(1,xSIM_GPIO_OFF);

  //TEST GPIO Input
  xSim_GPI_Set(0,1);    //Set High
  xSim_GPI_Read(0);
  xSim_DelayMS(150);
  xSim_GPI_Set(1,1);    //Set High
  xSim_GPI_Read(1);
  xSim_DelayMS(150);
  xSim_GPI_Set(0,0);    //Set Low
  xSim_GPI_Read(0);

  U32 Delay = 0;
  for(U32 i=0;i<10;i++)
  {
    xSim_GPO_Write(0,i%2);
    Delay = (rand() % 500) + 1;
    xSim_DelayMS(Delay);
  }

  xSim_GPIO_Dump(SIM_GPIO_LOG);
  return 0;
}