#include "f90tw_test.h"

TESTMODULE(test_example, example)

TESTCODE(TEST, test_gtest, test_example1, add_test_method,
    use ISO_C_BINDING, only : C_CHAR, C_NULL_CHAR ;
    character(KIND=C_CHAR,LEN=*), parameter :: message = "delta=0.000001 !" F90CONCAT C_NULL_CHAR ;
    call F90_ASSERT_EQ( method(2,1),3) ;
    call F90_ASSERT_EQ( method(2,2), 3, F90SPOTMSG("method(2,1) == 3") ) ;
    call F90_ASSERT_FLOAT_EQ( 1.0, 1.0+0.000001, message ) ;
)

ENDTESTMODULE(test_example)
