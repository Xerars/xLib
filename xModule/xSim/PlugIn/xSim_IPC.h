#ifndef __XSIM_IPC_H__  //__XSIM_IPC_H__
#define __XSIM_IPC_H__  //__XSIM_IPC_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[Macro Declare]
#define xSIM_IPC_NAME             "./xSIM_IPC_QUEUE"    //POSIX MsgQue

#define xSIM_IPC_NAME_SIZE        32                    //Max Module Name Size
#define xSIM_IPC_MSG_SIZE         256                   //Max Size Per Message
#define xSIM_IPC_MSG_MAX          10                    //Max Message in Queue
#define xSIM_IPC_CMD_MAX          32                    //Max Register Command
#define xSIM_IPC_ARGV_MAX         16                    //Max Num of Command Parameter


//[Callback Function Declare]
typedef void (*xSim_IPC_CmdCB)(int Argc,char **Argv);


//[Struct Declare]
//IPC Command
typedef struct _xSim_IPC_Cmd
{
  CCHAR          *Cmd;                                  //Command Name
  xSim_IPC_CmdCB  CB;                                   //Callback Function
  CCHAR          *Help;                                 //Help Description
} xSim_IPC_Cmd;


//IPC
typedef struct _xSim_IPC
{
  int             ID;                                   //Message Queue Descriptor
  char            Module[xSIM_IPC_NAME_SIZE];           //Module Name
  char            QueuePath[64];                        //Message Queue Path
  xSim_IPC_Cmd    CmdTable[xSIM_IPC_CMD_MAX];           //Command Registation Table
  U32             nCmd;                                 //Num of Register Command
  U8              IsRun;                                //Is Running Flag
} xSim_IPC;


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Init
void xSim_IPC_Init(CCHAR *Module);
void xSim_IPC_Destroy(void);
void xSim_IPC_Start(void);
void xSim_IPC_Stop(void);
U8   xSim_IPC_IsRun(void);

//Regist
void xSim_IPC_Regist(CCHAR *Cmd,xSim_IPC_CmdCB CB,CCHAR *Help);
void xSim_IPC_UnRegist(CCHAR *Cmd);

//Send/Recv
void xSim_IPC_Service(void);
void xSim_IPC_Send(CCHAR *Module,CCHAR *Msg);

#ifdef __cplusplus
}
#endif

#endif  //__XSIM_IPC_H__
