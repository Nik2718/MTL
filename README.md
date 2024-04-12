# The Smith normal form of an integer matrix with C++

This project provides tools to calculate the [Smith normal form](https://en.wikipedia.org/wiki/Smith_normal_form) of an integer matrix. The project was tested on macOS Sonoma 14.4.1 with clang 15.0.0, boost 1.84.0.

## Get started

To build the project [boost](https://www.boost.org) libraries should be installed. They are required to use higher precision [integers](https://www.boost.org/doc/libs/1_84_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/cpp_int.html) and a unit test [framework](https://www.boost.org/doc/libs/1_34_1/libs/test/doc/index.html). 

Then [Makefile](Makefile) must be adapted. The beginning of the Makefile should be probably changed. The first three variables contain the name of a C++ compiler,

```
CXX = clang++
```

an absolute path to the boost headers,

```
BOOST_PATH = -I/opt/homebrew/Cellar/boost/1.84.0_1/include
```

and an absolute path to `libboost_unit_test_framework.a`,

```
TEST_LIB = \
/opt/homebrew/Cellar/boost/1.84.0_1/lib/libboost_unit_test_framework.a
```


At least this variables should be changed if necessary.

The command `make` creates a static library `libint_matrix.a` in the directory `lib`, executable files `test` for testing and `example` for a short example

```
make
```

```
./test
Running 32 test cases...

*** No errors detected

```


```
./example

**********************************************
This is is an example of work with the library
**********************************************

Let's consider an integer matrix A equal to 
|| -2   4  -2 -16  -8  -6||
|| -2  10   4  14  -8   0||
||  2  -4  44  16  92  90||
||  0   6   6 114  -1  90||

The invariant factors of the matrix A are 1 2 6 42 

The left transformation matrix L is 
||  0   0   0  -1||
|| -3   2   0  -2||
|| -8   5   0  -6||
|| 29 -49   1  42||

The right transformation matrix R is 
||  -5  -27   31   -3  150  169||
||   0    1    0   -1  163  169||
||   0    0   -1    1 -168 -170||
||   0    0    0    0    1    0||
||   1    6   -6    0   84   84||
||   0    0    0    0    0    1||

The product L * A * R equals to the diagonal matrix of the invariant factors
|| 1  0  0  0  0  0||
|| 0  2  0  0  0  0||
|| 0  0  6  0  0  0||
|| 0  0  0 42  0  0||

```

The file [example.cpp](src/example.cpp) can be freely modified and recompiled by calling `make` again.

After `libint_matrix.a` is created it can be used as a usual static library together with [init_matrix.h](include/int_matrix.h) and boost.

## The main tools

### Matrices

All declarations of functions and classes are collected in [init_matrix.h](include/int_matrix.h). To create an integer matrix the constructor of the corresponding class should be called. An initializer list and some other options are available. `IntegerMatrix` is realized without use of `std::vector`.

```C++
IntegerMatrix A {{-2,  4, -2, -16,  -8, -6},
                 {-2,  10, 4,  14,  -8,  0},
                 { 2, -4,  44, 16,   92, 90},
                 { 0,  6,  6,  114, -1,  90}};

IntegerMatrix B(10, 12); 
// B is the matrix with 10 rows and 12 columns
//Each entry equals zero

IntegerMatrix C(3, 4, -2);
// C is the matrix with 3 rows and 4 columns
//Each entry equals -2 
```
The operator `<<` is overloaded and provides a nice output of an integer matrix. All entries are aligned to the longest one.

```C++
std::cout << A;
```

```
|| -2   4  -2 -16  -8  -6||
|| -2  10   4  14  -8   0||
||  2  -4  44  16  92  90||
||  0   6   6 114  -1  90||
```


 Each entry of a matrix has a type `IntegerMatrix::integer`. This is a synonym for `boost::multiprecision::cpp_int`. Probably, other [boost integers](https://www.boost.org/doc/libs/1_84_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/cpp_int.html) can be used with some bad or good consequence for speed of the program. Also some tests can fail due to too long integers. To modify the type  `IntegerMatrix::integer` it suffices to change the corresponding `typedef` in [init_matrix.h](include/int_matrix.h) and rebuild the project.


The number of rows and columns has type `IntegerMatrix::size_type`, which is a synonym for `unsigned int`.


```C++
IntegerMatrix::size_type m = A.getNumberOfRows(); // m == 4
IntegerMatrix::size_type n = A.getNumberOfColumns(); // n == 6
```

The maximum number of rows or columns is returned by the static method `getMaxSize()`.

```C++
IntegerMatrix::size_type max = A.getMaxSize(); // max == 10000

```
This method not only returns but also stores the maxim size of a matrix. To change this parameter for the class, it is sufficient to change the returning value for `getMaxSize()` in [init_matrix.h](include/int_matrix.h).

The operator `()` provides access to elements of a matrix. **Indices of rows and columns begin with the zero.** There is no check for out of range errors  

```C++
IntegerMatrix::integer a = A(0,1); // a == 4
A(1,3) = -5; //entry 14 is replaced by -5
A(1,6) = 1; //undefined behavior
```

### The Smith form

To find the Smith normal form of a matrix, a special class `SmithForm` should be used.

```C++
SmithForm S(A); //Smith Form is calculated
```

The constructor of `SmithForm` copies the matrix `A` and then transforms the copy to the diagonal form. After that, the diagonal elements are saved but the matrix itself is deleted. Thus, the object `S` of the class `SmithForm` does not store the matrix `A`.

The method `getMinSize()` returns the minimum number of rows and columns of the matrix `A`.

```C++
bool b = (S.getMinSize() == std::min(m, n));
//b == true
```
Then the number of invariant factors equals `getMinSize()`. The method `getInvariantFactor(i)` returns the i-th invariant factor.

```C++
for (IntegerMatrix::size_type i = 0; i < S.getMinSize(); ++i) {
    std::cout << S.getInvariantFactor(i) << ' ';
}
//printing all invariant factor
```
The object `S` also stores left and right transformation matrices:

```C++
std::cout << S.getLeftMatrix() << '\n';
std::cout << S.getRightMatrix() << '\n';
```
The class `IntegerMatrix` overloads multiplication for matrices and we can calculate:

```C++
std::cout << S.getLeftMatrix() * A * S.getRightMatrix() << "\n";
//The output is the diagonal matrix of invariant factors
```






