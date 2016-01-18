#ifndef __BCLIB_DL_LIST_H__
#define __BCLIB_DL_LIST_H__

struct DLListNode;

typedef struct DLListNode {

    struct DLListNode *next;
    struct DLListNode *prev;

    void *value;

} DLListNode;

typedef struct DLList {

    DLListNode *first;
    DLListNode *last;

    int length;

} DLList;

DLList *dl_list_empty();
void dl_list_destroy(DLList *list);

int dl_list_length(DLList *list);

void *dl_list_first(DLList *list);
void *dl_list_last(DLList *list);

DLList *dl_list_push(DLList *list, void *value);
void *dl_list_pop(DLList *list);

DLList *dl_list_unshift(DLList *list, void *value);
void *dl_list_shift(DLList *list);

void *dl_list_remove(DLList *list, DLListNode *node);

#define DL_LIST_FOREACH(L, S, M, V) DLListNode *_node = NULL;\
    DLListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
