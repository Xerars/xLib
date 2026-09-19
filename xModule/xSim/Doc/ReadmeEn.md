# xSim

**Project** : xSim
**Author**  : William Hsiao
**Descript**: Embedded System Hardware and Peripheral Simulation Tool Library

## Introduction
`xSim` is one of the core modules in the `xLib` tool library, designed to provide a lightweight and flexible hardware and peripheral simulation environment for embedded system development.
This module is optimized for software verification and testing when there is no physical hardware. It supports simulation of various common microcontroller peripherals and provides standardized control and log export APIs to simplify unit testing and early development processes.

## characteristic
1. Comprehensive Simulation: Covers cross-process communication including `ADC`, `GPIO`, `PWM`, `Interrupt`, `Timer`, `WDT`, `Register`, `CLI`, and `IPC`.
2. Flexible Configuration: Supports parameterized registration, channel management, and random/single-time data behavior settings for each peripheral.
3. Operational Tracing: Built-in logging and a Dump mechanism facilitate the recording and analysis of signal changes and states during simulation.
4. Easy Integration: Employs a consistent API design, supporting independent module customization or overall integration, adaptable to various embedded software architectures.


#### ADC Module
Analog-to-Digital Converter (ADC) supporting channel registration, range setting, and random or single-shot data simulation.
xSim_ADC_Regist          : Registers the ADC for a specified number of channels and bit count.
xSim_ADC_UnRegist        : Unregisters the specified channel.
xSim_ADC_Init            : Initializes the ADC simulation module and logging functionality.
xSim_ADC_GetValue        : Retrieves the analog conversion value for a specified channel.
xSim_ADC_SetValue        : Sets the analog value for a specified channel.
xSim_ADC_SetRange        : Sets the upper and lower limits of the value range for a specified channel.
xSim_ADC_Dump            : Exports the ADC simulation log to a specified file.


#### CLI Module
Command Line Interface (CLI) emulation, supporting thread-based interactive command input and parsing.
* xSim_CLI_Init          : Initializes the CLI module and internal resources.
* xSim_CLI_Start         : Starts the CLI thread.
* xSim_CLI_Stop          : Stops the CLI thread.
* xSim_CLI_IsRun         : Checks if the CLI is running.
* xSim_CLI_Regist        : Registers commands, callback functions, and descriptions.
* xSim_CLI_UnRegist      : Unregisters the specified command.

#### GPIO Module
General-Purpose Input/Output (GPIO) simulation, supporting input (GPI) and output (GPO) status control and logging.
* xSim_GPI_Regist        : Registers an input pin with a specified ID and name.
* xSim_GPO_Regist        : Registers an output pin with a specified ID and name.
* xSim_GPI_UnRegist      : Unregisters a specified input pin.
* xSim_GPO_UnRegist      : Unregisters a specified output pin.
* xSim_GPIO_Init         : Initializes the GPIO simulation environment.
* xSim_GPI_Set           : Sets the level of an input pin.
* xSim_GPI_Read          : Reads the level of an input pin.
* xSim_GPO_Write         : Writes the level of an output pin.
* xSim_GPIO_Dump         : Exports `GPIO` status and logs to a file.


#### INT Module
External interrupt (`Interrupt`) emulation, supporting multi-channel edge trigger settings and callback mechanisms.
* xSim_INT_Init          : Initializes the interrupt emulation module.
* xSim_INT_Destroy       : Destroys the interrupt emulation module.
* xSim_INT_Regist        : Registers the interrupt channel, name, trigger edge, and `ISR` callback.
* xSim_INT_UnRegist      : Unregisters the interrupt channel.
* xSim_INT_SetEdge       : Sets the interrupt trigger edge type.
* xSim_INT_SetTrigger    : Sets the current trigger signal level.
* xSim_INT_Dump          : Exports the interrupt log to a file.


#### IPC Module
Improves Inter-Process Communication (IPC) functionality, providing cross-process command sending and receiving and service mechanisms based on POSIX message queues.
* xSim_IPC_Init          : Initializes the `IPC` module and binds the module name.
* xSim_IPC_Destroy       : Destroys `IPC` resources.
* xSim_IPC_Start         : Starts the `IPC` service thread.
* xSim_IPC_Stop          : Stops the `IPC` service thread.
* xSim_IPC_IsRun         : Checks the running status of the `IPC` service.
* xSim_IPC_Regist        : Registers the `IPC` remote call command.
* xSim_IPC_UnRegist      : Unregisters the `IPC` remote call command.
* xSim_IPC_Service       : Handles the `IPC` message service. * xSim_IPC_Send: Sends a message to the specified module.


