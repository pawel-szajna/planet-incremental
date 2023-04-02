add_subdirectory(world)
add_subdirectory(resources)

add_module(
    NAME game
    TYPE EXECUTABLE
    SOURCES
        main.cpp
)
