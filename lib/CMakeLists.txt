
include_directories(include)

set(SOURCES
    "src/bstrlib.c"
    "src/darray.c"
    "src/hashmap.c"
    "src/list.c"
    "src/simple_list.c"
    )
set(HEADERS
    "include/bstrlib.h"
    "include/darray.h"
    "include/dbg.h"
    "include/hashmap.h"
    "include/list.h"
    "include/simple_list.h"
    )

add_library(bclib STATIC ${SOURCES})

set_target_properties(bclib PROPERTIES
    PUBLIC_HEADER "${HEADERS}")

install(TARGETS bclib
    DESTINATION lib
    EXPORT BCLibTargets
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/bclib"
    COMPONENT dev
    )

