#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Stack stackCreate(int capacity) {
    Stack stack = malloc(sizeof(struct StackStruct));
    if (!stack) {
        fprintf(stderr, "No space for creating stack\n");
        exit(EXIT_FAILURE);
    }

    stack->data = malloc(sizeof(Element) * capacity);
    if (!stack->data) {
        fprintf(stderr, "No space for stack data\n");
        exit(EXIT_FAILURE);
    }

    stack->size = 0;
    stack->capacity = capacity;

    return stack;
}

void stackDestroy(Stack stack) {
    free(stack->data);
    free(stack);
}

void stackPush(Element element, Stack stack) {
    if (stack->size == stack->capacity) {
        stack->capacity = stack->size * 2;
        Element* newData = malloc(sizeof(Element) * stack->capacity);
        if (!newData) {
            fprintf(stderr, "No space for newData\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < stack->size; i++) {
            newData[i] = stack->data[i];
        }
        free(stack->data);
        stack->data = newData;
    }

    stack->data[stack->size++] = element;
}

void stackPop(Stack stack) {
    if (stack->size <= 0) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }

    stack->size--;
}

Element stackTop(Stack stack) {
    if (!stack->size) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }

    return stack->data[stack->size - 1];
}
