# HISTORY

#### [2026/03/27]
1. Create `xType` Lib `(1.0.0)`
2. Create `xMeta` Lib `(1.0.0)`
3. Create `Readme.md`  Blank File
4. Create `Rule.md`    Blank File
5. Create `Version.md` Blank File
6. Create `.gitignore` Blank File
7. Create `License.md` Blank File

#### [2026/03/27]
1. `xType` Lib
   1. [1.0.1]Add the Definition of Decorative Prefixs(`volatile,extern ...`)
   1. [1.0.2]Add the Definition of NULL
2. `xMeta` Lib
   1. [1.0.1]E -> EXP Prevent MisUse
   2. [1.0.2]Add `IS_ALIGN` Macro
   3. [1.0.3]Add `SAFE_SWAP` Macro and `SAFE_SORT` Macro
   4. [1.0.4]Add `LIKELY` Macro and `UNLIKELY` Macro
   5. [1.0.5]Add `Coroutine` Related Macro
   6. [1.0.6]Add `CAST` Macro
   7. [1.0.7]Add `EXECUTE` Macro
3. Complete the First Version of `.gitignore`

#### [2026/03/31]
   1. Create the `xDLoad` library `(1.0.0)`
   2. Create the function library
   3. Create the basic example
   4. Create the tool (CLI)

#### [2023/04/05]
1. [1.0.1] Fixed the title description of `xDLoad`
2. Created the `xDuff` library `(1.0.1)`
   1. Created the function library
   2. Created basic examples

#### [2023/04/06]
1. Create the `xVector` library `(1.0.4)`
   1. Create the function library
   2. Create basic examples
2. Add `Valgrind` test to example testing
3. Fixed the issue of `xDLoad` example loading dynamic library addresses.

#### [2026/04/22]
1. Create the `xTCA9555` library `(1.0.0)`
   1. Create a function library
   2. Create a basic example
2. Example test: rename the file extension `valgrid` -> `vgd`


#### [2026/04/25]
1. Created the `xCPrint` library `(1.0.0)`
   1. Created the function library
   2. Created a basic example
2. Fixed an error in the `xType` library regarding `DWORD` and `CCHAR` in `Windows`
3. Created the `xHexGen` application `(1.0.6)`
4. Created the `xLeackCheck` library `(1.1.1)`
   1. Created the function library
   2. Created a basic example

#### [2026/05/15]
1. Create the `xCheckSum` library `(1.0.0)`
   1. Create the function library
      1. `xCheckSum` library
      2. `xCheckSum_BCC` library
      3. `xCheckSum_LRC` library
      4. `xCheckSum_CRC` library
   2. Create a basic example


#### [2026/05/17]
1. Create the `xTMP102` library (1.0.0)
   1. Create a function library
   2. Create a basic example

#### [2026/09/19]
1. Create the `xSim` module `(1.0.0)`
   1. Add simulation PlugIns for `ADC`, `CLI`, `GPIO`, `INT`, `IPC`, `PWM`, `Reg`, `Timer`, and `WDT`
   2. Add sample programs, log data, and GUI monitoring tools
   3. Add Chinese and English documentation
2. Create the `xSTM` device utility library `(1.0.0)`
   1. Add `Debug`, `DWT`, `Flash`, `Sys`, and `Power` PlugIns
   2. Add `STM32CubeMX` / `Keil MDK-ARM` integration samples and Chinese and English documentation
   3. Add target `ELF` / `AXF` library-size measurement guidance
3. Update `xType` to `(1.0.6)`
   1. Extend character and string type definitions
   2. Standardize type comments and macro formatting
4. Update `xMeta` to `(1.0.10)`
   1. Rename generic operator macros to `_AND`, `_OR`, `_NOT`, and related names to prevent STM32 HAL field conflicts
   2. Add bit-operation, saturating increment/decrement, and program-exit macros
5. Update `xCPrint` to `(1.2.0)`
   1. Add `Shell` and `Lua` support with examples
   2. Complete Chinese and English documentation
6. Reorganize `xDevice` and remove the legacy `xTCA9555` implementation
