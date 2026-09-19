# xSTM Sample5

> **Project** : xSTM Sample5
> **Author**  : William Hsiao
> **Descript**: xSTM_Flash reserved-area configuration, API demonstration and unit test example


## Flash Configuration

This document currently describes the safe configuration for `xSTM_Flash`. The Sample5 unit test erases, writes and erases the selected Flash sector again. Do not program or run the sample until the linker reserved-area configuration is complete.


#### 1. Confirm the Target STM32

The current settings apply to an STM32F446 with 512 KB of internal Flash. Its Flash range is:

```text
0x08000000 ~ 0x0807FFFF
```

The sample reserves the final Flash sector as its test area. If the MCU model, Flash capacity or sector layout differs, recalculate the address, sector and size from the datasheet.

#### 2. Reserve the Flash Test Area

The final STM32F446 sector is `FLASH_SECTOR_7`:

| Item | Value |
| :--- | :--- |
| Test Sector | `FLASH_SECTOR_7` |
| Start Address | `0x08060000` |
| End Address | `0x0807FFFF` |
| Size | `0x00020000` (128 KB) |

`xSTM_TEST_Flash()` erases this entire area. Do not place code, constant data, the vector table or any persistent data in it.

#### 3. Configure Keil IROM1

In Keil, open `Project` → `Options for Target` → `Target`, then set IROM1:

| Setting | Value |
| :--- | :--- |
| Start | `0x08000000` |
| Size | `0x00060000` |

This limits the linker to `0x08000000` through `0x0805FFFF` and reserves `0x08060000` through `0x0807FFFF` for the Flash unit test.

If the application exceeds 384 KB, Keil should report insufficient space. Do not increase IROM1 Size over the test area.

#### 4. Confirm the xSTM_Flash Settings

Confirm that the unit test settings in `xSTM_Flash.h` match the reserved area:

```c
#define xSTM_FLASH_SUPPORT_UNIT_TEST     1
#define xSTM_FLASH_TEST_ADDR             0x08060000UL
#define xSTM_FLASH_TEST_SECTOR           FLASH_SECTOR_7
#define xSTM_FLASH_TEST_SECTOR_COUNT     1
#define xSTM_FLASH_TEST_SIZE             0x00020000UL
```

`xSTM_FLASH_VOLTAGE_RANGE` is in `xSTM_Config.h`. The current `FLASH_VOLTAGE_RANGE_3` setting is suitable for a typical 3.3 V STM32F4 supply. Reconfirm it if the actual supply conditions differ.

#### 5. Add Source Files

Add the following files to the Keil Target:

```text
../Code/App/App.c
../Code/xSTM/PlugIn/xSTM_Flash.c
../Code/xSTM/PlugIn/xSTM_Debug.c
```

Keep these header paths:

```text
../Code
../Code/App
../Code/xSTM
../Code/xSTM/PlugIn
```

`xSTM_Debug.c` redirects Flash unit test printf output to the debug UART.

#### 6. Configuration Checklist

Before programming, confirm:

1. IROM1 Size is `0x00060000`.
2. `xSTM_FLASH_TEST_ADDR` is `0x08060000UL`.
3. `xSTM_FLASH_TEST_SECTOR` is `FLASH_SECTOR_7`.
4. `xSTM_Flash.c`, `xSTM_Debug.c` and the sample App.c are in the same Target.
5. The test area contains no data that must be preserved.


## Example Description

#### Example Behavior

`App_Init()` runs the built-in unit test and then `App_FlashDemo()`.

The unit test erases the test area, verifies that the area contains `0xFF`, writes and reads one word, writes and reads a buffer, and erases the area again.

`App_FlashDemo()` demonstrates each public API:

1. `xSTM_Flash_Erase()`: erases the reserved `FLASH_SECTOR_7`.
2. `xSTM_Flash_IsErased()`: checks the erased state before and after writing.
3. `xSTM_Flash_Write()` and `xSTM_Flash_Read()`: writes and reads one 32-bit word.
4. `xSTM_Flash_WriteBuf()` and `xSTM_Flash_ReadBuf()`: writes, reads and compares a buffer.
5. `xSTM_HexDump()`: displays the read buffer as hexadecimal bytes.
6. Erases the test area again and confirms its erased state.

#### Actual Output

The following output passed on an `STM32F446` target:

```text
[Flash]: Test Addr: 0x08060000 Sector: 7 Size: 20000 Bytes
[FLASH TEST]: Start
[FLASH TEST]: Read Word : 0x12345678
[FLASH TEST]: Read Buf  : 12 34 56 78 9A BC DE F0
[FLASH TEST]: PASS
[Flash Demo]: Start
[Erase]: OK
[IsErased]: YES
[Write Word]: OK
[Read Word ]: 0x12345678
[IsErased  ]: NO
[Write Buf ]: OK
[Read Buf  ]: OK
[Hex]: 10 32 54 76 98 BA DC FE 55
[Compare Buf]: PASS
[Clean     ]: OK
[IsErased  ]: YES
[Flash Demo]: Finish
[xSTM Flash Sample]: Init Finish
```

## Notes

#### Erasure Is Irreversible

Erasing a Flash sector clears the complete 128 KB test area and cannot be undone. Enable `xSTM_FLASH_SUPPORT_UNIT_TEST` only after confirming that the linker has reserved this area.

#### Flash Programming Limits

Flash programming can change bits only from `1` to `0`; it cannot directly change a bit from `0` to `1`. For example, `0xFF` can be programmed as `0x12`, but programmed `0x12` cannot be changed directly back to `0xFF`.

`xSTM_Flash_Write()` and `xSTM_Flash_WriteBuf()` currently use `FLASH_TYPEPROGRAM_WORD`. Their programming unit is 4 bytes and the start address must be 4-byte aligned. Even with Byte Program, changing bits from `0` back to `1` requires erasing the sector first.

#### Updating Existing Data

To update data already written to Flash:

1. Read all data that must be preserved from the same sector into RAM.
2. Modify the target field in RAM.
3. Erase the complete sector.
4. Write all modified and preserved data back to Flash.

Do not read only one structure before erasing a sector, because other data in that sector would be lost.

#### Frequently Updated Data

For settings that change frequently, use append-only `Record` entries within a sector. Write every new value to the next `0xFF` location and use the last valid record when reading. When the sector is full, retain the latest data, erase the sector and write it again. This reduces erase cycles and extends Flash endurance.

#### Different MCU Sector Layouts

`FLASH_SECTOR_7` and `0x08060000` apply only to the current 512 KB STM32F446 configuration. Other STM32F4 models can have different sector counts and sizes.


## License Terms

This example is licensed under the MIT License.