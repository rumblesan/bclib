#include <assert.h>

#include "minunit.h"
#include "dbg.h"
#include "hashmap.h"
#include "bstrlib.h"

Hashmap *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static int traverse_good_cb(HashmapNode *node) {
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;
    return 0;
}

static int traverse_fail_cb(HashmapNode *node) {
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;
    if (traverse_called == 2) {
        return 1;
    } else {
        return 0;
    }
}

char *test_create() {
    map = hashmap_create(NULL, NULL);
    mu_assert(map != NULL, "failed to create map");

    return NULL;
}

char *test_destroy() {
    hashmap_destroy(map);

    return NULL;
}

char *test_get_set() {
    int rc = hashmap_set(map, &test1, &expect1);
    mu_assert(rc == 0, "failed to set &test1");
    bstring result = hashmap_get(map, &test1);
    mu_assert(result == &expect1, "wrong value for test1");

    rc = hashmap_set(map, &test2, &expect2);
    mu_assert(rc == 0, "failed to set &test2");
    result = hashmap_get(map, &test2);
    mu_assert(result == &expect2, "wrong value for test2");

    rc = hashmap_set(map, &test3, &expect3);
    mu_assert(rc == 0, "failed to set &test3");
    result = hashmap_get(map, &test3);
    mu_assert(result == &expect3, "wrong value for test3");

    return NULL;
}

char *test_traverse() {
    int rc = hashmap_traverse(map, traverse_good_cb);
    mu_assert(rc == 0, "failed to traverse");
    mu_assert(traverse_called == 3, "wrong count traverse");

    traverse_called = 0;
    rc = hashmap_traverse(map, traverse_fail_cb);
    mu_assert(rc == 1, "failed to traverse");
    mu_assert(traverse_called == 2, "wrong count traverse for fail");

    return NULL;
}

char *test_delete() {
    bstring deleted = (bstring)hashmap_delete(map, &test1);
    mu_assert(deleted != NULL, "got NULL on first delete");
    mu_assert(deleted == &expect1, "should get test1");
    bstring result = hashmap_get(map, &test1);
    mu_assert(result == NULL, "should delete");

    deleted = (bstring)hashmap_delete(map, &test2);
    mu_assert(deleted != NULL, "got NULL on second delete");
    mu_assert(deleted == &expect2, "should get test2");
    result = hashmap_get(map, &test2);
    mu_assert(result == NULL, "should delete");

    deleted = (bstring)hashmap_delete(map, &test3);
    mu_assert(deleted != NULL, "got NULL on third delete");
    mu_assert(deleted == &expect3, "should get test3");
    result = hashmap_get(map, &test3);
    mu_assert(result == NULL, "should delete");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_get_set);
    mu_run_test(test_traverse);
    mu_run_test(test_delete);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
