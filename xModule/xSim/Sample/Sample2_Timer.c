//Demostrating How to Use the xSim_Timer Module With Timer Event

//[STD Lib Include]
#include <stdio.h>

//[POSIX Lib Include]
#include <unistd.h>

//[xLib Include]
#include "xSim.h"

//[Prototype Declare]
void xSim_Timer_Event(void);

//[Variable Declare]
U32 gTick = 0;

int main(void)
{
  xSim_Timer_Init();
  xSim_SysTick_Init();
  xSim_Timer_Regist(xSim_Timer_Event);

  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_Delay(1);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_Delay(2);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_Delay(3);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayMS(1);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayMS(20);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayMS(300);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayUS(1);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayUS(20);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayUS(300);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());

  while(1);
  return 0;
}



///@Function: xSim_Timer_Event
///@Descript: Simulate Timer Interrupt Event Function
void xSim_Timer_Event(void)
{
  gTick++;
  if(gTick % 1000 == 0)
  {
    printf("[Timer]: 1000 Ticks Reached! gTick = %d\n",gTick);
    printf("Cur Tick: %d ms\n",xSim_GetSysTick());
    fflush(stdout);
  }
}