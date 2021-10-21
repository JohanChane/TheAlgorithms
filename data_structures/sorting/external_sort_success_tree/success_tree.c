#include <stdio.h>
#include <stdlib.h>

#include "success_tree.h"

static void successTreeAdjustNode(int nodeNum, SuccessTree successTree);

void successTreeAdjustToRoot(int leaveIndex, SuccessTree successTree) {
    // 第 leaveNum 个结点是 leaves[0]
    int parent = leaveIndex + successTree->leaveNum;
    while (parent /= 2) {
        successTreeAdjustNode(parent, successTree);
    }
}

// 使用 nodeNum 结点的左右儿子对决（nodeNum 为树的序号, 且该结点是非叶子结点）。
static void successTreeAdjustNode(int nodeNum, SuccessTree successTree) {
    int leaveNum = successTree->leaveNum;

    // ### 获取左右结点的对应的叶子结点的索引
    // #### 获取左结点的叶子索引值
    int leftChildNum = nodeNum * 2;
    int leftChildIndex;
    // 左儿子结点是非叶子结点
    if (leftChildNum < leaveNum) {
        leftChildIndex = successTree->nonLeaves[leftChildNum];
    }
    // 左儿子结点是叶子结点
    else {
        // 第 leaveNum 个结点是 leaves[0]
        leftChildIndex = leftChildNum - leaveNum;
    }

    // #### 获取右结点的叶子索引值
    int rightChildNum = leftChildNum + 1;
    int rightChildIndex;
    if (rightChildNum < leaveNum) {
        rightChildIndex = successTree->nonLeaves[rightChildNum];
    } else {
        rightChildIndex = rightChildNum - leaveNum;
    }

    // ### 比较并调整结点（小者胜）
    successTree->nonLeaves[nodeNum] = \
        successTree->leaves[leftChildIndex] < successTree->leaves[rightChildIndex] ? \
        leftChildIndex : rightChildIndex;
}

SuccessTree successTreeCreate(int leaveNum) {
    SuccessTree successTree = malloc(sizeof(struct SuccessTreeStruct));
    if (!successTree) {
        perror("malloc successTree failed");
        exit(EXIT_FAILURE);
    }

    successTree->leaves = malloc(sizeof(Element) * leaveNum);
    if (!successTree->leaves) {
        perror("malloc leaves failed");
        exit(EXIT_FAILURE);
    }
    successTree->leaveNum = leaveNum;

    successTree->nonLeaves = malloc(sizeof(int) * leaveNum);
    if (!successTree->nonLeaves) {
        perror("malloc nonLeaves failed");
        exit(EXIT_FAILURE);
    }

    return successTree;
}

void successTreeDestroy(SuccessTree successTree) {
    free(successTree->leaves);
    free(successTree->nonLeaves);
    free(successTree);
}
