cmake_minimum_required(VERSION 3.21)
project(planet_incremental CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

option(ENABLE_UT "Enable unit tests" ON)
option(ENABLE_DOCS "Enable docs generation" OFF)

if(EMSCRIPTEN)
    set(PLATFORM Web)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    add_compile_options(-Os)
    add_link_options(-sUSE_GLFW=3)
    add_link_options(-sASSERTIONS=1)
    add_link_options(-sWASM=1)
    add_link_options(-sALLOW_MEMORY_GROWTH)
    add_link_options(-sASYNCIFY)
    add_link_options(-sEXPORTED_FUNCTIONS=_main,_updateSize)
    add_link_options(-sEXPORTED_RUNTIME_METHODS=ccall,cwrap)
endif()

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

include(modules)

if(ENABLE_DOCS)
    add_subdirectory(docs)
endif()

add_subdirectory(lib/raylib SYSTEM)
add_subdirectory(src)
