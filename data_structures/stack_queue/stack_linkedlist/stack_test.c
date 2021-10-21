#include <stdio.h>
#include <stdbool.h>

#include "stack.h"
#include "test_utils/utils.h"

#define ARRAY_SIZE (10000 * 10)

static void testStack();

static void testStack() {
    StackElement array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    Stack stack = stackCreate();
    clock_t start, end;
    start = getTime();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        stackPush(array[i], stack);
    }
    StackElement tmpArray[ARRAY_SIZE];
    for (int j = ARRAY_SIZE - 1; j >= 0; j--) {
        tmpArray[j] = stackPop(stack);
    }
    end = getTime();

    printf("duration = %lfs\n", (double) calcDuration(start, end));

    if (!areArraysSame(array, tmpArray, ARRAY_SIZE)) {
        fprintf(stderr, "Arrays aren't same.\n");
        return;
    }

    stackDestroy(stack);
}

int main() {
    testStack();

    return 0;
}
