#include <stdio.h>
#include <stdlib.h>

#include "heap_sort.h"
#include "test_utils/utils.h"

#define ARRAY_SIZE (10000 * 100)

static void testHeapSort();

static void testHeapSort() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end;
    start = getTime();
    heapSort(array, ARRAY_SIZE);
    end = getTime();
    printArray(array, ARRAY_SIZE);
    printf("duration = %lfs\n", calcDuration(start, end));

    if (checkArrayOrder(array, ARRAY_SIZE, ASC) < 0) {
        fprintf(stderr, "checkArrayOrder failed\n");
        return;
    }
}

int main() {
    testHeapSort();
}
