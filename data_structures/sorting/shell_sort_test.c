#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "shell_sort.h"
#include "test_utils/utils.h"

#define ARRAY_SIZE (10000 * 100)

static void testShellSort();

static void testShellSort() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end;
    start = getTime();
    shellSort(array, ARRAY_SIZE);
    end = getTime();
    printArray(array, ARRAY_SIZE);
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    if (checkArrayOrder(array, ARRAY_SIZE, ASC) < 0) {
        fprintf(stderr, "checkArrayOrder failed\n");
        return;
    }
}

int main() {
    testShellSort();
    return 0;
}
