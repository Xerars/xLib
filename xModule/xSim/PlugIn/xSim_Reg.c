#define _POSIX_C_SOURCE       199309L

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

//[xLib Include]
#include "xSim_Reg.h"


//[Prototype Declare]
static U32 _GetSysTick(void);
static xSim_RegDevice* xSim_FindDevice(U32 Addr);
static xSim_Reg* xSim_FindRegister(U32 Addr,U32 Reg);
static void _LogAppend(const char *Format,...);


//[Variable Declare]
static xSim_RegDevice  gDevTable[xSIM_REGDEV_MAX] = {0};
static xSim_Reg_Log    gReg_Log        = {NULL,0,0};
static U8              gReg_Log_Enable = 0;
static U8              gReg_Inited     = 0;
static U32             gReg_Tick_Start = 0;


///@Function: xSim_RegDevice_Regist
///@Descript: Register a Virtual Device Table to the Manager
void xSim_RegDevice_Regist(U8 ID,U8 Addr,xSim_Reg *RegTable,U32 Count)
{
  if(ID >= xSIM_REGDEV_MAX)
    return;

  gDevTable[ID].Addr  = Addr;
  gDevTable[ID].Table = RegTable;
  gDevTable[ID].Count = Count;
}


///@Function: xSim_RegDevice_UnRegist
///@Descript: UnRegister and Clear a Virtual Device Instance
void xSim_RegDevice_UnRegist(U8 ID)
{
  if(ID >= xSIM_REGDEV_MAX)
    return;
  
  gDevTable[ID].Addr   = 0;
  gDevTable[ID].Table  = NULL;
  gDevTable[ID].Count  = 0;  
}


///@Function: xSim_Reg_Init
///@Descript: Initialize the Register Simulator Module and Optional Log Buffer
void xSim_Reg_Init(U8 LogEn)
{
  if(gReg_Inited == 0)
  {
    srand((unsigned int)time(NULL));
    if(LogEn)
    {
      gReg_Log_Enable = 1;
      if(gReg_Log.Buf == NULL)
      {
        gReg_Log.Capacity = xSIM_REG_LOG_CAPACITY;       //4KB
        gReg_Log.Size     = 0;
        gReg_Log.Buf      = (char*)malloc(gReg_Log.Capacity);
        if(gReg_Log.Buf == NULL)
          return;
        gReg_Log.Buf[0] = '\0';
      }
    }
    gReg_Tick_Start = _GetSysTick();
    gReg_Inited     = 1;
  }
}


///@Function: xSim_RegWrite
///@Descript: Write Values to Target Register and Append Log
void xSim_RegWrite(U32 Addr,U32 Reg,U32 *Value,U32 Len)
{
  xSim_RegDevice *TargetDev = xSim_FindDevice(Addr);
  xSim_Reg *Target = xSim_FindRegister(Addr,Reg);
  if(Target == NULL)            return;     //Not Find   Register
  if(Value == NULL || Len == 0) return;     //Value is Valid

  TargetDev->Stamp = _GetSysTick() - gReg_Tick_Start;   //Update Stamp
  for(U32 i=0;i<Len;i++)
  {
    if(Target->En == 0)
      return;         //Not Enable Register
    switch(Target->Attr)
    {
      case xSIM_ATTR_RO:  return;
      case xSIM_ATTR_WO:
      case xSIM_ATTR_WR:
        if(Target->Type == xSIM_TYPE_REGUALR)
        {
          char Str[128] = {0};
          Target->Value = Value[i];
          snprintf(Str,sizeof(Str),"%8d::[I2C-%02XH]: [W][%02X] = %02X\n",TargetDev->Stamp,TargetDev->Addr
                                                                         ,Target->Reg,Target->Value);
          printf("%s", Str);
          if(gReg_Log_Enable)
            _LogAppend("%s",Str);
          Target++;
        }
        break;
      default:  return;
    }
  }
}


///@Function: xSim_RegRead
///@Descript: Read Values from Target Register and Append Log
void xSim_RegRead(U32 Addr,U32 Reg,U32 *Value,U32 Len)
{
  xSim_RegDevice *TargetDev = xSim_FindDevice(Addr);
  xSim_Reg *Target = xSim_FindRegister(Addr,Reg);
  if(Target == NULL)            return;     //Not Find   Register
  if(Value == NULL || Len == 0) return;     //Value is Valid

  TargetDev->Stamp = _GetSysTick() - gReg_Tick_Start;   //Update Stamp
  for(U32 i=0;i<Len;i++)
  {
    if(Target->En == 0)
      return;         //Not Enable Register
    switch(Target->Attr)
    {
      case xSIM_ATTR_WO:  return;
      case xSIM_ATTR_RO:
      case xSIM_ATTR_WR:
        switch(Target->Type)
        {
          case xSIM_TYPE_REGUALR:
            Value[i] = (Target->Max >= Target->Min)? Target->Value: Target->Min;
            break;
          case xSIM_TYPE_ONESHOT:
            Value[i] = (Target->Max >= Target->Min)? Target->Value: Target->Min;
            Target->Type = xSIM_TYPE_RANDOM;
            break;
          case xSIM_TYPE_RANDOM:
            Value[i] = (Target->Max >= Target->Min)? (Target->Min+(rand()%(Target->Max-Target->Min+1))): (Target->Min);
            break;
          default:  break;
        }
        
        char Str[128] = {0};
        snprintf(Str,sizeof(Str),"%8d::[I2C-%02XH]: [R][%02X] = %02X\n",TargetDev->Stamp,TargetDev->Addr
                                                                       ,Target->Reg,Value[i]);
        printf("%s", Str);
        if(gReg_Log_Enable)
          _LogAppend("%s",Str);
        Target++;
        break;
      default:
        return;
    }
  }
}


