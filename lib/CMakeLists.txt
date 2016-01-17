
include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(mylib SHARED ${SOURCES})

set_target_properties(mylib PROPERTIES
    PUBLIC_HEADER "${HEADERS}")

install(TARGETS mylib
    DESTINATION lib
    EXPORT MyLibTargets
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/mylib"
    COMPONENT dev
    )

