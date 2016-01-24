#include <stdlib.h>

#include "stack.h"
#include "dbg.h"

Stack *stack_create() {
    Stack *stack = calloc(1, sizeof(Stack));
    check_mem(stack);
    return stack;
error:
    return NULL;
}

void stack_destroy(Stack *stack) {
    STACK_FOREACH(stack, cur) {
        free(cur);
    }
    free(stack);
}

void stack_clear(Stack *stack) {
    STACK_FOREACH(stack, cur) {
        if (cur->value != NULL) {
            free(cur->value);
        }
    }
}

void stack_clear_destroy(Stack *stack) {
    stack_clear(stack);
    stack_destroy(stack);
}

Stack *stack_push(Stack *stack, void *value) {
    StackNode *node = calloc(1, sizeof(StackNode));
    check_mem(node);

    node->value = value;
    node->tail = stack->stack;

    stack->stack = node;
    stack->count += 1;

    return stack;
error:
    return NULL;
}

void *stack_pop(Stack *stack) {
    if (stack->stack == NULL) return NULL;
    StackNode *node = stack->stack;
    stack->stack = node->tail;
    stack->count -= 1;
    return node->value;
}

