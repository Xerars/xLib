#!/bin/bash

# Project : xCPrint.sh
# Author  : William Hsiao
# Descript: Color Terminal Control & Formatted Output
# Version : 1.2.0

# Guard
[[ -n "${__XCPRINT_SHELL_INCLUDED__:-}" ]] && return 0
__XCPRINT_SHELL_INCLUDED__=1

# [Macro Declare]
# Reset
declare -r CPRINT_RESET=$'\033[0m'                # Reset All Attributes

# Text
declare -r CPRINT_BOLD=$'\033[1m'                 # Bold       Text
declare -r CPRINT_DIM=$'\033[2m'                  # Dim        Text
declare -r CPRINT_ITALIC=$'\033[3m'               # Italic     Text
declare -r CPRINT_UNDERLINE=$'\033[4m'            # Underlined Text
declare -r CPRINT_BLINK=$'\033[5m'                # Blinking   Text
declare -r CPRINT_REVERSE=$'\033[7m'              # Reverse Fore & Back
declare -r CPRINT_HIDE=$'\033[8m'                 # Hidden     Text
declare -r CPRINT_STRIKE=$'\033[9m'               # Strike     Text

# Fore-Color
declare -r CPRINT_FG_RED=$'\033[0;31m'            # Red          Fore-Ground
declare -r CPRINT_FG_GREEN=$'\033[0;32m'          # Green        Fore-Ground
declare -r CPRINT_FG_YELLOW=$'\033[0;33m'         # Yellow       Fore-Ground
declare -r CPRINT_FG_BLUE=$'\033[0;34m'           # Blue         Fore-Ground
declare -r CPRINT_FG_MAGENTA=$'\033[0;35m'        # Magenta      Fore-Ground
declare -r CPRINT_FG_CYAN=$'\033[0;36m'           # Cyan         Fore-Ground
declare -r CPRINT_FG_WHITE=$'\033[0;37m'          # White        Fore-Ground

# Fore-Color(Bold)
declare -r CPRINT_FG_BOLD_RED=$'\033[1;31m'       # Bold Red     Fore-Ground
declare -r CPRINT_FG_BOLD_GREEN=$'\033[1;32m'     # Bold Green   Fore-Ground
declare -r CPRINT_FG_BOLD_YELLOW=$'\033[1;33m'    # Bold Yellow  Fore-Ground
declare -r CPRINT_FG_BOLD_BLUE=$'\033[1;34m'      # Bold Blue    Fore-Ground
declare -r CPRINT_FG_BOLD_MAGENTA=$'\033[1;35m'   # Bold Magenta Fore-Ground
declare -r CPRINT_FG_BOLD_CYAN=$'\033[1;36m'      # Bold Cyan    Fore-Ground
declare -r CPRINT_FG_BOLD_WHITE=$'\033[1;37m'     # Bold White   Fore-Ground

# Back-Color
declare -r CPRINT_BG_BLACK=$'\033[40m'            # Black        Back-Ground
declare -r CPRINT_BG_RED=$'\033[41m'              # Red          Back-Ground
declare -r CPRINT_BG_GREEN=$'\033[42m'            # Green        Back-Ground
declare -r CPRINT_BG_YELLOW=$'\033[43m'           # Yellow       Back-Ground
declare -r CPRINT_BG_BLUE=$'\033[44m'             # Blue         Back-Ground
declare -r CPRINT_BG_MAGENTA=$'\033[45m'          # Magenta      Back-Ground
declare -r CPRINT_BG_CYAN=$'\033[46m'             # Cyan         Back-Ground
declare -r CPRINT_BG_WHITE=$'\033[47m'            # White        Back-Ground


