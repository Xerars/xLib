//[STD Lib Include]
#include <stdio.h>
#include <stdlib.h>

//[xLib Include]
#include "xType.h"
#include "xMeta.h"

//Author  : William Hsiao
//Descript: Lightweight Memory Leak Detection
//Version : 1.1.1

//[Macro Declare]
#define xLEAK_EXECUTE_NONE        0       //Execute None
#define xLEAK_EXECUTE_ONCE        1       //Execute Once

//[Struct Declare]
typedef struct _xLeak_Node
{
  void    *Addr;                    //Memory Leaked Address
  size_t   Block;                   //Memory Leaked Block
  size_t   Line;                    //Memory Leaked Line
  char    *FileName;                //Memory Leaked File Name
  xCC     *FuncName;                //Memory Leaked Function Name
  struct _xLeak_Node *Next;         //Pointer to Next Memory Node
} xLeak_Node;


//[Variable Declare]
xLeak_Node *Head  = NULL;
static int  gOnce = xLEAK_EXECUTE_NONE;

//Prototype Declare
static void xLeak_NodeAdd(void *Addr,size_t Block,size_t Line,char *FileName,xCC *FuncName);
static void xLeak_NodeRemove(void *Addr);

///@Function: xLeak_NodeAdd
///@Descript: Memory Node Add
static void xLeak_NodeAdd(void *Addr,size_t Block,size_t Line,char *FileName,xCC *FuncName)
{
  //Create New Node
  xLeak_Node *Node = (xLeak_Node*)malloc(sizeof(xLeak_Node));
  if(Node == NULL)
    return;

  //Set Data
  Node->Addr     = Addr;        //Set Address
  Node->Block    = Block;       //Set Block
  Node->Line     = Line;        //Set Line
  Node->FileName = FileName;    //Set File Name
  Node->FuncName = FuncName;    //Set Function Name
  Node->Next     = NULL;

  //Add Node to Linked List
  if(Head)  //First Node
  {
    Node->Next = Head;
    Head = Node;
  }
  else      //Other Node
    Head = Node;
}


///@Function: xLeak_NodeRemove
///@Descript: Memory Node Remove
static void xLeak_NodeRemove(void *Addr)
{
  //Check Head Node is Exist
  if(Head)
  {
    if(Head->Addr == Addr)    //Head Node
    {
      //Delete Head Node
      xLeak_Node* pNode = Head->Next;
      free(Head);
      Head = pNode;
    }
    else  //Check Linked Table is Null
    {
      xLeak_Node* pNode    = Head->Next;
      xLeak_Node* pCurNode = Head;
      while(pNode)    //Traverse all Node
      {
        xLeak_Node* pNext = pNode->Next;
        if(pNode->Addr == Addr)
        {
          pCurNode->Next = pNext;
          free(pNode);
        }
        else
          pCurNode = pCurNode->Next;
        pNode=pNext;
      }
    }
  }
}


///@Function: xLeak_MemInfo
///@Descript: Show Leak Memory Information
int xLeak_MemInfo(void)
{
  size_t Total = 0;
  if(gOnce == 0)
  {
    if(Head)
    {
      xLeak_Node* pNode = Head;
      int Count = 0;
      //Output Title
      puts("\n------------------------- Memory Leak Report -------------------------\n");
      while(pNode)   //Traverse all Node
      {
        Count++;
        //Output Leaked Memory Information
        printf("%02d.[%s\t]:(%s\t) <Line:%4zu>:Addr:%p (%zu byte)\n",
              Count,pNode->FileName,pNode->FuncName,pNode->Line,pNode->Addr,pNode->Block);

        Total += pNode->Block;

        xLeak_Node* pNext = pNode->Next;
        if(pNode != NULL)   //Check Link List Node is Not NULL
          free(pNode);      //Destroy Linked List Node
        pNode = pNext;
      }
      printf("\n@ Total Leak Memory:%zu byte\n",Total);
      //Output End of Line
      puts("\n--------------------- End of Memory Lake Report ----------------------\n");
      gOnce = xLEAK_EXECUTE_ONCE;
    }
  }
  else
    printf("@ xLeak_MemInfo can Only be Execute Once!");
  return Total;
}


///@Function: xLeak_Malloc
///@Descript: The Malloc Function with Memory Laked Checking
void* xLeak_Malloc(size_t Size,char *FileName,xCC *FuncName,size_t Line)
{
  void* Addr = malloc(Size);
  xLeak_NodeAdd(Addr,Size,Line,FileName,FuncName);
  return Addr;
}


///@Function: xLeak_Calloc
///@Descript: The Calloc Function with Memory Laked Checking
void* xLeak_Calloc(size_t Count,size_t Size,char *FileName,xCC *FuncName,size_t Line)
{
  void* Addr = calloc(Count,Size);
  xLeak_NodeAdd(Addr,Size*Count,Line,FileName,FuncName);
  return Addr;
}


///@Function: xLeak_Realloc
///@Descript: The Realloc Function with Memory Laked Checking
void* xLeak_Realloc(void* Addr,size_t Size,char *FileName,xCC *FuncName,size_t Line)
{
  void* tmpAddr = Addr;
  Addr = (void*)realloc(Addr,Size);

  xLeak_Node* pNode = Head->Next;
  while(pNode)   //Traverse all Node
  {
    if(pNode->Addr == tmpAddr)
    {
      pNode->Addr     = Addr;       //Set Address
      pNode->Block    = Size;       //Set Size
      pNode->FileName = FileName;   //Set File Name
      pNode->FuncName = FuncName;   //Set Function Name
      pNode->Line     = Line;       //Set Line
      break;
    }
    pNode = pNode->Next;
  }
  return Addr;
}


///@Function: xLeak_Free
///@Descript: The Free Function with Memory Leaked Checking
void xLeak_Free(void *Addr)
{
  xLeak_NodeRemove(Addr);
  free(Addr);
}