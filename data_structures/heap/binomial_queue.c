#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "binomial_queue.h"

#define MAX_ELEMENT INT_MAX

static int binQueueCalTreeCount(int capacity);
static int binQueueCalCapacity(int treeCount);

static BinTree binTreeCombine(BinTree binTree1, BinTree binTree2);
static void binTreeDestroy(BinTree binTree);

// ### debug
static int checkBinTree(BinTree binTree);
static int binTreeSize();
static void printBinTree(BinTree binTree);
static void printBinTreeUtil(BinTree binTree);

// 合并之后，为了 destroy, 会将 binQueue2 的所有二项树置为空。
BinQueue binQueueMerge(BinQueue binQueue1, BinQueue binQueue2) {
    int newSize = binQueue1->size + binQueue2->size;
    if (newSize > binQueue1->capacity) {
        binQueueRecapacity(newSize, binQueue1);
    }
    if (newSize > binQueue2->capacity) {
        binQueueRecapacity(newSize, binQueue2);
    }

    binQueue1->size = newSize;
    BinTree binTreeCarry = NULL, tmpBinTree;
    for (int i = 0, j = 1; j <= binQueue1->size; i++, j *= 2) {
        switch ((!!binQueue1->theTrees[i]) + (!!binQueue2->theTrees[i] << 1) + (!!binTreeCarry << 2)) {
            case 0:
            case 1:
                break;
            case 2:
                binQueue1->theTrees[i] = binQueue2->theTrees[i];
                binQueue2->theTrees[i] = NULL;
                break;
            case 3:
                binTreeCarry = binTreeCombine(binQueue1->theTrees[i], binQueue2->theTrees[i]);
                binQueue1->theTrees[i] = binQueue2->theTrees[i] = NULL;
                break;
            case 4:
                binQueue1->theTrees[i] = binTreeCarry;
                binTreeCarry = NULL;
                break;
            case 5:
                binTreeCarry = binTreeCombine(binQueue1->theTrees[i], binTreeCarry);
                binQueue1->theTrees[i] = NULL;
                break;
            case 6:
                binTreeCarry = binTreeCombine(binQueue2->theTrees[i], binTreeCarry);
                binQueue2->theTrees[i] = NULL;
                break;
            case 7:
                tmpBinTree = binTreeCarry;
                binTreeCarry = binTreeCombine(binQueue1->theTrees[i], binQueue2->theTrees[i]);
                binQueue1->theTrees[i] = tmpBinTree;
                binQueue2->theTrees[i] = NULL;
                break;
        }
    }

    return binQueue1;
}

BinQueue binQueueInsert(Element element, BinQueue binQueue) {
    // ### 创建 newBinQueue
    BinQueue newBinQueue = binQueueInitialize(1);
    // #### 创建 newBinTree
    BinTree newBinTree = malloc(sizeof(struct BinomialTreeNode));
    if (!newBinTree) {
        fprintf(stderr, "No space for creating newBinTree!\n");
        exit(EXIT_FAILURE);
    }
    newBinTree->element = element;
    newBinTree->leftChild = newBinTree->nextSibling = NULL;

    // #### 将 newBinTree 加入 newBinQueue
    newBinQueue->theTrees[0] = newBinTree;
    newBinQueue->size++;

    // ### 合并
    binQueue = binQueueMerge(binQueue, newBinQueue);
    binQueueDestroy(newBinQueue);

    return binQueue;
}

Element binQueueDeleteMin(BinQueue binQueue) {
    if (!binQueue->size) {
        fprintf(stderr, "binQueue->size == 0!\n");
        exit(EXIT_FAILURE);
    }

    // ### 找出最小的二项树
    Element minElement = MAX_ELEMENT;
    int indexOfMinBinTree = 0;
    int treeCount = binQueueCalTreeCount(binQueue->capacity);
    // binQueue->size > 0
    for (int i = 0; i < treeCount; i++) {
        if (binQueue->theTrees[i] && binQueue->theTrees[i]->element < minElement) {
            minElement = binQueue->theTrees[i]->element;
            indexOfMinBinTree = i;
        }
    }

    // ### 删除最小的结点
    Position oldRoot = binQueue->theTrees[indexOfMinBinTree];
    BinTree deletedBinTree = oldRoot->leftChild;
    free(oldRoot);

    // ### 将剩余的结点放入一个 binQueue 中
    int deletedBinQueueSize = (1 << indexOfMinBinTree) - 1;
    BinQueue deletedBinQueue = binQueueInitialize(deletedBinQueueSize);
    // indexOfMinBinTree = 0 时，size = 0;
    deletedBinQueue->size = deletedBinQueueSize;
    for (int j = indexOfMinBinTree - 1; j >= 0; j--) {
        deletedBinQueue->theTrees[j] = deletedBinTree;
        deletedBinTree = deletedBinTree->nextSibling;
        deletedBinQueue->theTrees[j]->nextSibling = NULL;
    }

    // ### 更新 binQueue
    binQueue->theTrees[indexOfMinBinTree] = NULL;
    binQueue->size -= deletedBinQueue->size + 1;

    // ### 合并
    binQueue = binQueueMerge(binQueue, deletedBinQueue);
    binQueueDestroy(deletedBinQueue);

    return minElement;
}

