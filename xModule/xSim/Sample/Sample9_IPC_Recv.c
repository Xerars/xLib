//Demostrating How to Use the xSim_IPC Module to Simulate IPC Receive

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[Posix Lib Include]
#include <unistd.h>

//[xLib Include]
#include "xSim_IPC.h"
#include "xSim_Timer.h"


//[Prototype Declare]
void Cmd_Hello_CB(int Argc,char **Argv);
void Cmd_LED_CB  (int Argc,char **Argv);
void Cmd_Exit_CB (int Argc,char **Argv);


//[Variable Declare]
static volatile int gRun = 1;

//Main Code
int main(void)
{
  xSim_IPC_Init("Recv");

  xSim_IPC_Regist("Hello",Cmd_Hello_CB,"Print Greeting: Hello [Name]");
  xSim_IPC_Regist("LED"  ,Cmd_LED_CB  ,"Control LED: LED [1/0]");
  xSim_IPC_Regist("Exit" ,Cmd_Exit_CB ,"Exit the Receiver Program");
  xSim_IPC_Start();
  while(gRun && xSim_IPC_IsRun())
  {
    xSim_DelayMS(10);
    xSim_IPC_Service();
  }

  printf("[Recv]: Stop IPC Service...\n");
  xSim_IPC_Stop();
  xSim_IPC_Destroy();
  printf("[Recv]: Terminated Safely\n");
  return 0;
}


///@Function: Cmd_Hello_CB
///@Descript: Execute Hello Callback Function
void Cmd_Hello_CB(int Argc,char **Argv)
{
  for(int i=0;i<Argc;i++)
    printf("Argv[%d] = %s\n",i,Argv[i]);
}


///@Function: Cmd_LED_CB
///@Descript: Execute LED Callback Function
void Cmd_LED_CB(int Argc,char **Argv)
{
  if(Argc > 1)
  {
    if(strcmp(Argv[1],"1") == 0)
      printf("[Recv]: LED On\n");
    else if(strcmp(Argv[1],"0") == 0)
      printf("[Recv]: LED Off\n");
    else
      printf("[Recv]: Unknow Argument: %s\n",Argv[1]);
  }
}


///@Function: Cmd_Exit_CB
///@Descript: Execute Exit Callback Function
void Cmd_Exit_CB(int Argc,char **Argv)
{
  xUNUSED(Argc);
  xUNUSED(Argv);
  printf("[Recv]: Exit CMD Received. (ShutDown Now)...\n");
  gRun = 0;
}
