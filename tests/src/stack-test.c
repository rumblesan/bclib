#include "minunit.h"
#include "stack.h"

static Stack *stack = NULL;

int test1 = 1;
int test2 = 2;
int test3 = 3;

char *test_create() {
    stack = stack_create();
    return NULL;
}

char *test_destroy() {
    stack_clear_destroy(stack);
    return NULL;
}

char *test_push_pop() {
    stack_push(stack, &test1);
    mu_assert(stack_head(stack) == &test1, "wrong stack head value");

    stack_push(stack, &test2);
    mu_assert(stack_head(stack) == &test2, "wrong stack head value");

    stack_push(stack, &test3);
    mu_assert(stack_head(stack) == &test3, "wrong stack head value");
    mu_assert(stack_count(stack) == 3, "wrong stack count on push");

    int *val = stack_pop(stack);
    mu_assert(val == &test3, "wrong value on pop");

    val = stack_pop(stack);
    mu_assert(val == &test2, "wrong value on pop");

    val = stack_pop(stack);
    mu_assert(val == &test1, "wrong value on pop");
    mu_assert(stack_count(stack) == 0, "wrong stack count after pop");

    return NULL;
}


char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
