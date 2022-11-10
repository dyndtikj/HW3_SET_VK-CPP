cmake_minimum_required(VERSION 3.18)
project(hw3_set_main)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(project)

add_executable(${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
        )

target_link_libraries(${PROJECT_NAME} hw3_set)

if(BUILD_TESTS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
    add_subdirectory(tests)
endif()