#### PWM Module
Pulse Width Modulation (PWM) simulation, supporting multi-channel frequency, duty cycle adjustment, and operation control.
* xSim_PWM_Init          : Initializes the PWM simulation module.
* xSim_PWM_Destroy       : Destroys the PWM module.
* xSim_PWM_Regist        : Registers a PWM channel.
* xSim_PWM_UnRegist      : Unregisters a PWM channel.
* xSim_PWM_SetEnable     : Enables PWM.
* xSim_PWM_SetFreq       : Sets the PWM frequency (Hz).
* xSim_PWM_SetDuty       : Sets the PWM duty cycle (0-100%).
* xSim_PWM_Start         : Starts the specified PWM channel.
* xSim_PWM_Stop          : Stops the specified `PWM` channel.
* xSim_PWM_Dump          : Exports the `PWM` runtime log to an archive.


#### REG Module
Register device emulation, supporting read/write permission control, attribute setting, and range restrictions for memory-mapped devices.
* xSim_RegDevice_Regist  : Registers the register device and its corresponding table and size.
* xSim_RegDevice_UnRegist: Unregisters the register device.
* xSim_Reg_Init          : Initializes register emulation and logging functionality.
* xSim_RegWrite          : Writes data to the specified address and register.
* xSim_RegRead           : Reads data from the specified address and register.
* xSim_Reg_SetValue      : Sets the value of the specified register.
* xSim_Reg_SetRange      : Sets the valid range of the register value.
* xSim_Reg_Dump          : Exports the register operation log to a file.


#### Timer Module
Simulates timers, delays, and system ticks (`SysTick`), providing precise timing control and background callback execution.
* xSim_DelayUS           : Delay function for microseconds.
* xSim_DelayMS           : Delay function for milliseconds.
* xSim_Delay             : Delay function for seconds.
* xSim_Timer_Regist      : Registers the timer callback function.
* xSim_Timer_UnRegist    : Unregisters the timer callback function.
* xSim_Timer_Init        : Initializes the timer module.
* xSim_SysTick_Init      : Initializes the system tick timer module.
* xSim_GetSysTick        : Initializes the system tick and retrieves the current `SysTick` value.


#### WDT Module
Watchdog timer emulation, supporting timeout settings, watchdog feeding mechanism, and program exit control.
* xSim_WDT_Regist        : Registers the watchdog and sets the timeout.
* xSim_WDT_UnRegist      : Registers or unregisters the watchdog and sets the timeout.
* xSim_WDT_Init          : Initializes the `WDT` module.
* xSim_WDT_Feed          : Performs a watchdog feed to reset the counter.
* xSim_WDT_SetTimeOut    : Sets the timeout threshold.
* xSim_WDT_SetEn         : Enables or disables the watchdog.
* xSim_WDT_SetExit       : Sets whether to trigger program exit after timeout.


## Library Information
* xSim Library Size      : 0.031KB (  32-Byte)
* xSim_Timer Library Size: 1.353KB (1385-Byte)
* xSim_GPIO Library Size : 4.547KB (4656-Byte)
* xSim_Reg Library Size  : 3.780KB (3871-Byte)
* xSim_WDT Library Size  : 1.611KB (1650-Byte)
* xSim_CLI Library Size  : 3.273KB (3351-Byte)
* xSim_ADC Library Size  : 2.577KB (2639-Byte)
* xSim_IPC Library Size  : 3.004KB (3076-Byte)
* xSim_PWM Library Size  : 4.665KB (4777-Byte)
* xSim_INT library size  : 3.411KB (3493-Byte)

