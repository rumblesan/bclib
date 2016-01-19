#include "testing/minunit.h"
#include "list.h"

char *test_list_empty() {
    List l = list_empty();
    int len = list_length(l);
    mu_assert(len == 0, "List length should be zero");
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_list_empty);

    return NULL;
}

RUN_TESTS(all_tests);
