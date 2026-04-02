#ifndef __XTYPE_H__ //__XTYPE_H__
#define __XTYPE_H__ //__XTYPE_H__
//Author  : William Hsiao
//Descript: Data Type Manager
//Version : 1.0.0

//[Typedef Declare]
//Sub-Name Express
typedef unsigned char       BYTE;         //1-Byte UINT
typedef unsigned short      WORD;         //2-Byte UINT
typedef unsigned int        DWORD;        //4-Byte UINT

//Unsigned Short Express
typedef unsigned char       U8;           //1-Byte UINT
typedef unsigned short      U16;          //2-Byte UINT
typedef unsigned int        U32;          //4-Byte UINT

//xType Style Express
typedef unsigned char       xU8;          //1-Byte UINT
typedef unsigned short      xU16;         //2-Byte UINT
typedef unsigned int        xU32;         //4-Byte UINT

//Signed Short Express
typedef signed char         S8;           //1-Byte SINT
typedef signed short        S16;          //2-Byte SINT
typedef signed int          S32;          //4-Byte SINT

//xType Style Express
typedef signed char         xS8;          //1-Byte SINT
typedef signed short        xS16;         //2-Byte SINT
typedef signed int          xS32;         //4-Byte SINT

//Unsigned Long Express
typedef unsigned char       UINT8;        //1-Byte UINT
typedef unsigned short      UINT16;       //2-Byte UINT
typedef unsigned int        UINT32;       //4-Byte UINT

//Signed Long Express
typedef signed char         SINT8;        //1-Byte SINT
typedef signed short        SINT16;       //2-Byte SINT
typedef signed int          SINT32;       //4-Byte SINT

//64-Bit
typedef unsigned long long  U64;          //8-Byte UINT
typedef unsigned long long  xU64;         //8-Byte UINT
typedef unsigned long long  UINT64;       //8-Byte UINT

typedef signed long long    S64;          //8-Byte SINT
typedef signed long long    xS64;         //8-Byte SINT
typedef signed long long    SINT64;       //8-Byte SINT

//Float Express
typedef float               F32;          //Float
typedef double              F64;          //Double
typedef float               FLT32;        //Float
typedef double              FLT64;        //Double
typedef float               FLT;          //Float
typedef double              DBL;          //Double


//Constant String Express
typedef const char          CCHAR;        //const char
typedef const char          CC;           //const char
typedef const char          xCC;          //const char

//Boolean
typedef int                 xBOOL;        //Boolean

//Error
typedef int                 xErr;         //Error
typedef int                 Err;          //Error

//Misc
typedef unsigned int        xHandle;      //Handle
typedef unsigned int        xID;          //ID

//[Macro Declare]
//Decorate
#define VOL                 volatile      //Volatile
#define EXT                 extern        //Extern
#define REG                 register      //Register
#define CONST               const         //Constant
#define INLINE              inline        //Inline
#define STATIC              static        //Static

//NULL
#ifndef NULL
  #define NULL              ((void*)0)    //NULL
#endif

//Constant
#define xTRUE               1             //True
#define xFALSE              0             //False

#define xON                 1             //On
#define xOFF                0             //Off

#define xENABLE             1             //Enable
#define xDISABLE            0             //Disable

#define xSET                1             //Set
#define xRESET              0             //Reset

#define xUNMUTE             0             //UnMute
#define xMUTE               1             //Mute

#define xSUCCESS            0x00          //Success
#define xFAILED             0xFF          //Failed

#define xNOT_INITED					0							//Not Inited
#define xINITED							1							//Inited

#endif  //__XTYPE_H__
