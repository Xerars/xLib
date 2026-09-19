#!/bin/bash

# Demo CPrint Lib How to Control Color Output Using ANSI on Shell

source ../xCPrint.sh

xPRINT "${CPRINT_UNDERLINE}" "Under Line Text\n"

xFG_RPRINT "Red     Fore-Color Text\n"
xFG_GPRINT "Green   Fore-Color Text\n"
xFG_YPRINT "Yellow  Fore-Color Text\n"
xFG_BPRINT "Blue    Fore-Color Text\n"
xFG_MPRINT "Magenta Fore-Color Text\n"
xFG_CPRINT "Cyan    Fore-Color Text\n"
xFG_WPRINT "White   Fore-Color Text\n"


xPRINT "${CPRINT_BG_RED}"     "Red     Back-Color Text\n"
xPRINT "${CPRINT_BG_GREEN}"   "Green   Back-Color Text\n"
xPRINT "${CPRINT_BG_YELLOW}"  "Yellow  Back-Color Text\n"
xPRINT "${CPRINT_BG_BLUE}"    "Blue    Back-Color Text\n"
xPRINT "${CPRINT_BG_MAGENTA}" "Magenta Back-Color Text\n"
xPRINT "${CPRINT_BG_CYAN}"    "Cyan    Back-Color Text\n"
xPRINT "${CPRINT_BG_WHITE}"   "White   Back-Color Text\n"

xINFO  "Info Info   : %d%%\n" 50
xWARN  "Warn Warn   : %d%%\n" 85
xERROR "Error Error : %d\n"   -1
xPASS  "Pass Pass   : %.3f\n" 0.125