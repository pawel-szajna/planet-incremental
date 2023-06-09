function(add_ut)
    if(ENABLE_UT)
        set(OPTIONS HAS_MOCKS)
        set(VALUE_ARGS TESTED_MODULE)
        set(LIST_ARGS SOURCES)
        cmake_parse_arguments(
            UT
            "${OPTIONS}"
            "${VALUE_ARGS}"
            "${LIST_ARGS}"
            ${ARGN})

        set(UT_TESTS_MODULE ${UT_TESTED_MODULE}UT)
        list(TRANSFORM UT_SOURCES PREPEND tests/)

        add_executable(
            ${UT_TESTS_MODULE}
            ${UT_SOURCES}
        )

        set_target_properties(
            ${UT_TESTS_MODULE}
            PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/ut"
                LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/ut"
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/ut"
        )

        add_test(
                NAME ${UT_TESTS_MODULE}
                COMMAND ${UT_TESTS_MODULE}
        )

        if(UT_HAS_MOCKS)
            set(MOCKS_MODULE ${UT_TESTED_MODULE}Mocks)
            add_library(
                ${MOCKS_MODULE}
                INTERFACE
            )

            target_include_directories(
                ${MOCKS_MODULE}
                INTERFACE
                    mocks
            )
        endif()

        target_include_directories(
            ${UT_TESTS_MODULE}
            PRIVATE
                $<TARGET_PROPERTY:${UT_TESTED_MODULE},INCLUDE_DIRECTORIES>
        )

        get_target_property(UT_TESTED_MODULE_TYPE ${UT_TESTED_MODULE} TYPE)
        if(${UT_TESTED_MODULE_TYPE} STREQUAL INTERFACE_LIBRARY)
            string(TOLOWER ${UT_TESTED_MODULE} UT_TESTED_MODULE_DIRECTORY)
            target_include_directories(
                ${UT_TESTS_MODULE}
                PRIVATE
                    include/${UT_TESTED_MODULE_DIRECTORY}
            )
        endif()

        target_link_libraries(
            ${UT_TESTS_MODULE}
            PRIVATE
                ${UT_TESTED_MODULE}
                gtest
                gmock
                gtest_main
        )

        if(UT_HAS_MOCKS)
            target_link_libraries(
                ${UT_TESTS_MODULE}
                PRIVATE
                    ${MOCKS_MODULE}
            )
        endif()
    endif()
endfunction()

function(add_module)
    set(OPTIONS HAS_MOCKS)
    set(VALUE_ARGS NAME TYPE)
    set(LIST_ARGS SOURCES TESTS DEPENDENCIES PUBLIC_DEPENDENCIES INCLUDES SYSTEM_INCLUDES)
    cmake_parse_arguments(
        MODULE
        "${OPTIONS}"
        "${VALUE_ARGS}"
        "${LIST_ARGS}"
        ${ARGN})

    list(LENGTH MODULE_SOURCES SOURCES_COUNT)
    if(MODULE_TYPE STREQUAL INTERFACE AND SOURCES_COUNT GREATER 0)
        message(FATAL_ERROR "Module ${MODULE_NAME} has type set to ${MODULE_TYPE}, but was given sources.")
    elseif(NOT MODULE_TYPE STREQUAL INTERFACE AND SOURCES_COUNT EQUAL 0)
        message(FATAL_ERROR "Module ${MODULE_NAME} has type set to ${MODULE_TYPE}, but has no source files.")
    endif()

    if(MODULE_TYPE STREQUAL EXECUTABLE)
        add_executable(
            ${MODULE_NAME}
            ${MODULE_SOURCES}
        )
    else()
        list(TRANSFORM MODULE_SOURCES PREPEND src/)
        add_library(
            ${MODULE_NAME}
            ${MODULE_TYPE}
            ${MODULE_SOURCES}
        )
    endif()

    set_target_properties(
        ${MODULE_NAME}
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    list(LENGTH MODULE_SYSTEM_INCLUDES SYSTEM_INCLUDES_COUNT)

    if(${MODULE_TYPE} STREQUAL INTERFACE)
        target_include_directories(
            ${MODULE_NAME}
            INTERFACE
                include
                ${MODULE_INCLUDES}
        )
        if(SYSTEM_INCLUDES_COUNT GREATER 0)
            target_include_directories(
                ${MODULE_NAME}
                SYSTEM INTERFACE
                    ${MODULE_SYSTEM_INCLUDES}
            )
        endif()
    else()
        string(TOLOWER ${MODULE_NAME} MODULE_LOWERCASE)
        target_include_directories(
            ${MODULE_NAME}
            PUBLIC
                include
            PRIVATE
                include/${MODULE_LOWERCASE}
                ${MODULE_INCLUDES}
        )
        if(SYSTEM_INCLUDES_COUNT GREATER 0)
            target_include_directories(
                ${MODULE_NAME}
                SYSTEM PRIVATE
                    ${MODULE_SYSTEM_INCLUDES}
            )
        endif()
    endif()

    list(LENGTH MODULE_DEPENDENCIES DEPENDENCIES_COUNT)
    list(LENGTH MODULE_PUBLIC_DEPENDENCIES PUBLIC_DEPENDENCIES_COUNT)
    if(DEPENDENCIES_COUNT GREATER 0 OR PUBLIC_DEPENDENCIES_COUNT GREATER 0)
        if(${MODULE_TYPE} STREQUAL INTERFACE)
            if(PUBLIC_DEPENDENCIES_COUNT GREATER 0)
                message("Warning: module ${MODULE_NAME} has PUBLIC_DEPENDENCIES defined, but as an INTERFACE module, all its dependencies are treated as INTERFACE.")
            endif()
            target_link_libraries(
                ${MODULE_NAME}
                INTERFACE
                    ${MODULE_DEPENDENCIES}
                    ${MODULE_PUBLIC_DEPENDENCIES}
            )
        else()
            target_link_libraries(
                ${MODULE_NAME}
                PRIVATE
                    ${MODULE_DEPENDENCIES}
                PUBLIC
                    ${MODULE_PUBLIC_DEPENDENCIES}
            )
        endif()
    endif()

    list(LENGTH MODULE_TESTS TESTS_COUNT)
    if(TESTS_COUNT GREATER 0 OR MODULE_MOCKS)
        add_ut(
            ${MODULE_HAS_MOCKS}
            TESTED_MODULE ${MODULE_NAME}
            SOURCES ${MODULE_TESTS}
        )
    elseif(NOT MODULE_TYPE STREQUAL EXECUTABLE)
        message("Notice: module ${MODULE_NAME} has no unit tests defined.")
    endif()
endfunction()
