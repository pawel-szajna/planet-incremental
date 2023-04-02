cmake_minimum_required(VERSION 3.21)
project(planet_incremental CXX)
set(CMAKE_CXX_STANDARD 23)

option(ENABLE_UT "Enable unit tests" ON)
option(ENABLE_DOCS "Enable docs generation" OFF)

if (ENABLE_UT)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(lib/googletest)
    mark_as_advanced(
            BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS gmock_build_tests gtest_build_samples gtest_build_tests
            gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols)
    set_target_properties(gtest PROPERTIES FOLDER extern)
    set_target_properties(gmock PROPERTIES FOLDER extern)
    set_target_properties(gtest_main PROPERTIES FOLDER extern)
    set_target_properties(gtest_main PROPERTIES FOLDER extern)
endif()

if(ENABLE_DOCS)
    add_subdirectory(docs)
endif()

function(add_ut)
    if (ENABLE_UT)
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
    set(LIST_ARGS SOURCES TESTS DEPENDENCIES PUBLIC_DEPENDENCIES)
    cmake_parse_arguments(
        MODULE
        "${OPTIONS}"
        "${VALUE_ARGS}"
        "${LIST_ARGS}"
        ${ARGN})

    list(LENGTH MODULE_SOURCES SOURCES_COUNT)
    if(MODULE_TYPE STREQUAL INTERFACE AND SOURCES_COUNT GREATER 0)
        message(FATAL_ERROR "Module ${MODULE_NAME} has type set to ${MODULE_TYPE}, but was given sources!")
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

    if(${MODULE_TYPE} STREQUAL "INTERFACE")
        target_include_directories(
            ${MODULE_NAME}
            INTERFACE
                include
        )
    else()
        string(TOLOWER ${MODULE_NAME} MODULE_LOWERCASE)
        target_include_directories(
            ${MODULE_NAME}
            PUBLIC
                include
            PRIVATE
                include/${MODULE_LOWERCASE}
        )
    endif()

    list(LENGTH MODULE_DEPENDENCIES DEPENDENCIES_COUNT)
    list(LENGTH MODULE_PUBLIC_DEPENDENCIES PUBLIC_DEPENDENCIES_COUNT)
    if(DEPENDENCIES_COUNT GREATER 0 OR PUBLIC_DEPENDENCIES_COUNT GREATER 0)
        target_link_libraries(
            ${MODULE_NAME}
            PRIVATE
                ${MODULE_DEPENDENCIES}
            PUBLIC
                ${MODULE_PUBLIC_DEPENDENCIES}
        )
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

add_subdirectory(src)
