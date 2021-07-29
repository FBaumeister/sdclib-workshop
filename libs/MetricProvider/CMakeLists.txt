# Current Target
set( CURRENT_TARGET_NAME MetricProvider )
# Add this for better project structure after cmake generation
project(${CURRENT_TARGET_NAME})

message(STATUS "Adding Target ${CURRENT_TARGET_NAME}...")
add_executable(${CURRENT_TARGET_NAME} "")

# Variables for better handling
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})

# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/MetricProvider.cpp
        ${SRC_DIR}/MetricProvider.h
)

# PRIVATE Include Dirs
target_include_directories(${CURRENT_TARGET_NAME} PRIVATE ${INCLUDE_DIR})


################################################################################################################################

# SDC
target_link_libraries(${CURRENT_TARGET_NAME} PUBLIC SDCUtilities)

################################################################################################################################


# Build and Install properties
include(cmake_utils)
ApplyTargetProperties(${CURRENT_TARGET_NAME})


# install
ApplyInstallProperties(${CURRENT_TARGET_NAME})
install(DIRECTORY ${RUNTIME_CFG_INSTALL_PATH} DESTINATION ${PATH_INSTALL_RUNTIME}/)


configure_file(${SRC_DIR}/referenceMDIB.xml ${PATH_RUNTIME_OUTPUT_ROOT}/referenceMDIB.xml COPYONLY)

# ...