``` C
//Timer
xSim_Delay                // Occupied 79  Bytes
xSim_DelayMS              // Occupied 102 Bytes
xSim_DelayUS              // Occupied 102 Bytes
xSim_GetSysTick           // Occupied 108 Bytes
xSim_SysTick_Init         // Occupied 107 Bytes
xSim_Timer_Init           // Occupied 160 Bytes
xSim_Timer_Regist         // Occupied 12  Bytes
xSim_Timer_Task           // Occupied 185 Bytes
xSim_Timer_UnRegist       // Occupied 16  Bytes

//GPIO    
xSim_GPIO_Dump            // Occupied 134 Bytes
xSim_GPIO_Init            // Occupied 187 Bytes
xSim_GPI_Read             // Occupied 388 Bytes
xSim_GPI_Regist           // Occupied 187 Bytes
xSim_GPI_Set              // Occupied 53  Bytes
xSim_GPI_UnRegist         // Occupied 68  Bytes
xSim_GPO_Regist           // Occupied 187 Bytes
xSim_GPO_UnRegist         // Occupied 64  Bytes
xSim_GPO_Write            // Occupied 361 Bytes

//Reg   
xSim_RegDevice_Regist     // Occupied 43  Bytes
xSim_RegDevice_UnRegist   // Occupied 51  Bytes
xSim_Reg_Dump             // Occupied 134 Bytes
xSim_Reg_Init             // Occupied 223 Bytes
xSim_RegRead              // Occupied 887 Bytes
xSim_Reg_SetRange         // Occupied 287 Bytes
xSim_Reg_SetValue         // Occupied 246 Bytes
xSim_RegWrite             // Occupied 773 Bytes

//WDT   
xSim_WDT_Feed             // Occupied 131 Bytes
xSim_WDT_Init             // Occupied 186 Bytes
xSim_WDT_Regist           // Occupied 155 Bytes
xSim_WDT_SetEn            // Occupied 152 Bytes
xSim_WDT_SetExit          // Occupied 47  Bytes
xSim_WDT_SetTimeOut       // Occupied 47  Bytes
xSim_WDT_Task             // Occupied 262 Bytes
xSim_WDT_UnRegist         // Occupied 36  Bytes

//CLI   
xSim_CLI_Help             // Occupied 141 Bytes
xSim_CLI_Init             // Occupied 218 Bytes
xSim_CLI_IsRun            // Occupied 49  Bytes
xSim_CLI_Regist           // Occupied 247 Bytes
xSim_CLI_Start            // Occupied 83  Bytes
xSim_CLI_Stop             // Occupied 83  Bytes
xSim_CLI_Task             // Occupied 744 Bytes
xSim_CLI_UnRegist         // Occupied 169 Bytes

//ADC   
xSim_ADC_Dump             // Occupied 134 Bytes
xSim_ADC_GetValue         // Occupied 479 Bytes
xSim_ADC_Init             // Occupied 207 Bytes
xSim_ADC_Regist           // Occupied 159 Bytes
xSim_ADC_SetRange         // Occupied 120 Bytes
xSim_ADC_SetValue         // Occupied 56  Bytes
xSim_ADC_UnRegist         // Occupied 59  Bytes

//IPC   
xSim_IPC_Destroy          // Occupied 75  Bytes
xSim_IPC_Init             // Occupied 269 Bytes
xSim_IPC_IsRun            // Occupied 12  Bytes
xSim_IPC_Regist           // Occupied 199 Bytes
xSim_IPC_Send             // Occupied 217 Bytes
xSim_IPC_Service          // Occupied 503 Bytes
xSim_IPC_Start            // Occupied 12  Bytes
xSim_IPC_Stop             // Occupied 12  Bytes
xSim_IPC_UnRegist         // Occupied 129 Bytes

//PWM   
xSim_PWM_Destroy          // Occupied 98  Bytes
xSim_PWM_Dump             // Occupied 134 Bytes
xSim_PWM_Init             // Occupied 187 Bytes
xSim_PWM_Regist           // Occupied 390 Bytes
xSim_PWM_SetDuty          // Occupied 392 Bytes
xSim_PWM_SetEnable        // Occupied 383 Bytes
xSim_PWM_SetFreq          // Occupied 382 Bytes
xSim_PWM_Start            // Occupied 384 Bytes
xSim_PWM_Stop             // Occupied 373 Bytes
xSim_PWM_UnRegist         // Occupied 79  Bytes

//INT   
xSim_INT_Destroy          // Occupied 98  Bytes
xSim_INT_Dump             // Occupied 134 Bytes
xSim_INT_Init             // Occupied 187 Bytes
xSim_INT_Regist           // Occupied 199 Bytes
xSim_INT_SetEdge          // Occupied 46  Bytes
xSim_INT_SetTrigger       // Occupied 615 Bytes
xSim_INT_UnRegist         // Occupied 69  Bytes


```


