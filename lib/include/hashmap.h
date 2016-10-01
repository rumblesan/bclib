#ifndef __BCLIB_HASHMAP_H__
#define __BCLIB_HASHMAP_H__

#include <stdint.h>

#include "bstrlib.h"
#include "dbg.h"
#include "darray.h"

#define DEFAULT_NUMBER_OF_BUCKETS 100

typedef int (*Hashmap_compare)(void *a, void *b);
typedef uint32_t (*Hashmap_hash)(void *key);

typedef struct Hashmap {
    DArray* buckets;
    Hashmap_compare compare;
    Hashmap_hash hash;
} Hashmap;

typedef struct HashmapNode {
    void *key;
    void *data;
    uint32_t hash;
} HashmapNode;

typedef int (*Hashmap_traverse_cb)(HashmapNode *node);

Hashmap *hashmap_create(Hashmap_compare compare, Hashmap_hash hash);
void hashmap_destroy(Hashmap *map);

int hashmap_set(Hashmap *map, void *key, void *data);
void *hashmap_get(Hashmap *map, void *key);

int hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb);

void *hashmap_delete(Hashmap *map, void *key);

#endif
