#include "f90tw_test.h"

/* expanded in fortran, places the "header" of the 
// module contains the tests. essentially, defines
// the "test_example" module and declare the use of
// the "example" module (the module to be tested).
// expanded in c/c++ makes nothing. */
TESTMODULE(test_example, example)

/* expanded in fortran to contains statement. it is
// separated from TESTMODULE macro to allow for the
// declaration of module resources.
// */
TESTCONTAINS

/* place a test and it fortran implementation. 
//
// expanded in fortran, results in module procedure 
// (subroutine) add_test_method with the appropriate
// binding info and the implementation given from the
// 5th argument and forth. ";" should be used to declare
// the end of asource line. you can find more details on
// this at f90tw project page @github. 
//
// expanded in c/c++, results the appropriate definition
// of the fortran subroutine making it assessible from 
// c++ and the implemenation of the "test_example1" 
// test in the "test_gtest" testsuite (based on the the
// TEST macro) which essentially calls the "add_test_method"
// fortran routine. */
TESTCODE(TEST, test_gtest, test_example1, add_test_method,
    use ISO_C_BINDING, only : C_CHAR, C_NULL_CHAR ;
    real(4), parameter :: delta = 0.000001 ;
    character(KIND=C_CHAR,LEN=*), parameter :: message = "delta=0.000001 !" F90CONCAT C_NULL_CHAR ;
    call F90_ASSERT_EQ( method(2,1),3) ;
    call F90_ASSERT_EQ( method(2,2), 3, F90SPOTMSG("method(2,1) == 3") ) ;
    call F90_ASSERT_FLOAT_EQ( 1.0, 1.0+delta, message ) ;
)

/* the end statement of the "test_example" module.
// expanded in c/c++ makes nothing. */
ENDTESTMODULE(test_example)
