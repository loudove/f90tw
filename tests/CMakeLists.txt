if ( USEBOOST )

    F90TWTEST ( testboost 
        CFILES testboost.cpp
        FPPFILES testboost.fpp
        F2HFILES ${f90tw_MODULES_DIR}/assertions_boost.f90
        OUTDIR "${CMAKE_CURRENT_BINARY_DIR}"
        EXE ${FPP_EXE} OPTIONS ${FPP_OPTIONS} SWITCH ${FPP_SWITCH}
        INCLUDES ${f90tw_INCLUDE_DIR} "${CMAKE_CURRENT_BINARY_DIR}"
        MODULES ${f90tw_MODULES_DIR}
        LIBRARIES f90tw_boost
        DEFINITIONS USEBOOST
    )

endif()

if ( USEGTEST )

    F90TWTEST ( testgtest 
        CFILES testgtest.cpp
        FPPFILES testgtest.fpp
        F2HFILES ${f90tw_MODULES_DIR}/assertions_gtest.f90
        OUTDIR "${CMAKE_CURRENT_BINARY_DIR}"
        EXE ${FPP_EXE} OPTIONS ${FPP_OPTIONS} SWITCH ${FPP_SWITCH}
        INCLUDES ${f90tw_INCLUDE_DIR} "${CMAKE_CURRENT_BINARY_DIR}"
        MODULES ${f90tw_MODULES_DIR}
        LIBRARIES f90tw_gtest
        DEFINITIONS USEGTEST
    )

endif()
