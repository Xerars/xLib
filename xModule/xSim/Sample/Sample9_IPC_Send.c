//Demostrating How to Use the xSim_IPC Module to Simulate IPC Send

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
#include "xSim_IPC.h"
#include "xSim_Timer.h"

//Main Code
int main(int Argc,char **Argv)
{
  if(Argc < 2)
  {
    printf("Usage: %s <Command> [Arg1] [Arg2] ...\n",Argv[0]);
    printf("Example: %s Hello John\n",Argv[0]);
    printf("Example: %s LED 1\n",Argv[0]);
    printf("Example: %s Exit\n",Argv[0]);
    return 1;
  }

  printf("[Send]: Starting IPC Sender...\n");
  xSim_IPC_Init("Sender");

  char MsgBuf[xSIM_IPC_MSG_SIZE] = {0};
  int  CurLen = 0;
  for(int i = 1;i < Argc;i++)
  {
    int Remain = (int)sizeof(MsgBuf) - CurLen - 1;
    int Written = snprintf(MsgBuf + CurLen,Remain,"%s",Argv[i]);
    if(Written < 0 || Written >= Remain)
    {
      printf("[Send Error]: Message too long!\n");
      break;
    }
        
    CurLen += Written;
    if(i < Argc - 1)
    {
      if(CurLen < (int)sizeof(MsgBuf) - 1)
      {
        MsgBuf[CurLen++] = ' ';
        MsgBuf[CurLen]   = '\0';
      }
    }
  }

  printf("[Send]: Sending [%s] --> [Recv]...\n",MsgBuf);
  xSim_IPC_Send("Recv",MsgBuf);

  xSim_DelayMS(50);
  xSim_IPC_Destroy();
  printf("[Send]: Done.\n");
  return 0;
}
