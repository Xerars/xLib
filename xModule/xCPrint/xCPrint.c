//[xLib Include]
#include "xCPrint.h"

//Author  : William Hsiao
//Descript: Color Terminal Control & Formatted Output
//Version : 1.0.0

#ifdef _WIN32
///@Function: xWin_AnsiEnable
///@Descript: Enable Windows ANSI
void xWin_AnsiEnable(void)
{
  HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
  if(Out == INVALID_HANDLE_VALUE)
    return;

  DWORD Mode = 0;
  if(!GetConsoleMode(Out,&Mode))
    return;
  
  Mode |= 0x0004;
  SetConsoleMode(Out,Mode);
}


///@Function: xWin_CPrint
///@Descript: Windows Color Print
void xWin_CPrint(WORD Color,CCHAR* fmt,...)
{
  //Get STD Handle
  HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);

  //Backup Current Color
  CONSOLE_SCREEN_BUFFER_INFO CSBI;
  GetConsoleScreenBufferInfo(Console,&CSBI);
  WORD OColor = CSBI.wAttributes;

  //Switch Color
  SetConsoleTextAttribute(Console,Color);

  //Process Var
  va_list Args;
  va_start(Args,fmt);
  vprintf(fmt,Args);
  va_end(Args);

  //Recover
  SetConsoleTextAttribute(Console,OColor);
}

#endif
