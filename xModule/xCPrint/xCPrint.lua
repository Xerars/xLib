-- Project : xCPrint.lua
-- Author  : William Hsiao
-- Descript: Color Terminal Control & Formatted Output
-- Version : 1.2.0

local xCPrint = {}

-- [Macro Declare]
-- Reset
xCPrint.xFG_CLI_RESET         = "\27[0m"          -- Reset

-- Foreground Color
xCPrint.xFG_CLI_RED           = "\27[0;31m"       -- Foreground Red
xCPrint.xFG_CLI_GREEN         = "\27[0;32m"       -- Foreground Green
xCPrint.xFG_CLI_YELLOW        = "\27[0;33m"       -- Foreground Yellow
xCPrint.xFG_CLI_BLUE          = "\27[0;34m"       -- Foreground Blue
xCPrint.xFG_CLI_MAGENTA       = "\27[0;35m"       -- Foreground Magenta
xCPrint.xFG_CLI_CYAN          = "\27[0;36m"       -- Foreground Cyan
xCPrint.xFG_CLI_WHITE         = "\27[0;37m"       -- Foreground White


-- Foreground Bold Color
xCPrint.xFG_CLI_BOLD_RED      = "\27[1;31m"       -- Foreground Bold Red
xCPrint.xFG_CLI_BOLD_GREEN    = "\27[1;32m"       -- Foreground Bold Green
xCPrint.xFG_CLI_BOLD_YELLOW   = "\27[1;33m"       -- Foreground Bold Yellow
xCPrint.xFG_CLI_BOLD_BLUE     = "\27[1;34m"       -- Foreground Bold Blue
xCPrint.xFG_CLI_BOLD_MAGENTA  = "\27[1;35m"       -- Foreground Bold Magenta
xCPrint.xFG_CLI_BOLD_CYAN     = "\27[1;36m"       -- Foreground Bold Cyan
xCPrint.xFG_CLI_BOLD_WHITE    = "\27[1;37m"       -- Foreground Bold White


-- Background Color
xCPrint.xBG_CLI_BLACK         = "\27[40m"         -- Background Black
xCPrint.xBG_CLI_RED           = "\27[41m"         -- Background Red
xCPrint.xBG_CLI_GREEN         = "\27[42m"         -- Background Green
xCPrint.xBG_CLI_YELLOW        = "\27[43m"         -- Background Yellow
xCPrint.xBG_CLI_BLUE          = "\27[44m"         -- Background Blue
xCPrint.xBG_CLI_MAGENTA       = "\27[45m"         -- Background Magenta
xCPrint.xBG_CLI_CYAN          = "\27[46m"         -- Background Cyan
xCPrint.xBG_CLI_WHITE         = "\27[47m"         -- Background White


-- Text Type
xCPrint.xTYPE_CLI_BOLD        = "\27[1m"          -- Type Bold
xCPrint.xTYPE_CLI_DIM         = "\27[2m"          -- Type Dim
xCPrint.xTYPE_CLI_ITALIC      = "\27[3m"          -- Type Italic
xCPrint.xTYPE_CLI_UNDERLINE   = "\27[4m"          -- Type Underline
xCPrint.xTYPE_CLI_BLINK       = "\27[5m"          -- Type Slow Blink
xCPrint.xTYPE_CLI_RAPID_BLINK = "\27[6m"          -- Type Rapid Blink
xCPrint.xTYPE_CLI_REVERSE     = "\27[7m"          -- Type Reverse
xCPrint.xTYPE_CLI_HIDE        = "\27[8m"          -- Type Hide
xCPrint.xTYPE_CLI_STRIKE      = "\27[9m"          -- Type Strike

-- Function: xPRINT
-- Descript: Print Formatted Text With Terminal Attribute
function xCPrint.xPRINT(Attr,Fmt,...)
  if Fmt == nil then
    return
  end

  io.write(Attr)
  io.write(string.format(Fmt,...))
  io.write(xCPrint.xFG_CLI_RESET)
end


-- [Macro Function Declare]
-- Fore Color
-- Print Formatted Text in Red
function xCPrint.xFG_RPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_RED,Fmt,...)
end

-- Print Formatted Text in Green
function xCPrint.xFG_GPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_GREEN,Fmt,...)
end

-- Print Formatted Text in Yellow
function xCPrint.xFG_YPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_YELLOW,Fmt,...)
end

-- Print Formatted Text in Blue
function xCPrint.xFG_BPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_BLUE,Fmt,...)
end

-- Print Formatted Text in Magenta
function xCPrint.xFG_MPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_MAGENTA,Fmt,...)
end

-- Print Formatted Text in Cyan
function xCPrint.xFG_CPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_CYAN,Fmt,...)
end

-- Print Formatted Text in White
function xCPrint.xFG_WPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_WHITE,Fmt,...)
end


-- Bold Color Print
-- Print Formatted Text in Bold Red
function xCPrint.xFB_RPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_BOLD_RED,Fmt,...)
end

-- Print Formatted Text in Bold Green
function xCPrint.xFB_GPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_BOLD_GREEN,Fmt,...)
end

-- Print Formatted Text in Bold Yellow
function xCPrint.xFB_YPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_BOLD_YELLOW,Fmt,...)
end

-- Print Formatted Text in Bold Blue
function xCPrint.xFB_BPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_BOLD_BLUE,Fmt,...)
end

-- Print Formatted Text in Bold Magenta
function xCPrint.xFB_MPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_BOLD_MAGENTA,Fmt,...)
end

-- Print Formatted Text in Bold Cyan
function xCPrint.xFB_CPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_BOLD_CYAN,Fmt,...)
end

-- Print Formatted Text in Bold White
function xCPrint.xFB_WPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_BOLD_WHITE,Fmt,...)
end


-- Candy
-- Print Red Text Using Short Function Name
function xCPrint.xRPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_RED,Fmt,...)
end

-- Print Green Text Using Short Function Name
function xCPrint.xGPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_GREEN,Fmt,...)
end

-- Print Yellow Text Using Short Function Name
function xCPrint.xYPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_YELLOW,Fmt,...)
end

-- Print Blue Text Using Short Function Name
function xCPrint.xBPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_BLUE,Fmt,...)
end

-- Print Magenta Text Using Short Function Name
function xCPrint.xMPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_MAGENTA,Fmt,...)
end

-- Print Cyan Text Using Short Function Name
function xCPrint.xCPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_CYAN,Fmt,...)
end

-- Print White Text Using Short Function Name
function xCPrint.xWPRINT(Fmt,...)
  xCPrint.xPRINT(xCPrint.xFG_CLI_WHITE,Fmt,...)
end


-- Utility
-- Print Info Message in Bold Cyan
function xCPrint.xINFO(Fmt,...)
  xCPrint.xFB_CPRINT("[INFO]:  " .. Fmt,...)
end

-- Print Warn Message in Bold Yellow
function xCPrint.xWARN(Fmt,...)
  xCPrint.xFB_YPRINT("[WARN]:  " .. Fmt,...)
end

-- Print Error Message in Bold Red
function xCPrint.xERROR(Fmt,...)
  xCPrint.xFB_RPRINT("[ERROR]: " .. Fmt,...)
end

-- Print Success Message in Bold Green
function xCPrint.xPASS(Fmt,...)
  xCPrint.xFB_GPRINT("[PASS]:  " .. Fmt,...)
end

return xCPrint
