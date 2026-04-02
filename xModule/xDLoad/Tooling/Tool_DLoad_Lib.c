//[STD Lib Include]
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

//[xLib Include]
#include "Tool_DLoad_Lib.h"


///@Function: DLoad_IsHeaderFile
///@Descript: Check File Name is Header File
int DLoad_IsHeaderFile(char *FileName)
{
  int Len = strlen(FileName);
  return (strcmp(FileName+Len-2,".h") == 0);
}


///@Function: DLoad_FileIsExist
///@Descript: Check File Is Exist
int DLoad_FileIsExist(char *FileName)
{
  FILE *fp = fopen(FileName,"r");
  if(fp)
  {
    fclose(fp);
    return 1;
  }
  return 0;
}


///@Function: DLoad_SplitPath
///@Descript: Split Full Path to Path and File Name
void DLoad_SplitPath(char *FullPath,char *Path,char *File)
{
  if(!FullPath || !Path || !File)
    return;

  char *Slash1 = strrchr(FullPath,'/');
  char *Slash2 = strrchr(FullPath,'\\');
  char *Slash  = Slash1 > Slash2 ? Slash1 : Slash2;

  if(Slash)
  {
    int Len = Slash - FullPath + 1;
    strncpy(Path,FullPath,Len);
    Path[Len] = '\0';
    //File
    strcpy(File,Slash + 1);
  }
  else
  {
    Path[0] = '\0';
    strcpy(File,FullPath);
  }
}


///@Function: DLoad_FileName_Generate
///@Descript: xxx.h -> xxx_DPort.h
void DLoad_FileName_Generate(char *In,char *Out)
{
  strcpy(Out,In);
  char *Dot = strrchr(Out,'.');
  if(Dot)
    *Dot = '\0';

  strcat(Out,"_DPort.h");
}


///@Function: DLoad_File_Read
///@Descript: Read File info Buffer
long DLoad_File_Read(char *FileName,char **Buf)
{
  FILE *fp = fopen(FileName,"rb");
  if(!fp)
    return 0;

  //Get Size
  fseek(fp,0,SEEK_END);
  long Size = ftell(fp);
  rewind(fp);

  //Allocate Memory
  *Buf = (char*)malloc(Size + 1);
  if(!(*Buf))
  {
    fclose(fp);
    return 0;
  }

  size_t RSize = fread(*Buf,1,Size,fp);
  if(RSize != (size_t)Size)
  {
    printf("[Error]: FRead Failed(%zu/%ld)\n",RSize,Size);
    free(*Buf);
    fclose(fp);
    return -1;
  }
  
  (*Buf)[Size] = '\0';
  fclose(fp);
  return Size;
}


///@Function: DLoad_File_Write
///@Descript: Write String Buffer to File
void DLoad_File_Write(char *FileName,char *Buf)
{
  FILE *fp = fopen(FileName,"w");
  if(!fp)
    return;

  fwrite(Buf,1,strlen(Buf),fp);
  fclose(fp);
}



///@Function: DLoad_ToUpper
///@Descript: String to Upper
void DLoad_ToUpper(char *Str)
{
  for(int i=0;i<Str[i];i++)
    if(Str[i] >= 'a' && Str[i] <= 'z')
      Str[i] -= 32;
}


///@Function: DLoad_HeadGuard_Generate
///@Descript: Generate #ifndef / #define 
void DLoad_HeadGuard_Generate(char *Str,char *FileName)
{
  char tmp[256] = {0};
  strcpy(tmp,FileName);

  //Remove Path
  char *p = strrchr(tmp,'/');
  if(p)
    memmove(tmp,p+1,strlen(p));

  //Remove Extension
  char *Dot = strchr(tmp,'.');
  if(Dot)
    *Dot = '\0';

  DLoad_ToUpper(tmp);
  strcat(tmp, "_DPORT_H__");
  sprintf(Str,"#ifndef __%s  //__%s\n"
              "#define __%s  //__%s\n\n",tmp,tmp,tmp,tmp);
}


///@Function: DLoad_TailGuard_Generate
///@Descript: Generate #endfi //__xxxx_h__
void DLoad_TailGuard_Generate(char *Str,char *FileName)
{
  char tmp[256] = {0};
  strcpy(tmp,FileName);

  //Remove Path
  char *p = strrchr(tmp,'/');
  if(p)
    memmove(tmp,p+1,strlen(p));
  
  //Remove Extension
  char *Dot = strchr(tmp,'.');
  if(Dot)
    *Dot = '\0';

  strcat(tmp,"_DPORT_H__");
  DLoad_ToUpper(tmp);
  sprintf(Str,"\n#endif //__%s\n\n",tmp);
}


