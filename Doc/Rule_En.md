# Rule

## Overview
This document outlines the development rules and design philosophy of this project, aiming to improve code quality and development efficiency, and ensure the overall architecture has good maintainability and scalability.

During the development process, this project will adhere to the following principles as much as possible:
1. Simplify code, reducing unnecessary length and complexity.
2. Establish a clear and consistent file and directory structure.
3. Employ modular design, allowing components to be freely combined and reused.
4. Improve portability, enabling the program to run on different systems or platforms.

The above principles are design directions and suggestions, not mandatory specifications. Developers can flexibly adjust them according to actual needs to achieve the best development experience and implementation results.

## Core Design Concepts
#### <Parameters>
1. Parameter Naming Convention: Uses Upper Camel Case (the first letter of each word is capitalized).

``` c
int Handle = 1;
int Device = 2;
int Status = 3;
```

2. Commonly used fixed cases can be prefixed with lowercase letters or symbols.
   1. `tStart`: Indicates a timer. Adding `t` to the prefix indicates `Time`, allowing for quick identification of time-related variables during development.
   2. `gValue`: Indicates a global variable. Adding `g` to the prefix indicates `Global`, allowing for quick identification of global variables during development.
   3. `nData`: Indicates quantity. Adding `n` to the prefix indicates `Numeric`, allowing for quick differentiation between quantity and data during development.
   4. `pArray`: This indicates a pointer. Adding `p` as a prefix signifies a pointer, allowing for quick differentiation between pointers and variables during development.
   5. Avoid using two-part variable types like `unsigned char`. Instead, use `xType.h` or `Macro` to wrap them into shorter variable types (`U8`).
3. Use abbreviations to optimize abbreviation length.
  1. Status  => Stat
  2. Count   => Cnt
  3. Enable  => En
  4. Length  => Len
  5. Index   => Idx
  6. Buffer  => Buf
  7. Address => Addr
  8. Initial => Init
  9. Message => Msg

#### <Macros/Macro Functions>
1. Macro definitions should be prefixed with the filename (or module name) and use all uppercase letters. This effectively establishes a namespace and prevents conflicts between different modules due to identical names.
2. Macro names, values, continuation characters, and comments should be vertically aligned as much as possible to keep the code clean.
3. Line break alignment: The continuation character `\` at the end of a multi-line macro must be vertically aligned.
4. When defining a multi-line macro function, the logic must be wrapped in `do { ... } while(0)`.
5. When defining a multi-line macro function, it is recommended to use `/* ... */` for comments to avoid exceptions in some older compilers regarding `//` continuation handling. This restriction does not apply to single-line macros.

``` c
#define XDATA_MIN_SIZE          5         //Min Size               
#define XDATA_MAX_SIZE          10        //Max Size

#define XDATA_CONFIG(A,B,C,D)   \
do                              \
{                               \
  A+=B;                         \
  B+=C;                         \
  C+=D;  /* C = C + D */        \
} while(0)

```

#### <Example>
1. Hard-coded numbers (`Type = 3`) are strictly prohibited in program logic. All numerical values ​​with status, type, or option meanings must be defined using `Enum` to improve code readability.
2. To simplify variable declarations and comply with type safety, always use the `typedef enum` format.
3. The starting tag immediately follows `enum`, and it is recommended to begin with an underscore `_` and use all uppercase letters.
4. The ending type is located after `}` and should correspond to the tag name (without the underscore). Optionally, `_E` can be added as a suffix.
5. All elements within the enumeration must use all uppercase letters.
6. Elements should be explicitly assigned numerical values ​​whenever possible, and the equals sign `=` should be vertically aligned to improve visual readability.
7. It is recommended to add a `_MAX` member at the end. This facilitates `for` loop traversal and allows for boundary checks when receiving data.

``` c
typedef enum _DATE_TYPE
{
  DATA_TYPE_INT   = 0,
  DATA_TYPE_FLAOT = 1,
  DATA_TYPE_CHAR  = 2,
  DATA_TYPE_MAX,
} DATA_TYPE;
```

