#ifndef __TOOL_DLOAD_LIB_H__ //__TOOL_DLOAD_LIB_H__
#define __TOOL_DLOAD_LIB_H__ //__TOOL_DLOAD_LIB_H__

//[xLib Include]
#include "xType.h"
#include "xMeta.h"


//[Macro Declare]
#define DLOAD_ALIGN_COL         80        //DLoad Align Column


#ifdef __cplusplus
extern "C" {
#endif
//[Prototype Declare]
//File Name
void DLoad_FileName_Generate(char *In,char *Out);
void DLoad_SplitPath(char *FullPath,char *Path,char *File);

//File
long DLoad_File_Read (char *FileName,char **Buf);
void DLoad_File_Write(char *FileName,char *Buf);
int  DLoad_IsHeaderFile(char *FileName);
int  DLoad_FileIsExist (char *FileName);

//Info
void DLoad_Info_Generate(char *Str,char *FileName);


//Utils
void DLoad_ToUpper(char *Str);

//Guard
void DLoad_HeadGuard_Generate(char *Str,char *FileName);
void DLoad_TailGuard_Generate(char *Str,char *FileName);
void DLoad_HeadPlus_Generate(char *Str);
void DLoad_TailPlus_Generate(char *Str);

//Parser
void DLoad_Include_Parse (char *IBuf,char *Str);
void DLoad_Typedef_Parse (char *IBuf,char *Str);
void DLoad_Macros_Parse  (char *IBuf,char *Str);
void DLoad_Enum_Parse    (char *IBuf,char *Str);
void DLoad_Callback_Parse(char *IBuf,char *Str);
void DLoad_Struct_Parse  (char *IBuf,char *Str);

//Generate
void DLoad_Callback_Generate(char *IBuf,char *Str);
void DLoad_Struct_Generate  (char *IBuf,char *Str,char *FileName);
void DLoad_MFunc_Generate   (char *IBuf,char *Str,char *FileName);


#ifdef __cplusplus
}
#endif

#endif  //__TOOL_DLOAD_LIB_H__
