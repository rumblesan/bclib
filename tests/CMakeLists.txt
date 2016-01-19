include_directories(../lib/include)

add_executable(bclib-list-test "list-test.c")
target_link_libraries(bclib-list-test bclib)
add_test(list-tests bclib-list-test)

add_executable(bclib-darray-test "darray-test.c")
target_link_libraries(bclib-darray-test bclib)
add_test(darray-tests bclib-darray-test)

