#ifdef F90TESTWRAPPERS

#ifdef DOINTERFACE
/* version */
VERSIONSUB
#endif

/* For each supported boost assertion, a wrapper is created for
// the various levels (see boost_level.h) and arguments type (see
// <implement|interface>_boost_wrapers.h) supported. The latter is
// controlled with HAVECINT, HAVECBOOL, HAVECFLOAT and HAVECDOUBLE
// definitions corresponding to integer(kind=C_INT), logical(kind=C_BOOL),
// real(kind=C_FLOAT) and real(kind=C_DOUBLE) types. The BOOSTFUNCTION
// marco controls the specific implementation of the wrapper. The name
// of the arguments is controlled by NAME1 and NAME2 macros. */

/* set variable names for the arguments */
#define NAME1 left
#define NAME2 right
/* set the definition of the boost function of the wrapper */
#define BOOSTFUNCTION BOOSTFUNCTION2
/* set the flags for the arguments type supported for the wrapper*/
#define HAVECINT
#define HAVECBOOL
#undef HAVECAST
#define HAVECFLOAT
#define HAVECDOUBLE
#undef HAVEDIM

/* set the test arguments. initialize the two arguments, test pass case. */
#undef CINTARGS
#undef CFLOATARGS
#undef CDOUBLEARGS
#undef CBOOLARGS
#undef LOGICALARGS

/* each block creates the implementation of the wrapper.
// The name of the macro is set with WHAT definition, the
// flags for supported arguments type, the appropriate
// implementation macro. */

#undef HAVECBOOL
#undef HAVECFLOAT
#undef HAVECDOUBLE
#define HAVEDIM
/* BOOST_(LEVEL)_BITWISE_EQUAL and similars section */
/* test defs */
#define DOTESTS
#define CINTARGS 1024, 1024
#define CINT1DARGS [ 1024, 2048 ], [ 1024, 2048 ]
#define CINT2DARGS [ CINT1DARGS ], [ CINT1DARGS ]
/* end test defs */
#define WHAT BITWISE_EQUAL
#include HEADERLEVEL
#undef WHAT
#undef HAVEDIM

#define HAVECBOOL
#define HAVECFLOAT
#define HAVECDOUBLE
#define HAVECAST
/* BOOST_(LEVEL)_EQUAL and similars section */
/* test defs */
#define CFLOATARGS 1.0, 1.0
#define CDOUBLEARGS 1.D0, 1.D0
#define CBOOLARGS logical(.true.,KIND=C_BOOL), logical(.true.,KIND=C_BOOL)
#define LOGICALARGS .true., .true.
/* end test defs */
#define WHAT EQUAL
#include HEADERLEVEL
#undef WHAT
#undef HAVECAST

#undef HAVECINT
#undef HAVECBOOL
#undef NAME2
#define NAME2 tolerance
/* BOOST_(LEVEL)_SMALL and similars section */
/* test defs */
#undef CFLOATARGS
#undef CDOUBLEARGS
#undef CFLOAT1DARGS
#undef CDOUBLE1DARGS
#undef CFLOAT2DARGS
#undef CDOUBLE2DARGS
#define CFLOATARGS 0.E-7, 0.E-6
#define CDOUBLEARGS 0.D-14, 0.D-12
#define CFLOAT1DARGS [ 0.E-7, 5.E-7 ], 0.E-6
#define CDOUBLE1DARGS [ 0.D-14, 5.D-14 ], 0.D-12
#define CFLOAT2DARGS [ [ 0.E-7, 5.E-7 ], [ 1.E-7, 9.E-7 ] ], 0.E-6
#define CDOUBLE2DARGS [ [ 1.D-14, 5.D-14 ], [ 3.D-14, 9.D-14 ] ], 0.D-12
/* end test defs */
#define WHAT SMALL
#include HEADERLEVEL
#undef WHAT
#undef NAME2
#define NAME2 right

#undef BOOSTFUNCTION
#define BOOSTFUNCTION BOOSTFUNCTION3
#define HAVEDIM
/* BOOST_(LEVEL)_CLOSE and similars section */
/* test defs */
#undef CFLOATARGS
#undef CDOUBLEARGS
#undef CFLOAT1DARGS
#undef CDOUBLE1DARGS
#undef CFLOAT2DARGS
#undef CDOUBLE2DARGS
#undef CFLOATTOL
#undef CDOUBLETOL
#define CFLOATTOL 0.085
#define CDOUBLETOL 1.D-4
#define CFLOATARGS 1.234E-5, 1.233E-5, CFLOATTOL
#define CDOUBLEARGS 1.234567D-15, 1.234566D-15, CDOUBLETOL
#define CFLOAT1DARGS [ 1.234E-5, 1.234E-5 ], [ 1.233E-5, 1.233E-5 ], CFLOATTOL
#define CDOUBLE1DARGS [ 1.234567D-15, 1.234567D-15 ], [ 1.234566D-15, 1.234566D-15 ], CDOUBLETOL
#define CFLOAT2DARGS [ [ 1.234E-5, 1.234E-5 ], [ 1.233E-5, 1.233E-5 ] ], [ [ 1.234E-5, 1.234E-5 ], [ 1.233E-5, 1.233E-5 ] ], CFLOATTOL
#define CDOUBLE2DARGS [ [ 1.234567D-15, 1.234567D-15 ], [ 1.234566D-15, 1.234566D-15 ] ], [ [ 1.234567D-15, 1.234567D-15 ], [ 1.234566D-15, 1.234566D-15 ] ], CDOUBLETOL
/* end test defs */
#define WHAT CLOSE
#include HEADERLEVEL
#undef WHAT

