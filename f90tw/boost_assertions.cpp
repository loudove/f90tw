/* just expanding the wrappers without boost and obtain a more
// comprehensive source file. */
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "f90tw_defs_boost.h"

#define HEADERLEVEL "boost_level.h"
#define HEADERLEVELWHAT "implement_boost_wrappers.h"
#define VERSIONSUB C_F90TW_VER
#define BOOSTFUNCTION0 C_BOOST_LEVEL
#define BOOSTFUNCTION1 C_BOOST_LEVEL_MESSAGE
#define BOOSTFUNCTION2 C_BOOST_LEVEL_CHECK1T2A
#define BOOSTFUNCTION3 C_BOOST_LEVEL_CHECK1T3A
#define BOOSTSOMETHING C_BOOST_SOMETHING
#define BOOSTVOID C_BOOST_VOID

#define DOINTERFACE
#include "boost_what.h"
#undef DOINTERFACE

#undef BOOSTVOID
#undef BOOSTSOMETHING
#undef BOOSTFUNCTION3
#undef BOOSTFUNCTION2
#undef BOOSTFUNCTION1
#undef BOOSTFUNCTION0
#undef VERSIONSUB
#undef HEADERLEVELWHAT
#undef HEADERLEVEL