# Function: xPRINT
# Descript: Print Color Message
xPRINT()
{
  local Attr="$1"                   # Get Print Attribute
  shift                             # Shift to Format String and Argument
  
  [[ $# -eq 0 ]] && return 0        # Check Format String
  printf '%b' "${Attr}"             # Output ANSI Attribute
  printf "$@"                       # Output Format String & Arguments
  printf '%b' "${CPRINT_RESET}"     # Reset Attribute and Print NewLine
}

# [Macro Function Declare]
# Color Print
xFG_RPRINT() { xPRINT "$CPRINT_FG_RED"          "$@"; }  # Print Formatted Text With Red          ForeGround Color
xFG_GPRINT() { xPRINT "$CPRINT_FG_GREEN"        "$@"; }  # Print Formatted Text With Green        ForeGround Color 
xFG_YPRINT() { xPRINT "$CPRINT_FG_YELLOW"       "$@"; }  # Print Formatted Text With Yellow       ForeGround Color 
xFG_BPRINT() { xPRINT "$CPRINT_FG_BLUE"         "$@"; }  # Print Formatted Text With Blue         ForeGround Color 
xFG_MPRINT() { xPRINT "$CPRINT_FG_MAGENTA"      "$@"; }  # Print Formatted Text With Magenta      ForeGround Color 
xFG_CPRINT() { xPRINT "$CPRINT_FG_CYAN"         "$@"; }  # Print Formatted Text With Cyan         ForeGround Color 
xFG_WPRINT() { xPRINT "$CPRINT_FG_WHITE"        "$@"; }  # Print Formatted Text With White        ForeGround Color 

# Bold Color Print
xFB_RPRINT() { xPRINT "$CPRINT_FG_BOLD_RED"     "$@"; }  # Print Formatted Text With Bold Red     ForeGround Color
xFB_GPRINT() { xPRINT "$CPRINT_FG_BOLD_GREEN"   "$@"; }  # Print Formatted Text With Bold Green   ForeGround Color
xFB_YPRINT() { xPRINT "$CPRINT_FG_BOLD_YELLOW"  "$@"; }  # Print Formatted Text With Bold Yellow  ForeGround Color
xFB_BPRINT() { xPRINT "$CPRINT_FG_BOLD_BLUE"    "$@"; }  # Print Formatted Text With Bold Blue    ForeGround Color
xFB_MPRINT() { xPRINT "$CPRINT_FG_BOLD_MAGENTA" "$@"; }  # Print Formatted Text With Bold Magenta ForeGround Color
xFB_CPRINT() { xPRINT "$CPRINT_FG_BOLD_CYAN"    "$@"; }  # Print Formatted Text With Bold Cyan    ForeGround Color
xFB_WPRINT() { xPRINT "$CPRINT_FG_BOLD_WHITE"   "$@"; }  # Print Formatted Text With Bold White   ForeGround Color

# Candy
xRPRINT()    { xPRINT "$CPRINT_FG_RED"          "$@"; }  # Print Formatted Text With Red     ForeGround Color
xGPRINT()    { xPRINT "$CPRINT_FG_GREEN"        "$@"; }  # Print Formatted Text With Green   ForeGround Color
xYPRINT()    { xPRINT "$CPRINT_FG_YELLOW"       "$@"; }  # Print Formatted Text With Yellow  ForeGround Color
xBPRINT()    { xPRINT "$CPRINT_FG_BLUE"         "$@"; }  # Print Formatted Text With Blue    ForeGround Color 
xMPRINT()    { xPRINT "$CPRINT_FG_MAGENTA"      "$@"; }  # Print Formatted Text With Magenta ForeGround Color
xCPRINT()    { xPRINT "$CPRINT_FG_CYAN"         "$@"; }  # Print Formatted Text With Cyan    ForeGround Color
xWPRINT()    { xPRINT "$CPRINT_FG_WHITE"        "$@"; }  # Print Formatted Text With White   ForeGround Color

# Utility
xINFO()  { local fmt="$1"; shift; xFB_CPRINT "[INFO] : $fmt" "$@"; }  # Print Info    Message With Bold Cyan   Color
xWARN()  { local fmt="$1"; shift; xFB_YPRINT "[WARN] : $fmt" "$@"; }  # Print Warn    Message With Bold Yellow Color
xERROR() { local fmt="$1"; shift; xFB_RPRINT "[ERROR]: $fmt" "$@"; }  # Print Error   Message With Bold Red    Color
xPASS()  { local fmt="$1"; shift; xFB_GPRINT "[PASS] : $fmt" "$@"; }  # Print Success Message With Bold Green  Color 