/* BOOST_(LEVEL)_CLOSE_FRACTION */
/* test defs */
#undef CFLOATTOL
#undef CDOUBLETOL
#define CFLOATTOL 0.00085
#define CDOUBLETOL 1.D-6
/* end test defs */
#define WHAT CLOSE_FRACTION
#include HEADERLEVEL
#undef WHAT

#undef HAVEDIM
#undef BOOSTFUNCTION
#define BOOSTFUNCTION BOOSTFUNCTION2
#define HAVECINT
/* BOOST_(LEVEL)_GE and similars section */
/* test defs */
#undef CINTARGS
#undef CFLOATARGS
#undef CDOUBLEARGS
#define CINTARGS 2, 1
#define CFLOATARGS 2.0, 1.0
#define CDOUBLEARGS 2.D0, 1.D0
/* end test defs */
#define WHAT GE
#include HEADERLEVEL
#undef WHAT

/* BOOST_(LEVEL)_GT */
#define WHAT GT
#include HEADERLEVEL
#undef WHAT

/* BOOST_(LEVEL)_LE */
/* test defs */
#undef CINTARGS
#undef CFLOATARGS
#undef CDOUBLEARGS
#define CINTARGS 1, 2
#define CFLOATARGS 1.0, 2.0
#define CDOUBLEARGS 1.D0, 2.D0
/* end test defs */
#define WHAT LE
#include HEADERLEVEL
#undef WHAT

/* BOOST_(LEVEL)_LT */
#define WHAT LT
#include HEADERLEVEL
#undef WHAT

#define HAVECBOOL
#define HAVECAST
/* BOOST_(LEVEL)_NE */
/* test defs */
#undef CBOOLARGS
#undef LOGICALARGS
#define CBOOLARGS logical(.true.,KIND=C_BOOL), logical(.false.,KIND=C_BOOL)
#define LOGICALARGS .true., .false.
/* end test defs */
#define WHAT NE
#include HEADERLEVEL
#undef WHAT

#undef HAVECAST
#undef NAME1
#undef NAME2
#undef BOOSTFUNCTION

#undef HAVECFLOAT
#undef HAVECDOUBLE
#define NAME1 expr
#define NAME2 message
#define BOOSTFUNCTION BOOSTFUNCTION1
#define HAVEDIM
#define HAVECAST
/* BOOST_(LEVEL)_MESSAGE and similars section */
/* test defs */
#undef CINTARGS
#undef CINT1DARGS
#undef CINT2DARGS
#undef CFLOATARGS
#undef CDOUBLEARGS
#undef CBOOLARGS
#undef LOGICALARGS
#define CINTARGS 1, "failed"
#define CINT1DARGSD [ 1, 1 ]
#define CINT1DARGS CINT1DARGSD, "failed"
#define CINT2DARGS [ CINT1DARGSD, CINT1DARGSD ], "failed"
#define CBOOLARGS logical(.true.,KIND=C_BOOL), "failed"
#define CBOOLARGSD [logical(.true.,KIND=C_BOOL), logical(.true.,KIND=C_BOOL)]
#define CBOOL1DARGS CBOOLARGSD, "failed"
#define CBOOL2DARGS [ CBOOLARGSD, CBOOLARGSD ], "failed"
#define LOGICALARGS .true., "failed"
#define LOGICALARGSD [ .true., .true. ]
#define LOGICAL1DARGS [ LOGICALARGSD ], "failed"
#define LOGICAL2DARGS [ LOGICALARGSD, LOGICALARGSD ], "failed"
/* end test defs */
#define WHAT MESSAGE
#include HEADERLEVEL
#undef WHAT
#undef DOTESTS
#undef CINT2DARGS
#undef CINT1DARGS

#undef HAVECAST
#undef HAVEDIM
#undef HAVECBOOL
#undef HAVECINT
#undef HAVECFLOAT
#undef HAVECDOUBLE
#undef BOOSTFUNCTION
#undef NAME2
#undef NAME1

#ifdef DOINTERFACE

#ifndef __cplusplus
!$f90tw TESTCODE(BOOST_AUTO_TEST_CASE, DUMMY, F90_BOOST_ETC, CONCAT2(TEST,F90_BOOST_ETC,_),
!$f90tw   F90TWUSE (ISO_C_BINDING)
!$f90tw   F90TWUSE (assertions_boost)
#endif

/* BOOST_TEST_CHECKPOINT */
BOOSTSOMETHING(TEST_CHECKPOINT)

/* BOOST_TEST_MESSAGE */
BOOSTSOMETHING(TEST_MESSAGE)

/* BOOST_TEST_INFO */
BOOSTSOMETHING(TEST_INFO)

/* BOOST_TEST_CONTEXT */
BOOSTSOMETHING(TEST_CONTEXT)

#if defined(BOOST_VERSION) && BOOST_VERSION > 107000
/* BOOST_TEST_INFO_SCOPE */
BOOSTSOMETHING(TEST_INFO_SCOPE)
#endif

/* BOOST_FAIL (disable api test)*/
#define F90TWSUB(...) 
BOOSTSOMETHING(FAIL)

/* BOOST_ERROR (disable api test) */
BOOSTSOMETHING(ERROR)
#undef F90TWSUB

#ifndef __cplusplus
!$f90tw )
#endif

/* BOOST_TEST_PASSPOINT */
BOOSTVOID(TEST_PASSPOINT)

#endif

#endif
