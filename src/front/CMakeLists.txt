add_module(
    NAME Front
    TYPE STATIC
    SOURCES
        Front.cpp
    DEPENDENCIES
        Common
        raylib
        World
    SYSTEM_INCLUDES
        ${PROJECT_SOURCE_DIR}/lib/raygui/src
        ${PROJECT_SOURCE_DIR}/lib/raygui/styles
)
