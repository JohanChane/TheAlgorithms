#include <stdio.h>

#include "test_utils/utils.h"
#include "binary_search_tree.h"

#define ARRAY_SIZE (10000 * 100)

static void testBst();
static int checkBst(BinSearchTree binSearchTree);
static void printBst(BinSearchTree binSearchTree);
static void printBinSearchTree(BinSearchTree binSearchTree);

static Position bstFindMin(BinSearchTree binSearchTree);
static Position bstFindMax(BinSearchTree binSearchTree);

static void testBst() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 100, ARRAY_SIZE + 999);
    /* printArray(array, ARRAY_SIZE); */

    BinSearchTree binSearchTree = NULL;
    int center = ARRAY_SIZE / 2;
    clock_t start, end;
    start = getTime();
    for (int i = center; i >= 0; i--) {
        binSearchTree = bstInsert(array[i], binSearchTree);
    }
    for (int j = center + 1; j < ARRAY_SIZE; j++) {
        binSearchTree = bstInsert(array[j], binSearchTree);
    }
    /* int checkRet = checkBst(binSearchTree); */
    /* if (checkRet < 0) { */
    /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
    /*     exit(EXIT_FAILURE); */
    /* } */
    /* printBst(binSearchTree); */
    printf("Result of bstFindMin is %d\n", bstFindMin(binSearchTree)->element);
    printf("Result of bstFindMax is %d\n", bstFindMax(binSearchTree)->element);

    for (int q = 0; q < ARRAY_SIZE; q++) {
        binSearchTree = bstDelete(array[q], binSearchTree);
        /* checkRet = checkBst(binSearchTree); */
        /* if (checkRet < 0) { */
        /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
        /*     exit(EXIT_FAILURE); */
        /* } */
    }
    printBst(binSearchTree);
    end = getTime();
    printf("duration = %lfs\n", (double) calcDuration(start, end));
}

static void printBst(BinSearchTree binSearchTree) {
    printBinSearchTree(binSearchTree);
    printf("\n");
}

// 中序遍历
static void printBinSearchTree(BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        return;
    }

    printBinSearchTree(binSearchTree->leftChild);
    printf("%d\t", binSearchTree->element);
    printBinSearchTree(binSearchTree->rightChild);
}

static int checkBst(BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        return 0;
    }

    if (binSearchTree->leftChild) {
        if (binSearchTree->leftChild->element >= binSearchTree->element) {
            return -1;
        }
    } else if (binSearchTree->rightChild) {
        if (binSearchTree->rightChild->element <= binSearchTree->element) {
            return -2;
        }
    } else {
        return 0;
    }

    int checkRet = checkBst(binSearchTree->leftChild);
    if (checkRet < 0) {
        return checkRet;
    }

    checkRet = checkBst(binSearchTree->rightChild);
    if (checkRet < 0) {
        return checkRet;
    }

    return 0;
}

static Position bstFindMin(BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        return NULL;
    }

    Position curPos = binSearchTree;
    while (curPos->leftChild) {
        curPos = curPos->leftChild;
    }

    return curPos;
}

static Position bstFindMax(BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        return NULL;
    }

    Position curPos = binSearchTree;
    while (curPos->rightChild) {
        curPos = curPos->rightChild;
    }

    return curPos;
}

int main() {
    testBst();

    return 0;
}
