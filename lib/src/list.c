#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

List list_element() {

    List list = malloc(sizeof(ListEl));

    list->tail = NULL;

    return list;
}

List list_empty() {
    return list_element();
}

void list_cleanup(List list) {
    if (list->tail != NULL) {
        list_cleanup(list->tail);
    }
    // TODO Free the head element somehow?
    free(list);
}

List list_prepend(List list, void *value) {

    List newHead = list_element();

    newHead->head = value;
    newHead->tail = list;

    return newHead;
}

void *list_head(List list) {
    return list->head;
}

List list_tail(List list) {
    return list->tail;
}

bool list_is_empty(List list) {
    if (list->tail == NULL) {
        return true;
    } else {
        return false;
    }
}

int list_length(List list) {
    List l = list;
    int i = 0;
    while(!list_is_empty(l)) {
        i += 1;
        l = list_tail(l);
    }
    return i;
}
