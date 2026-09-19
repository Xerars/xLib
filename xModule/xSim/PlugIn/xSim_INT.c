#define _POSIX_C_SOURCE     199309L

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

//[xLib Include]
#include "xSim_INT.h"

//[Prototype Declare]
static U32 _GetSysTick(void);
static void _LogAppend(const char *Format,...);

//[Variable Declare]
static xSim_Int     gSim_Int_Table[xSIM_INT_CH_MAX] = {0};
static xSim_INT_Log gSim_INT_Log                    = {NULL,0,0};
static U8           gSim_INT_Inited                 = 0;
static U8           gSim_INT_Log_Enable             = 0;
static U32          gSim_INT_Tick_Start             = 0;


///@Function: xSim_INT_Init
///@Descript: Initialize Interrupt Simulator Module
void xSim_INT_Init(U8 LogEn)
{
if(gSim_INT_Inited == 0)
  {
    if(LogEn)
    {
      gSim_INT_Log_Enable = 1;
      if(gSim_INT_Log.Buf == NULL)
      {
        gSim_INT_Log.Capacity = xSIM_INT_LOG_CAPACITY;  //4KB
        gSim_INT_Log.Size     = 0;
        gSim_INT_Log.Buf      = (char*)malloc(gSim_INT_Log.Capacity);
        if(gSim_INT_Log.Buf == NULL)
          return;
        gSim_INT_Log.Buf[0] = '\0';
      }
    }
    gSim_INT_Inited     = 1;
    gSim_INT_Tick_Start = _GetSysTick();
  }
}


///@Function: xSim_INT_Destroy
///@Descript: Destroy Interrupt Simulator Module
void xSim_INT_Destroy(void)
{
if(gSim_INT_Inited == 1)
  {
    memset(gSim_Int_Table,0,sizeof(gSim_Int_Table));
    SAFE_DESTROY(gSim_INT_Log.Buf);
    gSim_INT_Log.Capacity = 0;
    gSim_INT_Log.Size     = 0;
    gSim_INT_Log_Enable   = 0;
    gSim_INT_Inited       = 0;
  }
}


///@Function: xSim_INT_Regsit
///@Descript: Regist an Interrupt Channel
void xSim_INT_Regist(U8 Channel,CCHAR *Name,xSIM_INT_EDGE Edge,xSim_Int_CB CB)
{
  if(!gSim_INT_Inited || Channel >= xSIM_INT_CH_MAX)
  {
    printf("[Error]: INT-(%d) Out of Range or Not Inited\n",Channel);
    return;
  }

  if(gSim_Int_Table[Channel].Used)
  {
    printf("[Error]: INT-(%d) is Already Registed\n",Channel);
    return;
  }

  gSim_Int_Table[Channel].Used    = 1;
  gSim_Int_Table[Channel].Channel = Channel;

  if(Name != NULL)
  {
    strncpy(gSim_Int_Table[Channel].Name,Name,xSIM_INT_NAME_SIZE - 1);
    gSim_Int_Table[Channel].Name[xSIM_INT_NAME_SIZE - 1] = '\0';
  }
  else
    gSim_Int_Table[Channel].Name[0] = '\0';


  gSim_Int_Table[Channel].Edge  = Edge;
  gSim_Int_Table[Channel].Last  = 0;
  gSim_Int_Table[Channel].ISR   = CB;
  gSim_Int_Table[Channel].Stamp = 0;
}


///@Function: xSim_INT_UnRegist
///@Descript: UnRegist an Interrupt Channel
void xSim_INT_UnRegist(U8 Channel)
{
  if(!gSim_INT_Inited || Channel >= xSIM_INT_CH_MAX)
    return;
  
  if(gSim_Int_Table[Channel].Used)
  {
    gSim_Int_Table[Channel].Used    = 0;
    gSim_Int_Table[Channel].Edge    = xSIM_INT_EDGE_NONE;
    gSim_Int_Table[Channel].Last    = 0;
    gSim_Int_Table[Channel].ISR     = NULL;
    gSim_Int_Table[Channel].Name[0] = '\0';
  }
}


