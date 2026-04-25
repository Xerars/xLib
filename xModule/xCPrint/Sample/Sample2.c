//Demo CPinrt Lib How to Control Color Output Using ANSI on Windows

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
  xWin_AnsiEnable();    //Windows ANSI Enable
#endif

  xFG_RPRINT("This is Color Red    \n");
  xFG_GPRINT("This is Color Green  \n");
  xFG_BPRINT("This is Color Blue   \n");
  xFG_YPRINT("This is Color Yellow \n");
  xFG_MPRINT("This is Color Magenta\n");
  xFG_CPRINT("This is Color Cyan   \n");
  xFG_WPRINT("This is Color White  \n");
  printf("\n\n");

  xFB_RPRINT("This is Bold Red     \n");
  xFB_GPRINT("This is Bold Green   \n");
  xFB_BPRINT("This is Bold Blue    \n");
  xFB_YPRINT("This is Bold Yellow  \n");
  xFB_MPRINT("This is Bold Blue    \n");
  xFB_CPRINT("This is Bold Cyan    \n");
  xFB_WPRINT("This is Bold Blue    \n");
  printf("\n\n");

  //Type
  xPRINT(xTYPE_CLI_ITALIC ,"Italic Text");
  xPRINT(xTYPE_CLI_STRIKE ,"Strikethrough Text");
  xPRINT(xTYPE_CLI_REVERSE,"Reversed Color");
  xPRINT(xTYPE_CLI_BLINK  ,"Blinking Text");

  //Custom
  xPRINT(xBG_CLI_RED  xFG_CLI_WHITE,"White Text on Red Background\n");
  xPRINT(xBG_CLI_BLUE xFG_CLI_YELLOW xTYPE_CLI_BOLD," Bold Yellow Text on Blue Background\n");

  //Format
  int   Status   = 404;
  char *Msg      = "Not Found"; 
  DBL   Progress = 85.5;
  xFB_RPRINT("Error [%d]: %s\n",Status,Msg);
  xFB_GPRINT("System Update: %.1f%% Complete\n",Progress);
  return 0;
}