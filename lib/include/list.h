#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct list_el *List;
typedef struct list_el {

    void *head;

    List tail;

} ListEl;

List list_element();

List list_empty();

void list_cleanup(List list);

List list_prepend(List list, void *value);

void *list_head(List list);

List list_tail(List list);

bool list_is_empty(List list);

int list_length(List list);

#endif
