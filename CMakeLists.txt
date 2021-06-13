cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)

project(dsalgo)

add_compile_options(-Wall )

include_directories(include)

file(GLOB SOURCES *.cpp)

add_executable(out_build test.cpp ${SOURCES})

# file(GLOB_RECURSE SRC_LIST src/*.cpp)
# Find a way to add clang format