## Compilation Dependencies
##### [Header Dependencies]
1. `xMeta.h`
2. `xType.h`

#### [Compilation]
Use the command `make all` within the `xSim` folder.
```shell
make all
```

#### [Standalone Use]
Each module can be used independently. Depending on the project size, it can be divided into independent modules for import and use; it's not necessary to use the entire `xSim.h` file.
1. Standalone use of `xSim_CLI.h`
2. Standalone use of `xSim_Timer.h`
3. Standalone use of `xSim_WDT.h`
4. Standalone use of `xSim_ADC.h`
5. Standalone use of `xSim_Reg.h`
6. Standalone use of `xSim_GPIO.h`
7. Standalone use of `xSim_INT.h`
8. Standalone use of `xSim_PWM.h`
9. Standalone use of `xSim_IPC.h`

#### [Example 1]
1. Demonstrating the use of functions within `xSim_CLI` to demonstrate registration commands and usage.
```C
//Main Code
int main(void)
{
  xSim_CLI_Init();
  xSim_CLI_Start();
  int i = 0;

  xSim_CLI_Regist("LED" ,xSim_CMD_LED ,"Control LED State(LED ON/OFF)");
  xSim_CLI_Regist("STAT",xSim_CMD_STAT,"Show Current Status");
  while(1)
  {
    printf(".");
    fflush(stdout);
    i++;

    if(i >= 20)
    {
      printf("\n");
      i = 0;
    }
    sleep(1);
  }
  return 0;
}

```

#### [Example 2]
1. Demonstrating the use of time modules using functions within `xSim_Timer`
```C
int main(void)
{
  xSim_Timer_Init();
  xSim_SysTick_Init();
  xSim_Timer_Regist(xSim_Timer_Event);

  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_Delay(1);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_Delay(2);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_Delay(3);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayMS(1);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayMS(20);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayMS(300);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayUS(1);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayUS(20);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());  xSim_DelayUS(300);
  printf("Cur Tick: %d ms\n",xSim_GetSysTick());

  while(1);
  return 0;
}
```

#### [Example 3]
1. Demonstrating the use of the watchdog module using functions within `xSim_WDT`
```C
int main(void)
{
  xSim_WDT_Init();
  xSim_WDT_Regist(2000);      //2s
  xSim_WDT_SetExit(1);        //Exit the Program
  xSim_WDT_SetEn(1);          //Enable

  printf("FEED DOG\n");
  for(U32 i=0;i<20;i++)
  {
    xSim_WDT_Feed();
    printf("FEED\n");
    usleep(500 * 1000);       //500ms
  }

  int Sec_Count = 0;
  printf("FUN DOG\n");
  while(1)
  {
    sleep(1);
    Sec_Count++;
    printf("[Main]: Waiting...(%d)\n",Sec_Count);
  }
  return 0;
}
```

#### [Example 4]
1. Demonstrating the use of the `ADC` module using functions within `xSim_ADC`.
``` C
int main(void)
{
  xSim_ADC_Init(1);
  xSim_ADC_Regist(0,8);      //CH0: 8-bit  (0 ~ 255)
  xSim_ADC_Regist(1,12);     //CH1: 12-bit (0 ~ 4095)
  xSim_ADC_Regist(2,24);     //CH2: 24-bit (0 ~ 16777215)
  xSim_ADC_Regist(3,32);     //CH3: 32-bit (0 ~ 4294967295)
  printf("[ADC]: Regist Channel CH0(8B),CH1(12B),CH2(24B),CH3(32B)\n");

  printf("[ADC]:Get Value\n");
  for(U8 Ch = 0;Ch < 4;Ch++)
  {
    printf("----------- Read CH%d (10 Times) -----------\n",Ch);
    for(int i = 0;i < 10;i++)
    {
      xSim_ADC_GetValue(Ch);
      usleep(10 * 1000);        //10ms Delay
    }
  }

  //Set Value
  printf("\n[ADC]: Set Value\n");
  U32 TEST_Value[] = {1111,2222,3333};
  for(int i = 0;i < 3;i++)
  {
    xSim_ADC_SetValue(1,TEST_Value[i]);
    printf("[V] ");
    xSim_ADC_GetValue(1);
    xSim_ADC_GetValue(1);
    usleep(10 * 1000); 
  }

  //Limit Range
  printf("\n[ADC]: Limit Range(1500~1800)\n");
  xSim_ADC_SetRange(1,1500,1800);
  for(int i = 0;i < 10;i++)
  {
    xSim_ADC_GetValue(1);
    usleep(10 * 1000); 
  }

  xSim_ADC_Dump(SIM_ADC_LOG);   //Dump
  return 0;
}

```

