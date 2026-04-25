//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

#ifdef LEAKCHECK
  #include "xLeakCheck.h"
#endif

//[Prototype Declare]
void Show_LeakMemInfo(void);

//Main Code
int main(void)
{
#ifdef LEAKCHECK
  atexit(Show_LeakMemInfo);
#endif    //LEAKCHECK

  int* ptr1 = malloc(1000*sizeof(int));
  int* ptr2 = calloc(1000,sizeof(int));

  memset(ptr1,0,1000*sizeof(int));
  memset(ptr2,0,1000*sizeof(int));

  ptr1=realloc(ptr1,2000*sizeof(int));
  memset(ptr1,0,2000*sizeof(int));

  return 0;
}

//Function:ShowLeakMemoryInfo
//Descript:Show Leak Memory Information
void Show_LeakMemInfo(void)
{
  xLeak_MemInfo();
}