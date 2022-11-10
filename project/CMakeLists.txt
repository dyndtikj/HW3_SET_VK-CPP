cmake_minimum_required(VERSION 3.18)
project(hw3_set VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)

# Compilation flags
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Wall -Wextra -fPIC")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")
string(APPEND CMAKE_CXX_FLAGS " -O0")

# Collects the names of all the source files in the specified directory
aux_source_directory(src SRC)
add_library(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)