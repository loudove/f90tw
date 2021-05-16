# check if FILENAME is an absolute path and 
# return the absolute path of the file and 
# the container directory
function ( F90TWCHKPATH FILENAME RETFILENAMEFULL RETFILEDIRECTORY )

    get_filename_component( filedir "${FILENAME}" DIRECTORY )
    if ( "${filedir}" STREQUAL "" )
        set ( ${RETFILENAMEFULL} "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}" PARENT_SCOPE )
        set ( ${RETFILEDIRECTORY} "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE )
    else()
        string ( FIND ${filedir} ${CMAKE_CURRENT_SOURCE_DIR} chk )
        if ( chk EQUAL -1 )
            set ( ${RETFILENAMEFULL} "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}" PARENT_SCOPE )
            set ( ${RETFILEDIRECTORY} "${CMAKE_CURRENT_SOURCE_DIR}/${filedir}" PARENT_SCOPE )
        else()
            set ( ${RETFILENAMEFULL} ${FILENAME} PARENT_SCOPE )
            set ( ${RETFILEDIRECTORY} ${dir} PARENT_SCOPE )
        endif()
    endif()
endfunction()

# preprocess a fortran source file.
# INFILE, OUTFILE : the input and the output files
# EXE, SWITCH : the preprocessor executable and arguments switch
# OPTIONS, INCLUDES DEFINITIONS : the preprocessor options, include
#           directories and definitions
function( F90TWFPP INFILE OUTFILE )

    set( prefix FPP )
    set( flags )
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

    set( FPPOPTS "${FPP_OPTIONS}" )
    set( FPPDEFS "${DEFS}" )
    set( FPPINCL "${INCL}" )
    if(CMAKE_SYSTEM_NAME STREQUAL Windows)
        find_program ( POWERSHELL_EXE NAMES "powershell.exe" REQUIRED)
        add_custom_command(
            OUTPUT ${OUTFILE}
            COMMAND ${POWERSHELL_EXE} -Command " \" ( ${FPP_EXE} ${FPPOPTS} ${FPPDEFS} ${FPPINCL} ${INFILE})  -replace ';', \\\"`n\\\" | select-string -pattern '^#' -notmatch | Set-Content -Path ${OUTFILE} \" "
            DEPENDS ${INFILE}
            COMMENT "precompile ${INFILE}"
        )
    else()
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

# preprocess several fortran source file.
# INFILES : a list of files to be preprocessed
# OUTFILE : for each input file, the output will placed in ${OUTDIR}/${basefilename}.f90
# the rest of the arguments are the arguments of F90TWFPP function.

function( F90TWFPPFILES )

    set( prefix FPP )
    set( flags )
    set( singleValues EXE SWITCH OUTDIR )
    set( multiValues INFILES OUTFILES OPTIONS INCLUDES DEFINITIONS )

    include(CMakeParseArguments)
    cmake_parse_arguments(PARSE_ARGV 0 ${prefix}
                     "${flags}"
                     "${singleValues}"
                     "${multiValues}"
        )

    list( LENGTH FPP_OUTFILES outlen )
    list( LENGTH FPP_INFILES inlen )
    # if the list of the output files is not given the create
    # it based on the given input files.
    if ( NOT ${outlen} EQUAL ${inlen} )
        foreach( fppinfile ${FPP_INFILES} )
            get_filename_component( f90filename "${fppinfile}" NAME_WE  )
            set ( f90file "${FPP_OUTDIR}/${f90filename}.f90")
            list ( APPEND OUTFILES ${dir} )
        endforeach()
    else()
        set ( OUTFILES ${FPP_OUTFILES} )
    endif()

    # setup files preprocessing
    math(EXPR len "${inlen} - 1")
    foreach( val RANGE ${len})
        list( GET FPP_INFILES  ${val} fppfile )
        list( GET OUTFILES  ${val} f90file )
        F90TWFPP ( "${fppfile}" "${f90file}"
            EXE ${FPP_EXE}
            SWITCH ${FPP_SWITCH}
            OPTIONS ${FPP_OPTIONS}
            INCLUDES ${FPP_INCLUDES}
            DEFINITIONS ${FPP_DEFINITIONS}
        )
    endforeach()

endfunction()

# setup a F90TWTEST
# F90TWFWK : framework to be used (boost|gtest)
# CFILES : list of c/c++ files
# F90FILES : list of fortran files
# FPPFILES : list of fortran files to be preprocessed (using f90tw)
# MODULES : list of modules direactories
# the rest of the arguments are the arguments of F90TWFPP and F90TWFPPFILES functions.
function( F90TWTEST NAME )

    set( prefix FTW )
    set( flags )
    set( singleValues F90TWFWK EXE SWITCH OUTDIR )
    set( multiValues CFILES F90FILES FPPFILES OPTIONS LIBRARIES INCLUDES MODULES DEFINITIONS )

    include(CMakeParseArguments)
    cmake_parse_arguments(PARSE_ARGV 1 ${prefix}
                    "${flags}"
                    "${singleValues}"
                    "${multiValues}"
        )

    # create the fortran library
    foreach( fppinfile ${FTW_FPPFILES} )
        get_filename_component( f90filename "${fppinfile}" NAME_WE  )
        get_filename_component( fppfilename "${fppinfile}" NAME  )

        F90TWCHKPATH ( ${fppinfile} fppinfilefull fppinfiledir )
        list ( FIND FPPINCLDS ${fppinfiledir} chk )
        if ( chk EQUAL -1 )
          list ( APPEND FPPINCLDS ${fppinfiledir} )
        endif()        


        set ( f90file "${FTW_OUTDIR}/${f90filename}.f90")
        list ( APPEND XF90FILES ${f90file} )
        list ( APPEND XFPPFILES ${fppinfilefull} )
    endforeach()
    F90TWFPPFILES (
        INFILES ${XFPPFILES} OUTFILES ${XF90FILES}
        EXE ${FTW_EXE} OPTIONS ${FTW_OPTIONS}  SWITCH ${FTW_SWITCH}
        INCLUDES ${FTW_INCLUDES} DEFINITIONS ${FTW_DEFINITIONS}
    )

    set ( FLIBNAME "${NAME}_f90" )
    add_library ( "${FLIBNAME}" STATIC ${XF90FILES} ${FTW_F90FILES} )
    set_property( TARGET ${FLIBNAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
    target_include_directories( ${FLIBNAME} PRIVATE ${FTW_INCLUDES} ${FTW_MODULES} )
    set_target_properties( ${FLIBNAME} PROPERTIES Fortran_MODULE_DIRECTORY ${FTW_MODULES} )
    set_property( TARGET ${FLIBNAME}
        APPEND PROPERTY ADDITIONAL_CLEAN_FILES ${XF90FILES}
    )
    target_link_libraries( ${FLIBNAME} PUBLIC ${FTW_LIBRARIES} )

    # compile c and create the executable
    add_executable( ${NAME} ${FTW_CFILES}  )
    target_include_directories( ${NAME} PRIVATE ${FPPINCLDS} ${FTW_INCLUDES} )
    target_link_libraries( ${NAME} ${FLIBNAME} ${FTW_LIBRARIES})
    target_compile_definitions( ${NAME} PUBLIC ${FTW_DEFINITIONS} )

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
    set( FPP_ID LLVM )
    set( FPP_OPTIONS -cc1 -E )
    set( FPP_SWITCH - )
elseif( FPP_EXE MATCHES "cpp*" )
    set( FPP_ID GNU )
    set( FPP_OPTIONS -E )
    set( FPP_SWITCH - )
else()
    set( FPP_ID MSVC )
    set( FPP_OPTIONS /E )
    set( FPP_SWITCH / )
endif()

# make available the preprocessor and the options through the FPP_ID and FPP_OPTIONS variables
set( FPP_ID ${FPP_ID} CACHE STRING "preprocessor id" )
set( FPP_OPTIONS ${FPP_OPTIONS} CACHE STRING "preprocessor options" )
set( FPP_SWITCH ${FPP_SWITCH} CACHE STRING "preprocessor switch" )

message( STATUS "Found cpp: ${FPP_EXE} of ${FPP_ID} flavor" )

if ( USEBOOST )
    # on windows the save vs project can't handle both c++ and f90 files
    # this is why to different libraries are created. moreover the f90twi
    # should be OBJECT library since only the module file are needed for
    # using the f90tw functionality. Nevertheless, this is not the case
    # due to a bug, possibly in ifort compiler, is will leads to buil
    # failure during the first attemp.

    add_library( f90tw_boost STATIC boost_assertions.cpp )
    set_property ( TARGET f90tw_boost PROPERTY POSITION_INDEPENDENT_CODE ON)
    target_include_directories( f90tw_boost PUBLIC ${Boost_INCLUDE_DIRS} )
    target_link_libraries( f90tw_boost PUBLIC ${Boost_LIBRARIES} )

    set ( file1fpp "${CMAKE_CURRENT_SOURCE_DIR}/assertions_boost.fpp" )
    set ( file1 "${CMAKE_CURRENT_BINARY_DIR}/assertions_boost.f90" )
    add_library( f90twi_boost OBJECT "${file1}"  )
    set_property( TARGET f90twi_boost
        APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${file1}"
    )

    F90TWFPP( "${file1fpp}" "${file1}"
        EXE ${FPP_EXE}
        OPTIONS ${FPP_OPTIONS}
        SWITCH ${FPP_SWITCH}
    )
    add_dependencies( f90tw_boost f90twi_boost )
endif()

if ( USEGTEST )

    add_library( f90tw_gtest STATIC gtest_assertions.cpp )
    set_property ( TARGET f90tw_gtest PROPERTY POSITION_INDEPENDENT_CODE ON)
    target_include_directories( f90tw_gtest PUBLIC ${gtest_INCLUDE_DIR} )
    target_link_libraries( f90tw_gtest PUBLIC gtest_main )
    target_compile_definitions( f90tw_gtest PUBLIC USEGTEST)


    set ( file2fpp "${CMAKE_CURRENT_SOURCE_DIR}/assertions_gtest.fpp" )
    set ( file2 "${CMAKE_CURRENT_BINARY_DIR}/assertions_gtest.f90" )
    add_library( f90twi_gtest OBJECT "${file2}" )
    set_property( TARGET f90twi_gtest
            APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${file2}"
    )

    F90TWFPP ( "${file2fpp}" "${file2}"
        EXE ${FPP_EXE}
        OPTIONS ${FPP_OPTIONS}
        SWITCH ${FPP_SWITCH}
        DEFINITIONS USEGTEST
    )
    add_dependencies( f90tw_gtest f90twi_gtest )
endif()

# make available the include and modulee paths
set( f90tw_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "f90tw include directory" )
set( f90tw_MODULES_DIR ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "f90tw modules/libraries directory" )
