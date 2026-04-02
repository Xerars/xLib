//[App Lib Include]
#include "Module.h"

//[Variable Declare]
int Round = 0;

///@Function: Calculate
///@Descript: Calculate X1 and X2
int Calculate(int X1,int X2)
{
  return (X1>X2)?(X1*X1+3*X2)-(X1-X2)
  				:(X2*X2+3*X1)-(X2-X1);
}


///@Function: PrintData
///@Descript: Print Input String
void PrintData(char *Str)
{
  printf("[DATA]:%s\n",Str);
}



///@Function: Slogan
///@Descript: Show Slogan
void Slogan(void)
{
  printf("Hello World\n"); 
}


///@Function: GetRound 
///@Descript: Get Round Data
int GetRound(void)
{
  Round++;
  return Round;
}