///@Function: DLoad_Info_Generate
///@Descript: Generate File Header Information Comment Block
void DLoad_Info_Generate(char *Str,char *FileName)
{
  time_t tCur = time(NULL);
  struct tm *tTM = localtime(&tCur);

  char tStr[64] = {0};
  strftime(tStr,sizeof(tStr),"%Y-%m-%d %H:%M:%S",tTM);
  sprintf(Str,
  "//**************************************************\n"
  "//  @File   : %s DPort Header\n"
  "//  @Author : DLoad Tool\n"
  "//  @Date   : %s\n"
  "//  @Brief  : DPort Interface Definition\n"
  "//**************************************************\n\n",FileName,tStr);
} 


///@Function: DLoad_HeadPlus_Generate
///@Descript: Generate C++ Compatibility Header
void DLoad_HeadPlus_Generate(char *Str)
{
  sprintf(Str,"#ifdef __cplusplus\n"
              "extern \"C\" {\n"
              "#endif  // __cplusplus\n\n");
}


///@Function: DLoad_TailPlus_Generate
///@Descript: Generate C++ Compatibility Tail
void DLoad_TailPlus_Generate(char *Str)
{
  sprintf(Str,"\n#ifdef __cplusplus\n"
              "}\n"
              "#endif  // __cplusplus\n");
}


///@Function: DLoad_Include_Parse
///@Descript: Parse and Extract #include Lines from Input Buffer
void DLoad_Include_Parse(char *IBuf,char *Str)
{
  if(!IBuf || !Str)
    return;
  
  int Len = strlen(IBuf);
  char *Buf = (char*)malloc(Len+1);
  if(!Buf)
    return;

  memcpy(Buf,IBuf,Len+1);
  char *Line = strtok(Buf,"\n");
  while(Line)
  {
    while(*Line == ' ' || *Line == '\t')    //Skip Leading Space
      Line++;
    if(strncmp(Line,"#include",8) == 0)
    {
      strcat(Str,Line);
      strcat(Str,"\n");
    }
    Line = strtok(NULL,"\n");
  }
  free(Buf);
}


///@Function: DLoad_Typedef_Parse
///@Descript: Parse and Extrace Simple Typedef Variable Declaration
void DLoad_Typedef_Parse(char *IBuf,char *Str)
{
  if(!IBuf || !Str)
    return;

  int Len = strlen(IBuf);
  char *Buf = (char*)malloc(Len+1);
  if(!Buf)
    return;

  memcpy(Buf,IBuf,Len+1);
  char *Line = strtok(Buf,"\n");

  while(Line)
  {
    char *ORG = Line;
    while(*Line == ' ' || *Line == '\t')    //Skip Leading Space
      Line++;

    if(strncmp(Line,"typedef",7) == 0)
    {
      if(strstr(Line,"struct") || strstr(Line,"enum") || strstr(Line,"union"))    //Filter Struct/Enum/Union
      {
        Line = strtok(NULL,"\n");
        continue;
      }

      if(strchr(Line,'(') || strchr(Line,')'))    //Filter Function Pointer
      {
        Line = strtok(NULL,"\n");
        continue;
      }

      if(!strchr(Line,';'))                //Check End
      {
        Line = strtok(NULL,"\n");
        continue;
      }
      strcat(Str,ORG);
      strcat(Str,"\n");
    }
    Line = strtok(NULL,"\n");
  }
  free(Buf);
}


