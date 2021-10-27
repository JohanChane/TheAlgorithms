#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "insertion_sort.h"
#include "test_utils/utils.h"

#define ARRAY_SIZE (10000 * 10)

static void testInsertionSort() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end;
    start = getTime();
    insertionSort(array, ARRAY_SIZE, INSERTION_SORT_ASC);
    end = getTime();
    printArray(array, ARRAY_SIZE);
    printf("duration = %lfs\n", calcDuration(start, end));

    if (checkArrayOrder(array, ARRAY_SIZE, ASC) < 0) {
        fprintf(stderr, "checkArrayOrder failed\n");
        return;
    }
}

int main() {
    testInsertionSort();
    return 0;
}


