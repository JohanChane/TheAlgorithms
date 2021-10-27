#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "splay_tree.h"

#define ARRAY_SIZE (10000 * 1)

static void testSplayTree();
static int checkSplayTree(SplayTree splayTree);
static void printSplayTreeInOrder(SplayTree splayTree);
static void printSplayTree(SplayTree splayTree);

static Position splayTreeFindMin(SplayTree splayTree);
static Position splayTreeFindMax(SplayTree splayTree);

static void testSplayTree() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 100, ARRAY_SIZE + 999);
    /* printArray(array, ARRAY_SIZE); */

    SplayTree splayTree = NULL;
    int center = ARRAY_SIZE / 2;
    clock_t start, end;
    start = getTime();
    for (int i = center; i >= 0; i--) {
        splayTree = splayTreeInsert(array[i], splayTree);
    }
    for (int j = center + 1; j < ARRAY_SIZE; j++) {
        splayTree = splayTreeInsert(array[j], splayTree);
    }
    /* int checkRet = checkSplayTree(splayTree); */
    /* if (checkRet < 0) { */
    /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
    /*     exit(EXIT_FAILURE); */
    /* } */
    /* printSplayTree(splayTree); */
    printf("Result of bstFindMin is %d\n", splayTreeFindMin(splayTree)->element);
    printf("Result of bstFindMax is %d\n", splayTreeFindMax(splayTree)->element);

    for (int q = 0; q < ARRAY_SIZE; q++) {
        splayTree = splayTreeDelete(array[q], splayTree);
        /* checkRet = checkSplayTree(splayTree); */
        /* if (checkRet < 0) { */
        /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
        /*     exit(EXIT_FAILURE); */
        /* } */
    }
    end = getTime();
    printSplayTree(splayTree);
    printf("duration = %lfs\n", calcDuration(start, end));

    splayTree = splayTreeMakeEmpty(splayTree);
}

static void printSplayTreeInOrder(SplayTree splayTree) {
    if (!splayTree) {
        return;
    }

    printSplayTreeInOrder(splayTree->leftChild);
    printf("%d\t", splayTree->element);
    printSplayTreeInOrder(splayTree->rightChild);
}

static void printSplayTree(SplayTree splayTree) {
    printSplayTreeInOrder(splayTree);
    printf("\n");
}

static int checkSplayTree(SplayTree splayTree) {
    if (!splayTree) {
        return 0;
    }

    if (splayTree->leftChild) {
        if (splayTree->leftChild->element >= splayTree->element) {
            return -1;
        }
    } else if (splayTree->rightChild) {
        if (splayTree->rightChild->element <= splayTree->element) {
            return -2;
        }
    } else {
        return 0;
    }

    int checkRet = checkSplayTree(splayTree->leftChild);
    if (checkRet < 0) {
        return checkRet;
    }

    checkRet = checkSplayTree(splayTree->rightChild);
    if (checkRet < 0) {
        return checkRet;
    }

    return 0;
}

static Position splayTreeFindMin(SplayTree splayTree) {
    if (!splayTree) {
        return NULL;
    }

    Position curPos = splayTree;
    while (curPos->leftChild) {
        curPos = curPos->leftChild;
    }

    return curPos;
}

static Position splayTreeFindMax(SplayTree splayTree) {
    if (!splayTree) {
        return NULL;
    }

    Position curPos = splayTree;
    while (curPos->rightChild) {
        curPos = curPos->rightChild;
    }

    return curPos;
}

int main() {
    testSplayTree();
    return 0;
}
