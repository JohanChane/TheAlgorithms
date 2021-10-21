#include <stdio.h>
#include <stdlib.h>

#include "bubble_sort.h"
#include "test_utils/utils.h"

#define ARRAY_SIZE (10000 * 10)

static void testBubbleSort();

static void testBubbleSort() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end;
    start = getTime();
    bubbleSort(array, ARRAY_SIZE);
    end = getTime();
    printArray(array, ARRAY_SIZE);
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    if (checkArrayOrder(array, ARRAY_SIZE, ASC) < 0) {
        fprintf(stderr, "checkArrayOrder failed\n");
        return;
    }
}

int main() {
    testBubbleSort();
    return 0;
}

