# xHexGen

> **Project** : xHexGen
> **Author**  : William Hsiao
> **Descript**: A tool for reading binary data and converting it into array data

## Introduction
`xHexGen` is a very small utility program used to help process embedded files in `C` or `C++` programs.

## Application Size
1. `xHexGen` Application Size: `4.488KB`


## Compiling
1. Compiling using `CMake`

``` shell
mkdir build
cd build
cmake ..
make
```

2. Compile using `Shell`
   1. Create a `build` folder
   2. Execute the `CMAKE` command
   3. Execute the `Make` command

``` shell
./Build.sh
```

3. Use `Shell` to clean up

``` shell
./Build.sh clean
```

## use
``` shell
> xHexGen ./In/Res.jpg > Res.c
> cat Res.c
```

```c
//[STD Lib Include]
#include <stdint.h>

/* Embedded Image File : Res.jpg */
const int Res_FileSize  = 671;        //File Size
const uint8_t Res_File[] =
{
  0xff,0xd8,0xff,0xe0,0x00,0x10,0x4a,0x46,0x49,0x46,0x00,0x01,0x01,0x01,0x00,0x60,
  0x00,0x60,0x00,0x00,0xff,0xdb,0x00,0x43,0x00,0x02,0x01,0x01,0x02,0x01,0x01,0x02,
  0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x03,0x05,0x03,0x03,0x03,0x03,0x03,0x06,0x04,
  0x04,0x03,0x05,0x07,0x06,0x07,0x07,0x07,0x06,0x07,0x07,0x08,0x09,0x0b,0x09,0x08,
  ....
}
```

## License Terms
This project is licensed under the `MIT License`.