#define _POSIX_C_SOURCE 200809L

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[POSIX Lib Include]
#include <unistd.h>
#include <sys/select.h>

//[xLib Include]
#include "xSim_CLI.h"

//[Prototype Declare]
static void* xSim_CLI_Task(void *Arg);
static void _Run_Command(char *CmdLine);
static void xSim_CLI_Help(int Argc,char **Argv);
static void _MutexLock(void);
static void _MutexUnLock(void);

//[Variable Declare]
static xSim_CLI gSim_CLI    = {0};
static U8       gSim_Inited = 0;


///@Function: xSim_CLI_Init
///@Descript: Initialize CLI Control Block and Register Built-In Commands
void xSim_CLI_Init(void)
{
  if(gSim_Inited == 0)
  {
    memset(&gSim_CLI,0,sizeof(xSim_CLI));
    gSim_CLI.IsRun = 0;

    //Create Mutex
    pthread_mutex_init(&gSim_CLI.Lock,NULL);

    char *HELP_Cmd  = "HELP";
    char *HELP_Desc = "Show All Registered Commands";
    xSim_CLI_Regist(HELP_Cmd,xSim_CLI_Help,HELP_Desc);     //Regist Help Command(First Command)

    //Create Task
    pthread_attr_t Attr;
    pthread_attr_init(&Attr);
    pthread_attr_setdetachstate(&Attr,PTHREAD_CREATE_DETACHED);
    U32 Ret = pthread_create(&gSim_CLI.TaskID,&Attr,xSim_CLI_Task,NULL);
    if(Ret != 0)
    {
      pthread_mutex_destroy(&gSim_CLI.Lock);
      return;
    }
    pthread_attr_destroy(&Attr);    //Attribute Destroy
    gSim_Inited = 1;
  }
}


///@Function: xSim_CLI_Start
///@Descript: Enable Command Processing Flag
void xSim_CLI_Start(void)
{
  _MutexLock();
  if(gSim_CLI.IsRun == 0)
  {
    gSim_CLI.IsRun = 1;
    printf("[xSim]: CLI Start...\n");
  }
  _MutexUnLock();
}


///@Function: xSim_CLI_Stop
///@Descript: Disable Command Processing Flag
void xSim_CLI_Stop(void)
{
  _MutexLock();
  if(gSim_CLI.IsRun == 1)
  {
    gSim_CLI.IsRun = 0;
    printf("[xSim]: CLI Stop...\n");
  }
  _MutexUnLock();
}


///@Function: xSim_CLI_IsRun
///@Descript: 
U8 xSim_CLI_IsRun(void)
{
  _MutexLock();
  U8 State = gSim_CLI.IsRun;
  _MutexUnLock();
  return State;
}


///@Function: 
///@Descript: 
void xSim_CLI_Regist(CCHAR *Cmd,xSim_CLI_CmdCB CB,CCHAR *Help)
{
  if(Cmd == NULL || CB == NULL)
    return;

  _MutexLock();
  //Check Duplicate Registration
  for(U32 i=0;i<gSim_CLI.nCmd;i++)
    if(gSim_CLI.CmdTable[i].Cmd != NULL && strcmp(gSim_CLI.CmdTable[i].Cmd,Cmd) == 0)
    {
      _MutexUnLock();
      return;
    }

  //Find First Empty Slot
  int FreeIdx = -1;
  for(int i = 0;i < xSIM_CLI_CMD_MAX;i++)
    if(gSim_CLI.CmdTable[i].Cmd == NULL)
    {
      FreeIdx = i;
      break;
    }

  if(FreeIdx == -1)
  {
    _MutexUnLock();
    return;   //Table is full
  }

  //Regist Entry
  gSim_CLI.CmdTable[gSim_CLI.nCmd].Cmd  = Cmd;
  gSim_CLI.CmdTable[gSim_CLI.nCmd].CB   = CB;
  gSim_CLI.CmdTable[gSim_CLI.nCmd].Help = Help;
  gSim_CLI.nCmd++;
  _MutexUnLock();
}


