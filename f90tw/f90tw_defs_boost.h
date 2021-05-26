#ifndef F90TW_DEFS_BOOST_H
#define F90TW_DEFS_BOOST_H

#include "f90tw_defs.h"

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
     !$f90tw F90TWSUB( CONCAT2(F90_BOOST,WHAT,_), TOSTR(WHAT)) ; \
     subroutine CONCAT2(c_BOOST,WHAT,_) (message) \
                 bind(C,name=TOSTR( CONCAT2(c_BOOST,WHAT,_))) ; \
         import C_CHAR ; \
         character(KIND=C_CHAR), intent(in) :: message ; \
     end subroutine CONCAT2(c_BOOST,WHAT,_) ; \
     end interface CONCAT2(F90_BOOST,WHAT,_)

/* c implementation: boost message methods */
#define C_BOOST_SOMETHING(WHAT) \
     extern "C" { \
     void CONCAT2(c_BOOST,WHAT,_) (const char* message) { \
         CONCAT2(BOOST,WHAT,_)(message); \
     } \
     }

/* f90 interface: boost assertions with two arguments the second of which is the assertion message */
#define F90_BOOST_LEVEL_MESSAGE(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_) (NAME1,NAME2) \
                 bind(C,name=TOSTR( CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_))) ; \
         import CTYPE, C_CHAR ; \
         TYPE (KIND=CTYPE), intent(in) :: NAME1;  \
         character(KIND=C_CHAR), intent(in) :: NAME2 ; \
     end subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)

/* cast to logical(4) interface and implementation */
#define F90_BOOST_LEVEL_MESSAGE_CAST(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT4(F90_BOOST,LEVEL,WHAT,TYPE,_)

#define F90_BOOST_LEVEL_MESSAGE_CAST_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT4(F90_BOOST,LEVEL,WHAT,TYPE,_) (NAME1, NAME2) ; \
         TYPE, intent(in) :: NAME1 ;  \
         character(LEN=*), intent(in) :: NAME2 ; \
         TYPE(KIND=CTYPE) :: CONCAT(C,NAME1) ;  \
         CONCAT(C,NAME1) = TYPE( NAME1, KIND=CTYPE) ; \
         call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)(CONCAT(C,NAME1), NAME2) ; \
     end subroutine CONCAT4(F90_BOOST,LEVEL,WHAT,TYPE,_)

/* dimension(:) argument interface and implementation */
#define F90_BOOST_LEVEL_MESSAGEDIM1(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,1D,_)

#define F90_BOOST_LEVEL_MESSAGEDIM1_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,1D,_) (NAME1, NAME2) ; \
         TYPE(KIND=CTYPE), dimension(:), intent(in) :: NAME1 ;  \
         character(LEN=*), intent(in) :: NAME2 ; \
         character(LEN=100) :: str ; \
         integer :: i ; \
         do i = 1, size(NAME1) ; \
           write(str,'(A, " : (", I0, ") INDX", A)') TRIM(NAME2), i, C_NULL_CHAR ; \
           call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)(NAME1(i), TRIM(str) ) ; \
         enddo ; \
     end subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,1D,_)

/* dimension(:) argument + cast to logical(4) interface and implementation */
#define F90_BOOST_LEVEL_MESSAGEDIM1_CAST(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT5(F90_BOOST,LEVEL,WHAT,TYPE,1D,_)

#define F90_BOOST_LEVEL_MESSAGEDIM1_IMPLEMENT_CAST_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,TYPE,1D,_) (NAME1, NAME2) ; \
         TYPE, dimension(:), intent(in) :: NAME1 ;  \
         character(LEN=*), intent(in) :: NAME2 ; \
         character(LEN=100) :: str ; \
         integer :: i ; \
         TYPE(KIND=CTYPE) :: CONCAT(C,NAME1) ;  \
         do i = 1, size(NAME1) ; \
           CONCAT(C,NAME1) = TYPE( NAME1(i), KIND=CTYPE) ;\
           write(str,'(A, " : (", I0, ") INDX", A)') TRIM(NAME2), i, C_NULL_CHAR ; \
           call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)(CONCAT(C,NAME1), TRIM(str)) ; \
         enddo ; \
     end subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,TYPE,1D,_)

/* dimension(:,:) argument interface and implementation */
#define F90_BOOST_LEVEL_MESSAGEDIM2(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,2D,_)

#define F90_BOOST_LEVEL_MESSAGEDIM2_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,2D,_) (NAME1, NAME2) ; \
         TYPE(KIND=CTYPE), dimension(:,:), intent(in) :: NAME1 ;  \
         character(LEN=*), intent(in) :: NAME2 ; \
         character(LEN=100) :: str ; \
         integer :: i, j, n(2) ; \
         n = shape(NAME1) ; \
         do i = 1, n(1) ; \
           do j = 1, n(2) ; \
             write(str,'(A, " : (", I0, ",", I0, ") INDX", A)') TRIM(NAME2), i, j, C_NULL_CHAR ; \
             call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)(NAME1(i,j), TRIM(str)) ; \
           enddo ; \
         enddo ; \
     end subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,2D,_)

/* dimension(:,:) argument + cast to logical(4) interface and implementation */
#define F90_BOOST_LEVEL_MESSAGEDIM2_CAST(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT5(F90_BOOST,LEVEL,WHAT,TYPE,2D,_)

