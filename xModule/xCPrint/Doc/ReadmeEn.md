# xCPrint

> **Project** : xCPrint
> **Author**  : William Hsiao
> **Descript**: Cross-platform color terminal control and formatted output library

## Introduction
`xCPrint` is a lightweight output utility library designed specifically for embedded systems and cross-platform C development.

It provides API compatibility for the `Windows` environment, solving the problem that traditional `printf` cannot directly output in color.

* Cross-platform support: Automatically detects `_WIN32` environments.
* Zero-overhead macros: Most functions are implemented through preprocessed macros, consuming no program space when not calling functions.
* Type safe: Strictly adheres to the `C99` standard and supports variable-argument macros (__VA_ARGS__).

## Features

1. ANSI Color Control: Supports 8 basic colors, a Bold mode, and background color settings.
2. Terminal State Resume: All output functions automatically append a RESET code at the end to prevent color contamination of subsequent output.
3. Windows Compatibility: Built-in xWin_AnsiEnable enables ANSI support in Windows terminals with a single click.
4. Minimal Dependencies: Only depends on xType.h and xMeta.h.

## API
#### [Color Macro Definition]
1. `xFG_CLI_COLOR`     : Base foreground color `ANSI` string.
2. `xFG_CLI_BOLD_COLOR`: Bold/high-brightness foreground color.
3. `xBG_CLI_COLOR`     : Background color setting.
4. `xTYPE_CLI_BOLD...` : Text style options such as bold,italic and underline.

#### [Core Functions]
1. `xWin_AnsiEnable`: (Windows-specific) Enables ANSI escape sequence processing via `SetConsoleMode`.
2. `xWin_CPrint`: (Windows-specific) Uses native APIs for color output, independent of ANSI codes.

#### [Core Macro Functions]
1. `xRPRINT/xGPRINT/xBPRINT`: Candy series. Most commonly used quick output for red, green, and blue.
2. `xFG_RPRINT/xFG_GPRINT`: Standard foreground color output.
3. `xFB_RPRINT/xFB_GPRINT`: High-bold (`Bold`) foreground color output.
4. `xPRINT(ATTR,FMT, ...)`: General output. `ATTR` can be customized (e.g., setting both background and foreground simultaneously).

5. `xWIN_RPRINT/xWIN_GPRINT`: (`Windows` specific) Forces the use of `Windows API` pen output.
## Library Information
1. The `xCPrint` library size on Linux is `0KB`.
2. On Linux, it is a simple macro library.

## Compilation Dependencies
##### [Header Dependencies]
1. `xMeta.h`
2. `xType.h`

##### [Compilation]
Use the command `make all` within the `xCPrint` folder.

```shell
make all
```

## example
Use the command `make all` within the `Sample` folder.

```shell
make all
```

#### [Example 1]
1. Demonstration of using `xCPrint` on the `Linux` platform.

```c
int main(void)
{
  int i = 0;
  xFG_RPRINT("This is Color Red    [%d]\n",i++);
  xFB_RPRINT("This is Bold Red     [%d]\n",i++);
  //Type
  xPRINT(xTYPE_CLI_ITALIC ,"Italic Text\n");
  xPRINT(xTYPE_CLI_STRIKE ,"Strikethrough Text\n");
  xPRINT(xTYPE_CLI_REVERSE,"Reversed Color\n");
  xPRINT(xTYPE_CLI_BLINK  ,"Blinking Text\n");
  printf("\n\n");

  //Candy
  xRPRINT("This is Bold Red     [%d]\n",i++);
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
```

#### [Example 2]
1. Demonstrate using `CPrint` with `ANSI Color` on `Windows`
2. Same content as Example 1, but with the following added:

```c
#ifdef __WIN32
  xWin_AnsiEnable();    //Windows ANSI Enable
#endif
```

#### [Example 3]
1. Demonstration of using `CPrint` with a wrapper pen function in `Windows`.
2. 
```c
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
```

## License Terms
This project is licensed under the `MIT License`.
