#include <stdlib.h>
#include <stdbool.h>

#include "simple_list.h"

SimpleList simple_list_element() {

    SimpleList list = malloc(sizeof(SimpleListEl));

    list->tail = NULL;

    return list;
}

SimpleList simple_list_empty() {
    return simple_list_element();
}

void simple_list_cleanup(SimpleList list) {
    if (list->tail != NULL) {
        simple_list_cleanup(list->tail);
    }
    // TODO Free the head element somehow?
    free(list);
}

SimpleList simple_list_prepend(SimpleList list, void *value) {

    SimpleList newHead = simple_list_element();

    newHead->head = value;
    newHead->tail = list;

    return newHead;
}

void *simple_list_head(SimpleList list) {
    return list->head;
}

SimpleList simple_list_tail(SimpleList list) {
    return list->tail;
}

bool simple_list_is_empty(SimpleList list) {
    if (list->tail == NULL) {
        return true;
    } else {
        return false;
    }
}

int simple_list_length(SimpleList list) {
    SimpleList l = list;
    int i = 0;
    while(!simple_list_is_empty(l)) {
        i += 1;
        l = simple_list_tail(l);
    }
    return i;
}
