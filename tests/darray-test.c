#include "testing/minunit.h"
#include "darray.h"

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create() {
    array = darray_create(sizeof(int), 100);
    mu_assert(array != NULL, "darray_create failed");
    mu_assert(array->contents != NULL, "contents are wrong in darray");
    mu_assert(array->end == 0, "end isn't at the correct spot");
    mu_assert(array->element_size == sizeof(int), "element size is wrong");
    mu_assert(array->max == 100, "wrong max length on initial size");

    return NULL;
}

char *test_destroy() {
    darray_destroy(array);
    return NULL;
}

char *test_new() {

    val1 = darray_new(array);
    mu_assert(val1 != NULL, "failed to make a new element");

    val2 = darray_new(array);
    mu_assert(val2 != NULL, "failed to make a new element");

    return NULL;
}

char *test_set() {
    darray_set(array, 0, val1);
    darray_set(array, 1, val2);
    return NULL;
}

char *test_get() {
    mu_assert(darray_get(array, 0) == val1, "wrong first value");
    mu_assert(darray_get(array, 1) == val2, "wrong first value");

    return NULL;
}

char *test_remove() {
    int *val_check = darray_remove(array, 0);
    mu_assert(val_check != NULL, "should not get NULL");
    mu_assert(*val_check == *val1, "should not get NULL");
    mu_assert(darray_get(array, 0) == NULL, "should be gone");
    darray_free(val_check);

    val_check = darray_remove(array, 1);
    mu_assert(val_check != NULL, "should not get NULL");
    mu_assert(*val_check == *val2, "should not get NULL");
    mu_assert(darray_get(array, 1) == NULL, "should be gone");
    darray_free(val_check);

    return NULL;
}

char* test_expand_contract() {
    int old_max = array->max;
    darray_expand(array);
    mu_assert(
        (unsigned int)array->max == old_max + array->expand_rate,
        "wrong size after expand"
    );

    darray_contract(array);
    mu_assert(
        (unsigned int)array->max == array->expand_rate + 1,
        "should stay at the expand rate at least"
    );

    darray_contract(array);
    mu_assert(
        (unsigned int)array->max == array->expand_rate + 1,
        "should stay at the expand rate at least"
    );

    return NULL;
}

char *test_push_pop() {

    int i = 0;
    for (i = 0; i < 1000; i += 1) {
        int *val = darray_new(array);
        *val = i * 333;
        darray_push(array, val);
    }

    mu_assert(array->max == 1201, "wrong max size");

    for(i = 999; i >= 0; i -= 1) {
        int *val = darray_pop(array);
        mu_assert(val != NULL, "shouldn't get a NULL");
        mu_assert(*val == i * 333, "wrong value");
        darray_free(val);
    }

    return NULL;
}


char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_new);
    mu_run_test(test_set);
    mu_run_test(test_get);
    mu_run_test(test_remove);
    mu_run_test(test_expand_contract);
    mu_run_test(test_push_pop);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