#### [Example 5]
1. Demonstrating the use of functions within `xSim_Reg` to illustrate the use of the `Reg` module.
```C
//Sensor-1 Device
#define SENSOR1_I2C_ADDR      0x50      //I2C Device ID
#define SENSOR1_DEV_ID        0         //Device ID

//Sensor-1
#define REG_TEMP_DEV_ID       0x00      //[RO]
#define REG_TEMP_CTRL         0x01      //[RW]
#define REG_TEMP_DATA         0x02      //[RO]
#define REG_TEMP_ONESHOT      0x03      //[RW]
#define SENSOR1_REG_COUNT     (sizeof(SimSensor1) / sizeof(xSim_Reg))

//Sensor-2 Device
#define SENSOR2_I2C_ADDR      0x38      //I2C Device ID
#define SENSOR2_DEV_ID        1         //Device ID

//Sensor-2
#define REG_AMB_DEV_ID        0x00      //[RO]
#define REG_AMB_CONF          0x01      //[RW]
#define REG_AMB_HLIGHT        0x02      //[RO]
#define REG_AMB_LLIGHT        0x03      //[RO]
#define SENSOR2_REG_COUNT     (sizeof(SimSensor2) / sizeof(xSim_Reg))

//[Variable Declare]
static xSim_Reg SimSensor1[] = 
{
//     Reg            Value  En      Attr          Type          Min  Max
  { REG_TEMP_DEV_ID , 0x68,  1,  xSIM_ATTR_RO, xSIM_TYPE_REGUALR, 0, 0xFF},
  { REG_TEMP_CTRL   , 0x00,  1,  xSIM_ATTR_WR, xSIM_TYPE_REGUALR, 0, 0xFF},
  { REG_TEMP_DATA   , 25  ,  1,  xSIM_ATTR_RO, xSIM_TYPE_RANDOM,  0, 0xFF},
  { REG_TEMP_ONESHOT, 50  ,  1,  xSIM_ATTR_RO, xSIM_TYPE_RANDOM,  0, 64, },
};


static xSim_Reg SimSensor2[] = 
{
//     Reg           Value  En      Attr          Type          Min  Max 
  { REG_AMB_DEV_ID  , 0x33, 1,  xSIM_ATTR_RO, xSIM_TYPE_REGUALR, 0, 0xFF},
  { REG_AMB_CONF    , 0x02, 1,  xSIM_ATTR_WR, xSIM_TYPE_REGUALR, 0, 0x0F},
  { REG_AMB_HLIGHT  , 0x00, 1,  xSIM_ATTR_RO, xSIM_TYPE_RANDOM , 0, 0xFF},
  { REG_AMB_LLIGHT  , 0x00, 1,  xSIM_ATTR_RO, xSIM_TYPE_RANDOM , 0, 0xFF},
};

//Main Code
int main(void)
{
  //Initial
  xSim_Reg_Init(1);   //Enable Log

  //Regist
  xSim_RegDevice_Regist(SENSOR1_DEV_ID,SENSOR1_I2C_ADDR,SimSensor1,SENSOR1_REG_COUNT);
  xSim_RegDevice_Regist(SENSOR2_DEV_ID,SENSOR2_I2C_ADDR,SimSensor2,SENSOR2_REG_COUNT);
  U32 rValue = 0;
  U32 wValue = 0;
  //Sensor-1 Operate
  printf("\n[1]\n");  xSim_DelayMS(100);
  xSim_RegRead (SENSOR1_I2C_ADDR,REG_TEMP_DEV_ID,&rValue,1);
  xSim_RegWrite(SENSOR1_I2C_ADDR,REG_TEMP_DEV_ID,&wValue,1);    //Write(Fault Operate)

  printf("\n[2]\n");  xSim_DelayMS(100);
  wValue = 0x15;
  xSim_RegRead (SENSOR1_I2C_ADDR,REG_TEMP_CTRL,&rValue,1);
  xSim_RegWrite(SENSOR1_I2C_ADDR,REG_TEMP_CTRL,&wValue,1);
  xSim_RegRead (SENSOR1_I2C_ADDR,REG_TEMP_CTRL,&rValue,1);

  printf("\n[3]\n");  xSim_DelayMS(100);
  for(int i=0;i<5;i++)
      xSim_RegRead(SENSOR1_I2C_ADDR,REG_TEMP_DATA,&rValue,1);

  printf("\n[4]\n");  xSim_DelayMS(100);
  xSim_Reg_SetValue(SENSOR1_I2C_ADDR,REG_TEMP_ONESHOT,0x11);      //Test Set Value
  xSim_RegRead(SENSOR1_I2C_ADDR,REG_TEMP_ONESHOT,&rValue,1);

  printf("\n[5]\n");  xSim_DelayMS(100);
  xSim_Reg_SetRange(SENSOR1_I2C_ADDR,REG_TEMP_ONESHOT,0x30,0x40); //Test Set Range
  for(int i=0;i<5;i++)
      xSim_RegRead(SENSOR1_I2C_ADDR,REG_TEMP_ONESHOT,&rValue,1);


  //Sensor-2 Operate
  printf("\n[6]\n");  xSim_DelayMS(100);
  xSim_RegRead (SENSOR2_I2C_ADDR,REG_AMB_DEV_ID,&rValue,1);
  xSim_RegWrite(SENSOR2_I2C_ADDR,REG_AMB_DEV_ID,&wValue,1);       //Write(Fault Operate)

  printf("\n[7]\n");  xSim_DelayMS(100);
  xSim_RegRead (SENSOR2_I2C_ADDR,REG_AMB_CONF,&rValue,1);
  xSim_RegWrite(SENSOR2_I2C_ADDR,REG_AMB_CONF,&wValue,1);
  xSim_RegRead (SENSOR2_I2C_ADDR,REG_AMB_CONF,&rValue,1);

  U32 r2Value[2] = {0};
  printf("\n[8]\n");  xSim_DelayMS(100);
  for(int i=0;i<5;i++)
    xSim_RegRead(SENSOR2_I2C_ADDR,REG_AMB_HLIGHT,r2Value,2);      //Test Read N-Byte

  //Dump
  xSim_Reg_Dump(SIM_REG_LOG);    //Dump

  //UnRegist
  xSim_RegDevice_UnRegist(SENSOR1_DEV_ID);
  xSim_RegDevice_UnRegist(SENSOR2_DEV_ID);
  return 0;
}
```

