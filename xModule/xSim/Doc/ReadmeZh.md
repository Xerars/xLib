# xSim

**Project** : xSim
**Author**  : William Hsiao
**Descript**: 嵌入式系統硬體與周邊模擬工具庫

## 簡介
`xSim` 是 `xLib` 工具庫中的核心模組之一，旨在為嵌入式系統開發提供輕量、靈活的硬體與周邊模擬環境。
本模塊針對沒有實體硬體時的軟體驗證與測試優化，支援多種常見微控制器周邊模擬，並提供標準化的控制與日誌導出 `API`，簡化單元測試與早期開發流程。

## 特性
1. 全方位模擬: 涵蓋 `ADC`、`GPIO`、`PWM`、`Interrupt`、`Timer`、`WDT`、`Register`、`CLI` 以及 `IPC` 跨行程通訊。
2. 靈活配置  : 各周邊支援參數化註冊、通道管理及隨機/單次等數據行為設定。
3. 運行追蹤  : 內建日誌記錄與 `Dump` 機制，方便將模擬過程中的訊號變化與狀態寫入檔案分析。
4. 易於集成  : 採用一致的 API 設計，支援獨立模塊裁剪或整體引入，適配各類嵌入式軟體架構。


#### ADC 模塊
模擬類比數位轉換器(`Analog-To-Digital Converter`)，支援通道註冊、範圍設定與隨機或單次數據模擬。
xSim_ADC_Regist：註冊指定通道與位元數的 ADC。  xSim_ADC_UnRegist：取消註冊指定通道。  xSim_ADC_Init：初始化 ADC 模擬模組與日誌功能。  xSim_ADC_GetValue：取得指定通道的類比轉換數值。  xSim_ADC_SetValue：設定指定通道的模擬數值。  xSim_ADC_SetRange：設定指定通道的數值上下限範圍。  xSim_ADC_Dump：將 ADC 模擬日誌導出至指定檔案。  


#### CLI 模塊
命令列介面(`Command Line Interface`)模擬，支援基於執行緒的互動式指令輸入與解析。
* xSim_CLI_Init          : 初始化 CLI 模組與內部資源。
* xSim_CLI_Start         : 啟動 CLI 執行緒。
* xSim_CLI_Stop          : 停止 CLI 執行緒。
* xSim_CLI_IsRun         : 檢查 CLI 是否正在運行。
* xSim_CLI_Regist        : 註冊指令、回調函數與說明。
* xSim_CLI_UnRegist      : 取消註冊指定指令。  


#### GPIO 模塊
通用輸入輸出 (`General-Purpose Input/Output`) 模擬，支援輸入 (`GPI`) 與輸出 (`GPO`) 狀態控制與日誌紀錄。
* xSim_GPI_Regist        : 註冊指定 `ID` 與名稱的輸入引腳。
* xSim_GPO_Regist        : 註冊指定 `ID` 與名稱的輸出引腳。
* xSim_GPI_UnRegist      : 取消註冊指定輸入引腳。
* xSim_GPO_UnRegist      : 取消註冊指定輸出引腳。
* xSim_GPIO_Init         : 初始化 `GPIO` 模擬環境。
* xSim_GPI_Set           : 設定輸入引腳的準位。
* xSim_GPI_Read          : 讀取輸入引腳的準位。
* xSim_GPO_Write         : 寫入輸出引腳的準位。
* xSim_GPIO_Dump         : 將 `GPIO` 狀態與日誌導出至檔案。


#### INT 模塊
外部中斷 (`Interrupt`) 模擬，支援多通道邊緣觸發設定與回調機制。
* xSim_INT_Init          : 初始化中斷模擬模組。
* xSim_INT_Destroy       : 銷毀中斷模擬模組。
* xSim_INT_Regist        : 註冊中斷通道、名稱、觸發邊緣與 `ISR` 回調。
* xSim_INT_UnRegist      : 取消註冊中斷通道。
* xSim_INT_SetEdge       : 設定中斷觸發邊緣類型。
* xSim_INT_SetTrigger    : 設定當前觸發訊號準位。
* xSim_INT_Dump          : 導出中斷日誌至檔案。


