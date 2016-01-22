#include "minunit.h"
#include "simple_list.h"

char *test_simple_list_empty() {
    SimpleList l = simple_list_empty();
    int len = simple_list_length(l);
    mu_assert(len == 0, "List length should be zero");
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_simple_list_empty);

    return NULL;
}

RUN_TESTS(all_tests);
