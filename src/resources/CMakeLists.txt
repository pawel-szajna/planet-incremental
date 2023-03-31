set(MODULE Resources)

add_library(
        ${MODULE}
        INTERFACE
)

target_include_directories(
        ${MODULE}
        INTERFACE
        include
)

add_ut(
        TESTED_MODULE ${MODULE}
        SOURCES
        TrackedTests.cpp
)
