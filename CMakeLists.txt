cmake_minimum_required(VERSION 3.0)

project(bclib C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99 -D_POSIX_C_SOURCE=199309L")

add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)
