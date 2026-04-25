//Demo CPrint Lib How to Control Color Output Using ANSI on Linux

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xCPrint.h"

//Main Code
int main(void)
{
  int i = 0;
  xFG_RPRINT("This is Color Red    [%d]\n",i++);
  xFG_GPRINT("This is Color Green  [%d]\n",i++);
  xFG_BPRINT("This is Color Blue   [%d]\n",i++);
  xFG_YPRINT("This is Color Yellow [%d]\n",i++);
  xFG_MPRINT("This is Color Magenta[%d]\n",i++);
  xFG_CPRINT("This is Color Cyan   [%d]\n",i++);
  xFG_WPRINT("This is Color White  [%d]\n",i++);
  printf("\n\n");

  xFB_RPRINT("This is Bold Red     [%d]\n",i++);
  xFB_GPRINT("This is Bold Green   [%d]\n",i++);
  xFB_BPRINT("This is Bold Blue    [%d]\n",i++);
  xFB_YPRINT("This is Bold Yellow  [%d]\n",i++);
  xFB_MPRINT("This is Bold Blue    [%d]\n",i++);
  xFB_CPRINT("This is Bold Cyan    [%d]\n",i++);
  xFB_WPRINT("This is Bold Blue    [%d]\n",i++);
  printf("\n\n");

  //Type
  xPRINT(xTYPE_CLI_ITALIC ,"Italic Text\n");
  xPRINT(xTYPE_CLI_STRIKE ,"Strikethrough Text\n");
  xPRINT(xTYPE_CLI_REVERSE,"Reversed Color\n");
  xPRINT(xTYPE_CLI_BLINK  ,"Blinking Text\n");
  printf("\n\n");

  //Candy
  xRPRINT("This is Bold Red     [%d]\n",i++);
  xGPRINT("This is Bold Green   [%d]\n",i++);
  xYPRINT("This is Bold Blue    [%d]\n",i++);
  xBPRINT("This is Bold Yellow  [%d]\n",i++);
  xMPRINT("This is Bold Blue    [%d]\n",i++);
  xCPRINT("This is Bold Cyan    [%d]\n",i++);
  xWPRINT("This is Bold Blue    [%d]\n",i++);
  printf("\n\n");

  //Custom
  xPRINT(xBG_CLI_RED  xFG_CLI_WHITE, " White text on Red background\n");
  xPRINT(xBG_CLI_BLUE xFG_CLI_YELLOW xTYPE_CLI_BOLD, " Bold Yellow text on Blue background\n");
  printf("\n\n");

  //Format
  int   Status   = 404;
  char *Msg      = "Not Found"; 
  DBL   Progress = 85.5;
  xFB_RPRINT("Error [%d]: %s\n",Status,Msg);
  xFB_GPRINT("System Update: %.1f%% Complete\n",Progress);
  return 0;
}