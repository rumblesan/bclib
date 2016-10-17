

set(SOURCES
  "src/bstrlib.c"
  "src/darray.c"
  "src/hashmap.c"
  "src/list.c"
  "src/ringbuffer.c"
  "src/simple_list.c"
  "src/stack.c"
  )
set(HEADERS
  "include/bstrlib.h"
  "include/darray.h"
  "include/dbg.h"
  "include/hashmap.h"
  "include/list.h"
  "include/ringbuffer.h"
  "include/simple_list.h"
  "include/stack.h"
  )

add_library(bclib ${HEADERS} ${SOURCES})

target_include_directories(bclib
  PUBLIC include
  PRIVATE src)

install(TARGETS bclib EXPORT BCLibTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/bclib)
