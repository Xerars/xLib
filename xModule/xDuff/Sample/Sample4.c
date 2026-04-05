//Demo the xDuff Lib about Coroutine
#define _DEFAULT_SOURCE

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xDuff.h"

//[Unix Lib Include]
#include <unistd.h>


//[Prototype Declare]
int Coro_LED1 (xDuff_Coro *Coro);
int Coro_LED2 (xDuff_Coro *Coro);
int Coro_Alram(xDuff_Coro *Coro);
int Coro_Producer(xDuff_Coro *Coro);
int Coro_Consumer(xDuff_Coro *Coro);
int Coro_PrintA(xDuff_Coro *Coro);
int Coro_PrintB(xDuff_Coro *Coro);
int Coro_CarPark(xDuff_Coro *Coro,int ID);
int Coro_SmartLight(xDuff_Coro *Coro);
int Coro_BGLog(xDuff_Coro *Coro);
void PrintInfo(void);

//[Variable Declare]
int SharedBuf = -1;
int HasData   = 0;
int CarSensed = 0;
xDuff_Locker PrintLocker = {0};
xDuff_Sem    ParkSem     = {3};

//Main Code
int main(void)
{
  xDuff_Coro CO_LED1     = {0,0};
  xDuff_Coro CO_LED2     = {0,0};
  xDuff_Coro CO_ALARM    = {0,0};
  xDuff_Coro CO_PRODUCER = {0,0};
  xDuff_Coro CO_CUSTOMER = {0,0};
  xDuff_Coro CO_PRINTERA = {0,0};
  xDuff_Coro CO_PRINTERB = {0,0};
  xDuff_Coro CO_CARPARK1 = {0,0};
  xDuff_Coro CO_CARPARK2 = {0,0};
  xDuff_Coro CO_CARPARK3 = {0,0};
  xDuff_Coro CO_CARPARK4 = {0,0};
  xDuff_Coro CO_SMLIGHT  = {0,0};
  xDuff_Coro CO_BGLOG    = {0,0};

  for(int Tick = 0;Tick <= 20;Tick++)
  {
    printf("\n\n[Tick]: %d\n",Tick);
    Coro_LED1 (&CO_LED1);
    Coro_LED2 (&CO_LED2);
    Coro_Alram(&CO_ALARM);
    Coro_Producer(&CO_PRODUCER);
    Coro_Consumer(&CO_CUSTOMER);
    Coro_PrintA(&CO_PRINTERA);
    Coro_PrintB(&CO_PRINTERB);
    Coro_CarPark(&CO_CARPARK1,1);
    Coro_CarPark(&CO_CARPARK2,2);
    Coro_CarPark(&CO_CARPARK3,3);
    Coro_CarPark(&CO_CARPARK4,4);
    Coro_SmartLight(&CO_SMLIGHT);
    Coro_BGLog(&CO_BGLOG);

    usleep(1000000);
  }
  printf("\n");
  return 0;
}


///@Function: Coro_LED1
///@Descript: LED1 Coroutine
int Coro_LED1(xDuff_Coro *Coro)
{
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    printf("[LED-1]:ON  ");
    xDUFF_CORO_YIELD(Coro,0);
    printf("[LED-1]:OFF ");
    xDUFF_CORO_YIELD(Coro,0);
  }
  xDUFF_CORO_END(Coro);
  return 0;
}


///@Function: Coro_LED2
///@Descript: LED2 Coroutine
int Coro_LED2(xDuff_Coro *Coro)
{
  static int Round = 0;
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    printf("[LED-2]:ON\n");
    for(Round = 0;Round < 4;Round++)    //Wait 4 Tick
      xDUFF_CORO_YIELD(Coro,0);

    printf("[LED-2]:OFF\n");
    for(Round = 0;Round < 4;Round++)    //Wait 4 Tick
      xDUFF_CORO_YIELD(Coro,0);
  }
  xDUFF_CORO_END(Coro);
  return 0;
}


///@Function: Coro_Alram
///@Descript: Alarm Coroutine
int Coro_Alram(xDuff_Coro *Coro)
{
  static int Round = 0;
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    printf("[Alarm]: Guarding...\n");
    for(Round = 0;Round < 15;Round++)
      xDUFF_CORO_YIELD(Coro,0);

    printf("[Alarm]: !!! Alram  Alram !!!\n");
    for(Round = 0;Round < 3;Round++)
    {
      printf("[Alarm]: Bee...\n");
      xDUFF_CORO_YIELD(Coro,0);
    }

    printf("[Alarm]: Alarm Cooling...\n");
    for(Round = 0;Round < 2;Round++)
      xDUFF_CORO_YIELD(Coro,0);
  }
  xDUFF_CORO_END(Coro);
  return 0;
}


