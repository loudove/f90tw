/* check:
// https://stackoverflow.com/questions/127318/is-there-any-sed-like-utility-for-cmd-exe
*/

#define F90TESTWRAPPERS

/* #include "f90tw_mangle.h" */

/* utility macros */
#define TOSTRHLP(x) #x
#define TOSTR(x) TOSTRHLP(x)

/* fix concatenation in traditional cpp macro definition.
// this is not possible for strigify operation and this is why
// cpp is (or another preprocessor is required for the correct
// preprocessing fortran sources when gfortran is in use. */
#ifdef __GFORTRAN__
#define PASTE(a) a
#define CONCAT(a,b) PASTE(a)b
#else
#define PASTE(a,b) a ## b
#define CONCAT(a,b) PASTE(a,b)
#endif

/* concatenation utilities with w as the separator character. */
#define CONCAT2(a,b,w) CONCAT(a,CONCAT(w,b))
#define CONCAT3(a,b,c,w) CONCAT(a,CONCAT(w,CONCAT2(b,c,w)))
#define CONCAT4(a,b,c,d,w) CONCAT(a,CONCAT(w,CONCAT3(b,c,d,w)))
#define CONCAT5(a,b,c,d,e,w) CONCAT(a,CONCAT(w,CONCAT4(b,c,d,e,w)))
#define CONCAT6(a,b,c,d,e,f,w) CONCAT(a,CONCAT(w,CONCAT5(b,c,d,e,f,w)))
#define PREPENDF90(x) CONCAT2(F90,x,_)

/* set boost as the default test framework TESTFRK =(boost|gtest) */
#if defined(USEGTEST)
#define TESTFRK gtest
#else
#define TESTFRK boost
#endif

/* utility macros for simple boost/gtest test implementation */

/* first lines of module TESTNAME for testing module MODNAME using TESTFRK test framework */
#define F90TESTMODULE(TESTNAME,MODNAME)   \
    module TESTNAME; \
        use CONCAT2(assertions,TESTFRK,_) ;  \
        use MODNAME; \
        implicit none; \
        contains

/* module TESTNAME closure */
#define F90ENDTESTMODULE(TESTNAME) end module TESTNAME

/* code generation macros */
#define HCODE_( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, ... ) extern "C" {  void SUBNAME(); }
#define HCODE( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, ... ) HCODE_( TESTTYPE,TESTSUITENAME, TESTNAME, SUBNAME, __VA_ARGS__ )
#define CCODE_( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, ... ) TESTTYPE(TESTNAME) { SUBNAME(); }
#define CCODEG_( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, ... ) TESTTYPE(TESTSUITENAME,TESTNAME) { SUBNAME(); }
#define CCODEFULL_( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, ... ) TESTTYPE(TESTNAME) { do { __VA_ARGS__ } while(false); }
#if defined(USEGTEST)
#define CCODE( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, ... ) CCODEG_( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, __VA_ARGS__ )
#else
#define CCODE( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, ... ) CCODE_( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, __VA_ARGS__ )
#endif
#define FCODE_( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, ... ) subroutine SUBNAME() BIND(C,name=#SUBNAME); __VA_ARGS__ ; end subroutine SUBNAME
#define FCODE( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, ... ) FCODE_( TESTTYPE, TESTSUITENAME, TESTNAME, SUBNAME, __VA_ARGS__ )

/* f90 interface: boost void methods */
#define F90_BOOST_VOID(WHAT) \
     interface CONCAT2(F90_BOOST,WHAT,_) ; \
     subroutine CONCAT2(c_BOOST,WHAT,_) () \
                 bind(C,name=TOSTR( CONCAT2(c_BOOST,WHAT,_))) ; \
     end subroutine CONCAT2(c_BOOST,WHAT,_) ; \
     end interface CONCAT2(F90_BOOST,WHAT,_)

