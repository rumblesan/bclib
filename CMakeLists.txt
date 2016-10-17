cmake_minimum_required(VERSION 2.8)

project(bclib C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")

add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)
