#ifndef __BCLIB_LIST_H__
#define __BCLIB_LIST_H__

struct StackNode;

typedef struct StackNode {

    struct StackNode *tail;

    void *value;

} StackNode;

typedef struct Stack {

    StackNode *stack;

    int count;

} Stack;

Stack *stack_create();
void stack_destroy(Stack *stack);

void stack_clear(Stack *stack);
void stack_clear_destroy(Stack *stack);

#define stack_count(S) ((S)->count)
#define stack_head(S) ((S)->stack != NULL ? (S)->stack->value : NULL)

Stack *stack_push(Stack *stack, void *value);
void *stack_pop(Stack *stack);

#define STACK_FOREACH(S, V) StackNode *_node = NULL;\
    StackNode *V = NULL;\
    for (V = _node = S->stack; _node != NULL; V = _node = _node->tail)

#endif
