#define _POSIX_C_SOURCE     199309L

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

//[xLib Include]
#include "xSim_GPIO.h"

//[Prototye Declare]
static U32 _GetSysTick(void);
static void _LogAppend(const char *Format,...);

//[Variable Declare]
static xSim_GPI       gGPI_Table[xSIM_GPI_MAX]  = {0};
static xSim_GPO       gGPO_Table[xSIM_GPO_MAX]  = {0};
static xSim_GPIO_Log  gGPIO_Log                 = {NULL,0,0};
static U8             gGPIO_Log_Enable          = 0;
static U8             gGPIO_Inited              = 0;
static U32            gGPIO_Tick_Start          = 0;


///@Function: xSim_GPI_Regist
///@Descript: Register and Initialize a Specific GPI Channel
void xSim_GPI_Regist(U8 ID,CCHAR *Name)
{
  if(ID >= xSIM_GPI_MAX)
  {
    printf("[Error]: GPI-(%d) Out of Range(Max: %d)\n",ID,xSIM_GPI_MAX-1);
    return;
  }

  if(gGPI_Table[ID].Used)
  {
    printf("[Error]: GPI-(%d) is Already Registed\n",ID);
    return;
  }

  strncpy(gGPI_Table[ID].Name,Name?Name:"GPI",xSIM_GPIO_NAME_SIZE-1);
  gGPI_Table[ID].Name[xSIM_GPIO_NAME_SIZE - 1] = '\0';
  gGPI_Table[ID].ID     = ID;
  gGPI_Table[ID].Dir    = xSIM_GPIO_DIR_IN;
  gGPI_Table[ID].Used   = 1;
  gGPI_Table[ID].Status = 0;
  gGPI_Table[ID].Last   = 0;
  gGPI_Table[ID].Stamp  = 0;
}


///@Function: xSim_GPO_Regist
///@Descript: Register and Initialize a Specific GPO Channel
void xSim_GPO_Regist(U8 ID,CCHAR *Name)
{
  if(ID >= xSIM_GPO_MAX)
  {
    printf("[Error]: GPO-(%d) Out of Range(Max: %d)\n",ID,xSIM_GPO_MAX-1);
    return;
  }

  if(gGPO_Table[ID].Used)
  {
    printf("[Error]: GPO-(%d) is Already Registed\n",ID);
    return;
  }

  strncpy(gGPO_Table[ID].Name,Name?Name:"GPO",xSIM_GPIO_NAME_SIZE-1);
  gGPO_Table[ID].Name[xSIM_GPIO_NAME_SIZE - 1] = '\0';
  gGPO_Table[ID].ID     = ID;
  gGPO_Table[ID].Dir    = xSIM_GPIO_DIR_OUT;
  gGPO_Table[ID].Used   = 1;
  gGPO_Table[ID].Status = 0;
  gGPO_Table[ID].Stamp  = 0;
}



///@Function: xSim_GPI_UnRegist
///@Descript: UnRegister and Disable a Specific GPI Channel
void xSim_GPI_UnRegist(U8 ID)
{
  if(ID >= xSIM_GPI_MAX)
    return;
  if(gGPI_Table[ID].Used)
    memset(&gGPI_Table[ID],0,sizeof(xSim_GPI));
}


///@Function: xSim_GPO_UnRegist
///@Descript: UnRegister and Disable a Specific GPO Channel
void xSim_GPO_UnRegist(U8 ID)
{
  if(ID >= xSIM_GPO_MAX)
    return;
  if(gGPO_Table[ID].Used)
    memset(&gGPO_Table[ID], 0, sizeof(xSim_GPO));
}


///@Function: xSim_GPIO_Init
///@Descript: Initialize the GPIO Simulator Module and Optional Log Buffer
void xSim_GPIO_Init(U8 LogEn)
{
  if(gGPIO_Inited == 0)
  {
    if(LogEn)
    {
      gGPIO_Log_Enable = 1;
      if(gGPIO_Log.Buf == NULL)
      {
        gGPIO_Log.Capacity = xSIM_GPIO_LOG_CAPACITY;  //4KB
        gGPIO_Log.Size     = 0;
        gGPIO_Log.Buf      = (char*)malloc(gGPIO_Log.Capacity);
        if(gGPIO_Log.Buf == NULL)
          return;
        gGPIO_Log.Buf[0] = '\0';
      }
    }
    gGPIO_Inited     = 1;
    gGPIO_Tick_Start = _GetSysTick();
  }
}


///@Function: xSim_GPI_Set
///@Descript: Set Simulate Input Level
void xSim_GPI_Set(U8 ID,U8 Level)
{
  if(ID >= xSIM_GPI_MAX)
    return;
  if(gGPI_Table[ID].Used && gGPI_Table[ID].Dir == xSIM_GPIO_DIR_IN)
    gGPI_Table[ID].Status = Level? 1: 0;
}


