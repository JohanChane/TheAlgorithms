#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef int Element;

typedef struct StackStruct {
    int capacity;
    int size;
    Element* data;
} * Stack;

void stackPush(Element element, Stack stack);
void stackPop(Stack stack);
Element stackTop(Stack stack);
Stack stackCreate(int capacity);
void stackDestroy(Stack stack);

static inline bool stackIsEmpty(Stack stack) {
    return stack->size == 0;
}

static inline int stackSize(Stack stack) {
    return stack->size;
}

#endif
