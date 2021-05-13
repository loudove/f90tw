#ifdef F90TESTWRAPPERS

/* version */
VERSIONSUB

/* For each supported boost assertion, a wrapper is created for
// the various levels (see boost_level.h) and arguments type (see
// <implement|interfae>_boost_wrapers.h) supported. The latter is
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
#define HAVECFLOAT
#define HAVECDOUBLE

/* each block creates the implementation of the wrapper.
// The name of the macro is set with WHAT definition, the
// flags for supported arguments type, the appropriate
// implementation macro. */

#undef HAVECFLOAT
#undef HAVECDOUBLE
/* BOOST_(LEVEL)_BITWISE_EQUAL and similars section */
#define WHAT BITWISE_EQUAL
#include HEADERLEVEL
#undef WHAT

#define HAVECFLOAT
#define HAVECDOUBLE
/* BOOST_(LEVEL)_EQUAL and similars section */
#define WHAT EQUAL
#include HEADERLEVEL
#undef WHAT

#undef HAVECINT
#undef HAVECBOOL
#undef NAME2
#define NAME2 tolerance
/* BOOST_(LEVEL)_SMALL and similars section */
#define WHAT SMALL
#include HEADERLEVEL
#undef WHAT
#undef NAME2
#define NAME2 right

#undef BOOSTFUNCTION
#define BOOSTFUNCTION BOOSTFUNCTION3
/* BOOST_(LEVEL)_CLOSE and similars section */
#define WHAT CLOSE
#include HEADERLEVEL
#undef WHAT
/* BOOST_(LEVEL)_CLOSE_FRACTION */
#define WHAT CLOSE_FRACTION
#include HEADERLEVEL
#undef WHAT

#undef BOOSTFUNCTION
#define BOOSTFUNCTION BOOSTFUNCTION2
#define HAVECINT
#define HAVECBOOL
/* BOOST_(LEVEL)_GE and similars section */
#define WHAT GE
#include HEADERLEVEL
#undef WHAT
/* BOOST_(LEVEL)_GT */
#define WHAT GT
#include HEADERLEVEL
#undef WHAT
/* BOOST_(LEVEL)_LE */
#define WHAT LE
#include HEADERLEVEL
#undef WHAT
/* BOOST_(LEVEL)_LT */
#define WHAT LT
#include HEADERLEVEL
#undef WHAT
/* BOOST_(LEVEL)_NE */
#define WHAT NE
#include HEADERLEVEL
#undef WHAT
#undef NAME1
#undef NAME2
#undef BOOSTFUNCTION

#define NAME1 expr
#define NAME2 message
#define BOOSTFUNCTION BOOSTFUNCTION1
/* BOOST_(LEVEL)_GE and similars section */
#define WHAT MESSAGE
#include HEADERLEVEL
#undef WHAT

#undef HAVECBOOL
#undef HAVECINT
#undef HAVECFLOAT
#undef HAVECDOUBLE
#undef BOOSTFUNCTION
#undef NAME2
#undef NAME1

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

/* BOOST_FAIL */
BOOSTSOMETHING(FAIL)

/* BOOST_ERROR */
BOOSTSOMETHING(ERROR)

/* BOOST_TEST_PASSPOINT */
BOOSTVOID(TEST_PASSPOINT)

#endif