#### <Structure>
1. Use `typedef struct` for definition to avoid repeatedly writing the `struct` keyword when declaring variables later.
2. The opening tag should immediately follow `struct` and must begin with an underscore `_`.
3. The closing type is located after curly braces `}`. The name should match the opening tag, but remove the leading underscore `_`.
4. Closing types can retain their original names or be uniformly suffixed with `_t` (representing `Type`).
5. Elements within the structure should be aligned as much as possible, and annotations should be added if possible.
6. Callback functions within the structure should first be defined using `typedef` with their type name, and then referenced within the structure body.

``` c
typedef struct _PersonInfo
{
  int   ID;
  char *Name;
  int   Score
} PersonInfo;
```

#### <Function>
1. Above the function definition in the source file `(.c)`, a comment starting with `///@` must be used.
   * Reason: This format will be highlighted in blue in `Keil C`, making it easy to quickly locate and read the function description.
   * Requirement: Only the function name and a brief description of its function are required; avoid lengthy `@param` or `@return` descriptions.
```c
///@Function: ShowData
///@Descript: Serial printing and formatted output of execution data
void ShowData(void)
{}
```
1. The total length of the function name plus parameters should be such that the IDE does not need to scroll horizontally, ensuring the complete declaration is clearly visible at a glance.
2. It is recommended that the logic of a single function be kept under 100 lines.
3. Reduce the number of parameters: If there are too many parameters, they should be encapsulated in a struct and passed as indicators.
4. Avoid using lengthy primitive modifiers such as `const char*` in the parameter list. Use concise types defined by `xType` (such as `CCHAR` or `BOOL`) to shorten the declaration length.
5. Function names should be meaningful, prioritizing the "verb + noun" structure (such as `Get_Voltage`, `Set_State`), ensuring that developers can understand their purpose without having to read the code.


## Source File
1. Each function (including static functions) must include the following above it:
* `///@Function`: Function name.
* `///@Descript`: Brief description of the function.
``` c
///@Function: 
///@Descript: 
void TEST_Function(void)
{}
```
2. All `static` functions must first define their prototypes in the `[Prototype Declare]` block.
3. To avoid interfering with the readability of the main public `API`, it is recommended to place the implementation of `static` functions at the very end of the file.
4. If the `.c` file supports standalone compilation tests (via `main`), then `main` must be placed at the very beginning of all function implementations, allowing developers to immediately identify the program's entry point.
5. The order of placement is as follows:
   1. `[xxx Lib Include]`           : Highest priority, includes basic type definitions.
   2. `[Typedef Declare]`           : Includes external type definitions.
   3. `[Macro Declare]`             : Defines static constants.
   4. `[Enum Declare]`              : Defines states and enumerations.
   5. `[Callback Function Declare]` : Defines function pointers.
   6.  `[Struct Declare]`           : Main definition of the data structure.
   7.  `[Prototype Declare]`        : Function prototype.
   8.  `[Variable Declare]`         : External global variable.
   9.  `Function`


## Header File
1. The `Guard` macro should consistently use `__filename_H__` (all uppercase).
2. `//__filename_H__` must be added after `#ifndef`, `#define`, and `#endif` to facilitate quick block identification.

```c
#ifndef __TEST_H__  //__TEST_H__
#define __TEST_H__  //__TEST_H__
#endif  //__TEST_H__
```
3. Header files should ideally include an `extern "C"` declaration, regardless of whether `C++` is used.
4. Only variable declarations and function prototypes are allowed inside the `extern "C"` block; other declarations are discouraged.
5. Macro definitions and structure definitions (`Struct/Enum`) should ideally be placed outside of `extern "C"` (unless special linking incompatible with `C++` needs to be handled).

```c
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
```
1. Title annotations must use the format `//[Title Name]`.
2. If the block is empty, please mark it with `//None` or remove it directly.
3. The `extern "C"` isolation section is limited to `[Variable Declare]` and `[Prototype Declare]`.
4. External: Place type definitions such as `Enum`, `Struct`, and `Typedef`. These are syntactically universal in `C/C++`.
5.  Macro functions should be placed at the very end of the file to ensure that when macro functions use previously defined `Struct` or `Variable`, the relevant symbols have been fully expanded.
6.  The recommended placement order is as follows:

    1. `[xxx Lib Include]`            : Highest priority, includes basic type definitions.
    2. `[Config Include]`             : Module-specific configuration parameters.
    3. `[Typedef Include]`            : Includes external type definitions.
    4.  `[Macro Declare]`             : Definition of static constants.
    5.  `[Enum Declare]`              : Definition of states and enumerations.
    6.  `[Callback Function Declare]` : Definition of function indicators.
    7.  `[Struct Declare]`            : Definition of the data structure body.
    8.  `[Variable Declare]`          : (Must be inside `Extern C`) External global variables.
    9.  `[Prototype Declare]`         : (Must be inside `Extern C`) Function prototypes.
    10. `[Macro Function Declare]`    : (Place at the very end) Macro functions.