///@Function: Coro_Producer
///@Descript: Producer Coroutine
int Coro_Producer(xDuff_Coro *Coro)
{
  static int Round = 0;
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    printf("[Producer]: Prepare...\n");
    for(Round = 0;Round < 5;Round++)
      xDUFF_CORO_YIELD(Coro,0); 

    //Generate
    SharedBuf = rand() % 100;
    HasData = 1;
    printf("[Producer]: Generate!! Data: %d\n",SharedBuf);
    while(HasData)
      xDUFF_CORO_YIELD(Coro,0);
  }
  xDUFF_CORO_END(Coro);
  return 0;
}


///@Function: Coro_Consumer
///@Descript: Consumer Coroutine
int Coro_Consumer(xDuff_Coro *Coro)
{
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    printf("[Consumer]: Check Buffer...\n");
    if(HasData)
    {
      printf("[Consumer]: >>> Get Data: [%d] <<<\n", SharedBuf);
      SharedBuf = -1;   //Clear Data
      HasData   = 0;    //Clear Flag
    }
    xDUFF_CORO_YIELD(Coro,0);
  }
  xDUFF_CORO_END(Coro);
  return 0;
}


///@Function: Coro_PrintA
///@Descript: Mutex Sample Print
int Coro_PrintA(xDuff_Coro *Coro)
{
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    xDUFF_CORO_MUTEX_LOCK(Coro,&PrintLocker);
    printf("[AAA] Use Printer...\n");
    xDUFF_CORO_YIELD(Coro,0);
    xDUFF_CORO_YIELD(Coro,0);
    xDUFF_CORO_YIELD(Coro,0);
    xDUFF_CORO_YIELD(Coro,0);
    xDUFF_CORO_YIELD(Coro,0);
    printf("[AAA] AAA Finished!!\n");
    xDUFF_CORO_MUTEX_UNLOCK(&PrintLocker);
    xDUFF_CORO_YIELD(Coro,0);
  }
  xDUFF_CORO_END(Coro);
  return 0;
}


///@Function: Coro_PrintB
///@Descript: Mutex Sample Print
int Coro_PrintB(xDuff_Coro *Coro)
{
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    xDUFF_CORO_YIELD(Coro,0);
    xDUFF_CORO_MUTEX_LOCK(Coro,&PrintLocker);
    printf("[BBB]: Use Printer...\n");
    printf("[BBB]: BBB Finished!!\n");
    xDUFF_CORO_MUTEX_UNLOCK(&PrintLocker);
    xDUFF_CORO_YIELD(Coro,0);
  }
  xDUFF_CORO_END(Coro);
  return 0;
}


///@Function: Coro_CarPark
///@Descript: Semaphore Sample Car Parking
int Coro_CarPark(xDuff_Coro *Coro,int ID)
{
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    xDUFF_CORO_SEM_WAIT(Coro,&ParkSem);
    printf("[Car-%d]: Enter (Remain: %d)\n",ID,ParkSem.Count);
    xDUFF_CORO_YIELD(Coro,0);
    xDUFF_CORO_YIELD(Coro,0);
    xDUFF_CORO_YIELD(Coro,0);
    xDUFF_CORO_SEM_SIGNAL(&ParkSem);
    printf("[Car-%d]: Leave (Remain: %d)\n",ID,ParkSem.Count);
  }
  xDUFF_CORO_END(Coro);
  return 0;
}


///@Function: Coro_SmartLight
///@Descript: Delay Sample for Smart Light
int Coro_SmartLight(xDuff_Coro *Coro)
{
  static int Delay = 0;
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    xDUFF_CORO_WAIT_UNTIL(Coro,(CarSensed == 1));
    xDUFF_CORO_DELAY(Coro,Delay,5);
    CarSensed = 0;
    printf("[Smart]: One Cycle Finish!! Reset...\n");
  }
  xDUFF_CORO_END(Coro);
  return 0;
}


///@Function: Coro_BGLog
///@Descript: Every Sample for BG Log
int Coro_BGLog(xDuff_Coro *Coro)
{
  static int Delay = 0;
  static int Count = 0;
  xDUFF_CORO_BEGIN(Coro);
  while(1)
  {
    xDUFF_CORO_EVERY(Count,3,PrintInfo());
    xDUFF_CORO_YIELD(Coro,0);
    CarSensed = 1;
    xDUFF_CORO_DELAY(Coro,Delay,2);
  }
  xDUFF_CORO_END(Coro);
  return 0;
}



///@Function: PrintInfo
///@Descript: Print Information
void PrintInfo(void)
{
  printf("[LOG]: System Health OK!!\n");
}