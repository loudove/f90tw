# check
# https://crascit.com/2017/04/18/generated-sources-in-cmake-builds/
# https://community.intel.com/t5/Intel-Fortran-Compiler/string-concatenation-bug/td-p/741447
# https://stackoverflow.com/questions/56514533/how-to-specify-the-output-directory-of-a-given-dll

# buld fortran project (i.e. fortran functionality to be tested ) 
add_library( example STATIC example.f90 )

set_property( TARGET example PROPERTY POSITION_INDEPENDENT_CODE ON)

# compile the fortran tests in one library
add_library( test_example_boost_f90 STATIC ${CMAKE_CURRENT_BINARY_DIR}/test_module_example_boost.f90 )
set_property( TARGET test_example_boost_f90 PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories( test_example_boost_f90 PRIVATE ${f90tw_INCLUDE_DIR} ${f90tw_MODULES_DIR} )
set_target_properties( test_example_boost_f90 PROPERTIES Fortran_MODULE_DIRECTORY ${f90tw_MODULES_DIR} )
set_property(
        TARGET test_example_boost_f90
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/test_module_example_boost.f90
)
FORTRANFPP ( 
    "${CMAKE_CURRENT_SOURCE_DIR}/test_module_example_boost.fpp"
    "${CMAKE_CURRENT_BINARY_DIR}/test_module_example_boost.f90"
    EXE ${FPP_EXE}
    OPTIONS ${FPP_OPTIONS}
    SWITCH ${FPP_SWITCH}
    INCLUDES ${f90tw_INCLUDE_DIR}   
)
target_link_libraries( test_example_boost_f90 example f90tw_boost )
# add_dependencies( test_example_boost_f90 f90tw_boost)

# create the test exe from the cpp
add_executable( test_example_boost test_example_boost.cpp  )
target_include_directories( test_example_boost PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${f90tw_INCLUDE_DIR} ${f90tw_MODULES_DIR} )
target_link_libraries( test_example_boost f90tw_boost test_example_boost_f90 ${Boost_LIBRARIES} )

# compile the fortran tests in one library
add_library( test_example_gtest_f90 STATIC ${CMAKE_CURRENT_BINARY_DIR}/test_module_example_gtest.f90 )
set_property( TARGET test_example_gtest_f90 PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories( test_example_gtest_f90 PRIVATE ${f90tw_INCLUDE_DIR} ${f90tw_MODULES_DIR} )
set_target_properties( test_example_gtest_f90 PROPERTIES Fortran_MODULE_DIRECTORY ${f90tw_MODULES_DIR} )
set_property(
        TARGET test_example_gtest_f90
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/test_module_example_gtest.f90
)

FORTRANFPP ( 
    "${CMAKE_CURRENT_SOURCE_DIR}/test_module_example_gtest.fpp"
    "${CMAKE_CURRENT_BINARY_DIR}/test_module_example_gtest.f90"
    EXE ${FPP_EXE}
    OPTIONS ${FPP_OPTIONS}
    SWITCH ${FPP_SWITCH}
    INCLUDES ${f90tw_INCLUDE_DIR}
    DEFINITIONS USEGTEST
)

target_link_libraries( test_example_gtest_f90 example f90tw_gtest )
# add_dependencies( test_example_gtest_f90 f90tw_gtest)

# create the test exe from the cpp
add_executable( test_example_gtest test_example_gtest.cpp  )
target_include_directories( test_example_gtest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${f90tw_INCLUDE_DIR} ${gtest_INCLUDE_DIR} )
target_link_libraries( test_example_gtest f90tw_gtest test_example_gtest_f90 gtest_main )
target_compile_definitions( test_example_gtest PUBLIC USEGTEST)

# add it to the test suite 
# add_test(NAME test_module COMMAND test_example)
