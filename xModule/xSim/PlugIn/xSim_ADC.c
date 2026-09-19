//[Config Declare]
#define _POSIX_C_SOURCE     199309L

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

//[xLib Include]
#include "xSim_ADC.h"

//[Prototype Declare]
static U32  _GetSysTick(void);
static void _LogAppend(const char *Format,...);


//[Variable Declare]
static xSim_ADC     gADC_Table[xSIM_ADC_MAX] = {0};
static xSim_ADC_Log gADC_Log        = {NULL,0,0};
static U8           gADC_Log_Enable = 0;
static U8           gADC_Inited     = 0;
static DBL          gADC_Tick_Start = 0;


///@Function: xSim_ADC_Regist
///@Descript: Register and Initialize a Specific ADC Channel
void xSim_ADC_Regist(U8 Channel,U8 nBit)
{
  if(Channel >= xSIM_ADC_MAX)
    return;
  
  if(nBit == 0 || nBit > 32)
    nBit = 12;

  gADC_Table[Channel].Channel = Channel;
  gADC_Table[Channel].nBit    = nBit;
  gADC_Table[Channel].Type    = xSIM_DATA_TYPE_RANDOM;
  gADC_Table[Channel].Value   = 0;
  gADC_Table[Channel].Used    = 1;
  gADC_Table[Channel].Min     = 0;
  gADC_Table[Channel].Max     = (nBit == 32)? 0xFFFFFFFF: (U32)((1ULL << nBit) - 1);
}


///@Function: xSim_ADC_UnRegist
///@Descript: UnRegister and Disable a Specific ADC Channel
void xSim_ADC_UnRegist(U8 Channel)
{
  if(Channel >= xSIM_ADC_MAX)
    return;
  
  if(gADC_Table[Channel].Used)
  {
    gADC_Table[Channel].Channel = 0;
    gADC_Table[Channel].nBit    = 0;
    gADC_Table[Channel].Type    = xSIM_DATA_TYPE_RANDOM;
    gADC_Table[Channel].Min     = 0;
    gADC_Table[Channel].Max     = 0;
    gADC_Table[Channel].Value   = 0;
    gADC_Table[Channel].Used    = 0;
  }
}


///@Function: xSim_ADC_Init
///@Descript: Initialize the ADC Simulator Module and Optional Log Buffer
void xSim_ADC_Init(U8 LogEn)
{
  if(gADC_Inited == 0)
  {
    if(LogEn)
    {
      gADC_Log_Enable = 1;
      if(gADC_Log.Buf == NULL)
      {
        gADC_Log.Capacity = xSIM_ADC_LOG_CAPACITY;       //4KB
        gADC_Log.Size     = 0;
        gADC_Log.Buf      = (char*)malloc(gADC_Log.Capacity);
        if(gADC_Log.Buf == NULL)
          return;
        gADC_Log.Buf[0] = '\0';
      }
      gADC_Inited = 1;
      gADC_Tick_Start = _GetSysTick();
    }
  }
}



///@Function: xSim_ADC_GetValue
///@Descript: Get the Current Simulated Value of an ADC Channel and Record Log
U32 xSim_ADC_GetValue(U8 Channel)
{
  static U8 ADC_Once = 0;
  if(ADC_Once == 0)   //Execute Once
  {
    srand(time(NULL));
    ADC_Once = 1;
  }

  if(Channel >= xSIM_ADC_MAX)
    return 0;

  U32 Value = 0;
  U32 Min   = gADC_Table[Channel].Min;
  U32 Max   = gADC_Table[Channel].Max;
  U32 Range = (Max >= Min) ? (Max - Min) : 1;
  switch(gADC_Table[Channel].Type)
  {
    case xSIM_DATA_TYPE_RANDOM:
      Value = (Range == 1)? Min: (rand() % Range) + Min;
      gADC_Table[Channel].Value = Value;
      break;
    case xSIM_DATA_TYPE_ONESHOT:
      Value = gADC_Table[Channel].Value;
      gADC_Table[Channel].Type = xSIM_DATA_TYPE_RANDOM;
      break;
    default:
      break;
  }

  gADC_Table[Channel].Stamp = _GetSysTick() - gADC_Tick_Start;
  char Str[128] = {0};
  snprintf(Str,sizeof(Str),"%8d::[ADC-%d]: %-10d(0x%X)\n",gADC_Table[Channel].Stamp
                                                         ,gADC_Table[Channel].Channel
                                                         ,gADC_Table[Channel].Value,gADC_Table[Channel].Value);
  printf("%s",Str);

  //Append Log
  if(gADC_Log_Enable)
    _LogAppend("%s",Str);
  return Value;
}


