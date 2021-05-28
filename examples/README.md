# f90tw example

Let's assume that we want to test the functionality of the example module in [`example.f90`](example.f90) i.e. to make sure the module procedure `method` (implementing the addition of the given arguments), works in the expected and presumably in a correct way.

## Preprocessor macros implementation

A demonstration of how you can use f90tw preprocessor macros is presented, following the Boost.Test framework example.

### Fortran test code

The fortran testing code is located in [`test_example_boost.fpp`](test_example_boost.fpp). The structure of the file is simple. First we include [`f90tw_test.h`](../f90tw/f90tw_test.h) which provides the necessary preprocessor's marco definitions for implementing tests in fortran.

```fortran
#include "f90tw_test.h"
```

Since we want to implement more than one test, it is convenient to use a module since, among other benefits, we can easily share resources among tests. To do so, we use the [`TESTMODULE`](../README.md#Use) macro:

```fortran
TESTMODULE(test_example, example)
```

which expands to:

```fortran
module test_example      ! module name (first argument of the macro)
    use assertions_boost ! use module to be tested (second argument of the macro)
    use example
    implicit none
    contains
```

The `TESTCONTAINS` macro follows, which expands to the `contain` statement. It was separated from the `TESTMODULE` to leave room for the declaration of module resources common to all the tests implemented in the module.

Now we implement the test(s) in mind with the help of [`TESTCODE`](../README.md#Preprocessor) macro:

```fortran
TESTCODE(BOOST_AUTO_TEST_CASE, DUMMY, test_example1, add_test_method,
    call F90_BOOST_WARN_EQUAL( method( 2,2), 3) ;
    call F90_BOOST_CHECK_EQUAL( method( 2.0,-1.0), 1.0) ;
    call F90_BOOST_REQUIRE_EQUAL( method( 1.d0,1.d0), 2.d0) ;
)
```

which expands to:

```fortran
! the name of the function (4th argument of the macro)
subroutine add_test_method() BIND(C,name="add_test_method")
   ! test implementation (whatever comes after the 4th argument of the macro)
   call F90_BOOST_WARN_EQUAL( method( 2,2), 3)
   call F90_BOOST_CHECK_EQUAL( method( 2.0,-1.0), 1.0)
   call F90_BOOST_REQUIRE_EQUAL( method( 1.d0,1.d0), 2.d0) 
end subroutine add_test_method
```

<u>You have to use</u> `";"` for terminating each source line since the preprocessor will output the macro's argument in a single line. Note that currently (05/2021) if `";"` is used in a fortran string will cause compilation problems. Strings concatenation operator `"//"` also results in problems since the preprocessor considers it as c/c++ single line comment and neglects all the next statements. This is why you should use the `F90CONCAT` macro instead. For example, the line:

```fortran
call F90_BOOST_REQUIRE_MESSAGE( check, "some message" F90CONCAT C_NULL_CHAR ) ;
```

strictly expands to:

```fortran
call F90_BOOST_REQUIRE_MESSAGE( check, "some message" /&;&/ C_NULL_CHAR ) ;
```

and in turn, results in a bit strange, but still valid, code block:

```fortran
call F90_BOOST_REQUIRE_MESSAGE( check, "some message" /&
&/ C_NULL_CHAR )
```

The rest of the tests (i.e. `test_example2` and `test_example3`) are implemented similarly. In the last one, you can see the use of [`F90SPOT` and `F90SPOTMSG` macros](../README.md#Preprocessor).

In the test(s) implementation, you should use the [boost assertions wrappers](../README.md#Boost.test) as you see fit in your case.

The fortran implementation using the gtest framework is similar. The only differences are that a) in the TESTCODE macro you should provide also the name of the test suite, b) the [gtest assertions wrappers](../README.md#Gtest) should be used, and (**MORE IMPORTANTLY**) c) the preprocessor symbol `USEGTEST` should be defined in the compilation stage.

### C/C++ test code

The c/c++ code located in [`test_example_boost.cpp`](test_example_boost.cpp) is even simpler. First we set the fortan file as the `CURRENTTESTFILE`:

```c
#define CURRENTTESTFILE "test_example_boost.fpp"
```

end then we include the f90tw header [`f90tw_boost.h`](../f90tw/f90tw_boost.h):

```c
#include "f90tw_boost.h"
```

And that's it! Essentially, the preprocessor will parse the provided fortran file twice (see [`f90tw_boost.h`](../f90tw/f90tw_boost.h)). In the first pass, creates the definitions for the fortran subroutines declared in [`test_example_boost.cpp`](test_example_boost.cpp) and in the second, creates the boost tests that will call their fortran counterparts.

Again, the implementation using the gtest framework is similar except that a) different f90tw header is used (`f90tw_gtest.h`](../f90tw/f90tw_gtest.h), b)) and (**MORE IMPORTANTLY**) b) the preprocessor symbol `USEGTEST` should be defined in the compilation stage.

## Directives implementation

The fortran testing code is located in [`test_example_gtest.f90`](test_example_example.f90). It is a standard fortran source file where the !$f90wt directive is utilized to indicate the test methods to be included in a specific test. For example :

```fortran
   !$f90tw TESTCODE(TEST, test_gtest, test_example1, add_test_method,
   subroutine add_test_method() BIND(C, name="add_test_method")
   ...
   end subroutine add_test_method
   !$f90tw )
```

the `add_test_method` will be wrapped in the `test_example1` test of the `test_gtest` test suite.

Essensially, the directive lines will be processed and included in the c/c++ pair file in order to create the tests using exactly the same logic (and preprocessor macros) described in the preprocessor based implementation.

### C/C++ test code

The c/c++ code located in [`test_example_gtest.cpp`](test_example_gtest.cpp) is almost identical to the one described in the preprocessor based implementation. The only difference is that the `CURRENTTESTFILE` is set to `test_example_gtest.f90.h`. The name of the header is the name of the fortran file with the header extension `.h` appended, and it is created automaticaly by processing the fortran counterpart (see `F90TWTEST` cmake function implemented in [f90wt/CMakeLists.txt](../f90wt/CMakeLists.txt)).

Then we include the f90tw header [`f90tw_gtest.h`](../f90tw/f90tw_gtest.h):

```c
#include "f90tw_boost.h"
```

## Buid the examples

You can see the build details in the [`CMakeLists.txt`](CMakeLists.txt). After configuring with -DEXAMPLES=ON and a successful build, the executables `test_example_boost<.exe>` and `test_example_gtest<.exe>`, are located in `build/example/<conf>/` folder together with the preprocessed fortran test files `test_example_boost.f90` in the case of the boost framework example.
