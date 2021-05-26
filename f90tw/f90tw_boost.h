#if defined(CURRENTTESTFILE)

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SIMPLEST_TEST_SUITE

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/results_collector.hpp>

extern "C" {
bool current_test_passing()
{
  using namespace boost::unit_test;
  test_case::id_t id = framework::current_test_case().p_id;
  test_results rez = results_collector.results(id);
  return rez.passed();
}
}

#include "f90tw_defs_boost.h"

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
