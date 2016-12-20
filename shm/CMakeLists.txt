cmake_minimum_required(VERSION 3.6)
project(shm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp increment.cpp clear.cpp)
add_executable(shm ${SOURCE_FILES})