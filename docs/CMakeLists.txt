find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED)

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.hpp)

set(DOCS_INTERMEDIATE_DIRECTORY ${CMAKE_BINARY_DIR}/src/docs)
set(DOCS_TARGET_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
set(DOXYGEN_INPUT ${PROJECT_SOURCE_DIR}/src)
set(DOXYGEN_OUTPUT ${DOCS_INTERMEDIATE_DIRECTORY}/doxygen)
set(DOXYGEN_INDEX ${DOXYGEN_OUTPUT}/xml/index.xml)
set(SPHINX_DIRECTORY ${DOCS_INTERMEDIATE_DIRECTORY}/sphinx)

file(GLOB_RECURSE ALL_HPP_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE ALL_RST_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.rst)
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    ${DOCS_INTERMEDIATE_DIRECTORY}/Doxyfile
    @ONLY
)

add_custom_command(
    OUTPUT
        ${DOXYGEN_INDEX}
    DEPENDS
        ${ALL_HPP_FILES}
    COMMAND
        ${DOXYGEN_EXECUTABLE}
        ${DOCS_INTERMEDIATE_DIRECTORY}/Doxyfile
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    MAIN_DEPENDENCY
        Doxyfile
)

set(TARGET_RST_LOCATIONS "")
foreach(RST_FILE IN LISTS ALL_RST_FILES)
    string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} ${SPHINX_DIRECTORY} TARGET_RST ${RST_FILE})
    list(APPEND TARGET_RST_LOCATIONS ${TARGET_RST})
    add_custom_command(
        OUTPUT
            ${TARGET_RST}
        DEPENDS
            ${RST_FILE}
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${RST_FILE} ${TARGET_RST}
        COMMENT
            "Prepare RST source ${RST_FILE} in build directory"
    )
endforeach()

set(CONF_PY_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/conf.py)
set(CONF_PY_TARGET ${SPHINX_DIRECTORY}/conf.py)
add_custom_command(
    OUTPUT
        ${CONF_PY_TARGET}
    DEPENDS
        ${CONF_PY_SOURCE}
    COMMAND
        ${CMAKE_COMMAND} -E copy ${CONF_PY_SOURCE} ${CONF_PY_TARGET}
    COMMENT
        "Copy conf.py"
)

add_custom_target(
    docs_html
    DEPENDS
        ${TARGET_RST_LOCATIONS}
        ${CONF_PY_TARGET}
    COMMAND
        ${SPHINX_BUILD_EXECUTABLE}
        -b html
        ${SPHINX_DIRECTORY}
        ${DOCS_TARGET_DIRECTORY}
        -Dbreathe_projects.schron=${DOXYGEN_OUTPUT}/xml
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(
    docs_pdf
    DEPENDS
        ${TARGET_RST_LOCATIONS}
        ${CONF_PY_TARGET}
    COMMAND
        ${SPHINX_BUILD_EXECUTABLE}
        -M latexpdf
        ${SPHINX_DIRECTORY}
        ${DOCS_TARGET_DIRECTORY}
        -Dbreathe_projects.schron=${DOXYGEN_OUTPUT}/xml
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(
    docs
    DEPENDS
        docs_html
        docs_pdf
    COMMAND
        true
)
