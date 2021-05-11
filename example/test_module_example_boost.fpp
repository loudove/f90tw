#include "f90tw_test.h"

TESTMODULE(test_example, example)

TESTCODE(BOOST_AUTO_TEST_CASE, DUMMY, test_example1, add_test_method,
    call F90_BOOST_WARN_EQUAL( method(2,2),3);
    call F90_BOOST_CHECK_EQUAL( method(2,-1),1);
    call F90_BOOST_REQUIRE_EQUAL( method(1,1),2);
)

TESTCODE(BOOST_AUTO_TEST_CASE, DUMMY, test_example2, add_test_methodf1,
    call F90_BOOST_REQUIRE_EQUAL( method(1.0,1.0+1.e-12),2.0);
    call F90_BOOST_REQUIRE_EQUAL( method(1.d0,1.d0+1.d-12),2.d0);
)

TESTCODE(BOOST_AUTO_TEST_CASE, DUMMY, test_example3, add_test_methodf2,
    use ISO_C_BINDING, only : C_BOOL, C_CHAR, C_NULL_CHAR ;
    logical(KIND=C_BOOL) :: check ;
    check = (method(1.d0,1.d0+1.d-07) .eq. 2.d0) ;
    call F90_BOOST_REQUIRE_MESSAGE( check, F90SPOTMSG("method(1.d0,1.d0+1.d-07) .eq. 2.d0") ) ; 
    // call F90_BOOST_REQUIRE_MESSAGE( check, "method(1.d0,1.d0+1.d-07) .eq. 2.d0" F90CONCAT C_NULL_CHAR ) ; 
)

ENDTESTMODULE(test_example)
