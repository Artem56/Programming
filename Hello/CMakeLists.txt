cmake_minimum_required(VERSION 3.6)
project(Hello)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

set(SOURCE_FILES main.cpp)
add_executable(Hello ${SOURCE_FILES})