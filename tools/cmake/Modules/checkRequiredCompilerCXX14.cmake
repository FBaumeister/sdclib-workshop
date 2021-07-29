# cmake version
cmake_minimum_required(VERSION 3.5.0)

################################################################################
# Check Compiler Version
# Min Requirements chosen based on C++14
################################################################################
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
        message(FATAL_ERROR "GCC version must be at least 5.1!")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4)
        message(FATAL_ERROR "Clang version must be at least 3.4!")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
        message(FATAL_ERROR "MSVC version must be at least 19.0!")
    endif()
else()
    message(FATAL_ERROR "No supported Compiler detected. Checked for GCC(5.1+), Clang(3.4+) or MSVC(19.0+).")
endif()

################################################################################
