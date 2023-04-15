add_module(
    NAME Game
    TYPE STATIC
    SOURCES
        Game.cpp
    DEPENDENCIES
        Common
        raylib
        World
    SYSTEM_INCLUDES
        ${PROJECT_SOURCE_DIR}/lib/raygui/src
        ${PROJECT_SOURCE_DIR}/lib/raygui/styles
)
