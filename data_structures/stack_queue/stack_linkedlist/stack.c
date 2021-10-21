#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void stackPush(StackElement element, Stack stack) {
    StackNode newNode = malloc(sizeof(struct StackNodeStruct));
    if (!newNode) {
        fprintf(stderr, "No space for newNode!\n");
        exit(EXIT_FAILURE);
    }
    newNode->element = element;

    newNode->next = stack->data;
    stack->data = newNode;

    stack->size++;
}

StackElement stackPop(Stack stack) {
    if (stackIsEmpty(stack)) {
        fprintf(stderr, "The stack is empty!\n");
        exit(EXIT_FAILURE);
    }

    StackNode tmpNode = stack->data;
    stack->data = tmpNode->next;

    StackElement element = tmpNode->element;
    free(tmpNode);

    stack->size--;

    return element;
}

Stack stackCreate() {
    Stack stack = malloc(sizeof(struct StackStruct));
    if (!stack) {
        fprintf(stderr, "No space for creating stack!\n");
        exit(EXIT_FAILURE);
    }
    stack->data = NULL;
    stack->size = 0;

    return stack;
}

void stackDestroy(Stack stack) {
    StackNode curNode = stack->data;
    StackNode tmpNode;
    while (curNode) {
        tmpNode = curNode;
        curNode = curNode->next;
        free(tmpNode);
    }

    free(stack);
}

void stackClear(Stack stack) {
    StackNode curNode = stack->data;
    StackNode tmpNode;
    while (curNode) {
        tmpNode = curNode;
        curNode = curNode->next;
        free(tmpNode);
    }

    stack->size = 0;
}

StackElement stackTop(Stack stack) {
    if (stackIsEmpty(stack)) {
        fprintf(stderr, "The stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data->element;
}
