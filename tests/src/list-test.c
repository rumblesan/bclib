#include "minunit.h"
#include "list.h"

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create() {
    list = list_create();
    mu_assert(list != NULL, "failed to create list");

    return NULL;
}

char *test_destroy() {
    list_clear_destroy(list);
    return NULL;
}

char *test_push_pop() {
    list_push(list, test1);
    mu_assert(list_last(list) == test1, "wrong last value");

    list_push(list, test2);
    mu_assert(list_last(list) == test2, "wrong last value");

    list_push(list, test3);
    mu_assert(list_last(list) == test3, "wrong last value");
    mu_assert(list_count(list) == 3, "wrong count on push");

    char *val = list_pop(list);
    mu_assert(val == test3, "wrong value on pop");

    val = list_pop(list);
    mu_assert(val == test2, "wrong value on pop");

    val = list_pop(list);
    mu_assert(val == test1, "wrong value on pop");
    mu_assert(list_count(list) == 0, "wrong count after pop");

    return NULL;
}

char *test_unshift() {
    list_unshift(list, test1);
    mu_assert(list_first(list) == test1, "wrong first value");

    list_unshift(list, test2);
    mu_assert(list_first(list) == test2, "wrong first value");

    list_unshift(list, test3);
    mu_assert(list_first(list) == test3, "wrong first value");
    mu_assert(list_count(list) == 3, "wrong count on unshift");

    return NULL;
}

char *test_remove() {
    // we onlyu need to test the middle remove case since push/shift
    // already test the other cases

    char *val = list_remove(list, list->first->next);
    mu_assert(val == test2, "wrong removed element");
    mu_assert(list_count(list) == 2, "wrong count after remove");
    mu_assert(list_first(list) == test3, "wrong first after remove");
    mu_assert(list_last(list) == test1, "wrong last after remove");

    return NULL;
}

char *test_shift() {
    mu_assert(list_count(list) != 0, "wrong count before shift");

    char *val = list_shift(list);
    mu_assert(val == test3, "wrong value on shift");

    val = list_shift(list);
    mu_assert(val == test1, "wrong value on shift");
    mu_assert(list_count(list) == 0, "wrong count after shift");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