#### [Example Six]
1. Demonstrating the use of `GPIO` modules using functions within `xSim_GPIO`.
```C
int main(void)
{
  //Init
  xSim_GPIO_Init(1);

  //Regist
  xSim_GPI_Regist(0,"BTN1");
  xSim_GPI_Regist(1,"BTN2");
  xSim_GPO_Regist(0,"LED1");
  xSim_GPO_Regist(1,"LED2");

  //TEST GPIO Output
  printf("\nTEST GPO Output\n");
  xSim_GPO_Write(0,xSIM_GPIO_ON);  xSim_DelayMS(100);
  xSim_GPO_Write(1,xSIM_GPIO_ON);  xSim_DelayMS(100);
  xSim_GPO_Write(0,xSIM_GPIO_OFF);
  xSim_GPO_Write(1,xSIM_GPIO_OFF);

  //TEST GPIO Input
  xSim_GPI_Set(0,1);    //Set High
  xSim_GPI_Read(0);
  xSim_DelayMS(150);
  xSim_GPI_Set(1,1);    //Set High
  xSim_GPI_Read(1);
  xSim_DelayMS(150);
  xSim_GPI_Set(0,0);    //Set Low
  xSim_GPI_Read(0);

  U32 Delay = 0;
  for(U32 i=0;i<10;i++)
  {
    xSim_GPO_Write(0,i%2);
    Delay = (rand() % 500) + 1;
    xSim_DelayMS(Delay);
  }

  xSim_GPIO_Dump(SIM_GPIO_LOG);
  return 0;
}
```

