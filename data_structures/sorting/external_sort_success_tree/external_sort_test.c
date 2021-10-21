#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "external_sort.h"
#include "test_utils/utils.h"
#include "test_utils/insertion_sort.h"

#define K (5)
#define ARRAY_SIZE (10000 * 10)

static void testExternalSort();

static void testExternalSort() {
    // ### 将已排序的数列放入 runs
    int array[K][ARRAY_SIZE];

    for (int i = 0; i < K; i++) {
        genRandomNums(array[i], ARRAY_SIZE, 1, ARRAY_SIZE * 100);
    }

    Run* runs = runsCreate(K, ARRAY_SIZE);
    for (int i = 0; i < K; i++) {
        insertionSort(array[i], ARRAY_SIZE, INSERTION_SORT_ASC);
        for (int j = 0; j < ARRAY_SIZE; j++) {
            queuePush(array[i][j], runs[i]);
        }
        printArray(array[i], ARRAY_SIZE);
    }

    Run mergedRun = queueCreate(ARRAY_SIZE * K);

    clock_t start, end;
    start = getTime();
    extSortSort(mergedRun, runs, K);
    end = getTime();

    int mergedArray[K * ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE * K; i++) {
        mergedArray[i] = queueFront(mergedRun); queuePop(mergedRun);
    }
    printArray(mergedArray, K * ARRAY_SIZE);
    if (checkArrayOrder(mergedArray, ARRAY_SIZE, ASC) < 0) {
        fprintf(stderr, "checkArrayOrder failed\n");
        return;
    }

    printf("duration = %lfs\n", (double) calcDuration(start, end));

    runsDestroy(runs, K);
    queueDestroy(mergedRun);
}

int main() {
    testExternalSort();
}
