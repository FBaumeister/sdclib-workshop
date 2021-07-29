# cmake version
cmake_minimum_required(VERSION 3.5.0)

################################################################################
# Set compile definitions and options
# Variable naming is ${GLOBAL_COMPILE_DEFINITIONS}
# Variable naming is ${GLOBAL_COMPILE_OPTIONS}
################################################################################

################################################################################
# Compile Definitions
################################################################################
list(APPEND ${GLOBAL_COMPILE_DEFINITIONS} $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:linux _LINUX >)
################################################################################

################################################################################
# Compile Options
################################################################################
# Debug Flags
list(APPEND ${GLOBAL_COMPILE_OPTIONS} $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-ggdb -g>)
# Warnings
list(APPEND ${GLOBAL_COMPILE_OPTIONS} $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Wconversion -Wshadow -Wnon-virtual-dtor -pedantic>)
# Optimization
list(APPEND ${GLOBAL_COMPILE_OPTIONS} $<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O3>)
list(APPEND ${GLOBAL_COMPILE_OPTIONS} $<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O0>)
################################################################################

