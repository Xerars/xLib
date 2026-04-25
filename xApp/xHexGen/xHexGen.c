//Author  : William Hsiao
//Descript: Application about Hex Convert to Array
//Version : 1.0.6

//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//Main Code
int main(int argc,char *argv[])
{
  if(argc<2)
  {
    printf("Usage:\n\t xHexGen <filename>\n");
    return 1;
  }

  xCC *FileName=argv[1];

  //Strip Path
  char *BaseName = strrchr(FileName,'/');
  if(!BaseName)
    BaseName = strrchr(FileName,'\\');    //Windows Path
  if(!BaseName)
    BaseName = (char*)FileName;
  else
    BaseName++;

  //Strip Extension
  char NameBuf[256] = {0};
  char ExtBuf[16] = {0};
  strncpy(NameBuf,BaseName,sizeof(NameBuf)-1);
  char *Dot = strrchr(NameBuf,'.');
  if(Dot)
  {
    strncpy(ExtBuf,Dot+1,sizeof(ExtBuf)-1);
    *Dot = '\0';
  }
  
  FILE *fp = fopen(FileName,"rb");
  if(!fp)
  {
    fprintf(stderr,"Error Opening Files: %s.\n",FileName);
    return 1;
  }

  //Get File Size
  fseek(fp,0,SEEK_END);           //Shift to End
  const int FileSize=ftell(fp);   //Get File Size
  fseek(fp,0,SEEK_SET);           //Shift to First

  unsigned char *Bin = malloc(FileSize);

  if(fread(Bin,1,FileSize,fp) != (size_t)FileSize)  //Read File
  {
    fprintf(stderr,"[Error]: Could Not Read the Entire File\n");
    SAFE_DESTROY(Bin);
    SAFE_CLOSE(fp);
    return 1;
  }
  SAFE_CLOSE(fp);                 //Close File
  
  printf("//[STD Lib Include]\n");
  printf("#include <stdint.h>\n\n");
  printf("/* Embedded Image File : %s.%s */\n",NameBuf,ExtBuf);
  printf("const int %s_FileSize  = %d;        //File Size\n",NameBuf,FileSize);
  printf("const uint8_t %s_File[] =\n",NameBuf);
  printf("{\n");

  for(int i = 0;i < FileSize;++i)
  {
    if(i == 0)
      printf("  ");
    printf("0x%02x%s",Bin[i],i==FileSize-1?"":((i+1)%16 == 0?",\n":","));
    if((i+1)%16 == 0)
      printf("  ");
  }
  printf("\n};\n");

  //Destroy
  SAFE_DESTROY(Bin);
  return 0;
}