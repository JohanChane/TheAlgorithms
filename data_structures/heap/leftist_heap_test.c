#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "leftist_heap.h"

#define ARRAY_SIZE (1000 * 10)

static void testLeftistHeap();

static int checkLeftistHeap(LeftistHeap leftistHeap);
static void printLeftistHeap(LeftistHeap leftistHeap);
static void printLeftistHeapUtil(LeftistHeap leftistHeap);

static void testLeftistHeap() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 100, ARRAY_SIZE + 999);
    /* printArray(array, ARRAY_SIZE); */

    LeftistHeap leftistHeap = leftistHeapInitialize();
    int center = ARRAY_SIZE / 2;
    clock_t start, end, duration;
    start = getTime();
    for (int i = center; i >= 0; i--) {
        leftistHeap = leftistHeapInsert(array[i], leftistHeap);
    }
    for (int j = center + 1; j < ARRAY_SIZE; j++) {
        leftistHeap = leftistHeapInsert(array[j], leftistHeap);
    }
    /* int checkRet = checkLeftistHeap(leftistHeap); */
    /* if (checkRet < 0) { */
    /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
    /*     exit(EXIT_FAILURE); */
    /* } */
    /* printLeftistHeap(leftistHeap); */

    for (int q = 0; q < ARRAY_SIZE; q++) {
        leftistHeap = leftistHeapDeleteMin(leftistHeap);
        if (!leftistHeap) {
            break;
        }
        /* checkRet = checkLeftistHeap(leftistHeap); */
        /* if (checkRet < 0) { */
        /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
        /*     exit(EXIT_FAILURE); */
        /* } */
    }
    printLeftistHeap(leftistHeap);
    end = getTime();
    // 取上限
    duration = ((end - start) - 1) / CLOCKS_PER_SEC + 1;
    printf("duration = %lfs\n", (double) duration);

    leftistHeapDestroy(leftistHeap);
}

static int checkLeftistHeap(LeftistHeap leftistHeap) {
    if (!leftistHeap) {
        return 0;
    }

    bool isHeapInOrder = true;
    int leftChildNpl;
    if (!leftistHeap->leftChild) {
        leftChildNpl = -1;
    } else {
        leftChildNpl = leftistHeap->leftChild->npl;
        if (leftistHeap->element > leftistHeap->leftChild->element) {
            isHeapInOrder = false;
        }
    }

    int rightChildNpl;
    if (!leftistHeap->rightChild) {
        rightChildNpl = -1;
    } else {
        rightChildNpl = leftistHeap->rightChild->npl;
        if (leftistHeap->element > leftistHeap->rightChild->element) {
            isHeapInOrder = false;
        }
    }

    if (leftChildNpl < rightChildNpl) {
        return -1;
    }

    if (leftistHeap->npl != rightChildNpl + 1) {
        return -2;
    }

    if (!isHeapInOrder) {
        return -3;
    }

    int checkRet = checkLeftistHeap(leftistHeap->leftChild);
    if (checkRet < 0) {
        return checkRet;
    }

    checkRet = checkLeftistHeap(leftistHeap->rightChild);
    if (checkRet < 0) {
        return checkRet;
    }

    return 0;
}

static void printLeftistHeap(LeftistHeap leftistHeap) {
    printLeftistHeapUtil(leftistHeap);
    printf("\n");
}

static void printLeftistHeapUtil(LeftistHeap leftistHeap) {
    if (!leftistHeap) {
        return;
    }

    printf("%d\t", leftistHeap->element);
    printLeftistHeapUtil(leftistHeap->leftChild);
    printLeftistHeapUtil(leftistHeap->rightChild);
}

int main() {
    testLeftistHeap();
    return 0;
}
