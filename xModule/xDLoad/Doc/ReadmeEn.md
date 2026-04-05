# xDLoad

> **Project** : xDLoad  
> **Author**  : William Hsiao  
> **Descript**: Cross-Platform Dynamic Library Loading Utility  


## Overview
`xDLoad` is a Lightweight and Cross-Platform Dynamic Library Loader designed for `C/C++`.

It Abstracts the Platform-Specific Differences Between:
- **Windows (`.dll`)**
- **Linux   (`.so`)**

It Provides a Unified, Simple, and Clean Interface for Loading Symbols and Managing Dynamic Libraries.


## Features
- C / C++ Compatible  
- Supports C99  
- Cross-Platform (Windows / Linux)  
- Auto-Generated Binding Interface (DPort)  
- Simple Resource Management  


## API

##### [Types]
- `xDLib` : Dynamic Library Handler / Controller  


##### [Core Functions]
- `xDLIB_Load`  : Load a Dynamic Library  
- `xDLIB_Close` : Unload a Library and Release Resources  
- `xDLIB_Get`   : Retrieve a Symbol from the Library  


##### [Helper Macros]
- `xDLOAD_OPEN`  : Wrapper for Loading a Library  
- `xDLOAD_CLOSE` : Wrapper for Closing a Library  
- `xDLOAD_BIND`  : Automatically Resolves a Symbol by `NAME` and Casts it to `TYPE`  


## Build

##### [Header Dependencies]
- `xMeta.h`  
- `xType.h`  


## Examples
Inside the `Sample` Directory:

```c
make all
```

##### [Build Library]
Inside the `xDLoad` Directory:

``` shell
make all
```

##### [Example 1: Basic Usage]
1. Load a Dynamic Library
2. Retrieve Symbols (Functions & Variables)
3. Execute and Release Resources

```c
int main(void)
{
  // Load dynamic library
  Lib = xDLIB_Load(DLIB_NAME);

  if(!Lib)
  {
    printf("Load Module Lib Failed!\n");
    return -1;
  }
  
  // Get functions
  Calculate = (MOD_Calculate) xDLIB_Get(Lib,"Calculate");
  PrintData = (MOD_PrintData) xDLIB_Get(Lib,"PrintData");
  Slogan    = (MOD_Slogan)    xDLIB_Get(Lib,"Slogan");
  GetRound  = (MOD_GetRound)  xDLIB_Get(Lib,"GetRound");
  
  // Get variable
  xDLOAD_BIND(Lib,int*,Round);
  pRound = Round;

  // Run test
  Run_Test();
  
  // Close library
  xDLIB_Close(Lib);
  return 0;
}
```

##### [Example 2: Using DPort Interface]
1. Centralized Symbol Management Via DPort
2. Automatically bind all Symbols Into a Structure
3. DPort Files can be Generated Via Tooling

```c
int main(void)
{
  Module_DPort DPort;
  pDPort = &DPort;

  Lib = xDLOAD_OPEN(DLIB_NAME);   // Open library
  XDLIB_MODULE_GET(Lib,DPort);    // Bind all symbols
  Run_Test();                     // Run test
  xDLOAD_CLOSE(Lib);              // Close library

  return 0;
}
```

## Tooling
1. Build CLI Tool

Inside Tooling/CLI:
```shell
make all
```

#### [Usage]
Place Header Files in the In Directory (Or Specify Another Path)
Run: 

```shell
./Tool_DLoad_CLI <header_file>
```

Generated Output will be Placed in the Out Directory as:
`XXX_DPort.h`


## License
This Project is Licensed Under the MIT License
