add_module(
    NAME Game
    TYPE STATIC
    SOURCES
        Game.cpp
    DEPENDENCIES
        raylib
        World
)
