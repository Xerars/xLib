//Demostrating How to Use the xSim_CLI Module With Command

//[STD Lib Include]
#include <stdio.h>
#include <string.h>

//[POSIX Lib Include]
#include <unistd.h>

//[xLib Include]
#include "xSim.h"

//[Prototype Declare]
static void xSim_CMD_LED (int Argc,char **Argv);
static void xSim_CMD_STAT(int Argc,char **Argv);


//Main Code
int main(void)
{
  xSim_CLI_Init();
  xSim_CLI_Start();
  int i = 0;

  xSim_CLI_Regist("LED" ,xSim_CMD_LED ,"Control LED State(LED ON/OFF)");
  xSim_CLI_Regist("STAT",xSim_CMD_STAT,"Show Current Status");
  while(1)
  {
    printf(".");
    fflush(stdout);
    i++;

    if(i >= 20)
    {
      printf("\n");
      i = 0;
    }
    sleep(1);
  }
  return 0;
}



///@Function: xSim_CMD_LED
///@Descript: Callback Function to Handle LED Control Commands
static void xSim_CMD_LED(int Argc,char **Argv)
{
  if(Argc < 2)
  {
    printf("Usage: LED <ON/OFF>");
    return;
  }

  if(strcmp(Argv[1],"ON") == 0)
    printf("[LED]: ON\n");
  else if(strcmp(Argv[1],"OFF") == 0)
    printf("[LED]: OFF\n");
  else
    printf("Unknown Argument:[%s][%s]\n",Argv[0],Argv[1]);
}


///@Function: xSim_CMD_STAT
///@Descript: Callback Function to Display Current System Status
static void xSim_CMD_STAT(int Argc,char **Argv)
{
  xUNUSED(Argc);
  xUNUSED(Argv);
  printf("[STAT]: System is Running Normally!!\n");
}
