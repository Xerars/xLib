#ifndef __XCPRINT_H__ //__XCPRINT_H__
#define __XCPRINT_H__ //__XCPRINT_H__

//Author  : William Hsiao
//Descript: Color Terminal Control & Formatted Output
//Version : 1.0.0

//[STD Lib Include]
#include <stdio.h>
#include <stdarg.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//[OS Lib Include]
#ifdef _WIN32
  #include <windows.h>
#endif  //_WIN32

//[Macro Declare]
#define xFG_CLI_RESET         "\033[0m"           //Reset

//Front Color
#define xFG_CLI_RED           "\033[0;31m"        //Front Red
#define xFG_CLI_GREEN         "\033[0;32m"        //Front Green
#define xFG_CLI_YELLOW        "\033[0;33m"        //Front Yellow
#define xFG_CLI_BLUE          "\033[0;34m"        //Front Blue
#define xFG_CLI_MAGENTA       "\033[0;35m"        //Front Megenta
#define xFG_CLI_CYAN          "\033[0;36m"        //Front Cyan
#define xFG_CLI_WHITE         "\033[0;37m"        //Front White

//Front Bold Color
#define xFG_CLI_BOLD_RED      "\033[1;31m"        //Front Bold Red
#define xFG_CLI_BOLD_GREEN    "\033[1;32m"        //Front Bold Green
#define xFG_CLI_BOLD_YELLOW   "\033[1;33m"        //Front Bold Yellow
#define xFG_CLI_BOLD_BLUE     "\033[1;34m"        //Front Bold Blue
#define xFG_CLI_BOLD_MAGENTA  "\033[1;35m"        //Front Bold Megenta
#define xFG_CLI_BOLD_CYAN     "\033[1;36m"        //Front Bold Cyan
#define xFG_CLI_BOLD_WHITE    "\033[1;37m"        //Front Bold White

//Back Color
#define xBG_CLI_BLACK         "\033[40m"          //Back Black
#define xBG_CLI_RED           "\033[41m"          //Back Red
#define xBG_CLI_GREEN         "\033[42m"          //Back Green
#define xBG_CLI_YELLOW        "\033[43m"          //Back Yellow
#define xBG_CLI_BLUE          "\033[44m"          //Back Blue
#define xBG_CLI_MAGENTA       "\033[45m"          //Back Magenta
#define xBG_CLI_CYAN          "\033[46m"          //Back Cyan
#define xBG_CLI_WHITE         "\033[47m"          //Back White

//Type
#define xTYPE_CLI_BOLD        "\033[1m"           //Type Bold
#define xTYPE_CLI_DIM         "\033[2m"           //Type Dim
#define xTYPE_CLI_ITALIC      "\033[3m"           //Type Italic
#define xTYPE_CLI_UNDERLINE   "\033[4m"           //Type Underline
#define xTYPE_CLI_BLINK       "\033[5m"           //Type Slow  Blink
#define xTYPE_CLI_RAPID_BLINK "\033[6m"           //Type Rapid Blink
#define xTYPE_CLI_REVERSE     "\033[7m"           //Type Reverse
#define xTYPE_CLI_HIDE        "\033[8m"           //Type Hide
#define xTYPE_CLI_STRIKE      "\033[9m"           //Type Strike

//Windows
#ifdef _WIN32
#define xCOLOR_WIN_RED        (FOREGROUND_RED)
#define xCOLOR_WIN_GREEN      (FOREGROUND_GREEN)
#define xCOLOR_WIN_BLUE       (FOREGROUND_BLUE)
#define xCOLOR_WIN_YELLOW     (FOREGROUND_RED   | FOREGROUND_GREEN)
#define xCOLOR_WIN_CYAN       (FOREGROUND_GREEN | FOREGROUND_BLUE)
#define xCOLOR_WIN_MAGENTA    (FOREGROUND_RED   | FOREGROUND_BLUE)
#define xCOLOR_WIN_WHITE      (FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define xCOLOR_WIN_BOLD       (FOREGROUND_INTENSITY)
#endif  //_WIN32

