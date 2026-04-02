#ifndef __XMETA_H__  //__XMETA_H__
#define __XMETA_H__  //__XMETA_H__
//Author  : William Hsiao
//Descript: General-Purpose Macro Utility 
//Version : 1.0.7

//[Macro Declare]
//Identifier
#define AND                         &&                                          //Logical AND
#define OR                          ||                                          //Logical OR
#define NOT                         !                                           //Logical NOT
#define NOT_EQ                      !=                                          //Not Equal
#define EQ                          ==                                          //Equal
#define IS                          =                                           //Assignment

//Alias Var
#define _FUNC                       __func__                                    //Function Name
#define _FILE                       __FILE__                                    //File Name
#define _LINE                       __LINE__                                    //Line Number
#define _DATE                       __DATE__                                    //Compiler Name
#define _TIME                       __TIME__                                    //Compiler Time
#define _COUNT                      __COUNTER__                                 //Counter (Unique Accumulation)

//Math
#define PI                          3.14159265359                               //Math: PI
#define EXP                         2.71828182845                               //Math: Euler's Number
#define PHI                         1.61803398874                               //Math: Golden Ratio
#define SQRT2                       1.41421356237                               //Math: Square Root of 2
#define SQRT3                       1.73205080756                               //Math: Square Root of 3
#define LN2                         0.69314718055                               //Math: Nautral Log of 2
#define LN10                        2.30258509299                               //Math: Nautral Log of 3

//[Macro Function Declare]
//Memory
#define ASIZE(ARY)                  (sizeof(ARY)/sizeof((ARY)[0]))              //Return the Number of Element in the Array
#define MEMZERO(P,SIZE)             memset((P),0,(SIZE))                        //Clear Memory Block
#define MEMCOPY(DST,SRC,SIZE)       memcpy((DST),(SRC),(SIZE))                  //Copy  Memory Block

#define SAFE_DESTROY(P)             \
do                                  \
{                                   \
  if(P)                             \
  {                                 \
    free(P);                        \
    (P) = NULL;                     \
  }                                 \
} while(0)                                                                      //Check is Exist and Release Memory

#define SAFE_CLOSE(FP)              \
do                                  \
{                                   \
  if(FP)                            \
  {                                 \
    fclose(FP);                     \
    FP = NULL;                      \
  }                                 \
} while(0)                                                                      //Check is Exist and Close File


//Loop
#define FOREVER                     for(;;)
#define RANGE(I,Y,X)                \
  for(I=(Y);                        \
     (((X)>=(Y))?(I<=(X)):(I>=X));  \
     (((X)>=(Y))?((I)++):((I)--)))                                              //For-Loop Counts Up or Down fro Y~X Automatically

#define FOREACH(I,A)                \
  for(int _K=1,_CNT=0,              \
      _SZ=sizeof(A)/sizeof*(A);     \
      _K && _CNT!=_SZ;              \
      _K=!_K,_CNT++)                \
    for(I=(A)+_CNT;_K;_K = !_K)                                                 //Retrieve the Index of Each Element in Array

//Math
#define CONSTRAIN(V,L,H)            ((V)<(L)?(L):((V)>(H)?(H):(V)))             //Limit Value Range to Low ~ High
#define RAD2DEG(X)                  ((X)/PI*180)                                //RAD -> DEG
#define DEG2RAD(X)                  ((X)*PI/180)                                //DEG -> RAG
#define _MIN(X,Y)                   (((X)<(Y))? (X):(Y))                        //Get Min Value
#define _MAX(X,Y)                   (((X)>(Y))? (X):(Y))                        //Get Max Value
#define ABS(X)                      (((X)< 0 )?-(X):(X))                        //Get ABS Value
#define DIFF(X,Y)                   ABS((X)-(Y))                                //Get X,Y Difference
#define IMPLIES(X,Y)                (!(X)||(Y))                                 //Implication Operation
#define COMPARE(X,Y)                (((X)>(Y))-((X)<(Y)))                       //Compare: (X>Y):1 (X=Y):0 (X<Y):-1
#define SIGN(X)                     COMPARE(X,0)                                //Get X Sign
#define SQUARE(X)                   ((X)*(X))                                   //Calculate Square
#define CUBE(X)                     ((X)*(X)*(X))                               //Calculate Cube

