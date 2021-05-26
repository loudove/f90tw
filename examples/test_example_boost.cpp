/* set the fpp where the tests are implemented in fortran
// using the f90tw macros to indicate the structure. the
// file will be preprocessed using the appropriate macros
// (defined in f90tw_boost) and essentially wrapping the 
// Fortran tests subroutines to result in the corresponding
//  c/c++ implementation of the boost.test fwk. */
#define CURRENTTESTFILE "test_example_boost.fpp"

#include "f90tw_boost.h"
