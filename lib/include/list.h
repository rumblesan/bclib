#ifndef __BCLIB_LIST_H__
#define __BCLIB_LIST_H__

struct ListNode;

typedef struct ListNode {

    struct ListNode *next;
    struct ListNode *prev;

    void *value;

} ListNode;

typedef struct List {

    ListNode *first;
    ListNode *last;

    int length;

} List;

List *list_empty();
void list_destroy(List *list);

int list_length(List *list);

void *list_first(List *list);
void *list_last(List *list);

List *list_push(List *list, void *value);
void *list_pop(List *list);

List *list_unshift(List *list, void *value);
void *list_shift(List *list);

void *list_remove(List *list, ListNode *node);

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
