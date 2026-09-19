//Demostrating How to Use the xSim_PWM Module to Simulate PWM

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xSim_PWM.h"
#include "xSim_Timer.h"


//[Macro Declare]
#define SIM_PWM_LOG           "./SIM_PWM_LOG.LOG"

//Main Code
int main(void)
{
  //Init
  xSim_PWM_Init(1);

  //Regist
  xSim_PWM_Regist(0,"MOTOR1",1,1000,50);
  xSim_PWM_Regist(1,"MOTOR2",0,5000,20);

  //Start
  xSim_PWM_Start(0);          xSim_DelayMS(150);
  xSim_PWM_Start(1);          xSim_DelayMS(150);

  //Set
  xSim_PWM_SetFreq(0,2000);   xSim_DelayMS(150);
  xSim_PWM_SetDuty(0,80);     xSim_DelayMS(150);
  xSim_PWM_SetEnable(1,1);    xSim_DelayMS(150);
  xSim_PWM_SetDuty(1,50);     xSim_DelayMS(150);

  //Stop
  xSim_PWM_Stop(0);           xSim_DelayMS(150);
  xSim_PWM_Stop(1);           xSim_DelayMS(150);

  //Dump
  xSim_PWM_Dump(SIM_PWM_LOG);
  xSim_PWM_Destroy();
  return 0;
}
