cmake_minimum_required(VERSION 3.0)
project(mylib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")

add_library(mylib SHARED ${SOURCES})

