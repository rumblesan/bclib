#ifndef __BCLIB_SIMPLE_LIST_H__
#define __BCLIB_SIMPLE_LIST_H__

#include <stdbool.h>

typedef struct simple_list_el *SimpleList;
typedef struct simple_list_el {

    void *head;

    SimpleList tail;

} SimpleListEl;

SimpleList simple_list_element();

SimpleList simple_list_empty();

void simple_list_cleanup(SimpleList list);

SimpleList simple_list_prepend(SimpleList list, void *value);

void *simple_list_head(SimpleList list);

SimpleList simple_list_tail(SimpleList list);

bool simple_list_is_empty(SimpleList list);

int simple_list_length(SimpleList list);

#endif