///@Function: xSim_ADC_SetValue
///@Descript: Set a One-Show Value for a Specific ADC Channel
void xSim_ADC_SetValue(U8 Channel,U32 Value)
{
  if(Channel >= xSIM_ADC_MAX)
    return;

  if(Value > gADC_Table[Channel].Max)   Value = gADC_Table[Channel].Max;
  if(Value < gADC_Table[Channel].Min)   Value = gADC_Table[Channel].Min;

  gADC_Table[Channel].Value = Value;
  gADC_Table[Channel].Type  = xSIM_DATA_TYPE_ONESHOT;
}


///@Function: xSim_ADC_SetRange
///@Descript: Set the Minimum and Maximum Limit Range for an ADC Channel
void xSim_ADC_SetRange(U8 Channel,U32 Min,U32 Max)
{
  if(Channel >= xSIM_ADC_MAX)
    return;

  U32 MaxLimit = (gADC_Table[Channel].nBit >= 32)? 0xFFFFFFFF
                                                 : ((1UL << gADC_Table[Channel].nBit) - 1);

  if(Min > MaxLimit)  Min = MaxLimit;
  if(Max > MaxLimit)  Max = MaxLimit;

  //Check Max is Over Min
  if(Min > Max)
  {
    U32 Temp = Min;
    Min      = Max;
    Max      = Temp;
  }

  //Set Value Scope
  gADC_Table[Channel].Min = Min;
  gADC_Table[Channel].Max = Max;

  //Check Currect Value is On Scope
  if(gADC_Table[Channel].Value < Min) gADC_Table[Channel].Value = Min;
  if(gADC_Table[Channel].Value > Max) gADC_Table[Channel].Value = Max;
}



///@Function: xSim_ADC_Dump
///@Descript: Dump All Buffered Logs to a File and Release Allocated Memory
void xSim_ADC_Dump(const char *FileName)
{
  if(gADC_Log_Enable)
  {
    FILE *fp = fopen(FileName,"w");
    if(fp != NULL)
    {
      //Write Data
      if(gADC_Log.Size > 0)
        fwrite(gADC_Log.Buf,1,gADC_Log.Size,fp);
      
      //Close File
      fclose(fp);
      
      //Destroy
      SAFE_DESTROY(gADC_Log.Buf);
      gADC_Log.Capacity = 0;
      gADC_Log.Size     = 0;
      gADC_Log_Enable   = 0;    //Disable
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
  if(!gADC_Log_Enable)
    return;

  //Format String
  char Str[128] = {0};
  va_list Args;
  va_start(Args,Format);
  int Len = vsnprintf(Str,sizeof(Str),Format,Args);
  va_end(Args);

  if(Len <= 0)
    return;

  //Check Need Extended Memory
  if(gADC_Log.Size + Len + 1 >= gADC_Log.Capacity)
  {
    U32 NewCap = gADC_Log.Capacity + xSIM_ADC_LOG_CAPACITY;   //+4KB
    if(NewCap < gADC_Log.Size + Len + 1)
      NewCap = gADC_Log.Size + Len + xSIM_ADC_LOG_CAPACITY;   //+4KB

    char *NewBuf = (char*)realloc(gADC_Log.Buf,NewCap);
    if(NewBuf == NULL)
      return;
    
    gADC_Log.Buf      = NewBuf;
    gADC_Log.Capacity = NewCap;
  }

  memcpy(gADC_Log.Buf + gADC_Log.Size,Str,Len);
  gADC_Log.Size += Len;
  gADC_Log.Buf[gADC_Log.Size] = '\0';
}
