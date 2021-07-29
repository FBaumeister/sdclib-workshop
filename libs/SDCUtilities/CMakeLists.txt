# Current Target
set( CURRENT_TARGET_NAME SDCUtilities )
# Add this for better project structure after cmake generation
project(${CURRENT_TARGET_NAME})

message(STATUS "Adding Target ${CURRENT_TARGET_NAME}...")
add_library(${CURRENT_TARGET_NAME} STATIC "")

# Variables for better handling
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src/${CURRENT_TARGET_NAME})
set(INCLUDE_DIR_ROOT ${CMAKE_CURRENT_LIST_DIR}/include)
set(INCLUDE_DIR ${INCLUDE_DIR_ROOT}/${CURRENT_TARGET_NAME})


set(TARGET_PUBLIC_HEADERS   ${INCLUDE_DIR}/SDCUtilities_fwd.h
                            ${INCLUDE_DIR}/Prerequisites.h
                            ${INCLUDE_DIR}/Consumer.h
                            ${INCLUDE_DIR}/ConnectionLostHandlerImpl.h
                            # ...
)


# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        ${SRC_DIR}/Consumer.cpp
        ${SRC_DIR}/ConnectionLostHandlerImpl.cpp
    PUBLIC
        ${TARGET_PUBLIC_HEADERS}
)


# PRIVATE Include Dirs
target_include_directories(${CURRENT_TARGET_NAME} PRIVATE ${INCLUDE_DIR})
# PUBLIC Include Dirs
target_include_directories(${CURRENT_TARGET_NAME} PUBLIC ${INCLUDE_DIR_ROOT})
# Additional include directories
# ...


################################################################################################################################

# Note: Just copy pasted in all deps -> cluttered. Refactor that!

# Threads
target_link_libraries(${CURRENT_TARGET_NAME} PUBLIC Threads::Threads)
# OpenSSL
target_link_libraries(${CURRENT_TARGET_NAME} PUBLIC ${OPENSSL_LIBRARIES})
# SDCLib
target_link_libraries(${CURRENT_TARGET_NAME} PUBLIC ${SDCLib_LIBRARIES})
target_include_directories(${CURRENT_TARGET_NAME} PUBLIC ${SDCLib_INCLUDE_DIRS})
target_compile_definitions(${CURRENT_TARGET_NAME} PUBLIC ${SDCLib_DEFINITIONS})
# SDCLib Deps
target_link_libraries(${CURRENT_TARGET_NAME} PUBLIC ${SDCLib_DEPS_LIBRARIES})
target_include_directories(${CURRENT_TARGET_NAME} PUBLIC ${SDCLib_DEPS_INCLUDE_DIRS})
target_compile_definitions(${CURRENT_TARGET_NAME} PUBLIC ${SDCLib_DEPS_DEFINITIONS})

################################################################################################################################

# Build and Install properties
include(cmake_utils)
ApplyTargetProperties(${CURRENT_TARGET_NAME})


# install
ApplyInstallProperties(${CURRENT_TARGET_NAME})
install(DIRECTORY ${RUNTIME_CFG_PATH} DESTINATION ${PATH_INSTALL_RUNTIME}/)

# ...