#### IPC 模塊
行程間通訊(`Inter-Process Communication`)模擬，基於 POSIX 訊息佇列提供跨行程指令收發與服務機制。
* xSim_IPC_Init          : 初始化 `IPC` 模組並綁定模組名稱。
* xSim_IPC_Destroy       : 銷毀 `IPC` 資源。
* xSim_IPC_Start         : 啟動 `IPC` 服務執行緒。
* xSim_IPC_Stop          : 停止 `IPC` 服務執行緒。
* xSim_IPC_IsRun         : 檢查 `IPC` 服務運行狀態。
* xSim_IPC_Regist        : 註冊 `IPC` 遠端調用指令。
* xSim_IPC_UnRegist      : 取消註冊 `IPC` 遠端調用指令。
* xSim_IPC_Service       : 處理 `IPC` 訊息服務。
* xSim_IPC_Send          : 向指定模組發送訊息。


#### PWM 模塊
脈衝寬度調變(`Pulse Width Modulation`)模擬，支援多通道頻率、佔空比調整與運行控制。
* xSim_PWM_Init          : 初始化 `PWM` 模擬模組。
* xSim_PWM_Destroy       : 銷毀 `PWM` 模組。
* xSim_PWM_Regist        : 註冊 `PWM` 通道。
* xSim_PWM_UnRegist      : 取消註冊 `PWM` 通道。
* xSim_PWM_SetEnable     : 設定 `PWM` 啟用狀態。
* xSim_PWM_SetFreq       : 設定 `PWM` 頻率 (`Hz`)。
* xSim_PWM_SetDuty       : 設定 `PWM` 佔空比 (`0-100%`)。
* xSim_PWM_Start         : 啟動指定的 `PWM` 通道。 
* xSim_PWM_Stop          : 停止指定的 `PWM` 通道。
* xSim_PWM_Dump          : 導出 `PWM` 運行日誌至檔案。


#### REG 模塊
暫存器(`Register`)裝置模擬，支援記憶體映射裝置的讀寫權限控制、屬性設定與範圍限制。
* xSim_RegDevice_Regist  : 註冊暫存器裝置及其對應的表格與大小。  
* xSim_RegDevice_UnRegist: 取消註冊暫存器裝置。  
* xSim_Reg_Init          : 初始化暫存器模擬與日誌功能。 
* xSim_RegWrite          : 寫入指定地址與暫存器的資料。
* xSim_RegRead           : 讀取指定地址與暫存器的資料。
* xSim_Reg_SetValue      : 設定指定暫存器的數值。
* xSim_Reg_SetRange      : 設定暫存器的數值有效範圍。
* xSim_Reg_Dump          : 導出暫存器操作日誌至檔案。


#### Timer 模塊
計時器、延遲與系統滴答(`SysTick`)模擬，提供精確的時序控制與背景回調執行緒。
* xSim_DelayUS    　     : 微秒的延遲函數。
* xSim_DelayMS           : 毫秒的延遲函數。
* xSim_Delay             : 秒的延遲函數。  
* xSim_Timer_Regist      : 註冊定時回調函數。
* xSim_Timer_UnRegist    : 取消註冊定時回調函數。  
* xSim_Timer_Init        : 初始化計時器模組。  
* xSim_SysTick_Init      : 初始化系統滴答計時器模組
* xSim_GetSysTick        : 初始化系統滴答並取得當前 `SysTick` 數值。


#### WDT 模塊
看門狗計時器(`Watchdog Timer`)模擬，支援超時設定、餵狗機制與程式異常退出控制。
* xSim_WDT_Regist        : 註冊看門狗並設定超時時間
* xSim_WDT_UnRegist      : 註冊或取消註冊看門狗並設定超時時間。
* xSim_WDT_Init          : 初始化 `WDT` 模組。
* xSim_WDT_Feed          : 執行餵狗操作以重置計數器。
* xSim_WDT_SetTimeOut    : 設定超時門檻。
* xSim_WDT_SetEn         : 啟用或停用看門狗。
* xSim_WDT_SetExit       : 設定超時後是否觸發程式退出。


