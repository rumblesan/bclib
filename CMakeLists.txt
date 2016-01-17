cmake_minimum_required(VERSION 3.0)
project(mylib)

set(MYLIB_MAJOR_VERSION 0)
set(MYLIB_MINOR_VERSION 1)
set(MYLIB_PATCH_VERSION 0)
set(MYLIB_VERSION
    ${MYLIB_MAJOR_VERSION}.${MYLIB_MINOR_VERSION}.${MYLIB_PATCH_VERSION})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")

add_library(mylib SHARED ${SOURCES})

install(TARGETS mylib
    DESTINATION lib
    )
install(DIRECTORY include/
    DESTINATION include/mylib
    )

