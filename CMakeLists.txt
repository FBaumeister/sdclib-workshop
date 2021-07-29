#Minimum Cmake Version
cmake_minimum_required(VERSION 3.10)


################################################################################
# Using own CMake Modules
################################################################################
get_filename_component(PROJECT_CMAKE_MODULES ${CMAKE_CURRENT_LIST_DIR}/tools/cmake/Modules REALPATH)
message(STATUS "Adding ${PROJECT_CMAKE_MODULES} to Modules Path...")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_CMAKE_MODULES})
################################################################################

################################################################################
# C++ standard
################################################################################
message(STATUS "Setting CXX_STANDARD...")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
################################################################################


################################################################################
# Main Project
################################################################################
set( PROJECT_NAME "Workshop")
project(${PROJECT_NAME})
################################################################################


################################################################################
# Check Compiler Version
################################################################################
include(checkRequiredCompilerCXX14)
################################################################################


################################################################################
# Set Variables for Compile definitions and options
# Setting Variables: GLOBAL_COMPILE_DEFINITIONS and GLOBAL_COMPILE_OPTIONS
################################################################################
include(definitions_and_options)
include(cmake_utils)
################################################################################


################################################################################
# Targets
# Overwrite
################################################################################
set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Config Types")
# None specified?
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type specified, setting to Debug.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Debug as default" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug")
endif()
################################################################################


################################################################################
# RPATH Settings
# NOTE: Set the RPath to the "Current Directory". (Portability)
################################################################################
include(reset_RPATH)
################################################################################


################################################################################
# Bin and Install prefix
################################################################################
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "Default install prefix init to default, manually setting one...")
    set (CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install CACHE STRING "Where to install the binaries?" FORCE)
endif()

# Note: https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_DIRECTORY.html
#		"Multi-configuration generators (VS, Xcode) append a per-configuration
#		subdirectory to the specified directory unless a generator expression is used."
#		-> Append empty generator expression.
#
#		Use the _ROOT Version for all processes during "configure" phase (like configure_file)
#		Use the other Version for all processes during "generator" phase
set(PATH_RUNTIME_OUTPUT_ROOT ${CMAKE_BINARY_DIR}/bin)
set(PATH_LIBRARY_OUTPUT_ROOT ${CMAKE_BINARY_DIR}/bin)
set(PATH_ARCHIVE_OUTPUT_ROOT ${CMAKE_BINARY_DIR}/lib)
set(PATH_RUNTIME_OUTPUT ${PATH_RUNTIME_OUTPUT_ROOT}/$<0:>)
set(PATH_LIBRARY_OUTPUT ${PATH_LIBRARY_OUTPUT_ROOT}/$<0:>)
set(PATH_ARCHIVE_OUTPUT ${PATH_ARCHIVE_OUTPUT_ROOT}/$<0:>)

# Create folders manually
# Prevents errors under certain configurations with CTest and missing directories not being
# created by default
file(MAKE_DIRECTORY ${PATH_RUNTIME_OUTPUT_ROOT})
file(MAKE_DIRECTORY ${PATH_LIBRARY_OUTPUT_ROOT})
file(MAKE_DIRECTORY ${PATH_ARCHIVE_OUTPUT_ROOT})


set(CMAKE_DEBUG_POSTFIX _d) # Force the Debug Postfix

# by "default" take the install prefix
set(PATH_INSTALL_RUNTIME bin/$<0:>)
set(PATH_INSTALL_LIBRARY bin/$<0:>)
set(PATH_INSTALL_ARCHIVE lib/$<0:>)
set(PATH_INSTALL_INCLUDE include/$<0:>)

################################################################################
# Some more pathes - cleaned from symlinks
################################################################################
get_filename_component(EXTERNAL_ROOT ${CMAKE_SOURCE_DIR}/external/ REALPATH)
################################################################################


################################################################################
# Threads
################################################################################
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
################################################################################


################################################################################
# SDCLib
################################################################################
# Here we have to specify the SDC Folders root path
################################################################################
set(SDCLib_SEARCH_DIRS "${EXTERNAL_ROOT}/sdclib" CACHE STRING "SDCLib root dir")
# Out of Source build

# !WORKSHOP!
set(SDCLib_ADDITIONAL_LIBRARY_DIRS "${EXTERNAL_ROOT}/sdclib_build/bin" CACHE STRING "Additional Dirs")


# !WORKSHOP!
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${EXTERNAL_ROOT}/sdclib/cmake/Modules")
set(SDCLib_EXTERNAL_LIBRARY_DIRS ${EXTERNAL_ROOT}/sdclib_build/bin)

set(SDCLib_DYNAMIC_LINKING ON)
find_package(SDCLib)
if(NOT SDCLib_FOUND)
    message(FATAL_ERROR "SDC not found, build it first or specify correct path!")
endif()
################################################################################


# proceed to submodules
add_subdirectory(libs)

