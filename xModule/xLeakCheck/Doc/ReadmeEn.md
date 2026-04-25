# xLeakCheck

> **Project** : xLeakCheck
> **Author**  : William Hsiao
> **Descript**: Lightweight memory leak detection toolkit

## Introduction
xLeakCheck is an extremely lightweight C language utility library designed specifically for embedded systems and C++ projects.
Through macro substitution, it tracks all dynamic memory allocation and deallocation behavior without altering the original program logic,helping developers accurately locate the files, functions, and line numbers where memory leaks occur.

## Features
1. Extremely Lightweight: Core code is approximately 200 lines.
2. Seamless Integration: Overrides standard library functions `malloc`, `calloc`, `realloc`, and `free` via macro definitions.
3. Precise Location: Automatically records `__FILE__`, `__LINE__`, and `__func__` information for leak points.
4. C/C++ Compatible: Supports the C99 standard, suitable for various compilation environments.
5. Unit Test Friendly: `xLeak_MemInfo` returns leak counts, facilitating integration with automated tests.

## API
#### [Core Functions]
1. `xLeak_Malloc` : Wraps `malloc`  and logs trace information.
2. `xLeak_Calloc` : Wraps `calloc`  and logs trace information.
3. `xLeak_Realloc`: Wraps `realloc` and updates the trace list.
4. `xLeak_Free`   : Frees memory and removes it from the trace list.
5. `xLeak_MemInfo`: Prints information about all currently unfreezed memory and returns the total number of leaked blocks.

#### [Core Macro Functions]
To maintain development practices, the library defines macros with the same names as those in the standard library, which will automatically retrieve the call location:
1. `malloc(S)`
2. `calloc(C,S)`
3. `realloc(P,S)`
4. `free(P)`

An explicit invocation version is also provided:
1. `Leak_Malloc(S)`
2. `Leak_Calloc(C,S)`
3. `Leak_Realloc(P,S)`
4. `Leak_Free(P)`

## Library Information
1. The size of the `xLeakCheck` library on Linux is 1.433KB.

```c
xLeak_Calloc        // Occupied 55  KB
xLeak_Free          // Occupied 126 KB
xLeak_Malloc        // Occupied 127 KB
xLeak_MemInfo       // Occupied 224 KB
xLeak_Realloc       // Occupied 108 KB
```

## Compilation Dependencies
##### [Header Dependencies]
1. `xMeta.h`
2. `xType.h`

##### [Compilation]
Use the command `make all` within the `xLeakCheck` folder.

```shell
make all
```

## Example
Use the command `make all` within the `Sample` folder.

```shell
make all
```

#### [Example 1]
1. Demonstrating the result of using `xLeakCheck` to allocate memory without releasing it.

```c
//Main Code
int main(void)
{
#ifdef LEAKCHECK
  atexit(Show_LeakMemInfo);
#endif    //LEAKCHECK

  int* ptr1 = malloc(1000*sizeof(int));
  int* ptr2 = calloc(1000,sizeof(int));

  memset(ptr1,0,1000*sizeof(int));
  memset(ptr2,0,1000*sizeof(int));

  ptr1=realloc(ptr1,2000*sizeof(int));
  memset(ptr1,0,2000*sizeof(int));

  return 0;
}

void Show_LeakMemInfo(void)
{
  xLeak_MemInfo();
}
```

## License Terms
This project is licensed under the `MIT License`.
