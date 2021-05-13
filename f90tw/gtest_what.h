#ifdef F90TESTWRAPPERS

/* version */
VERSIONSUB

/* For each supported boost assertion, a wrapper is created for
// the various levels (see gtest_level.h) and arguments type (see
// <implement|interfae>_gtest_wrapers.h) supported. The latter is
// controlled with HAVECINT, HAVECBOOL, HAVECFLOAT, HAVECDOUBLE and
// DOSTR definitions corresponding to integer(kind=C_INT), 
// logical(kind=C_BOOL), real(kind=C_FLOAT), real(kind=C_DOUBLE) and
// character(LEN=C_CHAR) types. The GTESTFUNCTION2M and GTESTFUNCTION2
// marcos control the specific implementation of the wrapper (with and
// without a custom message). The name of the arguments is controlled
// by NAME1 and NAME2 macros. */

/* set variable names for the arguments */
#define NAME1 val1
#define NAME2 val2
/* set the definitions of the boost functions of the wrapper */
#define GTESTFUNCTION GTESTFUNCTION2
#define GTESTFUNCTIONM GTESTFUNCTION2M
/* set the flags for the arguments type supported for the wrapper*/
#define HAVECBOOL
#define HAVECINT
#define HAVECFLOAT
#define HAVECDOUBLE
#undef DOSTR

/* each block creates the implementation of the wrapper.
// The name of the macro is set with WHAT definition, the
// flags for supported arguments type, the appropriate
// implementation macro. */

/* (LEVEL)_EQ and similars section */
#define WHAT EQ
#include HEADERLEVEL
#undef WHAT

#undef HAVECBOOL
/* (LEVEL)_EQ and similars section */
#define WHAT NE
#include HEADERLEVEL
#undef WHAT
/* (LEVEL)_EQ and similars section */
#define WHAT LT
#include HEADERLEVEL
#undef WHAT
/* (LEVEL)_EQ and similars section */
#define WHAT LE
#include HEADERLEVEL
#undef WHAT
/* (LEVEL)_EQ and similars section */
#define WHAT GT
#include HEADERLEVEL
#undef WHAT
/* (LEVEL)_EQ and similars section */
#define WHAT GE
#include HEADERLEVEL
#undef WHAT

#undef HAVECINT
#undef HAVECDOUBLE
/* (LEVEL)_FLOAT_EQ and similars section */
#define WHAT FLOAT_EQ
#include HEADERLEVEL
#undef WHAT

#undef HAVECFLOAT
#define HAVECDOUBLE
/* (LEVEL)_FLOAT_EQ and similars section */
#define WHAT DOUBLE_EQ
#include HEADERLEVEL
#undef WHAT

#define HAVECFLOAT
#undef GTESTFUNCTION
#undef GTESTFUNCTIONM
#define GTESTFUNCTION GTESTFUNCTION3
#define GTESTFUNCTIONM GTESTFUNCTION3M
/* (LEVEL)_NEAR and similars section */
#define WHAT NEAR
#include HEADERLEVEL
#undef WHAT

#undef HAVECFLOAT
#undef HAVECDOUBLE
#define DOSTR
#undef NAME1
#undef NAME2
#define NAME1 str1
#define NAME2 str2
#undef GTESTFUNCTION
#undef GTESTFUNCTIONM
#define GTESTFUNCTION GTESTFUNCTION2STR
#define GTESTFUNCTIONM GTESTFUNCTION2STRM
/* (LEVEL)_STREQ and similars section (only one dummy TYPE should be defined) */
#define WHAT STREQ
#include HEADERLEVEL
#undef WHAT
/* (LEVEL)_STRNE and similars section */
#define WHAT STRNE
#include HEADERLEVEL
#undef WHAT
/* (LEVEL)_STRCASEEQ and similars section */
#define WHAT STRCASEEQ
#include HEADERLEVEL
#undef WHAT
/* (LEVEL)_STRCASENE and similars section */
#define WHAT STRCASENE
#include HEADERLEVEL
#undef WHAT

#undef DOSTR
#undef HAVECFLOAT
#undef HAVECDOUBLE
#define HAVECBOOL
#define HAVECINT
#undef GTESTFUNCTION
#undef GTESTFUNCTIONM
#define GTESTFUNCTION GTESTFUNCTION1
#define GTESTFUNCTIONM GTESTFUNCTION1M
#undef NAME1
#define NAME1 condition
/* (LEVEL)_TRUE and similars section */
#define WHAT TRUE
#include HEADERLEVEL
#undef WHAT
/* (LEVEL)_FALSE */
#define WHAT FALSE
#include HEADERLEVEL
#undef WHAT

#undef HAVECBOOL
#undef HAVECINT
#undef HAVECFLOAT
#undef HAVECDOUBLE
#undef  GTESTFUNCTION
#undef  GTESTFUNCTIONM
#undef NAME2
#undef NAME1

#endif
