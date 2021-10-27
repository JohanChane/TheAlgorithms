#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "radix_sort.h"

#define ARRAY_SIZE (10000 * 10)

static void testRadixSort();

static void testRadixSort() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end;
    start = getTime();
    radixSort(array, ARRAY_SIZE);
    end = getTime();
    printArray(array, ARRAY_SIZE);
    printf("duration = %lfs\n", calcDuration(start, end));

    if (checkArrayOrder(array, ARRAY_SIZE, ASC) < 0) {
        fprintf(stderr, "checkArrayOrder failed\n");
        return;
    }
}

int main() {
    testRadixSort();
    return 0;
}
