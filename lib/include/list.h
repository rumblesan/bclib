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

List *list_create();
void list_destroy(List *list);
void list_clear(List *list);
void list_clear_destroy(List *list);

#define list_count(A) ((A)->length)
#define list_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define list_last(A) ((A)->first != NULL ? (A)->last->value : NULL)

List *list_push(List *list, void *value);
void *list_pop(List *list);

List *list_unshift(List *list, void *value);
void *list_shift(List *list);

void *list_remove(List *list, ListNode *node);

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
