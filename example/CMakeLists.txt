# buld fortran project (i.e. fortran functionality to be tested )
add_library( example STATIC example.f90 )
set_property( TARGET example PROPERTY POSITION_INDEPENDENT_CODE ON)

if ( USEBOOST )

    F90TWTEST ( test_example_boost 
        CFILES test_example_boost.cpp
        FPPFILES test_module_example_boost.fpp
        OUTDIR "${CMAKE_CURRENT_BINARY_DIR}"
        EXE ${FPP_EXE} OPTIONS ${FPP_OPTIONS} SWITCH ${FPP_SWITCH}
        INCLUDES ${f90tw_INCLUDE_DIR}
        MODULES ${f90tw_MODULES_DIR}
        LIBRARIES example f90tw_boost
        DEFINITIONS USEBOOST
    )

endif()

if ( USEGTEST )

    F90TWTEST ( test_example_gtest 
        CFILES test_example_gtest.cpp
        FPPFILES test_module_example_gtest.fpp
        OUTDIR "${CMAKE_CURRENT_BINARY_DIR}"
        EXE ${FPP_EXE} OPTIONS ${FPP_OPTIONS} SWITCH ${FPP_SWITCH}
        INCLUDES ${f90tw_INCLUDE_DIR}
        MODULES ${f90tw_MODULES_DIR}
        LIBRARIES example f90tw_gtest
        DEFINITIONS USEGTEST
    )

endif()