```c
//[xxx Lib Include]
//None
//[Config Include]
//None
//[Typedef Include]
//None
//[Macro Declare]
//None
//[Enum Declare]
//None
//[Callback Function Declare]
//None
//[Struct Declare]
//None
#ifdef __cplusplus
extern "C" {
#endif
//[Variable Declare]
//None
//[Prototype Declare]
//None
#ifdef __cplusplus
}
#endif
//[Macro Function Declare]
//None
```

1.  The location of `Config` determines whether the module includes a specific algorithm, whether `Debug Log` is enabled, or whether it supports specific hardware features.
2.  The recommended naming convention for `Config` is `SUPPORT_XXXXX`. For example: `SUPPORT_REGEX`.
3.  It is recommended to explicitly define `Config` values ​​as `1` (enabled) or `0` (disabled).
4.  `Config` conditional logic must use `#if` instead of `#ifdef`.

```c
#define SUPPORT_DEBUG       1       //Support Debug Information
#define SUPPORT_PERF        1       //Support Perf Function

```

16. Functions with similar `Prototype` attributes must be placed under the same annotation heading.
17. It is recommended that functions within a module not exceed `7` types. If the functionality exceeds this limit, consider splitting the module or re-abstracting it.
```c
#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//Image Quality
void  xIQ_SetBrightness(int Value);
void  xIQ_SetSharpness(int Value);
void  xIQ_SetContrast(int Value);

//Init
void  xIQ_Init(void);
void  xIQ_Destroy(void);
xIQ_t xIQ_GetHandle(void);

//File Operate
void ReadFile(char *FileName);
void WriteFile(char *FileName);
#ifdef __cplusplus
}
#endif
```

## Module Planning
1. Each project is an independent module. The core code (.c/.h) of the module should be placed directly in the root directory.
2. The header files in the directory are the main external interfaces of the module. If the functionality is complex, multiple exported header files are allowed.
3. If the module has additional resources, the following subfolders should be created according to functionality:
   1. `Plugin/`: Used to store extension plugins or optional components for complex functions.
   2. `Sample/` or `Test/`: Store demonstration examples and unit test code.
   3. `Doc/`: Store technical documents and design specifications.
4. `Tooling`: Store small tools to assist in development.
   1. Should be distinguished between `CLI` (Command-line Interface) and `GUI` (Graphical Interface).
   2. Contains `In/` and `Out/` folders to isolate the input and output resources required by the tools.
5. `Spec/` or `Sch/`: For hardware driver modules (xDevice), this contains the datasheet or circuit schematic.


``` shell
.
├── Doc
│   ├── ReadmeEn.md
│   └── ReadmeZh.md
├── Makefile
├── Sample
│   ├── Makefile
│   ├── Module.c
│   ├── Module_DPort.h
│   ├── Module.h
│   ├── Sample1.c
│   └── Sample2.c
├── Tooling
│   ├── CLI
│   │   ├── Makefile
│   │   └── Tool_DLoad_CLI.c
│   ├── In
│   │   ├── Module.h
│   │   └── ModulePlus.h
│   ├── Makefile
│   ├── Out
│   │   ├── Module_DPort.h
│   │   └── ModulePlus_DPort.h
│   ├── Tool_DLoad_Lib.c
│   └── Tool_DLoad_Lib.h
├── xDLoad.c
└── xDLoad.h
```

## Class Classification
1. `xAdapter`: A unified interface for different functions based on third-party libraries.
2. `xApp`    : Programs with specific, purposeful, and highly complete functions based on real-world applications.
3. `xDevice` : Programs with functions based on actual hardware, sensor drivers, and hardware modules.
4. `xFake`   : Programs that simulate hardware or other methods to simulate software functions.
5. `xModule` : Programs based on pure software algorithms, general data, and standard protocol processing.
6. 