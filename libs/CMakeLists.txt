
# Enable submodules to build

list(APPEND ENABLED_SUBMODULES "SDCUtilities")

list(APPEND ENABLED_SUBMODULES "BasicProvider")
list(APPEND ENABLED_SUBMODULES "Discover")
list(APPEND ENABLED_SUBMODULES "MetricProvider")

# ...

foreach(submodule ${ENABLED_SUBMODULES})
    add_subdirectory(${submodule})
endforeach()
