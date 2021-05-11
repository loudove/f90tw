#ifdef F90TESTWRAPPERS

extern "C" {
#ifdef HAVECINT
        BOOSTFUNCTION(LEVEL,WHAT,int,C_INT,NAME1,NAME2)
#endif
#ifdef HAVECFLOAT
        BOOSTFUNCTION(LEVEL,WHAT,float,C_FLOAT,NAME1,NAME2)
#endif
#ifdef HAVECDOUBLE
        BOOSTFUNCTION(LEVEL,WHAT,double,C_DOUBLE,NAME1,NAME2)
#endif
#ifdef HAVECBOOL
        BOOSTFUNCTION(LEVEL,WHAT,bool,C_BOOL,NAME1,NAME2)
#endif
}

#endif
