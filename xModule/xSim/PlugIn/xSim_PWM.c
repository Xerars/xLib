#define _POSIX_C_SOURCE     199309L

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

//[xLib Include]
#include "xSim_PWM.h"


//[Prototype Declare]
static U32 _GetSysTick(void);
static void _LogAppend(const char *Format,...);


//[Variable Declare]
static xSim_PWM     gSim_PWM_Table[xSIM_PWM_CH_MAX] = {0};
static xSim_PWM_Log gSim_PWM_Log                    = {NULL,0,0};
static U8           gSim_PWM_Log_Enable             = 0;
static U8           gSim_PWM_Inited                 = 0;
static U32          gSim_PWM_Tick_Start             = 0;


///@Function: xSim_PWM_Init
///@Descript: Initialize PWM Simulator Module and Optional Log Buffer
void xSim_PWM_Init(U8 LogEn)
{
  if(gSim_PWM_Inited == 0)
  {
    if(LogEn)
    {
      gSim_PWM_Log_Enable = 1;
      if(gSim_PWM_Log.Buf == NULL)
      {
        gSim_PWM_Log.Capacity = xSIM_PWM_LOG_CAPACITY;  //4KB
        gSim_PWM_Log.Size     = 0;
        gSim_PWM_Log.Buf      = (char*)malloc(gSim_PWM_Log.Capacity);
        if(gSim_PWM_Log.Buf == NULL)
          return;
        gSim_PWM_Log.Buf[0] = '\0';
      }
    }
    gSim_PWM_Inited     = 1;
    gSim_PWM_Tick_Start = _GetSysTick();
  }
}


///@Function: xSim_PWM_Destroy
///@Descript: Destroy PWM Simulator Module and Release Log Memory
void xSim_PWM_Destroy(void)
{
  if(gSim_PWM_Inited == 1)
  {
    memset(gSim_PWM_Table,0,sizeof(gSim_PWM_Table));
    SAFE_DESTROY(gSim_PWM_Log.Buf);
    gSim_PWM_Log.Capacity = 0;
    gSim_PWM_Log.Size     = 0;
    gSim_PWM_Log_Enable   = 0;
    gSim_PWM_Inited       = 0;
  }
}


///@Function: xSim_PWM_Regist
///@Descript: Regist and Initialize a Specific PWM Channel
void xSim_PWM_Regist(U8 Channel,CCHAR *Name,U8 En,U32 Freq,U8 Rate)
{
  if(!gSim_PWM_Inited || Channel >= xSIM_PWM_CH_MAX)
  {
    printf("[Error]: PWM-(%d) Out of Range or Not Inited\n",Channel);
    return;
  }

  if(gSim_PWM_Table[Channel].Used)
  {
    printf("[Error]: PWM-(%d) is Already Registed\n",Channel);
    return;
  }

  gSim_PWM_Table[Channel].Used    = 1;
  gSim_PWM_Table[Channel].Channel = Channel;

  if(Name != NULL)
  {
    strncpy(gSim_PWM_Table[Channel].Name,Name,xSIM_PWM_NAME_SIZE - 1);
    gSim_PWM_Table[Channel].Name[xSIM_PWM_NAME_SIZE - 1] = '\0';
  }
  else
    gSim_PWM_Table[Channel].Name[0] = '\0';

  gSim_PWM_Table[Channel].En      = En? 1: 0;
  gSim_PWM_Table[Channel].Freq    = Freq;
  gSim_PWM_Table[Channel].Rate    = (Rate > 100)? 100: Rate;
  gSim_PWM_Table[Channel].Running = 0;
  gSim_PWM_Table[Channel].Stamp   = _GetSysTick() - gSim_PWM_Tick_Start;
}


///@Function: xSim_PWM_UnRegist
///@Descript: UnRegist and Disable a Specific PWM Channel
void xSim_PWM_UnRegist(U8 Channel)
{
  if(!gSim_PWM_Inited || Channel >= xSIM_PWM_CH_MAX)
    return;
  
  if(gSim_PWM_Table[Channel].Used)
    memset(&gSim_PWM_Table[Channel],0,sizeof(xSim_PWM));
}


///@Function: xSim_PWM_SetEnable
///@Descript: Set PWM Enable State and Log Change
void xSim_PWM_SetEnable(U8 Channel,U8 En)
{
  if(!gSim_PWM_Inited || Channel >= xSIM_PWM_CH_MAX)
    return;

  xSim_PWM *pPWM = &gSim_PWM_Table[Channel];
  if(pPWM->Used)
  {
    U8 NewEn = En? 1: 0;
    if(pPWM->En != NewEn)
    {
      pPWM->En = NewEn;
      pPWM->Stamp = _GetSysTick() - gSim_PWM_Tick_Start;
      char Str[128] = {0};
      snprintf(Str,sizeof(Str),"%8d::[PWM-%d]<%s> SetEnable: %d\n",
               pPWM->Stamp,pPWM->Channel,pPWM->Name,pPWM->En);
      printf("%s",Str);
      if(gSim_PWM_Log_Enable)
        _LogAppend("%s",Str);
    }
  }
}


///@Function: xSim_PWM_SetFreq
///@Descript: Set PWM Frequency and Log Change
void xSim_PWM_SetFreq(U8 Channel,U32 Freq)
{
  if(!gSim_PWM_Inited || Channel >= xSIM_PWM_CH_MAX)
    return;

  xSim_PWM *pPWM = &gSim_PWM_Table[Channel];
  if(pPWM->Used)
    if(pPWM->Freq != Freq)
    {
      pPWM->Freq = Freq;
      pPWM->Stamp = _GetSysTick() - gSim_PWM_Tick_Start;
      char Str[128] = {0};
      snprintf(Str,sizeof(Str),"%8d::[PWM-%d]<%s> SetFreq: %uHz\n",
               pPWM->Stamp,pPWM->Channel,pPWM->Name,pPWM->Freq);
      printf("%s",Str);
      if(gSim_PWM_Log_Enable)
        _LogAppend("%s",Str);
    }
}