///@Function: DLoad_Macros_Parse
///@Descript: Parse and Extrace #define Macros from Input Buffer
void DLoad_Macros_Parse(char *IBuf,char *Str)
{
  if(!IBuf || !Str)
    return;

  int Len = strlen(IBuf);
  char *Buf = (char*)malloc(Len+1);
  if(!Buf)
    return;

  memcpy(Buf,IBuf,Len+1);
  char *Line = strtok(Buf,"\n");
  int InMacro = 0;
  
  while(Line)
  {
    char *ORG = Line;
    while(*Line == ' ' || *Line == '\t')
      Line++;
    
    if(strncmp(Line,"#define",7) == 0)
    {
      char *Name = Line + 7;
      while(*Name == ' ' || *Name == '\t')
        Name++;
      //FIler __XXX_H__
      if(strncmp(Name, "__", 2) == 0 && strstr(Name, "_H__") != NULL)
        InMacro = 0;
      else
      {
        char *p = Name;
        int IsFuncMacro = 0;
        while(*p && *p != ' ' && *p != '\t')
        {
          if(*p == '(')
          { 
            IsFuncMacro = 1;
            break;
          }
          p++;
        }
        InMacro = IsFuncMacro? 0 : 1;
      }
    }

    if(InMacro)
    {
      strcat(Str,ORG);
      strcat(Str,"\n");

      //Multiline Process
      int OLen = strlen(ORG);
      if(OLen > 0 && ORG[Len-1] != '\\')
        InMacro = 0;
    }
    Line = strtok(NULL,"\n");
  }
  free(Buf);
}


///@Function: DLoad_Enum_Parse
///@Descript: Parse Enum Definition from Input Buffer
void DLoad_Enum_Parse(char *IBuf,char *Str)
{
  if(!IBuf || !Str)
    return;

  int Len = strlen(IBuf);
  char *Buf = (char*)malloc(Len+1);
  if(!Buf)
    return;
  
  memcpy(Buf,IBuf,Len+1);
  char *Line = strtok(Buf,"\n");
  int InEnum  = 0;
  int BraceLv = 0;
  while(Line)
  {
    char *ORG = Line;
    while(*Line==' '||*Line=='\t')
      Line++;

    for(char *p=Line; *p; p++)
    {
      if(*p == '{') BraceLv++;
      if(*p == '}') BraceLv--;
    }

    if(BraceLv == 0 && (strncmp(Line,"typedef enum",12) == 0 || strncmp(Line,"enum",4) == 0))
      InEnum = 1;

    if(InEnum)
    {
      strcat(Str,ORG);
      strcat(Str,"\n");

      if(strchr(ORG,';') != NULL)
      {
        InEnum = 0;
        strcat(Str,"\n");
      }
    }
    Line = strtok(NULL,"\n");
  }
  free(Buf);
}


///@Function: DLoad_Callback_Parse
///@Descript: Parse Callback Function Typedef
void DLoad_Callback_Parse(char *IBuf,char *Str)
{
  if(!IBuf || !Str)
    return;

  int Len = strlen(IBuf);
  char *Buf = (char*)malloc(Len+1);
  if(!Buf)
    return;

  memcpy(Buf,IBuf,Len+1);
  char *Line = strtok(Buf, "\n");
  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;

    if(strncmp(p,"typedef",7)==0 && strstr(p,"(*") != NULL)
    {
      strcat(Str,p);
      strcat(Str,"\n");
    }
    Line = strtok(NULL,"\n");
  }
  free(Buf);
}


///@Function: DLoad_Struct_Parse
///@Descript: Parse Struct Definitions from Input Buffer
void DLoad_Struct_Parse(char *IBuf,char *Str)
{
  if(!IBuf || !Str)
    return;

  int Len = strlen(IBuf);
  char *Buf = (char*)malloc(Len+1);
  if(!Buf)
    return;

  memcpy(Buf,IBuf,Len+1);
  char *Line = strtok(Buf, "\n");
  int InStruct = 0;

  while(Line)
  {
    char *ORG = Line;
    while(*Line==' '||*Line=='\t')
      Line++;

    if(strncmp(Line,"typedef struct",14) == 0 || strncmp(Line,"struct",6) == 0)
      InStruct = 1;

    if(InStruct)
    {
      strcat(Str,ORG);
      strcat(Str,"\n");
      if(strchr(ORG,'}') != NULL && strchr(ORG,';') != NULL)
      {
        InStruct = 0;
        strcat(Str,"\n");
      }
    }
    Line = strtok(NULL, "\n");
  }
  free(Buf);
}



