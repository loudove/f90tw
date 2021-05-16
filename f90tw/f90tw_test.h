#ifndef TESTMODULE

#include "f90tw_defs.h"

#define F90CONCAT /&;&/
#define F90LNCONT &;&
#define F90SPOT __FILE__ F90CONCAT ":" F90CONCAT TOSTR(__LINE__)
#define F90SPOTMSG(MSG) F90SPOT F90CONCAT ": " F90CONCAT MSG F90CONCAT C_NULL_CHAR

#define TESTF90
#define TESTMODULE F90TESTMODULE
#define TESTCONTAINS F90TESTCONTAINS
#define ENDTESTMODULE F90ENDTESTMODULE
#define TESTCODE FCODE

#endif