/* c implementation: boost void methods */
#define C_BOOST_VOID(WHAT) \
     void CONCAT2(c_BOOST,WHAT,_) () { \
         CONCAT2(BOOST,WHAT,_)(); \
     }

/* f90 interface: boost message methods */
#define F90_BOOST_SOMETHING(WHAT) \
     interface CONCAT2(F90_BOOST,WHAT,_) ; \
     subroutine CONCAT2(c_BOOST,WHAT,_) (message) \
                 bind(C,name=TOSTR( CONCAT2(c_BOOST,WHAT,_))) ; \
         import C_CHAR ; \
         character(KIND=C_CHAR), intent(in) :: message ; \
     end subroutine CONCAT2(c_BOOST,WHAT,_) ; \
     end interface CONCAT2(F90_BOOST,WHAT,_)

/* c implementation: boost message methods */
#define C_BOOST_SOMETHING(WHAT) \
     void CONCAT2(c_BOOST,WHAT,_) (const char* message) { \
         CONCAT2(BOOST,WHAT,_)(message); \
     }

/* f90 interface: boost assertions with two arguments the second of which is the assertion message */
#define F90_BOOST_LEVEL_MESSAGE(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_) (NAME1,NAME2) \
                 bind(C,name=TOSTR( CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_))) ; \
         import CTYPE, C_CHAR ; \
         TYPE (KIND=CTYPE), intent(in) :: NAME1;  \
         character(KIND=C_CHAR), intent(in) :: NAME2 ; \
     end subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)

/* c implementation: boost assertions with two arguments the second of which is the assertion message */
#define C_BOOST_LEVEL_MESSAGE(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     void CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_) (TYPE* NAME1, const char* NAME2) { \
         CONCAT3(BOOST,LEVEL,WHAT,_)(*NAME1, NAME2); \
     }

/* f90 interface: boost assertions with two or three arguments of the same type */
#define F90_BOOST_LEVEL_CHECK1T2A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_) (NAME1, NAME2) \
                 bind(C,name=TOSTR(CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_))) ; \
         import CTYPE ; \
         TYPE(KIND=CTYPE), intent(in) :: NAME1, NAME2;  \
     end subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)

#define F90_BOOST_LEVEL_CHECK1T3A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_) (NAME1,NAME2,tolerance) \
                 bind(C,name=TOSTR(CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_))) ; \
         import CTYPE ; \
         TYPE(KIND=CTYPE), intent(in) :: NAME1, NAME2, tolerance;  \
     end subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)

/* c wrapper: boost assertions with two or three arguments of the same type */
#define C_BOOST_LEVEL_CHECK1T2A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     void CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_) (TYPE* NAME1, TYPE* NAME2) { \
         CONCAT3(BOOST,LEVEL,WHAT,_)(*NAME1, *NAME2); \
     }

#define C_BOOST_LEVEL_CHECK1T3A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     void CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_) (TYPE* NAME1, TYPE* NAME2, TYPE* tolerance) { \
         CONCAT3(BOOST,LEVEL,WHAT,_)(*NAME1, *NAME2, *tolerance); \
     }

/* f90 interface: boost assertions with two arguments of (possibly) different type */
#define F90_BOOST_LEVEL_CHECK2T2A(LEVEL,WHAT,LTYPE,LCTYPE,RTYPE,RCTYPE,NAME1,NAME2) \
     subroutine CONCAT5(c_BOOST,LEVEL,WHAT,LCTYPE,RCTYPE,_) (NAME1,NAME2) \
                 bind(C,name=TOSTR( CONCAT5(c_BOOST,LEVEL,WHAT,LCTYPE,RCTYPE,_))) ; \
         import LCTYPE, RTYPE; \
         LTYPE(KIND=LCTYPE), intent(in) :: NAME1 ;  \
         RTYPE(KIND=RCTYPE), intent(in) :: NAME2 ;  \
     end subroutine CONCAT5(c_BOOST,LEVEL,WHAT,LCTYPE,RCTYPE,_)