///@Function: DLoad_Callback_Generate
///@Descript: Generate Callback Typedef from Function Prototypes with Correct _CB Alignment
void DLoad_Callback_Generate(char *IBuf, char *Str)
{
  if(!IBuf || !Str)
    return;

  int Len = strlen(IBuf);
  char *Buf = (char*)malloc(Len+1);
  if(!Buf)
    return;
  
  memcpy(Buf, IBuf, Len+1);
  int MaxTypeLen = 0;
  int MaxNameLen = 0;
  char *Line = strtok(Buf, "\n");
  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;

    if(strchr(p,'(') && strchr(p,')') && strchr(p,';') && strncmp(p,"typedef",7) != 0)
    {
      char *pLine = strchr(p,'(');
      char *ptmp = pLine;
      while(ptmp>p && *(ptmp-1)!=' ' && *(ptmp-1)!='\t')
        ptmp--;

      int TypeLen = ptmp - p;
      if(TypeLen > MaxTypeLen)
        MaxTypeLen = TypeLen;
      int NameLen = pLine - ptmp;
      if(NameLen > MaxNameLen)
        MaxNameLen = NameLen;
    }
    Line = strtok(NULL,"\n");
  }

  memcpy(Buf,IBuf,Len+1);
  Line = strtok(Buf, "\n");
  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;

    if(strchr(p,'(') && strchr(p,')') && strchr(p,';') && strncmp(p,"typedef",7) != 0)
    {
      char *lp = strchr(p,'(');
      char *rp = strchr(p,')');
      char FName[128] = {0};
      char *ptmp = lp;
      while(ptmp>p && *(ptmp-1)!=' ' && *(ptmp-1)!='\t')
        ptmp--;
      strncpy(FName,ptmp,lp-ptmp);
      FName[lp-ptmp] = 0;

      //Type
      char FType[128] = {0};
      strncpy(FType, p, ptmp-p);
      FType[ptmp-p] = 0;
      char *t = FType + strlen(FType)-1;    //Trim Right
      while(t>=FType && (*t==' '||*t=='\t'))
      { 
        *t=0;
        t--;
      }

      char FParam[256] = {0};
      char *Param = lp+1;
      while(Param<rp)
      {
        char *Comma = strchr(Param,',');
        if(!Comma || Comma>rp)
          Comma = rp;

        char tmp[128] = {0};
        strncpy(tmp,Param,Comma-Param);
        tmp[Comma-Param] = 0;

        char *LastSpace = strrchr(tmp,' ');
        if(LastSpace)
          *LastSpace = 0;

        if(FParam[0]!=0)
          strcat(FParam,", ");
        strcat(FParam,tmp);
        Param = Comma+1;
      }

      int CurNameLen = strlen(FName);
      int SpaceLen = MaxNameLen - CurNameLen;
      char tBuf[512] = {0};
      snprintf(tBuf,sizeof(tBuf),"typedef %-*s (*%s_CB)%*s(%s);\n",MaxTypeLen,FType,FName,SpaceLen,"",FParam);
      strcat(Str,tBuf);
    }
    Line = strtok(NULL,"\n");
  }
  free(Buf);
}