#### [Example 7]
1. Demonstrating the use of the `INT` module using functions within `xSim_INT`.
```C
int main(void)
{
  //Init
  xSim_INT_Init(1);

  //Regist
  xSim_INT_Regist(0,"INT1",xSIM_INT_EDGE_RISING,Button1_ISR);
  xSim_INT_Regist(1,"INT2",xSIM_INT_EDGE_BOTH  ,Button2_ISR);

  //Set Interrupt
  xSim_INT_SetTrigger(0,1);     xSim_DelayMS(100);
  xSim_INT_SetTrigger(0,0);     xSim_DelayMS(100);
  xSim_INT_SetTrigger(1,1);     xSim_DelayMS(100);
  xSim_INT_SetTrigger(1,0);     xSim_DelayMS(100);

  //Set Edge
  xSim_INT_SetEdge(0,xSIM_INT_EDGE_FALLING);
  xSim_INT_SetTrigger(0,1);     xSim_DelayMS(100);
  xSim_INT_SetTrigger(0,0);     xSim_DelayMS(100);

  //Dump
  xSim_INT_Dump(SIM_INT_LOG);
  xSim_INT_Destroy();
  return 0;
}

```

#### [Example 8]
1. Demonstrating the use of the `INT` module using functions within `xSim_INT`.
```C
int main(void)
{
  //Init
  xSim_PWM_Init(1);

  //Regist
  xSim_PWM_Regist(0,"MOTOR1",1,1000,50);
  xSim_PWM_Regist(1,"MOTOR2",0,5000,20);

  //Start
  xSim_PWM_Start(0);          xSim_DelayMS(150);
  xSim_PWM_Start(1);          xSim_DelayMS(150);

  //Set
  xSim_PWM_SetFreq(0,2000);   xSim_DelayMS(150);
  xSim_PWM_SetDuty(0,80);     xSim_DelayMS(150);
  xSim_PWM_SetEnable(1,1);    xSim_DelayMS(150);
  xSim_PWM_SetDuty(1,50);     xSim_DelayMS(150);

  //Stop
  xSim_PWM_Stop(0);           xSim_DelayMS(150);
  xSim_PWM_Stop(1);           xSim_DelayMS(150);

  //Dump
  xSim_PWM_Dump(SIM_PWM_LOG);
  xSim_PWM_Destroy();
  return 0;
}
```

#### [Example 9]
1. Demonstrating the use of the `IPC` module by using functions within `xSim_IPC`.

Receive
``` C
int main(void)
{
  xSim_IPC_Init("Recv");

  xSim_IPC_Regist("Hello",Cmd_Hello_CB,"Print Greeting: Hello [Name]");
  xSim_IPC_Regist("LED"  ,Cmd_LED_CB  ,"Control LED: LED [1/0]");
  xSim_IPC_Regist("Exit" ,Cmd_Exit_CB ,"Exit the Receiver Program");
  xSim_IPC_Start();
  while(gRun && xSim_IPC_IsRun())
  {
    xSim_DelayMS(10);
    xSim_IPC_Service();
  }

  printf("[Recv]: Stop IPC Service...\n");
  xSim_IPC_Stop();
  xSim_IPC_Destroy();
  printf("[Recv]: Terminated Safely\n");
  return 0;
}
```

Send
``` C
int main(int Argc,char **Argv)
{
  if(Argc < 2)
  {
    printf("Usage: %s <Command> [Arg1] [Arg2] ...\n",Argv[0]);
    printf("Example: %s Hello John\n",Argv[0]);
    printf("Example: %s LED 1\n",Argv[0]);
    printf("Example: %s Exit\n",Argv[0]);
    return 1;
  }

  printf("[Send]: Starting IPC Sender...\n");
  xSim_IPC_Init("Sender");

  char MsgBuf[xSIM_IPC_MSG_SIZE] = {0};
  int  CurLen = 0;
  for(int i = 1;i < Argc;i++)
  {
    int Remain = (int)sizeof(MsgBuf) - CurLen - 1;
    int Written = snprintf(MsgBuf + CurLen,Remain,"%s",Argv[i]);
    if(Written < 0 || Written >= Remain)
    {
      printf("[Send Error]: Message too long!\n");
      break;
    }
        
    CurLen += Written;
    if(i < Argc - 1)
    {
      if(CurLen < (int)sizeof(MsgBuf) - 1)
      {
        MsgBuf[CurLen++] = ' ';
        MsgBuf[CurLen]   = '\0';
      }
    }
  }

  printf("[Send]: Sending [%s] --> [Recv]...\n",MsgBuf);
  xSim_IPC_Send("Recv",MsgBuf);

  xSim_DelayMS(50);
  xSim_IPC_Destroy();
  printf("[Send]: Done.\n");
  return 0;
}

```

## License Terms
This project is licensed under the `MIT License`.