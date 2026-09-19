#ifndef __XSIM_CLI_H__  //__XSIM_CLI_H__
#define __XSIM_CLI_H__  //__XSIM_CLI_H__

//[Posix Lib Include]
#include <pthread.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
#define xSIM_CLI_CMD_MAX          32        //Max Num of Command
#define xSIM_CLI_ARGV_MAX         16        //Max Num of Command Parameter
#define xSIM_CLI_BUF_SIZE         256       //CLI Buffer Size


//[Callback Function Declare]
typedef void (*xSim_CLI_CmdCB)  (int Argc,char **Argv);

//[Struct Declare]
//CLI Cmd
typedef struct _xSim_CLI_Cmd
{
  CCHAR          *Cmd;                      //Command
  xSim_CLI_CmdCB  CB;                       //Callback Function
  CCHAR          *Help;                     //Help Function
} xSim_CLI_Cmd;


//CLI
typedef struct _xSim_CLI
{
  xSim_CLI_Cmd    CmdTable[xSIM_CLI_CMD_MAX];   //Table
  U32             nCmd;                     //Num of Regist Command
  U8              IsRun;                    //Is Running
  pthread_t       TaskID;                   //Task ID
  pthread_mutex_t Lock;                     //Mutex
} xSim_CLI;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Init
void xSim_CLI_Init(void);
void xSim_CLI_Start(void);
void xSim_CLI_Stop(void);
U8   xSim_CLI_IsRun(void);

//Regist
void xSim_CLI_Regist(CCHAR *Cmd,xSim_CLI_CmdCB CB,CCHAR *Help);
void xSim_CLI_UnRegist(CCHAR *Cmd);

#ifdef __cplusplus
}
#endif

#endif  //__XSIM_CLI_H__
