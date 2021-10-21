#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

typedef int StackElement;

typedef struct StackStruct {
    struct StackNodeStruct* data;
    int size;
} *Stack;

typedef struct StackNodeStruct {
    StackElement element;
    struct StackNodeStruct* next;
} *StackNode;

void stackPush(StackElement element, Stack stack);
StackElement stackPop(Stack stack);
StackElement stackTop(Stack stack);
Stack stackCreate();
void stackDestroy(Stack stack);
void stackClear(Stack stack);

static inline bool stackIsEmpty(Stack stack) {
    return stack->size == 0;
}

static inline int stackSize(Stack stack) {
    return stack->size;
}

#endif