#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
#ifdef _WIN32
void xWin_AnsiEnable(void);
void xWin_CPrint(WORD Color,CCHAR* fmt,...);
#endif  //_WIN32

#ifdef __cplusplus
}
#endif

//[Macro Function Declare]
//Color Print
#define xFG_RPRINT(FMT,...)   printf(xFG_CLI_RED          FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFG_GPRINT(FMT,...)   printf(xFG_CLI_GREEN        FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFG_YPRINT(FMT,...)   printf(xFG_CLI_YELLOW       FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFG_BPRINT(FMT,...)   printf(xFG_CLI_BLUE         FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFG_MPRINT(FMT,...)   printf(xFG_CLI_MAGENTA      FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFG_CPRINT(FMT,...)   printf(xFG_CLI_CYAN         FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFG_WPRINT(FMT,...)   printf(xFG_CLI_WHITE        FMT xFG_CLI_RESET,##__VA_ARGS__)

//Bold Color Print
#define xFB_RPRINT(FMT,...)   printf(xFG_CLI_BOLD_RED     FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFB_GPRINT(FMT,...)   printf(xFG_CLI_BOLD_GREEN   FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFB_YPRINT(FMT,...)   printf(xFG_CLI_BOLD_YELLOW  FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFB_BPRINT(FMT,...)   printf(xFG_CLI_BOLD_BLUE    FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFB_MPRINT(FMT,...)   printf(xFG_CLI_BOLD_MAGENTA FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFB_CPRINT(FMT,...)   printf(xFG_CLI_BOLD_CYAN    FMT xFG_CLI_RESET,##__VA_ARGS__)
#define xFB_WPRINT(FMT,...)   printf(xFG_CLI_BOLD_WHITE   FMT xFG_CLI_RESET,##__VA_ARGS__)

//Print
#define xPRINT(ATTR,FMT,...)  printf(ATTR FMT xFG_CLI_RESET,##__VA_ARGS__)

//Candy
#define xRPRINT(FMT,...)      xPRINT(xFG_CLI_RED    ,FMT,##__VA_ARGS__)
#define xGPRINT(FMT,...)      xPRINT(xFG_CLI_GREEN  ,FMT,##__VA_ARGS__)
#define xYPRINT(FMT,...)      xPRINT(xFG_CLI_YELLOW ,FMT,##__VA_ARGS__)
#define xBPRINT(FMT,...)      xPRINT(xFG_CLI_BLUE   ,FMT,##__VA_ARGS__)
#define xMPRINT(FMT,...)      xPRINT(xFG_CLI_MAGENTA,FMT,##__VA_ARGS__)
#define xCPRINT(FMT,...)      xPRINT(xFG_CLI_CYAN   ,FMT,##__VA_ARGS__)
#define xWPRINT(FMT,...)      xPRINT(xFG_CLI_WHITE  ,FMT,##__VA_ARGS__)

//Windows Brush
#ifdef _WIN32
#define xWIN_RPRINT(FMT,...)  xWin_CPrint(xCOLOR_WIN_RED    ,FMT,##__VA_ARGS__)
#define xWIN_GPRINT(FMT,...)  xWin_CPrint(xCOLOR_WIN_GREEN  ,FMT,##__VA_ARGS__)
#define xWIN_BPRINT(FMT,...)  xWin_CPrint(xCOLOR_WIN_BLUE   ,FMT,##__VA_ARGS__)
#define xWIN_YPRINT(FMT,...)  xWin_CPrint(xCOLOR_WIN_YELLOW ,FMT,##__VA_ARGS__)
#define xWIN_CPRINT(FMT,...)  xWin_CPrint(xCOLOR_WIN_CYAN   ,FMT,##__VA_ARGS__)
#define xWIN_MPRINT(FMT,...)  xWin_CPrint(xCOLOR_WIN_MAGENTA,FMT,##__VA_ARGS__)
#define xWIN_WPRINT(FMT,...)  xWin_CPrint(xCOLOR_WIN_WHITE  ,FMT,##__VA_ARGS__)
#endif  //_WIN32

#endif  //__XCPRINT_H__
