#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "binary_heap.h"

#define ARRAY_SIZE (10000 * 10)

int binHeapCmp(BinHeapElement e1, BinHeapElement e2) {
    return e1 - e2;
}

static void testBinHeap();
static void printBinHeap(BinHeap binHeap);
static int checkBinHeap(BinHeap binHeap);

static void testBinHeap() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 100, ARRAY_SIZE + 999);
    printArray(array, ARRAY_SIZE);

    BinHeap binHeap = binHeapCreate(ARRAY_SIZE + 1);
    clock_t start, end;
    start = getTime();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        binHeapPush(array[i], binHeap);
    }
    printBinHeap(binHeap);

    int sortedArray[ARRAY_SIZE];
    int checkRet;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        // checkRet = checkBinHeap(binHeap);
        // if (checkRet < 0) {
        //     fprintf(stderr, "checkRet: %d\n", checkRet);
        //     exit(EXIT_FAILURE);
        // }
        sortedArray[i] = binHeapTop(binHeap); binHeapPop(binHeap);
    }
    end = getTime();
    printBinHeap(binHeap);
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    // printArray(sortedArray, ARRAY_SIZE);
    if (checkArrayOrder(sortedArray, ARRAY_SIZE, ASC) < 0) {
        fprintf(stderr, "checkArrayOrder failed.\n");
        return;
    }

    binHeapDestroy(binHeap);
}

static void printBinHeap(BinHeap binHeap) {
    for (int i = 1; i <= binHeap->size; i++) {
        printf("%d\t", binHeap->elements[i]);
    }
    printf("\n");
}

static int checkBinHeap(BinHeap binHeap) {
    if (binHeapIsEmpty(binHeap)) {
        return 0;
    }

    int curPos = 1;
    int leftChild = curPos * 2, rightChild, minChild;
    while (leftChild <= binHeap->size) {
        rightChild = leftChild + 1;
        minChild = leftChild;
        if (rightChild <= binHeap->size && \
                binHeapCmp(binHeap->elements[leftChild], binHeap->elements[rightChild]) > 0) {
            minChild = rightChild;
        }

        // 父结点可以等于 minChild 结点
        if (binHeapCmp(binHeap->elements[curPos], binHeap->elements[minChild]) > 0) {
            return -1;
        }
        curPos++;
        leftChild = curPos * 2;
    }

    return 0;
}

int main() {
    testBinHeap();
    return 0;
}
