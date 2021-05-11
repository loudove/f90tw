#ifdef F90TESTWRAPPERS

/* set variable names */
#define NAME1 val1
#define NAME2 val2
/* set the definition of the gtest functions */
#define GTESTFUNCTION GTESTFUNCTION2
#define GTESTFUNCTIONM GTESTFUNCTION2M
/* set the type flags */
#define HAVECBOOL
#define HAVECINT
#define HAVECFLOAT
#define HAVECDOUBLE
#undef DOSTR

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