## 庫資訊
* xSim       庫大小: 0.031KB(  32-Byte)
* xSim_Timer 庫大小: 1.353KB(1385-Byte)
* xSim_GPIO  庫大小: 4.547KB(4656-Byte)
* xSim_Reg   庫大小: 3.780KB(3871-Byte)
* xSim_WDT   庫大小: 1.611KB(1650-Byte)
* xSim_CLI   庫大小: 3.273KB(3351-Byte)
* xSim_ADC   庫大小: 2.577KB(2639-Byte)
* xSim_IPC   庫大小: 3.004KB(3076-Byte)
* xSim_PWM   庫大小: 4.665KB(4777-Byte)
* xSim_INT   庫大小: 3.411KB(3493-Byte)

總大小約為 28.25 KB(共 28,930 Bytes)

``` C
//Timer
xSim_Delay                // 佔用 79 Bytes
xSim_DelayMS              // 佔用 102 Bytes
xSim_DelayUS              // 佔用 102 Bytes
xSim_GetSysTick           // 佔用 108 Bytes
xSim_SysTick_Init         // 佔用 107 Bytes
xSim_Timer_Init           // 佔用 160 Bytes
xSim_Timer_Regist         // 佔用 12 Bytes
xSim_Timer_Task           // 佔用 185 Bytes
xSim_Timer_UnRegist       // 佔用 16 Bytes

//GPIO    
xSim_GPIO_Dump            // 佔用 134 Bytes
xSim_GPIO_Init            // 佔用 187 Bytes
xSim_GPI_Read             // 佔用 388 Bytes
xSim_GPI_Regist           // 佔用 187 Bytes
xSim_GPI_Set              // 佔用 53 Bytes
xSim_GPI_UnRegist         // 佔用 68 Bytes
xSim_GPO_Regist           // 佔用 187 Bytes
xSim_GPO_UnRegist         // 佔用 64 Bytes
xSim_GPO_Write            // 佔用 361 Bytes

//Reg   
xSim_RegDevice_Regist     // 佔用 43 Bytes
xSim_RegDevice_UnRegist   // 佔用 51 Bytes
xSim_Reg_Dump             // 佔用 134 Bytes
xSim_Reg_Init             // 佔用 223 Bytes
xSim_RegRead              // 佔用 887 Bytes
xSim_Reg_SetRange         // 佔用 287 Bytes
xSim_Reg_SetValue         // 佔用 246 Bytes
xSim_RegWrite             // 佔用 773 Bytes

//WDT   
xSim_WDT_Feed             // 佔用 131 Bytes
xSim_WDT_Init             // 佔用 186 Bytes
xSim_WDT_Regist           // 佔用 155 Bytes
xSim_WDT_SetEn            // 佔用 152 Bytes
xSim_WDT_SetExit          // 佔用 47 Bytes
xSim_WDT_SetTimeOut       // 佔用 47 Bytes
xSim_WDT_Task             // 佔用 262 Bytes
xSim_WDT_UnRegist         // 佔用 36 Bytes

//CLI   
xSim_CLI_Help             // 佔用 141 Bytes
xSim_CLI_Init             // 佔用 218 Bytes
xSim_CLI_IsRun            // 佔用 49 Bytes
xSim_CLI_Regist           // 佔用 247 Bytes
xSim_CLI_Start            // 佔用 83 Bytes
xSim_CLI_Stop             // 佔用 83 Bytes
xSim_CLI_Task             // 佔用 744 Bytes
xSim_CLI_UnRegist         // 佔用 169 Bytes

//ADC   
xSim_ADC_Dump             // 佔用 134 Bytes
xSim_ADC_GetValue         // 佔用 479 Bytes
xSim_ADC_Init             // 佔用 207 Bytes
xSim_ADC_Regist           // 佔用 159 Bytes
xSim_ADC_SetRange         // 佔用 120 Bytes
xSim_ADC_SetValue         // 佔用 56 Bytes
xSim_ADC_UnRegist         // 佔用 59 Bytes

//IPC   
xSim_IPC_Destroy          // 佔用 75 Bytes
xSim_IPC_Init             // 佔用 269 Bytes
xSim_IPC_IsRun            // 佔用 12 Bytes
xSim_IPC_Regist           // 佔用 199 Bytes
xSim_IPC_Send             // 佔用 217 Bytes
xSim_IPC_Service          // 佔用 503 Bytes
xSim_IPC_Start            // 佔用 12 Bytes
xSim_IPC_Stop             // 佔用 12 Bytes
xSim_IPC_UnRegist         // 佔用 129 Bytes

//PWM   
xSim_PWM_Destroy          // 佔用 98 Bytes
xSim_PWM_Dump             // 佔用 134 Bytes
xSim_PWM_Init             // 佔用 187 Bytes
xSim_PWM_Regist           // 佔用 390 Bytes
xSim_PWM_SetDuty          // 佔用 392 Bytes
xSim_PWM_SetEnable        // 佔用 383 Bytes
xSim_PWM_SetFreq          // 佔用 382 Bytes
xSim_PWM_Start            // 佔用 384 Bytes
xSim_PWM_Stop             // 佔用 373 Bytes
xSim_PWM_UnRegist         // 佔用 79 Bytes

//INT   
xSim_INT_Destroy          // 佔用 98 Bytes
xSim_INT_Dump             // 佔用 134 Bytes
xSim_INT_Init             // 佔用 187 Bytes
xSim_INT_Regist           // 佔用 199 Bytes
xSim_INT_SetEdge          // 佔用 46 Bytes
xSim_INT_SetTrigger       // 佔用 615 Bytes
xSim_INT_UnRegist         // 佔用 69 Bytes


```


