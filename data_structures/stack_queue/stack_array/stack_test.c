#include <stdio.h>

#include "test_utils/utils.h"
#include "stack.h"

#define ARRAY_SIZE (10000 * 10)

static void testStack();

static void testStack() {
    Element array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end, duration;
    Stack stack = stackCreate(20);
    start = getTime();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        stackPush(array[i], stack);
    }
    printf("size of stack: %d\n", stackSize(stack));

    Element tmpArray[ARRAY_SIZE];
    for (int j = 0; j < ARRAY_SIZE; j++) {
        tmpArray[j] = stackTop(stack); stackPop(stack);
    }
    reverseArray(tmpArray, ARRAY_SIZE);

    end = getTime();
    printf("size of stack: %d\n", stackSize(stack));
    printf("duration = %lfs\n", calcDuration(start, end));

    if (!areArraysSame(tmpArray, array, ARRAY_SIZE)) {
        fprintf(stderr, "Array aren't same.\n");
        return;
    }

    stackDestroy(stack);
}

int main() {
    testStack();

    return 0;

}
