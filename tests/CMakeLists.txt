include_directories(../lib/include)

add_executable(bclib-list-test "list-test.c")
target_link_libraries(bclib-list-test bclib)
add_test(tests bclib-list-test)

