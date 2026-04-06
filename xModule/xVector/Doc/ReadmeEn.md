# xDuff

> **Project** : xVector
> **Author**  : William Hsiao
> **Descript**: Based on a macro-high elasticity, dynamic generic vector library

## Introduction
`xVector` is a lightweight `C` language library designed to provide dynamic array functionality similar to `C++ std::vector` in a pure C environment.
Through powerful `macro dispatch` technology, it supports:
* Pseudo-generic support: A single macro can generate a custom `Vector` implementation for a custom structure or primitive type.
* Automatic resizing mechanism: Built-in doubling random access memory management reduces the overhead of frequent `realloc` calls.
* Type safety: Generated functions have type names (e.g., xVec_Int_Push), effectively avoiding type misuse.

## Features
1. `C/C++` compatibility
2. `C99` support
3. Does not use `void*`, preserving the compiler's ability to optimize for specific types.
4. Minimal dependencies
5. Complete lifecycle management: Covers initialization, dynamic scaling, insertion, deletion, and basic operations.

## API
#### [Type Definitions]
1. `xVector`: A default int-type vector structure.
2. `XVEC_STRUCT(TYPE,NAME)`: A core macro used to declare a vector structure of a specific type.

#### [Core Functions]
1. `xVector_Init`    : Initializes the vector, pre-allocating the specified capacity.
2. `xVector_Destroy` : Deploys internal data space and resets the state.
3. `xVector_Resize`  : Manually adjusts the vector capacity.
4. `xVector_Push`    : Adds an element at the end (automatically doubles the capacity if insufficient).
5. `xVector_Pop`     : Removes the last element.
6. `xVector_At`      : Randomly accesses the element at the specified index (including boundary checks and static zero protection).
7. `xVector_Insert`  : Inserts an element at the specified position; subsequent elements are automatically shifted to the right.
8. `xVector_Remove`  : Removes the element at the specified position; subsequent elements are automatically shifted to the left.
9. `xVector_Update`  : Updates the content of the element at the specified position.
10. `xVector_Clear`  : Clears all data (preserves capacity).
11. `xVector_Merge`  : Merge two vectors of the same type
12. `xVector_Reverse`: Reverse the order of elements in a vector
13. `xVector_Sum`    : Calculate the sum of the vectors
14. `xVector_Average`: Calculate the average value of a vector
15. `xVector_Scale`  : Scale the vector
16. `xVector_FindMax`: Find the maximum value of a vector
17. `xVector_FindMin`: Find the minimum value of a vector

#### [Core Macro Functions]
1. `XVEC_IMPL(TYPE,NAME)`: Generates all operation function implementations for this type in one go
2. `xVec_NAME_Init`      : Initializes a vector, pre-allocating a specified capacity
3. `xVec_NAME_Destroy`   : Releases internal data space and resets the state
4. `xVec_NAME_Resize`    : Manually adjusts the vector capacity
5. `xVec_NAME_Push`      :Add an element at the end (automatically doubles the capacity if insufficient).
6. `xVec_NAME_Pop`       : Removes the last element.
7. `xVec_NAME_At`        : Randomly accesses the element at the specified index 
8. `xVec_NAME_Insert`    : Inserts an element at the specified position; subsequent elements are automatically shifted to the right.
9. `xVec_NAME_Remove`    : Removes the element at the specified position; subsequent elements are automatically shifted to the left.
10. `xVec_NAME_Update`   : Updates the content of the element at the specified position.
11. `xVec_NAME_Clear`    : Clears all data (preserves capacity).
12. `xVec_NAME_Merge`    : Merges two vectors of the same type.
13. `xVec_NAME_Reverse`  : Reverses the order of elements in a vector.

## 庫資訊
1. `xVector` Library size: `1.975KB`->`1.916KB`(-2.98%)
```c
xVector_FindMax   // Occupied 250->230(-8.00%)  Bytes
xVector_FindMin   // Occupied 247->227(-8.09%)  Bytes
xVector_Sum       // Occupied 159->143(-10.06%) Bytes
xVector_Insert    // Occupied 141->124(-12.06%) Bytes
xVector_Merge     // Occupied 115 Bytes
xVector_Push      // Occupied 62 Bytes
xVector_Remove    // Occupied 57 Bytes
xVector_Resize    // Occupied 49 Bytes
xVector_Reverse   // Occupied 49 Bytes
xVector_Average   // Occupied 48 Bytes
xVector_Init      // Occupied 45 Bytes
xVector_Destroy   // Occupied 38 Bytes
xVector_Scale     // Occupied 35 Bytes
xVector_At        // Occupied 26 Bytes
xVector_Update    // Occupied 23 Bytes
xVector_Pop       // Occupied 18 Bytes
xVector_Clear     // Occupied 12 Bytes
```

