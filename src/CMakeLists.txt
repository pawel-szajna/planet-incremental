add_subdirectory(common)
add_subdirectory(front)
add_subdirectory(world)
add_subdirectory(resources)
add_subdirectory(statistics)

add_module(
    NAME incremental
    TYPE EXECUTABLE
    SOURCES
        main.cpp
    DEPENDENCIES
        Common
        Front
)

if(EMSCRIPTEN)
    set(INDEX_FILE ${CMAKE_BINARY_DIR}/bin/index.html)
    add_custom_command(
        OUTPUT ${INDEX_FILE}
        DEPENDS ${PROJECT_SOURCE_DIR}/web/index.html
        COMMAND
            cmake -E copy_if_different
            ${PROJECT_SOURCE_DIR}/web/index.html
            ${INDEX_FILE}
    )
    add_custom_target(
        index
        DEPENDS ${INDEX_FILE}
    )
    add_dependencies(
        incremental
        index
    )
endif()