///@Function: xSim_GPI_Read
///@Descript: Read GOU Status and Log Change Automatically
U8 xSim_GPI_Read(U8 ID)
{
  if(ID >= xSIM_GPI_MAX)
    return 0;
  
  if(gGPI_Table[ID].Used && gGPI_Table[ID].Dir == xSIM_GPIO_DIR_IN)
  {
    U8 Cur = gGPI_Table[ID].Status;
    if(gGPI_Table[ID].Last != Cur)
    {
      gGPI_Table[ID].Last  = Cur;
      gGPI_Table[ID].Stamp = _GetSysTick() - gGPIO_Tick_Start;

      char Str[128] = {0};
      snprintf(Str,sizeof(Str),"%8d::[GPI-%d]<%s>: %d\n",gGPI_Table[ID].Stamp,gGPI_Table[ID].ID
                                                        ,gGPI_Table[ID].Name ,gGPI_Table[ID].Last);
      printf("%s",Str);
      if(gGPIO_Log_Enable)
        _LogAppend("%s",Str);
    }
    return gGPI_Table[ID].Status;
  }
  return 0;
}


///@Function: xSim_GPO_Write
///@Descript: Write GPIO Output Level and Log Change
void xSim_GPO_Write(U8 ID,U8 Level)
{
  if(ID >= xSIM_GPO_MAX)
    return;

  if(gGPO_Table[ID].Used && gGPO_Table[ID].Dir == xSIM_GPIO_DIR_OUT)
  {
    U8 Cur = Level? 1: 0;
    if(gGPO_Table[ID].Status != Cur)
    {
      gGPO_Table[ID].Status = Cur;
      gGPO_Table[ID].Stamp  = _GetSysTick() - gGPIO_Tick_Start;

      char Str[128] = {0};
      snprintf(Str,sizeof(Str),"%8d::[GPO-%d]<%s>: %d\n",gGPO_Table[ID].Stamp,gGPO_Table[ID].ID
                                                        ,gGPO_Table[ID].Name ,gGPO_Table[ID].Status);

      printf("%s",Str);
      if(gGPIO_Log_Enable)
        _LogAppend("%s",Str);
    }
  }
}


///@Function: xSim_GPIO_Dump
///@Descript: Dump Buffer GPIO Log to a File Release Memory
void xSim_GPIO_Dump(CCHAR *FileName)
{
  if(gGPIO_Log_Enable)
  {
    FILE *fp = fopen(FileName,"w");
    if(fp != NULL)
    {
      if(gGPIO_Log.Size > 0)
        fwrite(gGPIO_Log.Buf,1,gGPIO_Log.Size,fp);
      
      fclose(fp);
      SAFE_DESTROY(gGPIO_Log.Buf);
      gGPIO_Log.Capacity = 0;
      gGPIO_Log.Size     = 0;
      gGPIO_Log_Enable   = 0;
    }
  }
}


///@Function: _GetSysTick
///@Descript: Get the Current System Monotonic Time in Seconds
static U32 _GetSysTick(void)
{
  struct timespec TS;
  clock_gettime(CLOCK_MONOTONIC,&TS);   //Clock Monotonic Get Clock Time
  U32 MS = (U32)(TS.tv_sec * 1000) + (U32)(TS.tv_nsec / 1000000);
  return MS;
}


///@Function: _LogAppend
///@Descript: Append Formatted Log Text into the Dynamic Memory Buffer With Auto-Expansion
static void _LogAppend(const char *Format,...)
{
  if(!gGPIO_Log_Enable)
    return;

  char Str[128] = {0};
  va_list Args;
  va_start(Args,Format);
  int Len = vsnprintf(Str,sizeof(Str),Format,Args);
  va_end(Args);

  if(Len <= 0)
    return;

  if(gGPIO_Log.Size + Len + 1 >= gGPIO_Log.Capacity)
  {
    U32 NewCap = gGPIO_Log.Capacity + xSIM_GPIO_LOG_CAPACITY;
    if(NewCap < gGPIO_Log.Size + Len + 1)
      NewCap = gGPIO_Log.Size + Len + xSIM_GPIO_LOG_CAPACITY;

    char *NewBuf = (char*)realloc(gGPIO_Log.Buf,NewCap);
    if(NewBuf == NULL)
      return;
    
    gGPIO_Log.Buf      = NewBuf;
    gGPIO_Log.Capacity = NewCap;
  }

  memcpy(gGPIO_Log.Buf + gGPIO_Log.Size,Str,Len);
  gGPIO_Log.Size += Len;
  gGPIO_Log.Buf[gGPIO_Log.Size] = '\0';
}