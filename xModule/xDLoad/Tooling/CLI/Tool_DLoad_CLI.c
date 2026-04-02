//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"
#include "Tool_DLoad_Lib.h"

//[Macro Declare]
#define OUT_PATH          "../Out/"       //Output Path

//Main Code
int main(int argc,char **argv)
{
  if(argc < 2)
  {
    printf("[Usage]: %s <Header>\n",argv[0]);
    return -1;
  }

  char *InFile = argv[1];
  char InPath[256]  = {0};
  char InName[256]  = {0};
  char OutFile[256] = {0};
  char OutName[256] = {0};
  //Check
  if(!DLoad_IsHeaderFile(InFile))
  {
    printf("[Error]: Input File is Not Header(.h): %s\n",InFile);
    return -1;
  }

  if(!DLoad_FileIsExist(InFile))
  {
    printf("[Error]: File is Not Found: %s\n",InFile);
    return -1;
  }

  printf("[Info]: Input File: %s\n",InFile);

  //[STEP1]: Generate Output File Name
  DLoad_SplitPath(InFile,InPath,InName);              //Split Path
  DLoad_FileName_Generate(InName,OutName);
  printf("[Info]: Output File: %s\n",OutName);

  //[STEP2]: Read File
  char *IBuf = NULL;
  long Size = DLoad_File_Read(InFile,&IBuf);
  if(Size <= 0 || !IBuf)
  {
    printf("[Error]: Read File Fail!\n");
    return -1;
  }


  //[STEP3]: Allocate Memory
  char *OBuf = (char*)malloc(Size + 4096);    //+4KB Size
  if(!OBuf)
  {
    free(IBuf);
    return -1;
  }
  OBuf[0] = '\0';

  //[STEP3]: Parse
  char Include_Buf[2048]  = {0};
  char Typedef_Buf[2048]  = {0};
  char Macros_Buf[2048]   = {0};
  char Enum_Buf[2048]     = {0};
  char CallBack_Buf[2048] = {0};
  char Struct_Buf[2048]   = {0};

  DLoad_Include_Parse (IBuf, Include_Buf);
  DLoad_Typedef_Parse (IBuf, Typedef_Buf);
  DLoad_Macros_Parse  (IBuf, Macros_Buf);
  DLoad_Enum_Parse    (IBuf,Enum_Buf);
  DLoad_Callback_Parse(IBuf,CallBack_Buf);
  DLoad_Struct_Parse  (IBuf,Struct_Buf);

//printf("[Include Declare]\n");  printf("%s\n\n",Include_Buf);
//printf("[Typedef Declare]\n");  printf("%s\n\n",Typedef_Buf);
//printf("[Macro Declare]\n");    printf("%s\n\n",Macros_Buf);
//printf("[Enum Declare]\n");     printf("%s\n\n",Enum_Buf);
//printf("[Callback Declare]\n"); printf("%s\n\n",CallBack_Buf);
//printf("[Struct Declare]\n");   printf("%s\n\n",Struct_Buf);

  //[STEP4]: Generate
  char Head[256]         = {0};
  char Tail[256]         = {0};
  char CPP_Head[256]     = {0};
  char CPP_Tail[256]     = {0};
  char Info[256]         = {0};
  char GenCB_Buf[2048]   = {0};
  char GenST_Buf[2048]   = {0};
  char GenMF_Buf[4096]   = {0};
  DLoad_HeadGuard_Generate(Head,OutName);
  DLoad_Info_Generate(Info,OutName);
  DLoad_HeadPlus_Generate(CPP_Head);
  DLoad_TailPlus_Generate(CPP_Tail);
  DLoad_TailGuard_Generate(Tail,OutName);

  //Parse & Generate
  DLoad_Callback_Generate(IBuf,GenCB_Buf);
  DLoad_Struct_Generate(IBuf,GenST_Buf,InName);
  DLoad_MFunc_Generate(IBuf,GenMF_Buf,InName);

//printf("[Generate Callback]\n");        printf("%s\n\n",GenCB_Buf);
//printf("[Generate Struct]\n");          printf("%s\n\n",GenST_Buf);
//printf("[Generate Macro Function]\n");  printf("%s\n\n",GenMF_Buf);

  //[STEP5]
  strcat(OBuf,Head);
  strcat(OBuf,Info);
  //Include
  strcat(OBuf,"//[Include Declare]\n");
  (strlen(Include_Buf)>0)?strcat(OBuf,Include_Buf)
                         :strcat(OBuf,"//None\n");
  strcat(OBuf,"\n");

  //Typedef 
  strcat(OBuf,"//[Typedef Declare]\n");
  (strlen(Typedef_Buf)>0)?strcat(OBuf,Typedef_Buf)
                         :strcat(OBuf,"//None\n");
  strcat(OBuf,"\n");

  //Macro
  strcat(OBuf,"//[Macro Declare]\n");
  (strlen(Macros_Buf)>0)?strcat(OBuf,Macros_Buf)
                        :strcat(OBuf,"//None\n");
  strcat(OBuf,"\n");

  //Enum
  strcat(OBuf,"//[Enum Declare]\n");
  (strlen(Enum_Buf)>0)?strcat(OBuf,Enum_Buf)
                      :strcat(OBuf,"//None\n");
  strcat(OBuf,"\n");

  //Callback
  strcat(OBuf,"//[Callback Function Declare]\n");
  strcat(OBuf,CallBack_Buf);
  strcat(OBuf,"\n");
  strcat(OBuf,"//Generate Callback\n");
  strcat(OBuf,GenCB_Buf);
  strcat(OBuf,"\n");

  //Struct
  strcat(OBuf,"//[Struct Declare]\n");
  strcat(OBuf,Struct_Buf);
  strcat(OBuf,"\n");
  strcat(OBuf,"//Generate Struct\n");
  strcat(OBuf,GenST_Buf);
  strcat(OBuf,"\n");

  //Cplusplus
  strcat(OBuf,CPP_Head);
  strcat(OBuf,"//[Variable Declare]\n");
  strcat(OBuf,"//None\n");
  strcat(OBuf,"//[Prototype Declare]\n");
  strcat(OBuf,"//None");
  strcat(OBuf,CPP_Tail);
  
  //Macro Function
  strcat(OBuf,"//[Macro Function Declare]\n");
  strcat(OBuf,GenMF_Buf);
  strcat(OBuf,Tail);

  //[STEP6]: Write File
  snprintf(OutFile,sizeof(OutFile),"%s%s",OUT_PATH,OutName);
  DLoad_File_Write(OutFile,OBuf);
  printf("[Done]: Generate Success\n");

  //[STEP7]: Destroy Memory
  free(IBuf);
  free(OBuf);
  return 0;
}