## Compilation Dependencies
##### [Header Dependencies]
1. `xMeta.h`
2. `xType.h`

##### [Compilation]
Use the command `make all` in the `xVector` folder

```shell
make all
```

## Example
Use the command `make all` in the `Sample` folder

```shell
make all
```
#### [Example 1]
1. Demonstrating dynamic array operations using `xVector` integers

```c
//Main Code
int main(void)
{
  xVector Vec1;
  xVector Vec2;

  //Init
  xVector_Init(&Vec1,5);
  xVector_Init(&Vec2,5);

  //Push Data
  xVector_Push(&Vec1,1);
  xVector_Push(&Vec1,3);
  xVector_Push(&Vec1,5);

  xVector_Push(&Vec2,2);
  xVector_Push(&Vec2,4);
  xVector_Push(&Vec2,6);

  //At
  int V1 = xVector_At(&Vec1,2);
  int V2 = xVector_At(&Vec1,2);

  //Insert
  xVector_Insert(&Vec1,1,99);
  xVector_Insert(&Vec2,1,99);

  //Update
  xVector_Update(&Vec1,0,100);
  xVector_Update(&Vec2,0,100);

  //Remove
  xVector_Remove(&Vec1,3);
  xVector_Remove(&Vec2,3);

  //Math
  xVector_Scale(&Vec1,2);

  int Sum = xVector_Sum(&Vec1);
  DBL Avg = xVector_Average(&Vec1);
  int Max = xVector_FindMax(&Vec1);
  int Min = xVector_FindMin(&Vec1);

  //Utils
  xVector_Reverse(&Vec2);
  xVector_Merge(&Vec1,&Vec2);
  xVector_Clear(&Vec2);

  //Destroy
  xVector_Destroy(&Vec1);
  xVector_Destroy(&Vec2);
  return 0;
}
```

#### [Example 2]
1. Demonstrating the use of the `xVector` macro function for different data types
2. Demonstrating the use of macro functions to handle `int`    declarations
3. Demonstrating the use of macro functions to handle `double` declarations
4. Demonstrating the use of macro functions to handle `char`   declarations
5. Demonstrating the use of macro functions to handle `char*`  declarations
6. Demonstrating the use of macro functions to handle `struct` declarations
7. Demonstrating the use of macro functions to handle `char*` using the difference between `deep copy` and `shallow copy`

```c
XVEC_STRUCT(int  ,INT);
XVEC_IMPL(int ,INT);

//Main Code
int main(void)
{
  TEST_INT_VECTOR();    //TEST Integer   Vector
  TEST_DBL_VECTOR();    //TEST Double    Vector
  TEST_CHAR_VECTOR();   //TEST Character Vector
  TEST_STR_VECTOR();    //TEST String    Vector
  TEST_STU_VECTOR();    //TEST Struct    Vector
  
  //Demo Copy
  Demo_Copy();          //Deep Copy vs Shallow Copy
  return 0;
}

///@Function: TEST_INT_VECTOR
///@Descript: Test Integer Vector
static void TEST_INT_VECTOR(void)
{
  xVec_INT V1;
  xVec_INT V2;

  xVec_INT_Init(&V1,5);
  xVec_INT_Init(&V2,5);
  for(int i=0;i<5;i++)
  {
    xVec_INT_Push(&V1,i);
    xVec_INT_Push(&V2,5-i);
  }
  Show_INT_Result("PUSH",&V1,&V2);

  xVec_INT_Pop(&V1);
  xVec_INT_Pop(&V2);
  Show_INT_Result("POP",&V1,&V2);

  printf("[AT]\n");
  printf("V1[2] = %d\n"  ,xVec_INT_At(&V1,2));
  printf("V2[2] = %d\n\n",xVec_INT_At(&V2,2));

  xVec_INT_Insert(&V1,3,10);
  xVec_INT_Insert(&V2,3,10);
  Show_INT_Result("INSERT",&V1,&V2);

  xVec_INT_Remove(&V1,4);
  xVec_INT_Remove(&V2,4);
  Show_INT_Result("REMOVE",&V1,&V2);

  xVec_INT_Update(&V1,2,10);
  xVec_INT_Update(&V2,2,10);
  Show_INT_Result("UPDATE",&V1,&V2);

  xVec_INT_Reverse(&V1);    Show_INT_Result("REVERSE",&V1,&V2);
  xVec_INT_Merge(&V1,&V2);  Show_INT_Result("MERGE",&V1,&V2);

  xVec_INT_Clear(&V2);
  xVec_INT_Push(&V1,100);
  Show_INT_Result("CLEAR",&V1,&V2);

  xVec_INT_Destroy(&V1);
  xVec_INT_Destroy(&V2);
}
```

## License Terms
This project is licensed under the `MIT License`.