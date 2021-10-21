#include <stdio.h>
#include <stdlib.h>

#include "loser_tree.h"

static void loserTreeAdjustNode(int nodeNum, LoserTree loserTree);

void loserTreeAdjustToRoot(int leaveIndex, LoserTree loserTree) {
    int winnerLeaveIndex = leaveIndex;
    int loserLeaveIndex;

    // 第 leaveNum 个结点是 leaves[0]
    int parent = leaveIndex + loserTree->leaveNum;
    while (parent /= 2) {
        if (loserTree->leaves[winnerLeaveIndex] > loserTree->leaves[loserTree->nonLeaves[parent]]) {
            loserLeaveIndex = winnerLeaveIndex;
            winnerLeaveIndex = loserTree->nonLeaves[parent];
            loserTree->nonLeaves[parent] = loserLeaveIndex;
        }
    }
    loserTree->nonLeaves[0] = winnerLeaveIndex;
}

LoserTree loserTreeCreate(int leaveNum) {
    LoserTree loserTree = malloc(sizeof(struct LoserTreeStruct));
    if (!loserTree) {
        perror("malloc loserTree failed");
        exit(EXIT_FAILURE);
    }

    loserTree->leaves = malloc(sizeof(Element) * (leaveNum + 1));
    if (!loserTree->leaves) {
        perror("malloc leaves failed");
        exit(EXIT_FAILURE);
    }
    loserTree->leaveNum = leaveNum;

    loserTree->nonLeaves = malloc(sizeof(int) * leaveNum);
    if (!loserTree->nonLeaves) {
        perror("malloc nonLeaves failed");
        exit(EXIT_FAILURE);
    }

    return loserTree;
}

void loserTreeDestroy(LoserTree loserTree) {
    free(loserTree->leaves);
    free(loserTree->nonLeaves);
    free(loserTree);
}
