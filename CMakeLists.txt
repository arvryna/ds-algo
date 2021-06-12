cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(dsalgo)

add_compile_options(-Wall )

include_directories(include)

file(GLOB SOURCES *.cpp)

add_executable(out_build start.cpp ${SOURCES})

# file(GLOB_RECURSE SRC_LIST src/*.cpp)