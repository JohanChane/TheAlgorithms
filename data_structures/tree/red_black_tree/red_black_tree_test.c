#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "red_black_tree.h"

#define ARRAY_SIZE (10000 * 10)

static void testRBTree();

static void testRBTree() {
    Element array[ARRAY_SIZE];
    genRandomNumsNotSame(array, ARRAY_SIZE, 1, ARRAY_SIZE * 100);
    printArray(array, ARRAY_SIZE);

    RBTree rbtree = rbtreeCreate();
    clock_t start, end;
    start = getTime();
    // ### 插入
    for (int i = 0; i < ARRAY_SIZE; i++) {
        rbtreeInsert(array[i], rbtree);
    }

    int ret = checkRBTree(rbtree);
    if (ret < 0) {
        fprintf(stderr, "checkRBTreeSubTree ret is %d!\n", ret);
        exit(EXIT_FAILURE);
    }

    traverseBTree(rbtree);

    // ### 删除
    for (int j = ARRAY_SIZE / 2; j >= 0; j--) {
        rbtreeDelete(array[j], rbtree);
    }
    for (int k = ARRAY_SIZE / 2 + 1; k < ARRAY_SIZE; k++) {
        rbtreeDelete(array[k], rbtree);
    }
    end = getTime();

    rbtreeDestroy(rbtree);

    printf("duration = %lfs\n", calcDuration(start, end));
}


int main() {
    testRBTree();
    return 0;
}
