#ifndef __BCLIB_DARRAY_H__
#define __BCLIB_DARRAY_H__

#include <stdlib.h>
#include <assert.h>
#include "dbg.h"

typedef struct DArray {

    int end;
    int max;
    size_t element_size;
    size_t expand_rate;
    void **contents;

} DArray;

DArray *darray_create(size_t element_size, size_t initial_max);

void darray_destroy(DArray *array);

void darray_clear(DArray *array);

void darray_clear_destroy(DArray *array);

int darray_expand(DArray *array);

int darray_contract(DArray *array);

int darray_push(DArray *array, void *el);

void *darray_pop(DArray *array);

#define darray_last(A) ((A)->contents[(A)->end - 1])
#define darray_first(A) ((A)->contents[0])
#define darray_end(A) ((A)->end)
#define darray_count(A) darray_end(A)
#define darray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300

static inline DArray *darray_set(DArray *array, int i, void *el) {
    check(i < array->max, "darray attempt to set past max");
    if(i > array->end) array->end = i;
    array->contents[i] = el;
    return array;
error:
    return NULL;
}

static inline void *darray_get(DArray *array, int i) {
    check(i < array->max, "darray attempt to get past max");
    return array->contents[i];
error:
    return NULL;
}

static inline void *darray_remove(DArray *array, int i) {
    check(i < array->max, "darray attempt to remove past max");
    void *el = array->contents[i];
    array->contents[i] = NULL;
    return el;
error:
    return NULL;
}

static inline void *darray_new(DArray *array) {
    check(array->element_size > 0, "can't use darray_new on 0 size darrays");
    return calloc(1, array->element_size);
error:
    return NULL;
}

#define darray_free(E) free((E))

#endif
