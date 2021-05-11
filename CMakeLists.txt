# set minimum cmake version (TODO check the version)
cmake_minimum_required(VERSION 2.8.12)

# project name and language
project(f90tw LANGUAGES CXX Fortran)

set (f90tw_VERSION_MAJOR "0")
set (f90tw_VERSION_MINOR "1")

# cxx requirements
# set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# f90 line length; TODO handle compilers other than GNU
set( CMAKE_Fortran_FORMAT FREE )
if ( CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
    set( CMAKE_Fortran_FLAGS ${CMAKE_Fortran_FLAGS} "-ffree-line-length-none" )
endif()

# set find_package policy
cmake_policy( SET CMP0074 NEW)
cmake_policy( SET CMP0079 NEW)

# get the options for building boost (default yes)
if ( NOT DEFINED BOOSTFWK )
    option( USEBOOST "Use boost.test fwk" ON )
else()
    set( USEBOOST ${BOOSTFWK} CACHE BOOL "Use boost.test fwk" )
endif()
# get the options for building gtest (default no)
if ( NOT DEFINED GTESTFWK )
    option( USEGTEST "Use gtest fwk" OFF )
else()
    set( USEGTEST ${GTESTFWK} CACHE BOOL "Use gtest fwk" )
endif()
# check if at least one framework is on 
if ( ( NOT USEBOOST ) AND ( NOT USEGTEST ) )
    message( SEND_ERROR "Both boost and gtest frameworks are off, nothing will happen.")
endif()
# inform
if ( USEBOOST )
    message( STATUS "Build f90tw with Boost.Test framework.")
endif()
if ( USEGTEST )
    message( STATUS "Build t90tw with gtest framework.")
endif()

# boost requirement
if ( USEBOOST )
    set (Boost_USE_MULTITHREADED ON)
    ## mingw-w64 needs this hint(s) for selecting the appropriate library
    set ( Boost_USE_STATIC_LIBS OFF)
    set ( Boost_USE_STATIC_RUNTIME OFF)
    find_package (Boost 1.62.0 REQUIRED COMPONENTS unit_test_framework)
endif()

# gtest requirement
if ( USEGTEST )
    find_package(GTest CONFIG QUIET)
    message ( STATUS "Found Gtest: ${GTest_FOUND}")
    if ( NOT Gtest_FOUND )
        message ( STATUS "Gtest: installing ...")
        #https://chromium.googlesource.com/external/github.com/pwnall/googletest/+/HEAD/googletest/README.md
        # Download and unpack googletest at configure time
        configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
        if(result)
            message(FATAL_ERROR "CMake step for googletest failed: ${result}")
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
        if(result)
            message(FATAL_ERROR "Build step for googletest failed: ${result}")
        endif()

        # Prevent overriding the parent project's compiler/linker settings on Windows
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

        # Add googletest directly to our build. This defines the gtest and gtest_main targets.
        add_subdirectory(
            ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
            ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
            EXCLUDE_FROM_ALL)

        set ( Gtest_LIBRARY_DIR ${CMAKE_BINARY_DIR}/lib )
        set ( Gtest_INCLUDE_DIR ${CMAKE_BINARY_DIR}/googletest-src/googletest/include )
    endif()
endif()

# build f90tw
add_subdirectory( f90tw )

message ( STATUS "f90tw_INCLUDE_DIR is ${f90tw_INCLUDE_DIR}" )
message ( STATUS "f90tw_MODULES_DIR is ${f90tw_MODULES_DIR}" )

# build f90tw example
add_subdirectory(example)
