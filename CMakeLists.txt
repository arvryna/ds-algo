cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(dsalgo)

include_directories(dsalgo, include)

file(GLOB SOURCES *.cpp)

add_executable(dsalgo start.cpp ${SOURCES})

# file(GLOB_RECURSE SRC_LIST src/*.cpp)
# add_executable(dsalgo start.cpp ${SRC_LIST})

# file(GLOB SRC_LIST src/*.cpp)
# target_include_directories(dsalgo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)