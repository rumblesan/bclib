include_directories(include)
include_directories(../lib/include)

file(GLOB_RECURSE TEST_SOURCES "src/*.c")

foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable("bclib-${TEST_NAME}" ${TEST_FILE})
    target_link_libraries("bclib-${TEST_NAME}" bclib)
    add_test("${TEST_NAME}s" "bclib-${TEST_NAME}")
endforeach(TEST_FILE)

