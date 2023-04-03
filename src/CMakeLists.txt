add_subdirectory(game)
add_subdirectory(world)
add_subdirectory(resources)
add_subdirectory(statistics)

add_module(
    NAME incremental
    TYPE EXECUTABLE
    SOURCES
        main.cpp
    DEPENDENCIES
        Game
)
