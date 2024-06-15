#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "btree.h"

#define ARRAY_SIZE (10000 * 1)

static void testBTree();
static void traverseBTree(BTree btree);
static void traverseBTreeNode(BTreeNode btreeNode, int depth);
static int checkBTree(BTree btree);
static int checkBTreeNode(BTreeNode btreeNode);

static void testBTree() {
    int array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 100, ARRAY_SIZE + 999);
    /* printArray(array, ARRAY_SIZE); */

    BTree btree = btreeInitialize(2);
    int center = ARRAY_SIZE / 2;
    clock_t start, end;
    start = getTime();
    for (int i = center; i >= 0; i--) {
        btreeInsert(array[i], btree);
    }
    for (int j = center + 1; j < ARRAY_SIZE; j++) {
        btreeInsert(array[j], btree);
    }
    int checkRet = checkBTree(btree);
    if (checkRet < 0) {
        fprintf(stderr, "insert checkRet: %d\n", checkRet);
        exit(EXIT_FAILURE);
    }
    /* traverseBTree(btree); */

    for (int q = 0; q < ARRAY_SIZE; q++) {
        btreeDelete(array[q], btree);
        /* traverseBTree(btree); */
        int checkRet = checkBTree(btree);
        if (checkRet < 0) {
            fprintf(stderr, "delete checkRet: %d\n", checkRet);
            exit(EXIT_FAILURE);
        }
    }
    end = getTime();
    printf("After Deleting!\n");
    traverseBTree(btree);
    printf("duration = %lfs\n", calcDuration(start, end));

    btreeDestroy(btree);
}

static void traverseBTree(BTree btree) {
    traverseBTreeNode(btree->root, 0);
    printf("\n");
}

static void traverseBTreeNode(BTreeNode btreeNode, int depth) {
    if (!btreeNode) {
        return;
    }

    if (btreeNode->isLeaf) {
        for (int i = 0; i < btreeNode->keyCount; i++) {
            printf("[%d: %d]\t", depth, btreeNode->keys[i]);
        }
        return;
    }

    // ### nonleaf
    for (int j = 0; j < btreeNode->keyCount; j++) {
        traverseBTreeNode(btreeNode->childs[j], depth + 1);
        printf("<%d: %d>\t", depth, btreeNode->keys[j]);
    }
    traverseBTreeNode(btreeNode->childs[btreeNode->keyCount], depth + 1);
}

static int checkBTree(BTree btree) {
    if (!btree) {
        return 0;
    }

    if (!btree->root) {
        return 0;
    }

    if (btree->root->keyCount < 1) {
        return -1;
    }

    int checkRet;
    if (!btree->root->isLeaf) {
        for (int i = 0; i <= btree->root->keyCount; i++) {
            if (!btree->root->childs[i]) {
                printf("%d\n", i);
                return -2;
            }

            checkRet = checkBTreeNode(btree->root->childs[i]);
            if (checkRet < 0) {
                return -3 + checkRet;
            }
        }
    }

    return 0;
}

// 前提：不检查 root
static int checkBTreeNode(BTreeNode btreeNode) {
    if (!btreeNode) {
        return 0;
    }

    if (btreeNode->keyCount < (btreeNode->t - 1) || btreeNode->keyCount > (2 * btreeNode->t - 1)) {
        return -1;
    }

    if (btreeNode->isLeaf) {
        for (int i = 1; i < btreeNode->keyCount; i++) {
            if (btreeNode->keys[i - 1] > btreeNode->keys[i]) {
                return -2;
            }
        }
    } else {
        int checkRet;
        Position curChild;
        int j;
        for (j = 0; j < btreeNode->keyCount; j++) {
            curChild = btreeNode->childs[j];
            checkRet = checkBTreeNode(curChild);
            if (checkRet < 0) {
                return checkRet;
            }

            if (curChild->keys[curChild->keyCount - 1] > btreeNode->keys[j]) {
                return -3;
            }
        }
        // ### 检查最后一个 child
        curChild = btreeNode->childs[j];
        if (curChild->keys[0] < btreeNode->keys[j - 1]) {
            return -2;
        }
        checkRet = checkBTreeNode(curChild);
        if (checkRet < 0) {
            return checkRet;
        }
    }

    return 0;
}

int main() {
    testBTree();
    return 0;
}