///@Function: DLoad_Struct_Generate
///@Descript: Generate DPort Struct from Prototype & Extern Variable
void DLoad_Struct_Generate(char *IBuf,char *Str,char *FileName)
{
  if(!IBuf || !Str)
    return;

  int Len = strlen(IBuf);
  char *Buf = (char*)malloc(Len+1);
  if(!Buf)
    return;
  memcpy(Buf, IBuf, Len+1);

  //Struct Name
  char Base[256] = {0};
  strcpy(Base,FileName);
  char *Dot = strchr(Base,'.');
  if(Dot)
    *Dot = '\0';
  
  char tmp[256];
  //typedef struct _XXX_DPort
  snprintf(tmp,sizeof(tmp),"typedef struct _%s_DPort\n",Base);
  strcat(Str,tmp);
  strcat(Str,"{\n");

  //Function Part
  strcat(Str,"  //Function\n");
  char *Line = strtok(Buf,"\n");
  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;
    if(strchr(p,'(') && strchr(p,')') && strchr(p,';') && strncmp(p,"typedef",7)!=0)
    {
      char *lp = strchr(p,'(');
      char FName[128] = {0};    //Function Name
      char *ptmp = lp;
      while(ptmp>p && *(ptmp-1)!=' ' && *(ptmp-1)!='\t')
        ptmp--;
      strncpy(FName,ptmp,lp-ptmp);
      FName[lp-ptmp] = 0;
      snprintf(tmp,sizeof(tmp),"  %-20s %s;\n",strcat(FName,"_CB"),FName);
    }
    Line = strtok(NULL,"\n");
  }


  memcpy(Buf,IBuf,Len+1);
  Line = strtok(Buf,"\n");
  int HasProto = 0;
  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;

    if(strchr(p,'(') && strchr(p,')') && strchr(p,';') && strncmp(p,"typedef",7)!=0)
    {
      char *lp = strchr(p,'(');
      char FName[128] = {0};
      char *ptmp = lp;
      while(ptmp>p && *(ptmp-1)!=' ' && *(ptmp-1)!='\t')
        ptmp--;
      strncpy(FName,ptmp,lp-ptmp);
      FName[lp-ptmp] = 0;

      char CBName[128];
      snprintf(CBName,sizeof(CBName),"%s_CB",FName);
      snprintf(tmp,sizeof(tmp),"  %-15s %s;\n",CBName,FName);
      strcat(Str,tmp);
      HasProto = 1;
    }
    Line = strtok(NULL,"\n");
  }

  if(!HasProto)
    strcat(Str,"  //None\n");

  //Variable Part
  strcat(Str,"\n  //Variable\n");
  memcpy(Buf, IBuf, Len+1);
  Line = strtok(Buf,"\n");
  int HasVar = 0;
  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;
    if(strncmp(p,"extern",6)==0 && strchr(p,';') && !strchr(p,'('))
    {
      char Type[128]={0};
      char Name[128]={0};
      sscanf(p,"extern %s %[^;];",Type,Name);

      int  pCount = 0;
      char CleanType[128] = {0};
      int  Idx = 0;

      for(int i=0;Type[i];i++)
      {
        if(Type[i] == '*')
            pCount++;
        else
            CleanType[Idx++] = Type[i];
      }
      CleanType[Idx] = 0;
      pCount += 1;

      char pStr[16] = {0};
      for(int i=0;i<pCount;i++)
        strcat(pStr,"*");

      snprintf(tmp,sizeof(tmp),"  %-10s %s%s;\n",CleanType,pStr,Name);
      strcat(Str,tmp);
      HasVar = 1;
    }
    Line = strtok(NULL,"\n");
  }

  if(!HasVar)
    strcat(Str,"  //None\n");

  //End
  snprintf(tmp,sizeof(tmp),"} %s_DPort;\n",Base);
  strcat(Str,tmp);
  free(Buf);
}


///@Function: AppendAlignLine
///@Descript: 
static void AppendAlignLine(char *Str,char *fmt,...)
{
  char Buf[512];

  va_list args;
  va_start(args, fmt);
  int Len = vsnprintf(Buf,sizeof(Buf),fmt,args);
  va_end(args);

  while(Len < DLOAD_ALIGN_COL)
    Buf[Len++] = ' ';
  Buf[Len] = '\0';

  strcat(Buf,"\\\n");
  strcat(Str,Buf);
}