//Align
#define ALIGNB(X,AGN)               (((X)+((AGN)-1)) & ~((AGN)-1))              //2^X Bit Mask Alignment(Fast:4,8,16,32)
#define ALIGN(X,AGN)                ((((X)+((AGN)-1))/(AGN))*(AGN))             //Any Positive Integer Alignment(Slow)
#define IS_ALIGN(X,AGN)             (((X) & ((AGN)-1)) == 0)                    //Is Integer Alignment

//Clamp
#define FLOORB(X,AGN)               ((X) & ~((AGN) - 1))                        //Bitwise Floor(FLOORB(123,16) => 112)
#define FLOOR(X,AGN)                (((X) / (AGN)) * (AGN))                     //Math Floor
#define CEILB(X,AGN)                ALIGNB(X,AGN)                               //Bitewise Ceil(CEILB(123,16) => 128)
#define CEIL(X,AGN)                 ALIGN(X,AGN)                                //Math Ceil
#define CLIP(X,MIN,MAX)             (((X)<(MIN))?(MIN):(((X)>(MAX))?(MAX):(X))) //Clip X in [MIN~MAX]
#define UCLIP(X,MAX)                (((X)>(MAX))?(MAX):(X))                     //Clip Max
#define LCLIP(X,MIN)                (((X)<(MIN))?(MIN):(X))                     //Clip Min

//Swap
#define SWAP(A,B)                   \
do                                  \
{                                   \
  A ^= B;                           \
  B ^= A;                           \
  A ^= B;                           \
} while(0)                                                                      //Swap A & B

#define SAFE_SWAP(TYPE,A,B)         \
do                                  \
{                                   \
  TYPE _TMP = (A);                  \
  (A)       = (B);                  \
  (B)       = _TMP;                 \
} while(0)                                                                      //Swap A & B (SAFE)

//Sort
#define SORT(A,B)                   do { if((A)>(B))  SWAP((A),(B)); } while(0) //Check A>B and Swap
#define SAFE_SORT(A,B)              do { if((A)>(B))  SWAP((A),(B)); } while(0) //Check A>B and Safe Swap

//Check
#define IS_NAN(X)                   ((X) !=(X))                                 //Check X is NAN(Not a Numer)
#define IS_ODD(N)                   ((N) & 1)                                   //Check N is Odd Value
#define IS_EVEN(N)                  (!IS_ODD((N)))                              //Check N is Even Value
#define IS_BETWEEN(N,L,H)           (((N)>=(L) && (N)<=(H)))                    //Check N is Between L~H

//Bits
#define _BIT(X)                     (1<<(X))                                    //Creates a Bitmask with Bit X Set
#define SET_BIT(X,P)                ((X)|(1<<(P)))                              //Set   Bit P in X
#define CLR_BIT(X,P)                ((X)&(~(1<<(P))))                           //Clear Bit P in X
#define GET_BIT(X,P)                (((X)>>(P))&1)                              //Get the Value of Bit P in X
#define TOG_BIT(X,P)                ((X)^(1<<(P)))                              //Toggle Bit P in X

//Array
#define SET_ARRAY(D,N,V)            \
do                                  \
{                                   \
  size_t _I,_N;                     \
  for(_N= (N),_I=0;_N>0;--_N,++_I)  \
    (D)[_I]=(V);                    \
} while(0)                                                                      //Set the First N Element of Array D to the Value V
#define ZERO_ARRAY(D,N)             SET_ARRAY(D,N,0)                            //Set the First N Element of Array D to the Value 0
#define COLUMNS(S,E)                ((E)-(S)+1)                                 //Calculate Element Size Contain S~E
#define _IS_ARRAY(A)                ((void *)&A == (void *)A)                   //Check Var is Array
#define ARRAY_LAST(A)               ((A)[ASIZE(A)-1])                           //Get Last Array Element

//String
#define STRING                      char*                                       //Alias for String Type
#define STR2(S)                     #S                                          //Convert Token to String(No Expansion)
#define STR(S)                      STR2(S)                                     //Convert Token to String(Expansion)
#define CAT(S1,S2)                  (S1 "" S2)                                  //Concatenate Two String Literals

