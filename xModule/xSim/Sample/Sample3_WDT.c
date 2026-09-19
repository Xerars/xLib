//Demostrating How to Use the xSim_WDT Module to Simulate WatchDog
#define _DEFAULT_SOURCE

//[STD Lib Include]
#include <stdio.h>

//[POSIX Lib Inlcude]
#include <unistd.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xSim_WDT.h"

//Main Code
int main(void)
{
  xSim_WDT_Init();
  xSim_WDT_Regist(2000);      //2s
  xSim_WDT_SetExit(1);        //Exit the Program
  xSim_WDT_SetEn(1);          //Enable

  printf("FEED DOG\n");
  for(U32 i=0;i<20;i++)
  {
    xSim_WDT_Feed();
    printf("FEED\n");
    usleep(500 * 1000);       //500ms
  }

  int Sec_Count = 0;
  printf("FUN DOG\n");
  while(1)
  {
    sleep(1);
    Sec_Count++;
    printf("[Main]: Waiting...(%d)\n",Sec_Count);
  }
  return 0;
}


