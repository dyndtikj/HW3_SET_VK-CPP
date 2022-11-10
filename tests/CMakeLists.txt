cmake_minimum_required(VERSION 3.0)
project(tests)
set(CMAKE_CXX_STANDARD 20)

# Compilation flags
string(APPEND CMAKE_CXX_FLAGS " -g -Wpedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -fprofile-arcs -ftest-coverage -fPIC")
string(APPEND CMAKE_CXX_FLAGS " -O0")

enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Collects the names of all the source files in the specified directory
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME}  hw3_set GTest::gtest_main)
gtest_discover_tests(${PROJECT_NAME})
