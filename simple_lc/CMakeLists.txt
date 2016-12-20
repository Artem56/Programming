cmake_minimum_required(VERSION 3.6)
project(simple_lc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(simple_lc ${SOURCE_FILES})