/* c wrapper: boost assertions with two arguments of (possibly) different type */
#define C_BOOST_LEVEL_CHECK2T2A(LEVEL,WHAT,LTYPE,LCTYPE,RTYPE,RCTYPE,NAME1,NAME2) \
     void CONCAT5(c_BOOST,LEVEL,WHAT,LCTYPE,RCTYPE,_) (RTYPE* NAME1, LTYPE* NAME2) { \
         CONCAT4(BOOST,LEVEL,WHAT,_)(*NAME1, *NAME2); \
     }

/* f90 interface:  gtest assertions one/tow/three arguments [+ message] */
#define F90_GTEST_LEVEL_CHECK1T1A(LEVEL,WHAT,TYPE,CTYPE,NAME1,DUMMY) \
     subroutine CONCAT4(c,LEVEL,WHAT,CTYPE,_) (NAME1) \
                 bind(C,name=TOSTR(CONCAT4(c,LEVEL,WHAT,CTYPE,_))) ; \
         import CTYPE ; \
         TYPE(KIND=CTYPE), intent(in) :: NAME1;  \
     end subroutine CONCAT4(c,LEVEL,WHAT,CTYPE,_)

#define F90_GTEST_LEVEL_CHECK1T1AM(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(c,LEVEL,WHAT,CTYPE,M,_) (NAME1,message) \
                 bind(C,name=TOSTR(CONCAT5(c,LEVEL,WHAT,CTYPE,M,_))) ; \
         import CTYPE, C_CHAR ; \
         TYPE(KIND=CTYPE), intent(in) :: NAME1;  \
         character(KIND=C_CHAR), intent(in) :: message ; \
     end subroutine CONCAT5(c,LEVEL,WHAT,CTYPE,M,_)

#define F90_GTEST_LEVEL_CHECK1T2A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT4(c,LEVEL,WHAT,CTYPE,_) (NAME1, NAME2) \
                 bind(C,name=TOSTR(CONCAT4(c,LEVEL,WHAT,CTYPE,_))) ; \
         import CTYPE ; \
         TYPE(KIND=CTYPE), intent(in) :: NAME1, NAME2;  \
     end subroutine CONCAT4(c,LEVEL,WHAT,CTYPE,_)

#define F90_GTEST_LEVEL_CHECK1T2AM(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(c,LEVEL,WHAT,CTYPE,M,_) (NAME1,NAME2,message) \
                 bind(C,name=TOSTR(CONCAT5(c,LEVEL,WHAT,CTYPE,M,_))) ; \
         import CTYPE, C_CHAR ; \
         TYPE(KIND=CTYPE), intent(in) :: NAME1, NAME2;  \
         character(KIND=C_CHAR), intent(in) :: message ; \
     end subroutine CONCAT5(c,LEVEL,WHAT,CTYPE,M,_)

#define F90_GTEST_LEVEL_CHECK1T2STR(LEVEL,WHAT,NAME1,NAME2) \
     subroutine CONCAT3(c,LEVEL,WHAT,_) (NAME1, NAME2) \
                 bind(C,name=TOSTR(CONCAT3(c,LEVEL,WHAT,_))) ; \
         import C_CHAR ; \
         character(KIND=C_CHAR), intent(in) :: NAME1, NAME2;  \
     end subroutine CONCAT3(c,LEVEL,WHAT,_)

#define F90_GTEST_LEVEL_CHECK1T2STRM(LEVEL,WHAT,NAME1,NAME2) \
     subroutine CONCAT4(c,LEVEL,WHAT,M,_) (NAME1,NAME2,message) \
                 bind(C,name=TOSTR(CONCAT4(c,LEVEL,WHAT,M,_))) ; \
         import C_CHAR ; \
         character(KIND=C_CHAR), intent(in) ::  NAME1, NAME2, message ; \
     end subroutine CONCAT4(c,LEVEL,WHAT,M,_)