///@Function: xSim_Reg_SetValue
///@Descript: Set Fixed Value to Random Register and Force One-Shot Mode
void xSim_Reg_SetValue(U32 Addr,U32 Reg,U32 Value)
{
  xSim_Reg *Target = xSim_FindRegister(Addr,Reg);
  if(Target == NULL)
    return;

  if(Target->Type == xSIM_TYPE_RANDOM)
  {
    //Limit Value Within Min and Max Range
    if(Value > Target->Max)  Value = Target->Max;
    if(Value < Target->Min)  Value = Target->Min;

    //Set Value and Force Type to One-Shot (Only Affects Random)
    Target->Value = Value;
    Target->Type  = xSIM_TYPE_ONESHOT;
  }
}


///@Function: xSim_Reg_SetRange
///@Descript: Set Min/Max Value Range for Random Register Generation
void xSim_Reg_SetRange(U32 Addr,U32 Reg,U32 Min,U32 Max)
{
  xSim_Reg *Target = xSim_FindRegister(Addr,Reg);
  if(Target == NULL)
    return;

  //Check If Min is Greater than Max,Swap them If Necessary
  if(Min > Max)
  {
    U32 Temp = Min;
    Min      = Max;
    Max      = Temp;
  }

  //Set Value Scope
  Target->Min = Min;
  Target->Max = Max;

  //Check If Current Value is Still Within the Scope
  if(Target->Value < Min) Target->Value = Min;
  if(Target->Value > Max) Target->Value = Max;
}


///@Function: xSim_Reg_Dump
///@Descript: Dump All Buffered to a File and Release Allocated Memory
void xSim_Reg_Dump(const char *FileName)
{
if(gReg_Log_Enable)
  {
    FILE *fp = fopen(FileName, "w");
    if(fp != NULL)
    {
      //Write Data
      if(gReg_Log.Size > 0)
        fwrite(gReg_Log.Buf,1,gReg_Log.Size,fp);

      //Close File
      fclose(fp);

      //Destroy
      SAFE_DESTROY(gReg_Log.Buf);
      gReg_Log.Capacity = 0;
      gReg_Log.Size     = 0;
      gReg_Log_Enable   = 0;    //Disable
    }
  }
}


///@Function: _LogAppend
///@Descript: Append Formatted Log Text Into the Dynamic Memory Buffer With Auto-Expression
static void _LogAppend(const char *Format,...)
{
  if(!gReg_Log_Enable)
    return;

  //Format String
  char Str[128] = {0};
  va_list Args;
  va_start(Args, Format);
  int Len = vsnprintf(Str, sizeof(Str), Format, Args);
  va_end(Args);

  if(Len <= 0)
    return;

  //Check Need Extended Memory
  if(gReg_Log.Size + Len + 1 >= gReg_Log.Capacity)
  {
    U32 NewCap = gReg_Log.Capacity + xSIM_REG_LOG_CAPACITY;   //+4KB
    if(NewCap < gReg_Log.Size + Len + 1)
      NewCap = gReg_Log.Size + Len + xSIM_REG_LOG_CAPACITY;   //+4KB

    char *NewBuf = (char*)realloc(gReg_Log.Buf, NewCap);
    if(NewBuf == NULL)
      return;
    
    gReg_Log.Buf      = NewBuf;
    gReg_Log.Capacity = NewCap;
  }

  memcpy(gReg_Log.Buf + gReg_Log.Size, Str, Len);
  gReg_Log.Size += Len;
  gReg_Log.Buf[gReg_Log.Size] = '\0';
}

///@Function: _GetSysTick
///@Descript: Get the Current System Monotonic Time in ms
static U32 _GetSysTick(void)
{
  struct timespec TS;
  clock_gettime(CLOCK_MONOTONIC,&TS);   //Clock Monotonic Get Clock Time
  U32 MS = (U32)(TS.tv_sec * 1000) + (U32)(TS.tv_nsec / 1000000);
  return MS;
}


///@Function: xSim_FindDevice
///@Descript: Search Registered Device Table By Slave Address
static xSim_RegDevice* xSim_FindDevice(U32 Addr)
{
  for(U32 i = 0; i < xSIM_REGDEV_MAX; i++)
    if(gDevTable[i].Table != NULL && gDevTable[i].Addr == Addr)
        return &gDevTable[i];
  return NULL;
}


///@Function: xSim_FindRegister
///@Descript: Search Register Entry By Device Slave Address and Register Offset
static xSim_Reg* xSim_FindRegister(U32 Addr,U32 Reg)
{
  xSim_RegDevice *TargetDev = xSim_FindDevice(Addr);

  //Not Find Register Device
  if(TargetDev == NULL)
    return NULL;

  //Search Register
  for(U32 i = 0;i < TargetDev->Count;i++)
    if(TargetDev->Table[i].Reg == Reg)
      return &TargetDev->Table[i];
  return NULL;    //Not Find Register
}