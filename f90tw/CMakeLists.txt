cmake_minimum_required(VERSION 2.8.12)

project( f90tw LANGUAGES CXX Fortran )

# preprocess a fortran source file.
# INFILE, OUTFILE : the input and the output files
# FPPEXE : the preprocessor
# FPPOPTIONS : the preprocessor options
# Note that the rest of the arguments will be considers as the preprocessor options.

function( FORTRANFPP INFILE OUTFILE )

    set( prefix FPP )
    set( flags CURRENT )
    set( singleValues EXE SWITCH)
    set( multiValues OPTIONS INCLUDES DEFINITIONS )

    include(CMakeParseArguments)
    cmake_parse_arguments(PARSE_ARGV 2 ${prefix}
                     "${flags}"
                     "${singleValues}"
                     "${multiValues}"
        )

    foreach( dir ${FPP_INCLUDES} )
        string ( PREPEND dir ${FPP_SWITCH} I )
        list ( APPEND INCL ${dir} )
    endforeach()
    foreach( def ${FPP_DEFINITIONS} )
        string ( PREPEND def ${FPP_SWITCH} D )
        list ( APPEND DEFS ${def} )
    endforeach()

    if(CMAKE_SYSTEM_NAME STREQUAL Windows)
        string( REPLACE ";" " " FPPOPTS "${FPP_OPTIONS}" )
        string( REPLACE ";" " " FPPDEFS "${DEFS}" )
        string( REPLACE ";" " " FPPINCL "${INCL}" )      
        find_program ( POWERSHELL_EXE NAMES "powershell.exe" REQUIRED)
        add_custom_command(
            OUTPUT ${OUTFILE}
            COMMAND ${POWERSHELL_EXE} -Command " \" ( ${FPP_EXE} ${FPPOPTS} ${FPPDEFS} ${FPPINCL} ${INFILE})  -replace ';', \\\"`n\\\" | select-string -pattern '^#' -notmatch | Set-Content -Path ${OUTFILE} \" "
            DEPENDS ${INFILE}
            COMMENT "precompile ${INFILE}"
        )
    else()
        set( FPPOPTS "${FPP_OPTIONS}" )
        set( FPPDEFS "${DEFS}" )
        set( FPPINCL "${INCL}" )      
        find_program ( SED_EXE NAMES "sed" REQUIRED)
        find_program ( TR_EXE NAMES "tr" REQUIRED)
        add_custom_command(
            OUTPUT ${OUTFILE}
            COMMAND ${FPP_EXE} ${FPPOPTS} ${FPPDEFS} ${FPPINCL} ${INFILE} | ${SED_EXE} \"/\#/d\" | ${TR_EXE} \"\;\" \"\\n\" > ${OUTFILE}
            DEPENDS ${INFILE}
            COMMENT "precompile ${INFILE}"
        )
    endif()

endfunction()

# resolve the preprocessor to be used. it is assumed that on unix bases systems
# cpp or clang  will be found in the path and in addition, on windows based
# systems, cl.exe may be abailable. On mac os cpp in interface to clang with
# "-traditional-cpp" locked. To avoid this we use directly the clang frond end.
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    find_program ( FPP_EXE NAMES cpp.exe clang.exe cl.exe REQUIRED )
else()
    find_program ( FPP_EXE NAMES clang cpp REQUIRED )
endif()

# we have prioritized clang in find_program. otherwise we
# have to chech the cpp flavor and swtch to clang in the
# of LLVM where the option "-traditional-cpp" is locked
execute_process(
    COMMAND ${FPP_EXE} --version
    OUTPUT_VARIABLE FPPEXETMP
)
if ( FPPEXETMP MATCHES LLVM AND ( NOT FPP_EXE MATCHES clang ) )
    unset( FPP_EXE CACHE)
    find_program ( FPP_EXE NAMES clang REQUIRED)
endif()

# resolve preprocessor options
if (NOT FPP_EXE)
    message (FATAL_ERROR "C preprocessor was not found")
elseif ( FPP_EXE MATCHES "clang*" )
    set( FPP_ID "LLVM" )
    set( FPP_OPTIONS -cc1 -E )
    set( FPP_SWITCH - )
elseif( FPP_EXE MATCHES "cpp*" )
    set( FPP_ID "GNU" )
    set( FPP_OPTIONS -E )
    set( FPP_SWITCH - )
else()
    set( FPP_ID "MSVC" )
    set( FPP_OPTIONS /E )
    set( FPP_SWITCH / )
endif()

# make available the preprocessor and the options through the FPP_ID and FPP_OPTIONS variables
set( FPP_ID ${FPP_ID} PARENT_SCOPE)
set( FPP_OPTIONS ${FPP_OPTIONS} PARENT_SCOPE)
set( FPP_SWITCH ${FPP_SWITCH} PARENT_SCOPE)

message( STATUS "Found cpp: ${FPP_EXE} of ${FPP_ID} flavor" )

add_library( f90tw_boost STATIC boost_assertions.cpp )
set_property ( TARGET f90tw_boost PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories( f90tw_boost PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries( f90tw_boost ${Boost_LIBRARIES} )

add_library( f90tw_gtest STATIC gtest_assertions.cpp )
set_property ( TARGET f90tw_gtest PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries( f90tw_gtest gtest_main )
target_compile_definitions( f90tw_gtest PUBLIC USEGTEST)

# on windows the save vs project can't handle both c++ and f90 files
# this is why to different libraries are created. moreover the f90twi
# should be OBJECT library since only the module file are needed for
# using the f90tw functionality. Nevertheless, this is not the case
# due to a bug, possibly in ifort compiler, is will leads to buil
# failure during the first attemp. 
add_library( f90twi STATIC 
    "${CMAKE_CURRENT_BINARY_DIR}/assertions_boost.f90" 
    "${CMAKE_CURRENT_BINARY_DIR}/assertions_gtest.f90" )
set_property ( TARGET f90twi PROPERTY POSITION_INDEPENDENT_CODE ON )
set_property(
        TARGET f90twi
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/assertions_boost.f90 ${CMAKE_CURRENT_BINARY_DIR}/assertions_gtest.f90
)

# split the 
# use RUNTIME_OUTPUT_DIRECTORY insead of CMAKE_CURRENT_BINARY_DIR
FORTRANFPP( 
    ${CMAKE_CURRENT_SOURCE_DIR}/assertions_boost.fpp
    ${CMAKE_CURRENT_BINARY_DIR}/assertions_boost.f90
    EXE ${FPP_EXE}
    OPTIONS ${FPP_OPTIONS}
    SWITCH ${FPP_SWITCH} 
)

FORTRANFPP ( 
    ${CMAKE_CURRENT_SOURCE_DIR}/assertions_gtest.fpp
    ${CMAKE_CURRENT_BINARY_DIR}/assertions_gtest.f90
    EXE ${FPP_EXE}
    OPTIONS ${FPP_OPTIONS}
    SWITCH ${FPP_SWITCH}
    DEFINITIONS USEGTEST
)

# make available the include and modulee paths
set ( f90tw_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE )
set ( f90tw_MODULES_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE )
