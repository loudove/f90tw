#ifdef F90TESTWRAPPERS

/* set variable names */
#define NAME1 left
#define NAME2 right
/* set the definition of the boost function */
#define BOOSTFUNCTION BOOSTFUNCTION2
/* set the type flags */
#define HAVECINT
#define HAVECBOOL
#define  HAVECFLOAT
#define  HAVECDOUBLE

#undef  HAVECFLOAT
#undef  HAVECDOUBLE
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

#undef  BOOSTFUNCTION
#define BOOSTFUNCTION BOOSTFUNCTION3
/* BOOST_(LEVEL)_CLOSE and similars section */
#define WHAT CLOSE
#include HEADERLEVEL
#undef WHAT
/* BOOST_(LEVEL)_CLOSE_FRACTION */
#define WHAT CLOSE_FRACTION
#include HEADERLEVEL
#undef WHAT

#undef  BOOSTFUNCTION
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
