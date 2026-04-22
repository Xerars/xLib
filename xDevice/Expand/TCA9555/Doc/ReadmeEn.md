# TCA9555

> **Project** : xDuff
> **Author**  : xTCA9555
> **Descript**: TCA9555 Device Driver Lib

## Introduction
The TCA9555 is an I/O expander driver library designed for low-voltage 16-bit I²C and SMBus. 
It supports a wide voltage range from 1.65V to 5.5V and provides interrupt outputs and configurable register functions,
effectively expanding the general-purpose input/output (GPIO) interface for microcontrollers.


## Features
* Low standby current consumption: only 3.5 μA maximum
* I²C to parallel port expander: efficient communication protocol conversion
* Open-drain low-level active interrupt output (INT): notifies the master controller when the input state changes
* 5V withstand voltage I/O port: enhances system compatibility
* High compatibility: supports most microcontroller architectures
* High-speed communication: supports Fast I²C buses up to 400kHz
* Flexible addressing: 3 address pins, configurable for up to 8 different slave device addresses
* Polarity reversal: built-in polarity reversal register, allowing software switching of input logic
* Powerful drive capability: high-current latched output, directly drives LEDs
* High reliability:
  * Latch performance exceeds 100 mA (compliant with JESD 78 Class II standard)
  * ESD protection exceeds JESD 22 standard (2000V HBM / 1000V CDM)

## API
#### [Type definition]
1. `xTCA      `: The TCA9555 device entity control structure, containing I/O port configuration and status shadow registers.
2. `xTCA_Port `: Defines the I²C transmission interface, including slave address, speed, and read/write callback functions.
3. `xTCA_PIN  `: 16-bit pin definition (P0.0~P1.7).
4. `xTCA_DIR  `: Direction definition.
5. `xTCA_LEVEL`: Potential definition.

#### [core function]
Control and Initialization
1. `xTCA_GetHandle`: Retrieves the pointer to the current device handle.
2. `xTCA_SetHandle`: Sets the handle of the currently operating device.
3. `xTCA_Init     `: Initializes the TCA9555 device, configures the communication interface, and binds the callback function.
4. `xTCA_Reset    `: Resets the device state using software, restoring the shadow register to its default value.

I/O Configuration and Operation
1. `xTCA_SetDir`   : Sets the orientation (input or output) of a specified pin.
2. `xTCA_WritePin` : Writes the voltage state of a specified pin.
3. `xTCA_TogglePin`: Toggles the voltage state of a specified pin.
4. `xTCA_ReadPort` : Reads the current input state of the entire 16-bit port.
5. `xTCA_ReadPin`  : Reads the voltage state of a single specific pin.
6. `xTCA_SetInvert`: Sets the polarity inversion function of an input pin.


## Library Information
1. `xTCA9555`: Library size 1.204 KB

``` c
xTCA_GetHandle      // Occupies 12  Bytes
xTCA_I2C_Read       // Occupies 49  Bytes
xTCA_I2C_Write      // Occupies 49  Bytes
xTCA_Init           // Occupies 81  Bytes
xTCA_ReadPin        // Occupies 25  Bytes
xTCA_ReadPort       // Occupies 89  Bytes
xTCA_Reset          // Occupies 28  Bytes
xTCA_SetDir         // Occupies 107 Bytes
xTCA_SetHandle      // Occupies 12  Bytes
xTCA_SetInvert      // Occupies 107 Bytes
xTCA_TogglePin      // Occupies 93  Bytes
xTCA_WritePin       // Occupies 107 Bytes
```

## Compilation Dependencies
#### [Compilation]
1. xMeta.h
2. xType.h

``` shell
make all
```

## Example
Use the command `make all` within the `Sample` folder.

This example demonstrates how to define virtual I²C read/write functions and initialize the driver using xTCA_Init.
It then demonstrates the complete process of setting pin direction, writing/toggling output potential, reading input status, and setting polarity reversal.

```c
//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "xTCA9555.h"

//[Prototype Declare]
void TCA_Fake_I2C_Write(U8 Addr, U8 Reg, U8 *pData, U32 Len);
void TCA_Fake_I2C_Read(U8 Addr, U8 Reg, U8 *pData, U32 Len);

//[Variable]
U8 Register[8] = {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF};

int main(void)
{
  xTCA      DevTCA;
  xTCA_Port DevTCA_Port;

  //Regist Communication Port and Address
  DevTCA_Port.I2C_ID    = xTCA_SLAVE_ADDR(0,0,0);
  DevTCA_Port.I2C_Speed = 400000;
  DevTCA_Port.Write     = TCA_Fake_I2C_Write;
  DevTCA_Port.Read      = TCA_Fake_I2C_Read;

  //Initial Device
  xTCA_Init(&DevTCA, &DevTCA_Port);

  //Set Direction P0.0,P0.1 Output; P1.0 P1.1 Input
  xTCA_SetDir(TCA_PIN_P00 | TCA_PIN_P01, xTCA_DIR_OUT);
  xTCA_SetDir(TCA_PIN_P10 | TCA_PIN_P11, xTCA_DIR_IN);

  //Write & Toggle
  xTCA_WritePin(TCA_PIN_P00 | TCA_PIN_P01, xTCA_LEVEL_LOW);
  xTCA_TogglePin(TCA_PIN_P00);

  //Read Status
  U16 Value = xTCA_ReadPort();
  xTCA_LEVEL Level = xTCA_ReadPin(TCA_PIN_P11);

  printf("Port Value: 0x%04X\n", Value);
  printf("P1.1 Level: %d\n", Level);

  //Set P0.0 as Invert Polarity
  xTCA_SetInvert(TCA_PIN_P00, 1);
  return 0;
}

//Fake I2C Write
void TCA_Fake_I2C_Write(U8 Addr, U8 Reg, U8 *pData, U32 Len)
{
  printf("[I2C Write] Addr: 0x%02X, Reg: 0x%02X(%d) \n",Addr,Reg,Len);
  for(U32 i = 0; i < Len; i++)
    if((Reg + i) < 8)
      Register[Reg + i] = pData[i];
}

//Fake I2C Read
void TCA_Fake_I2C_Read(U8 Addr, U8 Reg, U8 *pData, U32 Len)
{
  printf("[I2C Read ] Addr: 0x%02X, Reg: 0x%02X(%d) \n",Addr,Reg,Len);
  for(U32 i = 0; i < Len; i++)
    if((Reg + i) < 8)
      pData[i] = Register[Reg + i];
}
```

## License
This project is licensed under the  `MIT` License.