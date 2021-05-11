#include "f90tw_defs.h"

module assertions_boost

      use ISO_C_BINDING

      implicit none

#define HEADERLEVEL "boost_level.h"
#define HEADERLEVELWHAT "interface_boost_wrappers.h"
#define BOOSTFUNCTION1 F90_BOOST_LEVEL_MESSAGE
#define BOOSTFUNCTION2 F90_BOOST_LEVEL_CHECK1T2A
#define BOOSTFUNCTION3 F90_BOOST_LEVEL_CHECK1T3A
#define BOOSTSOMETHING F90_BOOST_SOMETHING
#define BOOSTVOID F90_BOOST_VOID
#include "boost_what.h"
#undef BOOSTVOID
#undef BOOSTSOMETHING
#undef BOOSTFUNCTION3
#undef BOOSTFUNCTION2
#undef BOOSTFUNCTION1
#undef HEADERLEVELWHAT
#undef HEADERLEVEL

end module assertions_boost