#define F90_BOOST_LEVEL_MESSAGEDIM2_IMPLEMENT_CAST_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,TYPE,2D,_) (NAME1, NAME2) ; \
         TYPE, dimension(:,:), intent(in) :: NAME1 ;  \
         character(LEN=*), intent(in) :: NAME2 ; \
         character(LEN=100) :: str ; \
         integer :: i, j, n(2) ; \
         TYPE(KIND=CTYPE) :: CONCAT(C,NAME1) ;  \
         n = shape(NAME1) ; \
         do i = 1, n(1) ; \
           do j = 1, n(2) ; \
             CONCAT(C,NAME1) = TYPE( NAME1(i,j), KIND=CTYPE) ;\
             write(str,'(A, " : (", I0, ",", I0, ") INDX", A)') TRIM(NAME2), i, j, C_NULL_CHAR ; \
             call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)(CONCAT(C,NAME1), TRIM(str)) ; \
           enddo ; \
         enddo ; \
     end subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,TYPE,2D,_)

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

/* cast to logical(4) interface and implementation  */
#define F90_BOOST_LEVEL_CHECK1T2A_CAST(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT4(F90_BOOST,LEVEL,WHAT,TYPE,_)

#define F90_BOOST_LEVEL_CHECK1T2A_CAST_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT4(F90_BOOST,LEVEL,WHAT,TYPE,_) (NAME1, NAME2) ; \
         TYPE, intent(in) :: NAME1, NAME2;  \
         TYPE(KIND=CTYPE) :: CONCAT(C,NAME1), CONCAT(C,NAME2);  \
         CONCAT(C,NAME1) = TYPE( NAME1, KIND=CTYPE) ; \
         CONCAT(C,NAME2) = TYPE( NAME2, KIND=CTYPE) ; \
         call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)(CONCAT(C,NAME1), CONCAT(C,NAME2)) ; \
     end subroutine CONCAT4(F90_BOOST,LEVEL,WHAT,TYPE,_)

/* dimension(:) argument interface and implementation */
#define F90_BOOST_LEVEL_CHECK1T2ADIM1(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,1D,_)

#define F90_BOOST_LEVEL_CHECK1T2ADIM1_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,1D,_) (NAME1, NAME2) ; \
         TYPE(KIND=CTYPE), dimension(:), intent(in) :: NAME1, NAME2 ; \
         integer :: i, n ; \
         n = size( NAME1) ; \
         if ( n .ne. size( NAME2) ) then ; \
           call F90_BOOST_TEST_MESSAGE("arrays of different size, abording ...") ; \
           return ; \
         endif ; \
         do i = 1, n ; \
          call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)( NAME1(i), NAME2(i) ) ; \
         enddo ; \
     end subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,1D,_)

/* dimension(:,:) argument interface and implementation */
#define F90_BOOST_LEVEL_CHECK1T2ADIM2(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,2D,_)

#define F90_BOOST_LEVEL_CHECK1T2ADIM2_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,2D,_) (NAME1, NAME2) ; \
         TYPE(KIND=CTYPE), dimension(:,:), intent(in) :: NAME1, NAME2;  \
         integer :: i, j, n(2) ; \
         n = shape( NAME1) ; \
         if ( ANY( n .ne. shape( NAME2)) ) then ; \
           call F90_BOOST_TEST_MESSAGE("arrays of different shape, abording ...") ; \
           return ; \
         endif ; \
         do i = 1, n(1) ; \
           do j = 1, n(2) ; \
             call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)( NAME1(i,j), NAME2(i,j) ) ; \
           enddo ; \
         enddo ; \
     end subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,2D,_)

#define F90_BOOST_LEVEL_CHECK1T3A(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_) (NAME1,NAME2,tolerance) \
                 bind(C,name=TOSTR(CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_))) ; \
         import CTYPE ; \
         TYPE(KIND=CTYPE), intent(in) :: NAME1, NAME2, tolerance;  \
     end subroutine CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)

#define F90_BOOST_LEVEL_CHECK1T3ADIM1(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,1D,_)

#define F90_BOOST_LEVEL_CHECK1T3ADIM1_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,1D,_) (NAME1,NAME2,tolerance) ; \
         TYPE(KIND=CTYPE), dimension(:), intent(in) :: NAME1, NAME2;  \
         TYPE(KIND=CTYPE), intent(in) :: tolerance;  \
         integer :: i, n ; \
         n = size( NAME1) ; \
         if ( n .ne. size( NAME2) ) then ; \
           call F90_BOOST_TEST_MESSAGE("arrays of different size, abording ...") ; \
           return ; \
         endif ; \
         do i = 1, n ; \
          call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)( NAME1(i), NAME2(i), tolerance) ; \
         enddo ; \
     end subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,1D,_)

#define F90_BOOST_LEVEL_CHECK1T3ADIM2(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     module procedure CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,2D,_)

#define F90_BOOST_LEVEL_CHECK1T3ADIM2_IMPLEMENT(LEVEL,WHAT,TYPE,CTYPE,NAME1,NAME2) \
     subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,2D,_) (NAME1,NAME2,tolerance) ; \
         TYPE(KIND=CTYPE), dimension(:,:), intent(in) :: NAME1, NAME2;  \
         TYPE(KIND=CTYPE), intent(in) :: tolerance;  \
         integer :: i, j, n(2) ; \
         n = shape( NAME1) ; \
         if ( ANY( n .ne. shape( NAME2)) ) then ; \
           call F90_BOOST_TEST_MESSAGE("arrays of different shape, abording ...") ; \
           return ; \
         endif ; \
         do i = 1, n(1) ; \
           do j = 1, n(2) ; \
             call CONCAT4(c_BOOST,LEVEL,WHAT,CTYPE,_)( NAME1(i,j), NAME2(i,j), tolerance ) ; \
           enddo ; \
         enddo ; \
     end subroutine CONCAT5(F90_BOOST,LEVEL,WHAT,CTYPE,2D,_)

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

#endif // F90TW_DEFS_BOOST_H