///@Function: xSim_PWM_SetDuty
///@Descript: Set PWM Duty Cycle Rate and Log Change
void xSim_PWM_SetDuty(U8 Channel,U8 Rate)
{
  if(!gSim_PWM_Inited || Channel >= xSIM_PWM_CH_MAX)
    return;

  xSim_PWM *pPWM = &gSim_PWM_Table[Channel];
  if(pPWM->Used)
  {
    U8 NewRate = (Rate > 100)? 100: Rate;
    if(pPWM->Rate != NewRate)
    {
      pPWM->Rate = NewRate;
      pPWM->Stamp = _GetSysTick() - gSim_PWM_Tick_Start;
      char Str[128] = {0};
      snprintf(Str,sizeof(Str),"%8d::[PWM-%d]<%s> SetDuty: %d%%\n",
               pPWM->Stamp,pPWM->Channel,pPWM->Name,pPWM->Rate);
      printf("%s",Str);
      if(gSim_PWM_Log_Enable)
        _LogAppend("%s",Str);
    }
  }
}


///@Function: xSim_PWM_Start
///@Descript: Start PWM Output and Log State
void xSim_PWM_Start(U8 Channel)
{
  if(!gSim_PWM_Inited || Channel >= xSIM_PWM_CH_MAX)
    return;

  xSim_PWM *pPWM = &gSim_PWM_Table[Channel];
  if(pPWM->Used)
  {
    if(pPWM->Running == 0)
    {
      pPWM->Running = 1;
      pPWM->Stamp = _GetSysTick() - gSim_PWM_Tick_Start;
      char Str[128] = {0};
      snprintf(Str,sizeof(Str),"%8d::[PWM-%d]<%s> Start(Freq:%uHz,Duty:%d%%)\n",
               pPWM->Stamp,pPWM->Channel,pPWM->Name,pPWM->Freq,pPWM->Rate);
      printf("%s",Str);
      if(gSim_PWM_Log_Enable)
        _LogAppend("%s",Str);
    }
  }
}


///@Function: xSim_PWM_Stop
///@Descript: Stop PWM Output and Log State
void xSim_PWM_Stop(U8 Channel)
{
  if(!gSim_PWM_Inited || Channel >= xSIM_PWM_CH_MAX)
    return;

  xSim_PWM *pPWM = &gSim_PWM_Table[Channel];
  if(pPWM->Used)
    if(pPWM->Running == 1)
    {
      pPWM->Running = 0;
      pPWM->Stamp = _GetSysTick() - gSim_PWM_Tick_Start;

      char Str[128] = {0};
      snprintf(Str,sizeof(Str),"%8d::[PWM-%d]<%s> Stop\n",
               pPWM->Stamp,pPWM->Channel,pPWM->Name);
      printf("%s",Str);
      if(gSim_PWM_Log_Enable)
        _LogAppend("%s",Str);
    }
}


///@Function: xSim_PWM_Dump
///@Descript: Dump Buffer PWM Log to a File and Release Memory
void xSim_PWM_Dump(CCHAR *FileName)
{
  if(gSim_PWM_Log_Enable)
  {
    FILE *fp = fopen(FileName,"w");
    if(fp != NULL)
    {
      if(gSim_PWM_Log.Size > 0)
        fwrite(gSim_PWM_Log.Buf,1,gSim_PWM_Log.Size,fp);

      fclose(fp);
      SAFE_DESTROY(gSim_PWM_Log.Buf);
      gSim_PWM_Log.Capacity = 0;
      gSim_PWM_Log.Size     = 0;
      gSim_PWM_Log_Enable   = 0;
    }
  }
}


///@Function: _GetSysTick
///@Descript: Get the Current System Monotonic Time in Milliseconds
static U32 _GetSysTick(void)
{
  struct timespec TS;
  clock_gettime(CLOCK_MONOTONIC,&TS);
  U32 MS = (U32)(TS.tv_sec * 1000) + (U32)(TS.tv_nsec / 1000000);
  return MS;
}


///@Function: _LogAppend
///@Descript: Append Formatted Log Text into the Dynamic Memory Buffer With Auto-Expansion
static void _LogAppend(const char *Format,...)
{
  if(!gSim_PWM_Log_Enable || gSim_PWM_Log.Buf == NULL)
    return;

  char Str[128] = {0};
  va_list Args;
  va_start(Args,Format);
  int Len = vsnprintf(Str,sizeof(Str),Format,Args);
  va_end(Args);

  if(Len <= 0)
    return;

  if(gSim_PWM_Log.Size + Len + 1 >= gSim_PWM_Log.Capacity)
  {
    U32 NewCap = gSim_PWM_Log.Capacity + xSIM_PWM_LOG_CAPACITY;
    if(NewCap < gSim_PWM_Log.Size + Len + 1)
      NewCap = gSim_PWM_Log.Size + Len + xSIM_PWM_LOG_CAPACITY;

    char *NewBuf = (char*)realloc(gSim_PWM_Log.Buf,NewCap);
    if(NewBuf == NULL)
      return;
    
    gSim_PWM_Log.Buf      = NewBuf;
    gSim_PWM_Log.Capacity = NewCap;
  }

  memcpy(gSim_PWM_Log.Buf + gSim_PWM_Log.Size,Str,Len);
  gSim_PWM_Log.Size += Len;
  gSim_PWM_Log.Buf[gSim_PWM_Log.Size] = '\0';
}