#if defined(CURRENTTESTFILE)

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SIMPLEST_TEST_SUITE

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include "f90tw_defs.h"

/* get the test defined in the corresponding file
// and create the definitions of the fortran methods
// to be used */
#define TESTMODULE( ... )
#define TESTCONTAINS
#define ENDTESTMODULE( ... )
#define TESTCODE HCODE
#include CURRENTTESTFILE

/* get the test defined in the corresponding file
// and create implementation of the c++ methods for
// calling the paired fortran code */
#undef TESTCODE
#define TESTCODE CCODE
#include CURRENTTESTFILE

#endif