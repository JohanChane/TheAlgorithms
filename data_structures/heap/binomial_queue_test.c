#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "binomial_queue.h"

#define ARRAY_SIZE (1000 * 10)

static void testBinQueue();

static void testBinQueue() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 100, ARRAY_SIZE + 999);
    /* printArray(array, ARRAY_SIZE); */

    BinQueue binQueue = binQueueInitialize(1);
    clock_t start, end;
    start = getTime();
    for (int j = 0; j < ARRAY_SIZE; j++) {
        binQueue = binQueueInsert(array[j], binQueue);
    }
    /* int checkRet = checkBinQueue(binQueue); */
    /* if (checkRet < 0) { */
    /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
    /*     exit(EXIT_FAILURE); */
    /* } */
    /* printBinQueue(binQueue); */

    for (int q = 0; q < ARRAY_SIZE; q++) {
        if (!binQueue->size) {
            break;
        }
        binQueueDeleteMin(binQueue);
        /* checkRet = checkBinQueue(binQueue); */
        /* if (checkRet < 0) { */
        /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
        /*     exit(EXIT_FAILURE); */
        /* } */
    }
    /* printBinQueue(binQueue); */
    end = getTime();
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    binQueueDestroy(binQueue);
}

int main() {
    testBinQueue();
    return 0;
}
