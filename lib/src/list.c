#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "dbg.h"

List *list_create() {
    return calloc(1, sizeof(List));
}

void list_destroy(List *list) {
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }
    if (list->last) {
        free(list->last);
    }
    free(list);
}

void list_clear(List *list) {
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

void list_clear_destroy(List *list) {
    list_clear(list);
    list_destroy(list);
}

void *list_get(List *list, int el_num) {
    if (el_num >= list_count(list)) return NULL;

    ListNode *el = NULL;
    int i = 0;
    LIST_FOREACH(list, first, next, cur) {
        if (i == el_num) {
            el = cur;
            break;
        } else {
            i += 1;
        }
    }
    return el != NULL ? el->value : NULL;
}

List *list_push(List *list, void *value) {
    ListNode *node = calloc(1, sizeof(ListNode));
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
void *list_pop(List *list) {
    ListNode *node = list->last;
    return node != NULL ? list_remove(list, node) : NULL;
}

List *list_unshift(List *list, void *value) {
    ListNode *node = calloc(1, sizeof(ListNode));
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

void *list_shift(List *list) {
    ListNode *node = list->first;
    return node != NULL ? list_remove(list, node) : NULL;
}

void *list_remove(List *list, ListNode *node) {

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
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->length -= 1;
    result = node->value;
    free(node);

error:
    return result;
}

