#include <stdlib.h>
#include <stdbool.h>

#include "dl_list.h"
#include "dbg.h"

DLList *dl_list_empty() {
    return calloc(1, sizeof(DLList));
}

void dl_list_destroy(DLList *list) {
    DL_LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }
    if (list->last) {
        free(list->last);
    }
    free(list);
}

int dl_list_length(DLList *list) {
    return list->length;
}

void *dl_list_first(DLList *list) {
    return list->first->value;
}
void *dl_list_last(DLList *list) {
    return list->last->value;
}

DLList *dl_list_push(DLList *list, void *value) {
    DLListNode *node = calloc(1, sizeof(DLListNode));
    check_mem(node);
    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    list->length += 1;

    return list;

error:
    return NULL;
}
void *dl_list_pop(DLList *list) {
    DLListNode *node = list->last;
    return node != NULL ? dl_list_remove(list, node) : NULL;
}

DLList *dl_list_unshift(DLList *list, void *value) {
    DLListNode *node = calloc(1, sizeof(DLListNode));
    check_mem(node);
    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->first->prev = node;
        node->next = list->first;
        list->first = node;
    }
    list->length += 1;

    return list;

error:
    return NULL;
}

void *dl_list_shift(DLList *list) {
    DLListNode *node = list->first;
    return node != NULL ? dl_list_remove(list, node) : NULL;
}

void *dl_list_remove(DLList *list, DLListNode *node) {

    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if(node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a last that is NULL.");
        list->last->next = NULL;
    } else {
        DLListNode *after = node->next;
        DLListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->length -= 1;
    result = node->value;
    free(node);

error:
    return result;
}

