//Demo CPrint Lib Using a Drawing Tool to Output to Windows

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xCPrint.h"

//[OS Lib Include]
#ifdef __WIN32
  #include "windows.h"
#endif

//Main Code
int main(void)
{
#ifdef __WIN32
  int Value = 5;
  xWIN_RPRINT("Windows Color Red    [%d]\n",Value);
  xWIN_GPRINT("Windows Color Green  [%d]\n",Value);
  xWIN_BPRINT("Windows Color Blue   [%d]\n",Value);
  xWIN_YPRINT("Windows Color Yellow [%d]\n",Value);
  xWIN_CPRINT("Windows Color Cyan   [%d]\n",Value);
  xWIN_MPRINT("Windows Color Magenta[%d]\n",Value);
  xWIN_WPRINT("Windows Color White  [%d]\n",Value);
#endif
  return 0;
}