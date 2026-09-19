//Author  : William Hsiao
//Descript: STM32 Hardware and Peripheral Utility Library
//Version : 1.0.0

#ifndef __XSTM_H__  //__XSTM_H__
#define __XSTM_H__  //__XSTM_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//Config
#include "xSTM_Config.h"

//PlugIn
#if xSTM_SUPPORT_DEBUG    //Debug PlugIn
  #include "xSTM_Debug.h"
#endif

#if xSTM_SUPPORT_DWT      //DWT PlugIn
  #include "xSTM_DWT.h"
#endif

#if xSTM_SUPPORT_FLASH    //Flash PlugIn
  #include "xSTM_Flash.h"
#endif

#if xSTM_SUPPORT_SYS      //Sys PlugIn
  #include "xSTM_Sys.h"
#endif

#if xSTM_SUPPORT_POWER    //Power PlugIn
  #include "xSTM_Power.h"
#endif

#endif // __XSTM_H__
