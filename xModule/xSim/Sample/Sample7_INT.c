
//Demostrating How to Use the xSim_INT Module to Simulate Interrupt

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xSim_INT.h"
#include "xSim_Timer.h"


//[Macro Declare]
#define SIM_INT_LOG           "./SIM_INT_LOG.LOG"


//[Prototype Declare]
void Button1_ISR(U8 Channel,U8 Level);
void Button2_ISR(U8 Channel,U8 Level);


//Main Code
int main(void)
{
  //Init
  xSim_INT_Init(1);

  //Regist
  xSim_INT_Regist(0,"INT1",xSIM_INT_EDGE_RISING,Button1_ISR);
  xSim_INT_Regist(1,"INT2",xSIM_INT_EDGE_BOTH  ,Button2_ISR);

  //Set Interrupt
  xSim_INT_SetTrigger(0,1);     xSim_DelayMS(100);
  xSim_INT_SetTrigger(0,0);     xSim_DelayMS(100);
  xSim_INT_SetTrigger(1,1);     xSim_DelayMS(100);
  xSim_INT_SetTrigger(1,0);     xSim_DelayMS(100);

  //Set Edge
  xSim_INT_SetEdge(0,xSIM_INT_EDGE_FALLING);
  xSim_INT_SetTrigger(0,1);     xSim_DelayMS(100);
  xSim_INT_SetTrigger(0,0);     xSim_DelayMS(100);

  //Dump
  xSim_INT_Dump(SIM_INT_LOG);
  xSim_INT_Destroy();
  return 0;
}


///@Function: Button1_ISR
///@Descript: Button 1 Interrupt Service Routine
void Button1_ISR(U8 Channel,U8 Level)
{
  printf("   >>> [ISR Callback Triggered] Channel: %d, Level: %d <<<\n",Channel,Level);
}



///@Function: Button2_ISR
///@Descript: Button2 Interrupt Service Routine
void Button2_ISR(U8 Channel,U8 Level)
{
  printf("   >>> [ISR Callback Triggered] Channel: %d, Level: %d <<<\n",Channel,Level);
}