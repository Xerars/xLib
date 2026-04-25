//[xLib Include]
#include "xDLoad.h"

//Author  : William Hsiao
//Descript: Cross-Platform Dynamic Library Loading Function Library
//Version : 1.0.1

///@Function: xDLIB_Load
///@Descript: Dynamically Load Specified Shared Library
xDLib xDLIB_Load(xCC* Path)
{
#ifdef _WIN32
  return (xDLib)LoadLibrary(Path);
#else
  return (xDLib)dlopen(Path,RTLD_LAZY);
#endif
}


///@Function: xDLIB_Close
///@Descript: Close and UnInstall the Dynamic Library
void xDLIB_Close(xDLib Handle)
{
  if(!Handle)
    return;
#ifdef _WIN32
  FreeLibrary((HMODULE)Handle);
#else
  dlclose(Handle);
#endif
}


///@Function: xDLIB_Get
///@Descript: Obtain the Entry Point Address in Memory Based on the Function Name(Symbol)
void* xDLIB_Get(xDLib Handle,xCC* FName)
{
  if(!Handle)
    return NULL;
#ifdef _WIN32
  return (void*)GetProcAddress((HMODULE)Handle,FName);
#else
  return dlsym(Handle,FName);     //Get Function
#endif
}
