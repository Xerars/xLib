#define _POSIX_C_SOURCE   200809L

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[POSIX Lib Include]
#include "fcntl.h"
#include "mqueue.h"
#include "errno.h"
#include "unistd.h"
#include "sys/stat.h"

//[xLib Include]
#include "xSim_IPC.h"

//[Prototype Declare]
static void _Run_Command(char *CmdLine);


//[Variable Declare]
static xSim_IPC   gSim_IPC    = {0};
static U8         gSim_Inited = 0;


///@Function: xSim_IPC_Init
///@Descript: 
void xSim_IPC_Init(CCHAR *Module)
{
  if(gSim_Inited == 1)
    return;

  memset(&gSim_IPC,0,sizeof(xSim_IPC));
  (Module != NULL && strlen(Module) > 0)? snprintf(gSim_IPC.Module,sizeof(gSim_IPC.Module),"%s",Module)
                                        : snprintf(gSim_IPC.Module,sizeof(gSim_IPC.Module),"%s","DEFAULT");
  snprintf(gSim_IPC.QueuePath,sizeof(gSim_IPC.QueuePath),"/xSIM_IPC_%s",gSim_IPC.Module);
  //Setup Message Queue Attribute
  struct mq_attr Attr;
  Attr.mq_flags   = 0;
  Attr.mq_maxmsg  = xSIM_IPC_MSG_MAX;
  Attr.mq_msgsize = xSIM_IPC_MSG_SIZE;
  Attr.mq_curmsgs = 0;

  //Open/Create Message Queue With Non-Block Read Option
  gSim_IPC.ID = mq_open(gSim_IPC.QueuePath,O_CREAT | O_RDWR | O_NONBLOCK,0644,&Attr);
  if(gSim_IPC.ID == (mqd_t)-1)
    perror("[xSim]: OPC MQ_Open Failed!!\n");
  gSim_Inited = 1;
}


///@Function: xSim_IPC_Destroy
///@Descript: Clean Up Messaeg Queue and Resource
void xSim_IPC_Destroy(void)
{
  if(gSim_Inited == 0)
    return;

  xSim_IPC_Stop();
  if(gSim_IPC.ID != (mqd_t)-1)
  {
    mq_close(gSim_IPC.ID);
    mq_unlink(gSim_IPC.QueuePath);
    gSim_IPC.ID = -1;
  }
  gSim_Inited = 0;
}


///@Function: xSim_IPC_Regist
///@Descript: Regist Command and Callback Function for IPC
void xSim_IPC_Regist(CCHAR *Cmd,xSim_IPC_CmdCB CB,CCHAR *Help)
{
  if(Cmd == NULL || CB == NULL)
    return;
  
  //Check Duplicate
  for(U32 i=0;i<gSim_IPC.nCmd;i++)
    if(gSim_IPC.CmdTable[i].Cmd != NULL && strcmp(gSim_IPC.CmdTable[i].Cmd,Cmd) == 0)
      return;
  
  //Find Free Slot
  int FreeIdx = -1;
  for(int i = 0;i<xSIM_IPC_CMD_MAX;i++)
    if(gSim_IPC.CmdTable[i].Cmd == NULL)
    {
      FreeIdx = i;
      break;
    }
  
  if(FreeIdx == -1)
    return;     //Table is Full

  gSim_IPC.CmdTable[FreeIdx].Cmd  = Cmd;
  gSim_IPC.CmdTable[FreeIdx].CB   = CB;
  gSim_IPC.CmdTable[FreeIdx].Help = Help;
  gSim_IPC.nCmd++;
}


///@Function: xSim_IPC_UnRegist
///@Descript: UnRegist Command for IPC Table
void xSim_IPC_UnRegist(CCHAR *Cmd)
{
  if(Cmd == NULL)
    return;

  for(U32 i = 0;i<xSIM_IPC_CMD_MAX;i++)
    if(gSim_IPC.CmdTable[i].Cmd != NULL && strcmp(gSim_IPC.CmdTable[i].Cmd,Cmd) == 0)
    {
      gSim_IPC.CmdTable[i].Cmd  = NULL;
      gSim_IPC.CmdTable[i].CB   = NULL;
      gSim_IPC.CmdTable[i].Help = NULL;
      if(gSim_IPC.nCmd > 0)
        gSim_IPC.nCmd--;
      break;
    }
}


///@Function: xSim_IPC_Start
///@Descript: Enable IPC Processing Flag
void xSim_IPC_Start(void)
{
  gSim_IPC.IsRun = 1;
}


///@Function: xSim_IPC_Stop
///@Descript: Disable IPC Processing Flag
void xSim_IPC_Stop(void)
{
  gSim_IPC.IsRun = 0;
}


///@Function: xSim_IPC_IsRun
///@Descript: Check If IPC is Run
U8 xSim_IPC_IsRun(void)
{
  return gSim_IPC.IsRun;
}


///@Function: xSim_IPC_Service
///@Descript: IPC Service Function to be Called Inside While Loop
void xSim_IPC_Service(void)
{
  if(!gSim_IPC.IsRun)
    return;
  
  char Buf[xSIM_IPC_MSG_SIZE] = {0};
  ssize_t rByte = mq_receive(gSim_IPC.ID,Buf,xSIM_IPC_MSG_SIZE,NULL);
  if(rByte >= 0)
  {
    Buf[rByte] = '\0';
    if(strlen(Buf) > 0)
      _Run_Command(Buf);
  }
}


///@Function: xSim_IPC_Send
///@Descript: Send a Command String to Specific Target Module
void xSim_IPC_Send(CCHAR *Module,CCHAR *Msg)
{
  if(Module == NULL || Msg == NULL || strlen(Msg) == 0)
    return;

  char Path[64] = {0};
  snprintf(Path,sizeof(Path),"/xSIM_IPC_%s",Module);
  
  //Open Module for Writting
  mqd_t Send = mq_open(Path,O_WRONLY);
  if(Send == (mqd_t)-1)
    perror("[xSim]: IPC MQ_Open Send Fail!!\n");

  int Ret = mq_send(Send,Msg,strlen(Msg)+1,0);
  mq_close(Send);

  if(Ret == -1)
    perror("[xSim]: IPC MQ_Send Failed!!\n");
}


///@Function: _Run_Command
///@Descript: Parse Input Line Into Argc/Argv and Dispatch Registered Callback Function
static void _Run_Command(char *CmdLine)
{
  int   Argc = 0;
  char *Argv[xSIM_IPC_ARGV_MAX] = {NULL};
  
  char *Token = strtok(CmdLine," \t");
  while(Token != NULL && Argc < xSIM_IPC_ARGV_MAX)
  {
    Argv[Argc++] = Token;
    Token = strtok(NULL, " \t");
  }

  if(Argc == 0)
    return;
  
  //Search Command Table
  for(U32 i = 0;i < xSIM_IPC_CMD_MAX;i++)
    if(gSim_IPC.CmdTable[i].Cmd != NULL && strcmp(gSim_IPC.CmdTable[i].Cmd,Argv[0]) == 0)
    {
      if(gSim_IPC.CmdTable[i].CB != NULL)
        gSim_IPC.CmdTable[i].CB(Argc,Argv);
      return;
    }
  printf("[%s]: Unknown IPC Command: %s\n",gSim_IPC.Module,Argv[0]);
}