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

add_subdirectory(src)
