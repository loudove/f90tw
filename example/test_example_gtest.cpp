/* set the fpp where the tests are implemented in fortran
// using the f90tw macros to indicate the structure. the
// file will be preprocessed using the appropriate macros
// (defined in f90tw_gtest) and essentially wrapping the 
// Fortran tests subroutines to result in the corresponding
// c/c++ implementation of the gtest fwk. 
// NOTE that the USEGTEST preprocessor definition must be
// used to activate the correct macros. */
#define CURRENTTESTFILE "test_module_example_gtest.fpp"

#include "f90tw_gtest.h"
