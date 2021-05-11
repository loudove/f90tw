/* just expanding the wrappers without boost and obtain a more
// comprehensive source file. */
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "f90tw_defs.h"

#define HEADERLEVEL "boost_level.h"
#define HEADERLEVELWHAT "implement_boost_wrappers.h"
#define BOOSTFUNCTION1 C_BOOST_LEVEL_MESSAGE
#define BOOSTFUNCTION2 C_BOOST_LEVEL_CHECK1T2A
#define BOOSTFUNCTION3 C_BOOST_LEVEL_CHECK1T3A
#define BOOSTSOMETHING C_BOOST_SOMETHING
#define BOOSTVOID C_BOOST_VOID
#include "boost_what.h"
#undef BOOSTVOID
#undef BOOSTSOMETHING
#undef BOOSTFUNCTION3 
#undef BOOSTFUNCTION2 
#undef BOOSTFUNCTION1
#undef HEADERLEVELWHAT
#undef HEADERLEVEL


