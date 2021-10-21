#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test_utils/utils.h"
#include "bucket_sort.h"

#define ARRAY_SIZE (10000 * 10)

static void testBucketSort();

static void testBucketSort() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);
    printArray(array, ARRAY_SIZE);

    clock_t start, end;
    start = getTime();
    bucketSort(array, ARRAY_SIZE);
    end = getTime();
    printArray(array, ARRAY_SIZE);
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    if (checkArrayOrder(array, ARRAY_SIZE, ASC) < 0) {
        fprintf(stderr, "checkArrayOrder failed\n");
        return;
    }
}

int main() {
    testBucketSort();
}
