#include <stdio.h>

#include "test_utils/utils.h"
#include "skew_heap.h"

#define ARRAY_SIZE (1000 * 10)

static void testSkewHeap();

static int checkSkewHeap(SkewHeap skewHeap);
static void printSkewHeap(SkewHeap skewHeap);
static void printSkewHeapUtil(SkewHeap skewHeap);

static void testSkewHeap() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 100, ARRAY_SIZE + 999);
    /* printArray(array, ARRAY_SIZE); */

    SkewHeap skewHeap = skewHeapInitialize();
    int center = ARRAY_SIZE / 2;
    clock_t start, end;
    start = getTime();
    for (int i = center; i >= 0; i--) {
        skewHeap = skewHeapInsert(array[i], skewHeap);
    }
    for (int j = center + 1; j < ARRAY_SIZE; j++) {
        skewHeap = skewHeapInsert(array[j], skewHeap);
    }
    /* int checkRet = checkSkewHeap(skewHeap); */
    /* if (checkRet < 0) { */
    /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
    /*     exit(EXIT_FAILURE); */
    /* } */
    /* printSkewHeap(skewHeap); */

    for (int q = 0; q < ARRAY_SIZE; q++) {
        skewHeap = skewHeapDeleteMin(skewHeap);
        if (!skewHeap) {
            break;
        }
        /* checkRet = checkSkewHeap(skewHeap); */
        /* if (checkRet < 0) { */
        /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
        /*     exit(EXIT_FAILURE); */
        /* } */
    }
    printSkewHeap(skewHeap);
    end = getTime();
    printf("duration = %lfs\n", calcDuration(start, end));

    skewHeapDestroy(skewHeap);
}

static int checkSkewHeap(SkewHeap skewHeap) {
    if (!skewHeap) {
        return 0;
    }

    bool isHeapInOrder = true;
    if (skewHeap->leftChild && skewHeap->element > skewHeap->leftChild->element) {
        isHeapInOrder = false;
    }

    if (skewHeap->rightChild && skewHeap->element > skewHeap->rightChild->element) {
        isHeapInOrder = false;
    }

    if (!isHeapInOrder) {
        return -1;
    }

    int checkRet = checkSkewHeap(skewHeap->leftChild);
    if (checkRet < 0) {
        return checkRet;
    }

    checkRet = checkSkewHeap(skewHeap->rightChild);
    if (checkRet < 0) {
        return checkRet;
    }

    return 0;
}

static void printSkewHeap(SkewHeap skewHeap) {
    printSkewHeapUtil(skewHeap);
    printf("\n");
}

static void printSkewHeapUtil(SkewHeap skewHeap) {
    if (!skewHeap) {
        return;
    }

    printf("%d\t", skewHeap->element);
    printSkewHeapUtil(skewHeap->leftChild);
    printSkewHeapUtil(skewHeap->rightChild);
}

int main() {
    testSkewHeap();
    return 0;
}
