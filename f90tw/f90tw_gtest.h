#if defined(CURRENTTESTFILE)

#include "gtest/gtest.h"

#include "f90tw_defs.h"

/* get the test defined in the corresponding file
// and create the definitions of the fortran methods
// to be used */
#define TESTMODULE( ... )
#define ENDTESTMODULE( ... )
#define TESTCODE HCODE
#include CURRENTTESTFILE

/* get the test defined in the corresponding file
// and create implementation of the c++ methods for
// calling the paired fortran code */
#undef TESTCODE
#define TESTCODE CCODE
#include CURRENTTESTFILE

int main(int argc, char** argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}

#endif