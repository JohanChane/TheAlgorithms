#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counting_sort.h"
#include "test_utils/utils.h"

// 内存至少 ARRAY_SIZE * 4B
#define ARRAY_SIZE (10000 * 100)

static void testCountingSort();

static void testCountingSort() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 100, ARRAY_SIZE + 999);

    clock_t start, end;
    start = getTime();
    countingSort(array, ARRAY_SIZE);
    end = getTime();
    printArray(array, ARRAY_SIZE);
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    if (checkArrayOrder(array, ARRAY_SIZE, ASC) < 0) {
        fprintf(stderr, "checkArrayOrder failed\n");
        return;
    }
}

int main() {
    testCountingSort();
    return 0;
}
