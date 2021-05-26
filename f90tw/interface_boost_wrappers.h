#ifdef F90TESTWRAPPERS
#define INTERFACENAME PREPENDF90( CONCAT3(BOOST,LEVEL,WHAT,_))
#ifdef DOINTERFACE
#ifdef DOTESTS
!$f90tw TESTCODE(BOOST_AUTO_TEST_CASE, DUMMY, INTERFACENAME, CONCAT2(TEST,INTERFACENAME,_),
!$f90tw   F90TWUSE( ISO_C_BINDING)
!$f90tw   F90TWUSE( assertions_boost)
#endif
      interface INTERFACENAME
#endif

/* For each supported type the DOINTERFACE block includes the wrapper
// to the c function while the rest of the blocks set the corresponding
// utility functions implemented in the module. The HAVEDIM block set
// the same variants of the function with the 1D and 2D array argument(s)
// and. The HAVECAST block set the variants where instead of using the
// C_BOOL argument type, the default fortran logical type (kind=4) is
// used instead. Finally the DOTESTS block (located inside DOINTERFACE
// block) prepares simple tests for the implementation of f90tw using
// the directives approach. */
#ifdef HAVECINT
#ifdef DOINTERFACE
#ifdef DOTESTS
        !$f90tw F90TWSUB( INTERFACENAME, CINTARGS)
#ifdef HAVEDIM        
        !$f90tw F90TWSUB( INTERFACENAME, CINT1DARGS)
        !$f90tw F90TWSUB( INTERFACENAME, CINT2DARGS)
#endif
#endif
        BOOSTFUNCTION(LEVEL,WHAT,integer,C_INT,NAME1,NAME2)
#endif
#ifdef HAVEDIM
        CONCAT(BOOSTFUNCTION,DIM1) (LEVEL,WHAT,integer,C_INT,NAME1,NAME2)

        CONCAT(BOOSTFUNCTION,DIM2) (LEVEL,WHAT,integer,C_INT,NAME1,NAME2)
#endif
#endif

#ifdef HAVECFLOAT
#ifdef DOINTERFACE
#ifdef DOTESTS
        !$f90tw F90TWSUB( INTERFACENAME, CFLOATARGS)
#ifdef HAVEDIM        
        !$f90tw F90TWSUB( INTERFACENAME, CFLOAT1DARGS)
        !$f90tw F90TWSUB( INTERFACENAME, CFLOAT2DARGS)
#endif
#endif
        BOOSTFUNCTION(LEVEL,WHAT,real,C_FLOAT,NAME1,NAME2)
#endif
#ifdef HAVEDIM
        CONCAT(BOOSTFUNCTION,DIM1) (LEVEL,WHAT,real,C_FLOAT,NAME1,NAME2)

        CONCAT(BOOSTFUNCTION,DIM2) (LEVEL,WHAT,real,C_FLOAT,NAME1,NAME2)
#endif
#endif

#ifdef HAVECDOUBLE
#ifdef DOINTERFACE
#ifdef DOTESTS
        !$f90tw F90TWSUB( INTERFACENAME, CDOUBLEARGS)
#ifdef HAVEDIM        
        !$f90tw F90TWSUB( INTERFACENAME, CDOUBLE1DARGS)
        !$f90tw F90TWSUB( INTERFACENAME, CDOUBLE2DARGS)
#endif
#endif
        BOOSTFUNCTION(LEVEL,WHAT,real,C_DOUBLE,NAME1,NAME2)
#endif
#ifdef HAVEDIM
        CONCAT(BOOSTFUNCTION,DIM1) (LEVEL,WHAT,real,C_DOUBLE,NAME1,NAME2)

        CONCAT(BOOSTFUNCTION,DIM2) (LEVEL,WHAT,real,C_DOUBLE,NAME1,NAME2)
#endif
#endif

#ifdef HAVECBOOL
#ifdef DOINTERFACE
#ifdef DOTESTS
        !$f90tw F90TWSUB( INTERFACENAME, CBOOLARGS)
#ifdef HAVEDIM
        !$f90tw F90TWSUB( INTERFACENAME, CBOOL1DARGS)
        !$f90tw F90TWSUB( INTERFACENAME, CBOOL2DARGS)
#endif
#ifdef HAVECAST
        !$f90tw F90TWSUB( INTERFACENAME, LOGICALARGS)
#ifdef HAVEDIM
        !$f90tw F90TWSUB( INTERFACENAME, LOGICAL1DARGS)
        !$f90tw F90TWSUB( INTERFACENAME, LOGICAL2DARGS)        
#endif
#endif
#endif
        BOOSTFUNCTION(LEVEL,WHAT,logical,C_BOOL,NAME1,NAME2)
#endif
#ifdef HAVEDIM
        CONCAT(BOOSTFUNCTION,DIM1) (LEVEL,WHAT,logical,C_BOOL,NAME1,NAME2)

        CONCAT(BOOSTFUNCTION,DIM2) (LEVEL,WHAT,logical,C_BOOL,NAME1,NAME2)
#ifdef HAVECAST
        CONCAT2( CONCAT(BOOSTFUNCTION,DIM1),CAST,_) (LEVEL,WHAT,LOGICAL,C_BOOL,NAME1,NAME2)

        CONCAT2( CONCAT(BOOSTFUNCTION,DIM2),CAST,_) (LEVEL,WHAT,LOGICAL,C_BOOL,NAME1,NAME2)
#endif
#endif
#ifdef HAVECAST
        CONCAT2(BOOSTFUNCTION,CAST,_) (LEVEL,WHAT,LOGICAL,C_BOOL,NAME1,NAME2)
#endif
#endif

#ifdef DOINTERFACE
#ifdef DOTESTS
!$f90tw )
#endif
      end interface INTERFACENAME
#endif
#undef INTERFACENAME
#endif