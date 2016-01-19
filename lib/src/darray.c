#include <stdlib.h>
#include <assert.h>

#include "darray.h"
#include "dbg.h"

DArray *darray_create(size_t element_size, size_t initial_max) {
    DArray *array = malloc(sizeof(DArray));
    check_mem(array);
    array->max = initial_max;
    check(array->max > 0, "you must set an initial max > 0");

    array->contents = calloc(initial_max, sizeof(void *));
    check_mem(array->contents);

    array->end = 0;
    array->element_size = element_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;

    return array;
error:
    if (array) free(array);
    return NULL;
}

void darray_destroy(DArray *array) {
    if (array) {
        if (array->contents) free(array->contents);
        free(array);
    }
}

void darray_clear(DArray *array) {
    int i = 0;
    if (array->element_size > 0) {
        for (i = 0; i < array->max; i += 1) {
            if (array->contents[i] != NULL) {
                free(array->contents[i]);
            }
        }
    }
}

void darray_clear_destroy(DArray *array) {
    darray_clear(array);
    darray_destroy(array);
}

static inline int darray_resize(DArray *array, size_t newsize) {
    check(newsize > 0, "the newsize must be > 0");
    array->max = newsize;

    void *contents = realloc(array->contents, array->max * sizeof(void *));
    // check contents and assume realloc doesn't harm the original on error
    check_mem(contents);

    array->contents = contents;

    return 0;
error:
    return -1;
}

int darray_expand(DArray *array) {
    size_t old_max = array->max;
    check(
        darray_resize(array, array->max + array->expand_rate) == 0,
        "Failed to expand array to new size: %d",
        array->max + (int)array->expand_rate
    );
    memset(array->contents + old_max, 0, array->expand_rate + 1);
    return 0;

error:
    return -1;
}

int darray_contract(DArray *array) {
    int new_size = array->end < (int)array->expand_rate ? (int)array->expand_rate : array->end;
    return darray_resize(array, new_size + 1);
}

int darray_push(DArray *array, void *el) {
    array->contents[array->end] = el;
    array->end += 1;
    if (darray_end(array) >= darray_max(array)) {
        return darray_expand(array);
    } else {
        return 0;
    }
}

void *darray_pop(DArray *array) {
    check(array->end - 1 >= 0, "attempt to pop from empty array");

    void *el = darray_remove(array, array->end - 1);
    array->end -= 1;

    if (
        darray_end(array) > (int)array->expand_rate &&
        darray_end(array) % array->expand_rate) {
        darray_contract(array);
    }
    return el;
error:
    return NULL;
}