///@Function: xSim_CLI_UnRegist
///@Descript: 
void xSim_CLI_UnRegist(CCHAR *Cmd)
{
  if(Cmd == NULL)
    return;

  _MutexLock();
  for(U32 i = 0;i < xSIM_CLI_CMD_MAX;i++)
    if(gSim_CLI.CmdTable[i].Cmd != NULL && strcmp(gSim_CLI.CmdTable[i].Cmd,Cmd) == 0)
    {
      //Clear Slot Pointers to NULL(Create a ReUsable Hole)
      gSim_CLI.CmdTable[i].Cmd  = NULL;
      gSim_CLI.CmdTable[i].CB   = NULL;
      gSim_CLI.CmdTable[i].Help = NULL;
      
      if(gSim_CLI.nCmd > 0)
        gSim_CLI.nCmd--;
      break;
    }
  _MutexUnLock();
}


///@Function: xSim_CLI_Task
///@Descript: 
static void* xSim_CLI_Task(void *Arg)
{
  xUNUSED(Arg);
  char Buf[xSIM_CLI_BUF_SIZE] = {0};

  while(1)
  {
    fd_set FDS;
    struct timeval TV;

    FD_ZERO(&FDS);
    FD_SET(STDIN_FILENO,&FDS);

    //TimeOut 100ms for Thread Response
    TV.tv_sec  = 0;
    TV.tv_usec = 100000;    //100ms

    int Ret = select(STDIN_FILENO + 1,&FDS,NULL,NULL,&TV);
    if(Ret > 0 && FD_ISSET(STDIN_FILENO,&FDS))
      if(fgets(Buf,sizeof(Buf),stdin) != NULL)
        if(xSim_CLI_IsRun())
        {
          Buf[strcspn(Buf,"\r\n")] = '\0';    //Strip Tailing NewLine
          if(strlen(Buf) > 0)
            _Run_Command(Buf);
        }
  }
  return NULL;
}


///@Function: _Run_Command
///@Descript: Parse Input Line into Argc/Argv and Dispatch Callback
static void _Run_Command(char *CmdLine)
{
  int   Argc = 0;
  char *Argv[xSIM_CLI_ARGV_MAX] = {NULL};

  //Parse String With Space/Tab Delimiters
  char *Token = strtok(CmdLine," \t");
  while(Token != NULL && Argc < xSIM_CLI_ARGV_MAX)
  {
    Argv[Argc++] = Token;
    Token = strtok(NULL,"\t");
  }

  if(Argc == 0)
    return;
  _MutexLock();
  //Search Command Table
  for(U32 i = 0;i<gSim_CLI.nCmd;i++)
    if(strcmp(gSim_CLI.CmdTable[i].Cmd,Argv[0]) == 0)
    {
      if(gSim_CLI.CmdTable[i].CB != NULL)
        gSim_CLI.CmdTable[i].CB(Argc,Argv);
       _MutexUnLock();
      return;
    }
  _MutexUnLock();
  printf("Unknow Command: %s\n",Argv[0]);
}


///@Function: xSim_CLI_Help
///@Descript: Built-In Callback for Help Command
static void xSim_CLI_Help(int Argc,char **Argv)
{
  xUNUSED(Argc);
  xUNUSED(Argv);

  printf("\n----- Registered Command List -----\n");
  for(U32 i=0;i<gSim_CLI.nCmd;i++)
    if(gSim_CLI.CmdTable[i].Cmd != NULL)
      printf("[%-12s]: %s\n",gSim_CLI.CmdTable[i].Cmd,gSim_CLI.CmdTable[i].Help);
  printf("-------------------------------------\n\n");
}


///@Function: _MutexLock
///@Descript: Acquire the CLI Mutex Lock
static void _MutexLock(void)
{
  pthread_mutex_lock(&gSim_CLI.Lock);
}


///@Function: _MutexUnLock
///@Descript: Release the CLI Mutex Lock
static void _MutexUnLock(void)
{
  pthread_mutex_unlock(&gSim_CLI.Lock);
}
