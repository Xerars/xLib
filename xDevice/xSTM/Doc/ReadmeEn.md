# xSTM

> **Project** : xSTM
> **Author**  : William Hsiao
> **Descript**: STM32 hardware and peripheral utility library
> **Version** : 1.0.0

## Introduction

`xSTM` is a lightweight utility library for STM32 projects that use the STM32 HAL. It collects commonly used device-level functions behind one management header, `xSTM.h`.

The library is divided into independent PlugIns. Select only the PlugIns required by the application in `xSTM_Config.h`, then add the matching `.c` files to the target. The current default configuration targets STM32F4 HAL (`stm32f4xx_hal.h`); porting to another STM32 series requires updating the HAL include and any series-specific Flash or power settings.

## Features

1. PlugIn-based design: Debug, DWT, Flash, Sys and Power features can be enabled independently.
2. Central configuration: HAL, clock, UART and Flash settings are kept in `xSTM_Config.h`.
3. UART debug output: Redirects standard I/O and provides categorized messages and hexadecimal dumps.
4. DWT timing: Provides cycle-based delays, microsecond timing, performance measurement and periodic events.
5. System information: Reads CPU, device, clock, UID, boot address and reset-reason information.
6. Flash access: Supports internal Flash word/buffer read, write, erase and erased-state checking.
7. Power control: Supports Sleep, Stop and Standby modes, with HCLK divider adjustment and restoration.
8. C/C++ compatible: Public headers include `extern "C"` guards.

## Directory Structure

```text
xSTM/
├── xSTM.h                 PlugIn management header
├── xSTM_Config.h          Target HAL and PlugIn configuration
├── PlugIn/                PlugIn headers and source files
├── Sample/                Keil / STM32CubeMX integration examples
└── Doc/                   Library documentation
```

## Quick Start

1. Copy the `xSTM` directory into an STM32CubeMX-generated project.
2. In the compiler include paths, add the xLib root, `xSTM`, and `xSTM/PlugIn` directories.
3. Edit `xSTM_Config.h`: select the correct HAL header, configure the actual system clock and debug UART handle, then enable only required `xSTM_SUPPORT_*` macros.
4. Add the required PlugIn `.c` files to the target. Including a header does not compile its implementation.
5. Include `xSTM.h` from the application.

```c
#include "xSTM.h"

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_USART2_UART_Init();

  xSTM_DWT_Init();
  xSTM_DEBUG_INFO("xSTM ready\r\n");
  while(1)
  {
  }
}
```

For Keil projects using `printf` through `xSTM_Debug`, enable `Use MicroLIB` in `Options for Target` → `Target`.

## Configuration

`xSTM_Config.h` is the single target-dependent configuration point.

```c
#include "stm32f4xx_hal.h"

#define xSTM_SUPPORT_DEBUG  1
#define xSTM_SUPPORT_DWT    1
#define xSTM_SUPPORT_FLASH  1
#define xSTM_SUPPORT_SYS    1
#define xSTM_SUPPORT_POWER  1

#define xSTM_SYS_CLOCK      84      // MHz; must match CubeMX clock setup
#define xSTM_DEBUG_HANDLE   huart2
```

Set an unused `xSTM_SUPPORT_*` macro to `0`. The corresponding header is then excluded by `xSTM.h`; also omit its `.c` file from the build.

Before using Flash or Power, review the series-specific HAL constants in the same file. `xSTM_Config.h` currently declares `extern UART_HandleTypeDef huart2`; change both this declaration and `xSTM_DEBUG_HANDLE` when using another UART instance.

## API

### xSTM_Debug
- `fputc`              : redirect standard output through the configured UART.
- `fgetc`              : redirect standard input through the configured UART.
- `xSTM_HexDump`       : print one byte buffer in hexadecimal form.
- `xSTM_DEBUG_INFO`    : print an Info-category message.
- `xSTM_DEBUG_WARN`    : print a Warning-category message.
- `xSTM_DEBUG_ERROR`   : print an Error-category message.
- `xSTM_DEBUG_HEXDUMP` : HexDump macro wrapper.

### xSTM_DWT
- `xSTM_DWT_Init`         : enable the Cortex-M DWT cycle counter.
- `xSTM_DWT_DelayCycle`   : perform a blocking delay in cycles.
- `xSTM_DWT_DelayUS`      : perform a blocking delay in microseconds.
- `xSTM_DWT_Delay10US`    : perform a blocking delay in 10-microsecond units.
- `xSTM_DWT_DelayMS`      : perform a blocking delay in milliseconds.
- `xSTM_DWT_GetCycle`     : retrieve the current cycle count.
- `xSTM_DWT_GetUS`        : retrieve elapsed time in microseconds.
- `xSTM_DWT_PerfStart`    : retrieve the starting cycle count for a performance measurement.
- `xSTM_DWT_PerfFinish`   : calculate elapsed microseconds from a starting cycle count.
- `xSTM_DWT_TimerEvent`   : process one non-blocking periodic or one-shot event.
- `xSTM_DWT_TIMER_START`  : begin a macro-based periodic task section.
- `xSTM_DWT_TIMER_FINISH` : end a macro-based periodic task section.