///@Function: DLoad_MFunc_Generate
///@Descript: Generate Macro Function (Bind + Check + Regist)
void DLoad_MFunc_Generate(char *IBuf,char *Str,char *FileName)
{
  if(!IBuf || !Str || !FileName)
    return;

  int Len = strlen(IBuf);
  char *Buf = (char*)malloc(Len+1);
  if(!Buf)
    return;

  //Base Name
  char Base[128] = {0};

  char *FName = strrchr(FileName,'/');
  if(!FName)
    FName = strrchr(FileName,'\\');
  FName = FName ? FName + 1 : FileName;

  strcpy(Base,FName);

  char *Dot = strchr(Base,'.');
  if(Dot)
    *Dot = '\0';

  char MacroName[128] = {0};
  strcpy(MacroName,Base);
  DLoad_ToUpper(MacroName);

  //Header
  AppendAlignLine(Str,"#define XDLIB_%s_GET(LIB,DPORT)",MacroName);
  AppendAlignLine(Str,"do");
  AppendAlignLine(Str,"{");

  //Function Bind
  AppendAlignLine(Str,"  /* Function Bind */");

  memcpy(Buf,IBuf,Len+1);
  char *Line = strtok(Buf,"\n");
  int FunCnt = 0;
  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;

    //Filter Prototype
    if(strchr(p,'(') && strchr(p,')') && strchr(p,';') && strncmp(p,"typedef",7) != 0)
    {
      char *lp = strchr(p,'(');
      char FName[128]={0};
      char *q = lp;
      while(q>p && *(q-1)!=' ' && *(q-1)!='\t')
        q--;

      strncpy(FName,q,lp-q);
      FName[lp-q]=0;
      if(strlen(FName)==0)
      {
        Line=strtok(NULL,"\n");
        continue;
      }

      char Cb[128];
      snprintf(Cb,sizeof(Cb),"%s_CB",FName);
      AppendAlignLine(Str,"  xDLOAD_BIND(LIB,%-12s,%s);",Cb,FName);
      FunCnt++;
    }
    Line = strtok(NULL,"\n");
  }

  if(FunCnt == 0)
      AppendAlignLine(Str,"  /* None */");

  //Variable Bind
  AppendAlignLine(Str,"  /* Variable Bind */");
  int VarCnt = 0;
  memcpy(Buf,IBuf,Len+1);
  Line = strtok(Buf,"\n");

  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;

    if(strncmp(p,"extern",6) == 0 && strchr(p,';') && !strchr(p,'(') && strstr(p,"\"") == NULL)
    {
      char Type[128]={0};
      char Name[128]={0};
      sscanf(p,"extern %s %[^;];", Type,Name);

      if(strlen(Name)==0)
      { 
        Line=strtok(NULL,"\n");
        continue;
      }

      int ptr = 1;
      for(int i=0;Type[i];i++)
        if(Type[i]=='*')
          ptr++;

      char Clean[128]={0};
      int Idx=0;
      for(int i=0; Type[i]; i++)
        if(Type[i]!='*')
          Clean[Idx++] = Type[i];

      char FinalType[128]={0};
      strcpy(FinalType,Clean);
      for(int i=0;i<ptr;i++)
        strcat(FinalType,"*");
      AppendAlignLine(Str,"  xDLOAD_BIND(LIB,%-8s,%s);",FinalType,Name);
      VarCnt++;
    }
    Line = strtok(NULL,"\n");
  }
  if(VarCnt == 0)
    AppendAlignLine(Str,"  /* None */");

  //Check
  AppendAlignLine(Str,"  /* Check */");

  memcpy(Buf,IBuf,Len+1);
  Line = strtok(Buf,"\n");
  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;

    char Name[128]={0};
    //Function
    if(strchr(p,'(') && strchr(p,')') && strchr(p,';') && strncmp(p,"typedef",7) != 0)
    {
      char *lp = strchr(p,'(');
      char *q = lp;
      while(q>p && *(q-1)!=' ' && *(q-1)!='\t')
        q--;
      strncpy(Name,q,lp-q);
      Name[lp-q]=0;
    }
    //Variable
    else if(strncmp(p,"extern",6) == 0 && strchr(p,';') && !strchr(p,'(') && strstr(p,"\"") == NULL)
      sscanf(p,"extern %*s %[^;];",Name);

    if(strlen(Name)==0)
    { 
      Line=strtok(NULL,"\n");
      continue;
    }

    int MaxNameLen = 9;
    int CurNameLen = strlen(Name);
    int SpaceLen   = MaxNameLen - CurNameLen;
    char tBuf[512] = {0};
    snprintf(tBuf, sizeof(tBuf), "  if(!%s)%*s  printf(\"[ERROR]: %s Bind Failed!\\n\");",Name, SpaceLen, "", Name);
    AppendAlignLine(Str,"%s",tBuf);
    Line = strtok(NULL,"\n");
  }

  //Regist
  AppendAlignLine(Str,"  /* Regist */");
  memcpy(Buf,IBuf,Len+1);
  Line = strtok(Buf,"\n");
  while(Line)
  {
    char *p = Line;
    while(*p==' '||*p=='\t')
      p++;

    char Name[128]={0};
    if(strchr(p,'(') && strchr(p,')') && strchr(p,';') && strncmp(p,"typedef",7) != 0)
    {
      char *lp = strchr(p,'(');
      char *q = lp;
      while(q>p && *(q-1)!=' ' && *(q-1)!='\t')
        q--;

      strncpy(Name,q,lp-q);
      Name[lp-q]=0;
    }
    else if(strncmp(p,"extern",6) == 0 && strchr(p,';') && !strchr(p,'(') && strstr(p,"\"")==NULL)
      sscanf(p,"extern %*s %[^;];",Name);

    if(strlen(Name)==0)
    {
      Line=strtok(NULL,"\n");
      continue;
    }
    AppendAlignLine(Str,"  DPORT.%-10s = %s;",Name,Name);
    Line = strtok(NULL,"\n");
  }
  strcat(Str,"} while(0)\n");
  free(Buf);
}