## 編譯依賴
##### [標頭依賴]
1. `xMeta.h`
2. `xType.h`


#### [編譯]
在 `xSim` 資料夾內使用指令 `make all`
```shell
make all
```

#### [獨立使用]
每一個模塊可以獨立使用，可以視專案大小去切割成獨立模塊引入使用，不一定要使用一整塊的 `xSim.h`。

1. 獨立使用 `xSim_CLI.h`
2. 獨立使用 `xSim_Timer.h`
3. 獨立使用 `xSim_WDT.h`
4. 獨立使用 `xSim_ADC.h`
5. 獨立使用 `xSim_Reg.h`
6. 獨立使用 `xSim_GPIO.h`
7. 獨立使用 `xSim_INT.h`
8. 獨立使用 `xSim_PWM.h`
8. 獨立使用 `xSim_IPC.h`

#### [範例一]
1. 演示使用 `xSim_CLI` 內的函數演示註冊命令與使用
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

#### [範例二]
1. 演示使用 `xSim_Timer` 內的函數演示時間模組的使用
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

#### [範例三]
1. 演示使用 `xSim_WDT` 內的函數演示看門狗模組的使用
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

#### [範例四]
1. 演示使用 `xSim_ADC` 內的函數演示 `ADC` 模組的使用
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

#### [範例五]
1. 演示使用 `xSim_Reg` 內的函數演示 `Reg` 模組的使用
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

#### [範例六]
1. 演示使用 `xSim_GPIO` 內的函數演示 `GPIO` 模組的使用
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

#### [範例七]
1. 演示使用 `xSim_INT` 內的函數演示 `INT` 模組的使用
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

#### [範例八]
1. 演示使用 `xSim_INT` 內的函數演示 `INT` 模組的使用
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

#### [範例九]
1. 演示使用 `xSim_IPC` 內的函數演示 `IPC` 模組的使用

接收
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

發送
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

## 授權條款
本專案採用 `MIT License` 授權使用