#define F90_GTEST_LEVEL_CHECK1T3A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT4(c,LEVEL,WHAT,CTYPE,_) (NAME1,NAME2,abs_error) \
                 bind(C,name=TOSTR(CONCAT4(c,LEVEL,WHAT,CTYPE,_))) ; \
         import CTYPE ; \
         TYPE(KIND=CTYPE), intent(in) :: NAME1, NAME2, abs_error;  \
     end subroutine CONCAT4(c,LEVEL,WHAT,CTYPE,_)

#define F90_GTEST_LEVEL_CHECK1T3AM(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(c,LEVEL,WHAT,CTYPE,M,_) (NAME1,NAME2,abs_error,message) \
                 bind(C,name=TOSTR(CONCAT5(c,LEVEL,WHAT,CTYPE,M,_))) ; \
         import CTYPE, C_CHAR ; \
         TYPE(KIND=CTYPE), intent(in) :: NAME1, NAME2, abs_error;  \
         character(KIND=C_CHAR), intent(in) :: message ; \
     end subroutine CONCAT5(c,LEVEL,WHAT,CTYPE,M,_)

/* c wrapper: gtest assertions one/tow/three arguments [+ message] */
#define C_GTEST_LEVEL_CHECK1T1A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     void CONCAT4(c,LEVEL,WHAT,CTYPE,_) (TYPE* NAME1) { \
         CONCAT2(LEVEL,WHAT,_)(*NAME1); \
     }

#define C_GTEST_LEVEL_CHECK1T1AM(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     void CONCAT5(c,LEVEL,WHAT,CTYPE,M,_) (TYPE* NAME1, const char *message) { \
         CONCAT2(LEVEL,WHAT,_)(*NAME1) << message; \
     }

#define C_GTEST_LEVEL_CHECK1T2A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     void CONCAT4(c,LEVEL,WHAT,CTYPE,_) (TYPE* NAME1, TYPE* NAME2) { \
         CONCAT2(LEVEL,WHAT,_)(*NAME1, *NAME2); \
     }

#define C_GTEST_LEVEL_CHECK1T2AM(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     void CONCAT5(c,LEVEL,WHAT,CTYPE,M,_) (TYPE* NAME1, TYPE* NAME2, const char* message) { \
         CONCAT2(LEVEL,WHAT,_)(*NAME1, *NAME2) << message; \
     }

#define C_GTEST_LEVEL_CHECK1T2STR(LEVEL,WHAT,NAME1,NAME2) \
     void CONCAT4(c,LEVEL,WHAT,CTYPE,_) ( const char* NAME1,  const char* NAME2) { \
         CONCAT2(LEVEL,WHAT,_)(NAME1, NAME2); \
     }

#define C_GTEST_LEVEL_CHECK1T2STRM(LEVEL,WHAT,NAME1,NAME2) \
     void CONCAT5(c,LEVEL,WHAT,CTYPE,M,_) ( const char* NAME1,  const char* NAME2, const char* message) { \
         CONCAT2(LEVEL,WHAT,_)(NAME1, NAME2) << message; \
     }

#define C_GTEST_LEVEL_CHECK1T3A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     void CONCAT4(c,LEVEL,WHAT,CTYPE,_) (TYPE* NAME1, TYPE* NAME2, TYPE* abs_error) { \
         CONCAT2(LEVEL,WHAT,_)(*NAME1, *NAME2, *abs_error); \
     }

#define C_GTEST_LEVEL_CHECK1T3AM(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     void CONCAT5(c,LEVEL,WHAT,CTYPE,M,_) (TYPE* NAME1, TYPE* NAME2, TYPE* abs_error, const char* message) { \
         CONCAT2(LEVEL,WHAT,_)(*NAME1, *NAME2, *abs_error) << message; \
     }