BinQueue binQueueInitialize(int capacity) {
    int treeCount = binQueueCalTreeCount(capacity);
    capacity = binQueueCalCapacity(treeCount);

    // ### 创建 binQueue
    BinQueue binQueue = malloc(sizeof(struct BinomialQueue));
    if (!binQueue) {
        fprintf(stderr, "No space for creating binQueue!\n");
        exit(EXIT_FAILURE);
    }
    binQueue->theTrees = malloc(sizeof(BinTree) * treeCount);
    if (!binQueue->theTrees) {
        fprintf(stderr, "No space for creating theTrees!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < treeCount; i++) {
        binQueue->theTrees[i] = NULL;
    }
    binQueue->capacity = capacity;
    binQueue->size = 0;

    return binQueue;
}

void binQueueDestroy(BinQueue binQueue) {
    int treeCount = 0;
    int tmp = binQueue->capacity + 1;
    while (tmp >>= 1) {
        treeCount++;
    }

    for (int i = 0; i < treeCount; i++) {
        binTreeDestroy(binQueue->theTrees[i]);
    }
    free(binQueue->theTrees);
    free(binQueue);
}

void binQueueRecapacity(int capacity, BinQueue binQueue) {
    int oldTreeCount = binQueueCalTreeCount(binQueue->capacity);
    int newTreeCount = binQueueCalTreeCount(capacity);
    int newCapacity = binQueueCalCapacity(newTreeCount);

    BinTree* newBinTrees = malloc(sizeof(BinTree) * newTreeCount);
    if (!newBinTrees) {
        fprintf(stderr, "No space for creating newBinTree!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < oldTreeCount; i++) {
        newBinTrees[i] = binQueue->theTrees[i];
    }
    for (int j = oldTreeCount; j < newTreeCount; j++) {
        newBinTrees[j] = NULL;
    }
    free(binQueue->theTrees);
    binQueue->theTrees = newBinTrees;
    binQueue->capacity = newCapacity;
}

static int binQueueCalTreeCount(int capacity) {
    // ### 计算 treeCount
    // pow(2, k + 1) < capacity + 1
    // tmp = pow(2, k + 1)
    // treeCount = k + 1
    int treeCount = 0;
    int tmp = 1;
    while (tmp < capacity + 1) {
        tmp <<= 1;
        treeCount++;
    }
    return treeCount;
}

static int binQueueCalCapacity(int treeCount) {
    return (1 << treeCount) - 1;
}


static BinTree binTreeCombine(BinTree binTree1, BinTree binTree2) {
    if (binTree1->element > binTree2->element) {
        return binTreeCombine(binTree2, binTree1);
    }

    // binTree1->element <= binTree2->element
    binTree2->nextSibling = binTree1->leftChild;
    binTree1->leftChild = binTree2;

    return binTree1;
}

static void binTreeDestroy(BinTree binTree) {
    if (!binTree) {
        return;
    }

    // 销毁所有儿子
    Position tmpPos = binTree->leftChild;
    while (tmpPos) {
        binTreeDestroy(tmpPos);
        tmpPos = tmpPos->nextSibling;
    }

    free(binTree);
}

int checkBinQueue(BinQueue binQueue) {
    if (!binQueue) {
        return 0;
    }

    int checkRet;
    int sizeCount = 0;
    int size;
    int treeCount = binQueueCalTreeCount(binQueue->capacity);
    for (int i = 0; i < treeCount; i++) {
        if (!binQueue->theTrees[i]) {
            continue;
        }

        size = binTreeSize(binQueue->theTrees[i]);
        sizeCount += size;
        if ((1 << i) != size) {
            return -1;
        }

        checkRet = checkBinTree(binQueue->theTrees[i]);
        if (checkRet < 0) {
            fprintf(stderr, "in checkBinQueue. checkRet: %d\n", checkRet);
            return -2;
        }
    }

    if (binQueue->size != sizeCount) {
        return -3;
    }

    return 0;
}

void printBinQueue(BinQueue binQueue) {
    if (!binQueue) {
        return;
    }

    int treeCount = binQueueCalTreeCount(binQueue->capacity);
    for (int i = 0; i < treeCount; i++) {
        printf("%d: ", i);
        printBinTree(binQueue->theTrees[i]);
    }
}

static int checkBinTree(BinTree binTree) {
    if (!binTree) {
        return 0;
    }

    int lastSize = binTreeSize(binTree);
    int size;
    int checkRet;
    Position curPos = binTree->leftChild;
    while (curPos) {
        // ### 父结点是否是最小的
        if (curPos->element < binTree->element) {
            return -1;
        }

        // ### 每个儿子的 size 是否是 pow(2, k)
        size = binTreeSize(curPos);
        if (size * 2 != lastSize) {
            return -2;
        }
        lastSize = size;

        // ### 儿子是否是二项树
        checkRet = checkBinTree(curPos);
        if (checkRet < 0) {
            return checkRet;
        }

        curPos = curPos->nextSibling;
    }

    return 0;
}

static int binTreeSize(BinTree binTree) {
    if (!binTree) {
        return 0;
    }

    Position curPos = binTree->leftChild;
    int size = 0;
    while (curPos) {
        size += binTreeSize(curPos);
        curPos = curPos->nextSibling;
    }
    size++;

    return size;
}

static void printBinTree(BinTree binTree) {
    printBinTreeUtil(binTree);
    printf("\n");
}

static void printBinTreeUtil(BinTree binTree) {
    if (!binTree) {
        return;
    }

    printf("%d\t", binTree->element);

    // 打印所有儿子
    Position tmpPos = binTree->leftChild;
    while (tmpPos) {
        printBinTreeUtil(tmpPos);
        tmpPos = tmpPos->nextSibling;
    }
}
