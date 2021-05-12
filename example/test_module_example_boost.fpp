#include "f90tw_test.h"

/* expanded in fortran, places the "header" of the 
// module contains the tests. essentially, defines
// the "test_example" module and declare the use of
// the "example" module (the module to be tested).
// expanded in c/c++ makes nothing. */
TESTMODULE(test_example, example)

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
// boost test (based on the the BOOST_AUTO_TEST_CASE
// macro), which essentially calls the "add_test_method"
// fortran routine. */
TESTCODE(BOOST_AUTO_TEST_CASE, DUMMY, test_example1, add_test_method,
    call F90_BOOST_WARN_EQUAL( method( 2,2), 3) ;
    call F90_BOOST_CHECK_EQUAL( method( 2.0,-1.0), 1.0) ;
    call F90_BOOST_REQUIRE_EQUAL( method( 1.d0,1.d0), 2.d0) ;
)

TESTCODE(BOOST_AUTO_TEST_CASE, DUMMY, test_example2, add_test_methodf1,
    call F90_BOOST_REQUIRE_EQUAL( method( 1.0, 1.e-12), 1.0) ;
    call F90_BOOST_CHECK_EQUAL( method( 1.d0, 1.d-12), 1.d0) ;
    call F90_BOOST_REQUIRE_CLOSE( method( 1.d0, 1.d-12), 1.d0, 1.d-09) ;
)

TESTCODE(BOOST_AUTO_TEST_CASE, DUMMY, test_example3, add_test_methodf2,
    use ISO_C_BINDING, only : C_BOOL, C_CHAR, C_NULL_CHAR ;
    logical(KIND=C_BOOL) :: check1, check2 ;
    check1 = ( method( 1.0, 1.e-12) .eq. 1.d0) ;
    call F90_BOOST_REQUIRE_MESSAGE( check1, F90SPOTMSG("1.0 .eq. 1.0+1.e-12") ) ;
    check2 = ( method(0.d0,1.d-12) .eq. 0.d0 ) ;
    call F90_BOOST_REQUIRE_MESSAGE( check2, "0.d0 .ne. 1.d-12" F90CONCAT C_NULL_CHAR ) ;
)

/* the end statement of the "test_example" module.
// expanded in c/c++ makes nothing. */
ENDTESTMODULE(test_example)
