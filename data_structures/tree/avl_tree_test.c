#include <stdio.h>

#include "test_utils/utils.h"
#include "avl_tree.h"

#define ARRAY_SIZE (10000 * 1)

static void testAvlTree();
static int checkAvlTree(AvlTree avlTree);
static void printAvlTreeInOrder(AvlTree avlTree);
static void printAvlTree(AvlTree avlTree);

static void testAvlTree() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 100, ARRAY_SIZE + 999);
    /* printArray(array, ARRAY_SIZE); */

    AvlTree avlTree = NULL;
    int center = ARRAY_SIZE / 2;
    clock_t start, end;
    start = getTime();
    for (int i = center; i >= 0; i--) {
        avlTree = avlTreeInsert(array[i], avlTree);
    }
    for (int j = center + 1; j < ARRAY_SIZE; j++) {
        avlTree = avlTreeInsert(array[j], avlTree);
    }
    /* printAvlTree(avlTree); */
    printf("Result of avlTreeFindMin is %d\n", avlTreeFindMin(avlTree)->element);
    printf("Result of avlTreeFindMax is %d\n", avlTreeFindMax(avlTree)->element);
    /* int checkRet = checkAvlTree(avlTree); */
    /* if (checkRet < 0) { */
    /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
    /*     exit(EXIT_FAILURE); */
    /* } */

    for (int q = 0; q < ARRAY_SIZE; q++) {
        avlTree = avlTreeDelete(array[q], avlTree);
        /* checkRet = checkAvlTree(avlTree); */
        /* if (checkRet < 0) { */
        /*     fprintf(stderr, "checkRet: %d\n", checkRet); */
        /*     exit(EXIT_FAILURE); */
        /* } */
    }
    end = getTime();
    printAvlTree(avlTree);
    printf("duration = %lfs\n", (double) calcDuration(start, end));
}

// 中序遍历
static void printAvlTreeInOrder(AvlTree avlTree) {
    if (!avlTree) {
        return;
    }

    printAvlTreeInOrder(avlTree->leftChild);
    printf("%d\t", avlTree->element);
    printAvlTreeInOrder(avlTree->rightChild);
}

static void printAvlTree(AvlTree avlTree) {
    printAvlTreeInOrder(avlTree);
    printf("\n");
}

static int checkAvlTree(AvlTree avlTree) {
    if (!avlTree) {
        return 0;
    }

    // ### 检查父结点
    if (avlTree->leftChild) {
        if (avlTree->leftChild->element >= avlTree->element) {
            return -1;
        }
    } else if (avlTree->rightChild) {
        if (avlTree->rightChild->element <= avlTree->element) {
            return -2;
        }
    } else {
        return 0;
    }

    int diff = avlTreeHeight(avlTree->leftChild) - avlTreeHeight(avlTree->rightChild);
    if (diff > 1) {
        return -3;
    } else if (diff < -1) {
        return -4;
    } else {
        ;
    }

    // ### 检查子结点
    int checkRet = checkAvlTree(avlTree->leftChild);
    if (checkRet < 0) {
        return checkRet;
    }
    checkRet = checkAvlTree(avlTree->rightChild);
    if (checkRet < 0) {
        return checkRet;
    }

    return 0;
}

int main() {
    testAvlTree();
    return 0;
}
