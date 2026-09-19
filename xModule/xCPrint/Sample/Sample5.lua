#!/usr/bin/env lua

-- Demo CPrint Lib How to Control Color Output Using ANSI on Lua
package.path = package.path .. ";../?.lua"
local xCPrint = require("xCPrint")


-- Basic Color Test
xCPrint.xPRINT(xCPrint.xTYPE_CLI_UNDERLINE, "Under Line Text\n")

xCPrint.xFG_RPRINT("Red     Fore-Color Text\n")
xCPrint.xFG_GPRINT("Green   Fore-Color Text\n")
xCPrint.xFG_YPRINT("Yellow  Fore-Color Text\n")
xCPrint.xFG_BPRINT("Blue    Fore-Color Text\n")
xCPrint.xFG_MPRINT("Magenta Fore-Color Text\n")
xCPrint.xFG_CPRINT("Cyan    Fore-Color Text\n")
xCPrint.xFG_WPRINT("White   Fore-Color Text\n")


xCPrint.xFB_RPRINT("Red     Back-Color Text\n")
xCPrint.xFB_GPRINT("Green   Back-Color Text\n")
xCPrint.xFB_YPRINT("Yellow  Back-Color Text\n")
xCPrint.xFB_BPRINT("Blue    Back-Color Text\n")
xCPrint.xFB_MPRINT("Magenta Back-Color Text\n")
xCPrint.xFB_CPRINT("Cyan    Back-Color Text\n")
xCPrint.xFB_WPRINT("White   Back-Color Text\n")


xCPrint.xINFO("Info Info   : %d%%\n",50)
xCPrint.xWARN("Warn Warn   : %d%%\n",85)
xCPrint.xERROR("Error Error: %d\n"  ,-1)
xCPrint.xPASS("Pass Pass   : %.3f\n",0.125)