//Tokens
#define PASTE2(S1,S2)               S1##S2                                      //Concatenate Token A and B(No Expansion)
#define PASTE(S1,S2)                PASTE2(S1,S2)                               //Concatenate Token A and B(Expansion)
#define PRINT_TOKEN(TOKEN)          printf(#TOKEN " => %d",TOKEN)               //Print Token Name and Integer Value
#define UNIQUE_NAME(BASE)           PASTE(BASE,__COUNTER__)                     //Generate Unique ID(Avoid Naming Conficts)

//DEFER
#define DEFER2(HEAD,TAIL,I)         for(int I=(HEAD,0);!I;TAIL,I++)             //Initial and Clean a Block of Scoped Code
#define DEFER(HEAD,TAIL)            DEFER2(HEAD,TAIL,__DEFERVAR__##__COUNTER__) //Initial and Clean a Block of Scoped Code

//STMT
#define STMT(STUFF)                 do{STUFF} while(0)                          //Create Multiple Statement Macros Function

//Saturating Inc/Dec
#define SAT_INC(W,L)                (W=(((W)==(L))?(W):((W)+1)))                //Inc to Saturation Value and Stop
#define SAT_DEC(W,L)                (W=(((W)==(L))?(W):((W)-1)))                //Dec to Saturation Value and Stop

//Execute Once
#define ONCE2(EXP,VAR)              \
  static int VAR = 1;               \
  if(VAR)                           \
  {                                 \
    EXP;                            \
    VAR = 0;                        \
  }                                                                             //Execute Once

#define ONCE(EXP)                   ONCE2(EXP,__ONCEVAR_##__COUNTER__)          //Execute Once

//Execute Check
#define EXECUTE(FUNC)               \
do                                  \
{                                   \
  FUNC;                             \
  printf("[%s-%d]:EXECUTE"          \
  ,_FUNC,_LINE);                    \
} while(0);                         //Execute Function and Trace


//User ID
#define EUSER_ID                    geteuid()                                   //Get Effective User ID
#define USER_ID                     getuid()                                    //Get User ID

//Environment(C/C++)
#ifdef __cplusplus
  #define EXTERN_C_START            extern "C" {                                //Extern C++ Environment Start
  #define EXTERN_C_END              }                                           //Extern C++ Environment End
#else
  #define EXTERN_C_START                                                        //Extern C++ Environment Start
  #define EXTERN_C_END                                                          //Extern C++ Environment End
#endif

//Exit
#define DIE                         exit(0)                                     //Terminate Program

//Function ShortHands
#define MAIN()                      int main(int argc,char **argv)              //Short Main
#define NOW()                       time(NULL)                                  //Short Now

//Endian(Big/Little)
#define BSWAP16(x)                  ((U16)((((x) & 0x00FF)<<8)  | \
                                           (((x) & 0xFF00)>>8)))                //Endian Swap(16-Bit)

#define BSWAP32(x)                  ((U32)((((x) & 0x000000FF)<<24) | \
                                           (((x) & 0x0000FF00)<< 8) | \
                                           (((x) & 0x00FF0000)>> 8) | \
                                           (((x) & 0xFF000000)>>24)))           //Endian Swap(32-Bit)

#define BSWAP64(x)                  ((U64)((((x) & 0x00000000000000FF)<<56) | \
                                           (((x) & 0x000000000000FF00)<<40) | \
                                           (((x) & 0x0000000000FF0000)<<24) | \
                                           (((x) & 0x00000000FF000000)<< 8) | \
                                           (((x) & 0x000000FF00000000)>> 8) | \
                                           (((x) & 0x0000FF0000000000)>>24) | \
                                           (((x) & 0x00FF000000000000)>>40) | \
                                           (((x) & 0xFF00000000000000)>>56)))   //Endian Swap(64-Bit)

//Likely
#define LIKELY(X)                   _builtin_expect(!!(X),1)                    //Branch Prediction is 1
#define UNLIKELY(X)                 _builtin_expect(!!(X),0)                    //Branch Prediction is 0

//Coroutine
#define CORO_START(STAT)            switch(*(STAT)) { case 0:
#define CORO_YIELD(STAT)            do { *(STAT) = __LINE__; return; case __LINE__:;} while(0)
#define CORO_END()                  }

//Misc
#define UNUSED(V)                   (void)(V)                                   //Unused
#define CAST(TYPE,X)                ((TYPE)X)                                   //Convert X to Type

#endif  //__XMETA_H__
