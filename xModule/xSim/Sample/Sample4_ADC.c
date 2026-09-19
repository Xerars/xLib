//Demostrating How to Use the xSim_ADC Module to Simulate ADC
#define _DEFAULT_SOURCE

//[STD Lib Include]
#include <stdio.h>

//[POSIX Lib Include]
#include <unistd.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xSim.h"

//[Macro Declare]
#define SIM_ADC_LOG           "./SIM_ADC_LOG.LOG"

//Main Code
int main(void)
{
  xSim_ADC_Init(1);
  xSim_ADC_Regist(0,8);      //CH0: 8-bit  (0 ~ 255)
  xSim_ADC_Regist(1,12);     //CH1: 12-bit (0 ~ 4095)
  xSim_ADC_Regist(2,24);     //CH2: 24-bit (0 ~ 16777215)
  xSim_ADC_Regist(3,32);     //CH3: 32-bit (0 ~ 4294967295)
  printf("[ADC]: Regist Channel CH0(8B),CH1(12B),CH2(24B),CH3(32B)\n");

  printf("[ADC]:Get Value\n");
  for(U8 Ch = 0;Ch < 4;Ch++)
  {
    printf("----------- Read CH%d (10 Times) -----------\n",Ch);
    for(int i = 0;i < 10;i++)
    {
      xSim_ADC_GetValue(Ch);
      usleep(10 * 1000);        //10ms Delay
    }
  }

  //Set Value
  printf("\n[ADC]: Set Value\n");
  U32 TEST_Value[] = {1111,2222,3333};
  for(int i = 0;i < 3;i++)
  {
    xSim_ADC_SetValue(1,TEST_Value[i]);
    printf("[V] ");
    xSim_ADC_GetValue(1);
    xSim_ADC_GetValue(1);
    usleep(10 * 1000); 
  }

  //Limit Range
  printf("\n[ADC]: Limit Range(1500~1800)\n");
  xSim_ADC_SetRange(1,1500,1800);
  for(int i = 0;i < 10;i++)
  {
    xSim_ADC_GetValue(1);
    usleep(10 * 1000); 
  }

  xSim_ADC_Dump(SIM_ADC_LOG);   //Dump
  return 0;
}