### xSTM_Flash
- `xSTM_Flash_Read`     : read one 32-bit Flash word.
- `xSTM_Flash_Write`    : write one 32-bit Flash word.
- `xSTM_Flash_ReadBuf`  : read Flash data into a buffer.
- `xSTM_Flash_WriteBuf` : write a buffer to Flash.
- `xSTM_Flash_IsErased` : test whether an address range contains erased data.
- `xSTM_Flash_Erase`    : erase consecutive Flash sectors.

### xSTM_Sys
- `xSTM_SYS_GetUID`         : retrieve the 96-bit unique ID.
- `xSTM_SYS_GetCPUID`       : retrieve the CPU ID register.
- `xSTM_SYS_GetVer`         : retrieve the CPU revision.
- `xSTM_SYS_GetDeviceID`    : retrieve the STM32 device ID.
- `xSTM_SYS_GetDevVer`      : retrieve the STM32 device revision.
- `xSTM_SYS_GetReason`      : retrieve reset-reason flags.
- `xSTM_SYS_ClearReason`    : clear reset-reason flags.
- `xSTM_SYS_SoftReset`      : trigger a software reset.
- `xSTM_SYS_GetTick`        : retrieve the system tick in milliseconds.
- `xSTM_SYS_Delay`          : perform a blocking system-tick delay.
- `xSTM_SYS_GetClockInfo`   : retrieve system clock information.
- `xSTM_SYS_GetBootAddress` : retrieve the current vector-table address.

### xSTM_Power
- `xSTM_Power_Sleep`        : enter Sleep mode.
- `xSTM_Power_Stop`         : enter Stop mode.
- `xSTM_Power_Standby`      : enter Standby mode.
- `xSTM_Power_SetClock`     : set the target HCLK.
- `xSTM_Power_RestoreClock` : restore the saved HCLK divider.

## Build Dependencies

### Header Dependencies

1. `xType.h`
2. `xMeta.h`
3. STM32 HAL and CMSIS headers for the selected target

### Source Files

Add only the sources for enabled PlugIns:

```text
xSTM/PlugIn/xSTM_Debug.c
xSTM/PlugIn/xSTM_DWT.c
xSTM/PlugIn/xSTM_Flash.c
xSTM/PlugIn/xSTM_Sys.c
xSTM/PlugIn/xSTM_Power.c
```

The library is not intended to be built with host Linux GCC because it accesses STM32 HAL and Cortex-M registers. Build it with the target toolchain, such as Keil MDK-ARM or `arm-none-eabi-gcc`, together with the HAL/CMSIS files from STM32CubeMX.

## Size Measurement

Measure xSTM from a target ELF/AXF, not from the host system. The final size depends on the selected MCU, enabled PlugIns, optimization level, called APIs, HAL version and linker garbage collection.

Build a baseline application and an application that calls the required xSTM APIs using identical settings, then compare their Flash and RAM usage. With GNU Arm Embedded Toolchain:

```shell
arm-none-eabi-size -A app.elf
arm-none-eabi-nm -S --size-sort --radix=d app.elf | grep xSTM_
```

For Keil AXF output, use `fromelf --text -s app.axf` to inspect sections and symbols.

## Samples

| Sample    | PlugIn | Purpose                                        |
| :-------- | :----- | :--------------------------------------------- |
| `Sample1` | Debug  | UART I/O redirection, messages and HexDump     |
| `Sample2` | DWT    | Delay, time, performance and periodic events   |
| `Sample3` | Sys    | CPU, device, clock, UID and reset information  |
| `Sample4` | Power  | HCLK adjustment and low-power modes            |
| `Sample5` | Flash  | Reserved-area setup, read/write/erase and test |

Read the `ReadmeEn.md` or `ReadmeZh.md` inside each Sample directory before building it.

## Notes

1. `xSTM_SYS_CLOCK` and `xSTM_DWT_SYS_CLOCK` must match the actual MCU clock; otherwise DWT delays and time values are incorrect.
2. DWT Cycle Counter availability depends on the Cortex-M core. It must be supported by the selected device.
3. `xSTM_DWT_TimerEvent()` has one internal static state machine and therefore manages one event at a time.
4. Flash erase is irreversible. Reserve the test sector in the linker configuration before enabling `xSTM_FLASH_SUPPORT_UNIT_TEST`.
5. Flash program type, voltage range, sector layout and power-mode constants are MCU-series-specific. Confirm them against the reference manual and HAL documentation.
6. Stop and Standby modes require an appropriate wake source; Standby normally resets the MCU on wake-up.
7. Avoid generic macro names such as `OR`, `AND` and `NOT` in application headers because they may collide with STM32 HAL register fields.

## License Terms

This project is licensed under the `MIT License`.