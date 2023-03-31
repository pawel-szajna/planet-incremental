cmake_minimum_required(VERSION 3.21)
project(planet_incremental CXX)
set(CMAKE_CXX_STANDARD 23)

option(ENABLE_UT "Enable unit tests" ON)

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

function(add_ut)
    if (ENABLE_UT)
        set(options)
        set(oneValueArgs TESTED_MODULE)
        set(multiValueArgs SOURCES)
        cmake_parse_arguments(UT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

        set(UT_TESTS_MODULE ${UT_TESTED_MODULE}UT)
        list(TRANSFORM UT_SOURCES PREPEND tests/)

        add_executable(
                ${UT_TESTS_MODULE}
                ${UT_SOURCES}
        )

        add_test(
                NAME ${UT_TESTS_MODULE}
                COMMAND ${UT_TESTS_MODULE}
        )

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
    endif()
endfunction()

add_subdirectory(src)
