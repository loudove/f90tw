f90tw
=====
f90tw project provides fortran wrappers for a limitted subset of the [boost](https://www.boost.org/) and [google](https://github.com/google/googletest) test frameworks functionality. At the same time, offers a rather simple mechanism for setting up and managing test suites in fortran projects. All the way down, f90tw is a preprocessor-based approach.

Build
-----
You will need to obtain the repository from github and follow the usual cmake build steps. It is assumed that c/c++ and fortran compilers are available and you have installed boost and gtest packages. In short, [clone](https://github.com/git-guides/git-clone) the project from github, enter the project's directory and issue the usual [cmake](https://cmake.org/documentation/) build commands.

There is not specific installation directory. After a successful build, the module files and the libraries will be located under the `<build>/f90tw` directory (or `<build>/f90tw/<conf>` on windows). The actual source files of the modules will be located in the `<build>/f90tw` directory with the names `assertions_boost.f90` and `assertion_gtest.f90` for the boost and gtest frameworks respectively.

Use
---
A fortran module with the interface of the fortran wrappers and the corresponding libraries with the actual functionality are provided for each test framework:
- Boost: **assertions_boost** module (implementable in [`assertions_boost.fpp`](f90tw/assertions_boost.fpp)), `libf90tw_boost.a` library (implemented in [`boost_assertions.cpp`](f90tw/boost_assertions.cpp)). After a successful build a "readable" code for the module can be found in `<build>/f90tw/assertions_boost.f90`.
- Gtest: **assertions_gtest** module (implemented in [`assertions_gtest.fpp`](f90tw/assertions_gtest.fpp)), `libf90tw_gtest.a` library (implemented in `gtest_assertions.cpp`). Also in this case, after a successful build a "readable" code for the module will be located in `<build>/f90tw/ftest_boost.f90`.

If you include f90tw in your cmake project, the variables `f90tw_INCLUDE_DIR` (pointing to the heads directory) and `f90tw_MODULE_DIR` (pointing to the modules and libraries directory) are defined to help you access f90tw functionality.

To facilitate the setup of simple tests, additional header files are provided with their main usage demonstrated in the accompanying example found in the [`example`](example) directory. You can find hinds of f90tw use with cmake in [`example/CMakeLists.txt`](example/CMakeLists.txt).

Assuming that you want to test the functionality of a fortran module named *example*, implemented in [`example.f90`](example/example.f90). In this case, the test can be implemented with a pair of two files:
- Boost: a fortran module, ([`test_module_example_boost.fpp`](example/test_module_example_boost.fpp)), with the subroutines implementing the actual tests and its c/c++ pair, [`test_example_boost.cpp`](example/test_example_boost.cpp), implementing the boost tests wrapping their fortran counterparts. 
- Gtest: as you can guess, the pair of files is [`test_module_example_gtest.fpp`](example/test_module_example_gtest.fpp) for fortran, and [`test_example_gtest.cpp`](example/test_example_gtest.cpp) for c/c++. **PLEASE NOTE** that these files should be compiled/preprocessed by setting the USE GTEST preprocessor definition in order to set in the appropriate macros and avoid problems.

The structure of these files is simple and quite similar. In the fortran files, we first include the [`"f90tw_test.h"`](f90tw/f90tw_test.h) header and then the functionality is implemented by using the f90tw preprocessor macros:
- **TESTMODULE**: (*optional*) module initial statements (declaration, use of the module to be tested and set `imlicit none`). The arguments are:
( MODULENAME, MODULETOTEST)
    - MODULENAME: the name of the module
    - MODULETOTEST: the name of the module to test
- **TESTCODE**: prepares the specific test. The arguments are:
( *TESTTYPE*, *TESTSUITENAME*, *TESTNAME*, *SUBNAME*, **...** )
    - *TESTTYPE*: the framework macro to be used for test declaration
    - *TESTSUITENAME*: the name of the test suite
    - *TESTNAME*: the name of the test
    - *SUBNAME*: the name of the fortran subroutine to be implemented
    -  **...** : the rest of the arguments which are essentially, the fortran source code implementing the test. 
    **PLEASE NOTE** that each code line should be terminated with `;` while the string concatenation operator (`//`) should be replaced with the `F90CONCAT` macro and the line continuation operator (`&`) with the `F90LNCONT` macro. Moreover, `F90SPOT` macro expands to the `filename:line` string, while `F90SPOTMSG(MSG)` macro appends the MSG string to it. <u>You can simplify the implementation here by just calling a fortran method implemented elsewhere.</u> This approach is maybe preferable since you will avoid the drawbacks of preprocessing relevant to code's clarity and debugging.
- **ENDTESTMODULE** : (*optional*) module end statement. The only argument here is the name of the module (MODULENAME) used also with the **TESTMODULE** macro.

Using this approach, the c++ implementation becomes rather easy since you have to set the `CURRENTTESTFILE` definition located at the very begining of the file to point the fortran pair and just include the header corresponding to the framework in use (`f90tw_gtest.h` for *gtest* or `f90tw_boost.h` for *boost*).

Boost.test assertions tests
---------------------------

The following subset of boost.test framework is supported:

Fortran | C/C++ | level | argumens type
------- | ----- | ----- | -------------
F90_BOOST_&lt;level&gt;_BITWISE_EQUAL | BOOST_&lt;level&gt;_BITWISE_EQUAL | (WARN&#124;CHECK&#124;REQUIRE) | integer(KIND=C_INT)
F90_BOOST_&lt;level&gt;_EQUAL | BOOST_&lt;level&gt;_EQUAL | (WARN&#124;CHECK&#124;REQUIRE) | logical(KIND=C_BOOL), integer(KIND=C_INT), real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_BOOST_&lt;level&gt;_LT | BOOST_&lt;level&gt;_CLOSE_LT | (WARN&#124;CHECK&#124;REQUIRE) | logical(KIND=C_BOOL), integer(KIND=C_INT), real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_BOOST_&lt;level&gt;_CLOSE | BOOST_&lt;level&gt;_CLOSE | (WARN&#124;CHECK&#124;REQUIRE) | real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_BOOST_&lt;level&gt;_CLOSE_FRACTION | BOOST_&lt;level&gt;_CLOSE_FRACTION | (WARN&#124;CHECK&#124;REQUIRE) | real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_BOOST_&lt;level&gt;_SMALL | BOOST_&lt;level&gt;_CLOSE_SMALL | (WARN&#124;CHECK&#124;REQUIRE) | real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_BOOST_&lt;level&gt;_GE | BOOST_&lt;level&gt;_CLOSE_GE | (WARN&#124;CHECK&#124;REQUIRE) | integer(KIND=C_INT), real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_BOOST_&lt;level&gt;_GT | BOOST_&lt;level&gt;_CLOSE_GT | (WARN&#124;CHECK&#124;REQUIRE) | integer(KIND=C_INT), real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_BOOST_&lt;level&gt;_LE | BOOST_&lt;level&gt;_CLOSE_LE | (WARN&#124;CHECK&#124;REQUIRE) | integer(KIND=C_INT), real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_BOOST_&lt;level&gt;_LT | BOOST_&lt;level&gt;_CLOSE_LT | (WARN&#124;CHECK&#124;REQUIRE) | integer(KIND=C_INT), real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_BOOST_TEST_MESSAGE | BOOST_TEST_MESSAGE | - | character(KIND=C_CHAR,LEN=*)
F90_BOOST_TEST_ERROR | BOOST_TEST_ERROR | - | character(KIND=C_CHAR,LEN=*)
F90_BOOST_TEST_FAIL | BOOST_TEST_FAIL | - | character(KIND=C_CHAR,LEN=*)
F90_BOOST_TEST_CHECKPOINT | BOOST_TEST_CHECKPOINT | - | character(KIND=C_CHAR,LEN=*)
F90_BOOST_TEST_INFO | BOOST_TEST_INFO | - | character(KIND=C_CHAR,LEN=*)
F90_BOOST_TEST_INFO_SCOPE | BOOST_TEST_INFO_SCOPE | - | character(KIND=C_CHAR,LEN=*)
F90_BOOST_TEST_CONTEXT | BOOST_TEST_CONTEXT | - | character(KIND=C_CHAR,LEN=*)
F90_BOOST_TEST_PASSPOINT | BOOST_TEST_PASSPOINT | - | character(KIND=C_CHAR,LEN=*)

For more detailes please check the [Boost.Test](https://www.boost.org/doc/) documentation.

Gtest assertions tests
----------------------

The following subset of gtest framework is supported:

Fortran | C/C++ | level | operator | argumens type
------- | ----- | ----- | -------- | -------------
F90_&lt;level&gt;_&lt;operator&gt; | &lt;level&gt;__&lt;operator&gt | (ASSERT&#124;EXPECT) | (EQ&#124;NE) | logical(KIND=C_BOOL), integer(KIND=C_INT), real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_&lt;level&gt;_&lt;operator&gt; | &lt;level&gt;__&lt;operator&gt | (ASSERT&#124;EXPECT) | (GT&#124;GE&#124;LT&#124;LE) | integer(KIND=C_INT), real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_&lt;level&gt;_FLOAT_EQ | &lt;level&gt;_FLOAT_EQ | (ASSERT&#124;EXPECT) | - | real(KIND=C_FLOAT)
F90_&lt;level&gt;_DOUBLE_EQ | &lt;level&gt;_DOUBLE_EQ | (ASSERT&#124;EXPECT) | - | real(KIND=C_DOUBLE)
F90_&lt;level&gt;_NEAR | &lt;level&gt;_NEAR | (ASSERT&#124;EXPECT) | - | real(KIND=C_FLOAT), real(KIND=C_DOUBLE)
F90_&lt;level&gt;_&lt;operator&gt; | &lt;level&gt;__&lt;operator&gt | (ASSERT&#124;EXPECT) | (TRUE&#124;FALSE) | logical(KIND=C_BOOL)
F90_&lt;level&gt;_&lt;operator&gt; | &lt;level&gt;__&lt;operator&gt | (ASSERT&#124;EXPECT) | (STREQ&#124;STRNE&#124;STRCASEEQ&#124;STRCASENE) | character(KIND=C_CHAR,LEN=*)

I the gtest case all the assertion methods can be used with the assertion message as the last argumetn (of type character(KIND=C_CHAR,LEN=*) ) in order to overide the default assertion message.

For more detailes please check the [gtest](https://github.com/google/googletest) documentation.