///@Function: xSim_INT_SetEdge
///@Descript: Set Trigger Edge Type for Specific Channel
void xSim_INT_SetEdge(U8 Channel,xSIM_INT_EDGE Edge)
{
  if(!gSim_INT_Inited || Channel >= xSIM_INT_CH_MAX)
    return;
  
  if(gSim_Int_Table[Channel].Used)
    gSim_Int_Table[Channel].Edge = Edge;
}


///@Function: xSim_INT_SetTrigger
///@Descript: Set Trigger Edge Type for Specific Channel
void xSim_INT_SetTrigger(U8 Channel,U8 Cur)
{
  if(!gSim_INT_Inited || Channel >= xSIM_INT_CH_MAX)
    return;

  xSim_Int *pInt = &gSim_Int_Table[Channel];
  if(pInt->Used)
  {
    int Trig = 0;
    int Last = pInt->Last;
    if(Last != Cur)
    {
      if(Cur == 1 && Last == 0)       //0->1 Rising
      {
        if((pInt->Edge & xSIM_INT_EDGE_RISING) != 0)
          Trig = 1;
      }
      else if(Cur == 0 && Last == 1)  //1->0 Falling
      {
        if((pInt->Edge & xSIM_INT_EDGE_FALLING) != 0)
          Trig = 1;
      }

      pInt->Stamp = _GetSysTick() - gSim_INT_Tick_Start;
      pInt->Last  = Cur;

      if(Trig)
      {
        char Str[128] = {0};
        snprintf(Str,sizeof(Str),"%8d::[INT-%d]<%s>: %d (%s)\n",
                 pInt->Stamp,pInt->Channel,pInt->Name,pInt->Last,(Cur == 1)? "Rising": "Falling");
        printf("%s",Str);
        if(gSim_INT_Log_Enable)
          _LogAppend("%s",Str);

        if(pInt->ISR != NULL)
          pInt->ISR(pInt->Channel,Cur);
      }
    }
  }
}


///@Function: xSim_INT_Dump
///@Descript: Dump Buffer Interrupt Log to a File and Release Memory
void xSim_INT_Dump(CCHAR *FileName)
{
  if(gSim_INT_Log_Enable)
  {
    FILE *fp = fopen(FileName,"w");
    if(fp != NULL)
    {
      if(gSim_INT_Log.Size > 0)
        fwrite(gSim_INT_Log.Buf,1,gSim_INT_Log.Size,fp);
      fclose(fp);
      SAFE_DESTROY(gSim_INT_Log.Buf);
      gSim_INT_Log.Capacity = 0;
      gSim_INT_Log.Size     = 0;
      gSim_INT_Log_Enable   = 0;
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
  if(!gSim_INT_Log_Enable || gSim_INT_Log.Buf == NULL)
    return;

  char Str[128] = {0};
  va_list Args;
  va_start(Args,Format);
  int Len = vsnprintf(Str,sizeof(Str),Format,Args);
  va_end(Args);

  if(Len <= 0)
    return;

  if(gSim_INT_Log.Size + Len + 1 >= gSim_INT_Log.Capacity)
  {
    U32 NewCap = gSim_INT_Log.Capacity + xSIM_INT_LOG_CAPACITY;
    if(NewCap < gSim_INT_Log.Size + Len + 1)
      NewCap = gSim_INT_Log.Size + Len + xSIM_INT_LOG_CAPACITY;

    char *NewBuf = (char*)realloc(gSim_INT_Log.Buf,NewCap);
    if(NewBuf == NULL)
      return;
    
    gSim_INT_Log.Buf      = NewBuf;
    gSim_INT_Log.Capacity = NewCap;
  }

  memcpy(gSim_INT_Log.Buf + gSim_INT_Log.Size,Str,Len);
  gSim_INT_Log.Size += Len;
  gSim_INT_Log.Buf[gSim_INT_Log.Size] = '\0';
}
