# cmake version
cmake_minimum_required(VERSION 3.5.0)

################################################################################
# Some utility functions so ease the use with cmake in target files
# WARNING: Heavily dependend on preset variables!
################################################################################


################################################################################
# Target Properties
################################################################################
function(ApplyTargetProperties Target)

set_target_properties(  ${Target}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${PATH_RUNTIME_OUTPUT}
                        LIBRARY_OUTPUT_DIRECTORY ${PATH_LIBRARY_OUTPUT}
                        ARCHIVE_OUTPUT_DIRECTORY ${PATH_ARCHIVE_OUTPUT}
                        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
                        LINKER_LANGUAGE CXX
                        )

target_compile_definitions( ${Target}	PUBLIC ${GLOBAL_COMPILE_DEFINITIONS} )
target_compile_options( ${Target}		PUBLIC ${GLOBAL_COMPILE_OPTIONS} )

endfunction()
################################################################################


################################################################################
# INSTALL
################################################################################
function(ApplyInstallProperties Target)

install(TARGETS ${Target} CONFIGURATIONS ${CMAKE_BUILD_TYPE}
            RUNTIME DESTINATION ${PATH_INSTALL_RUNTIME}
            ARCHIVE DESTINATION ${PATH_INSTALL_ARCHIVE}
)

endfunction()
################################################################################
