#ifndef LOSER_TREE_H
#define LOSER_TREE_H

typedef int Element;

typedef struct LoserTreeStruct {
    // (leaveNum - 1) 个非叶子结点, nonleaves[1, leaveNum - 1]。nonleaves[0] 存放最终胜者。nonLeaves 长度是 leaveNum。
    int* nonLeaves;
    // leaves[0, leaveNum - 1]。leaves[leaveNum] 存入 ElEMENT_MIN，用于初始化。leaves 长度是 (leaveNum + 1)。
    Element* leaves;
    int leaveNum;
} *LoserTree;

void loserTreeAdjustToRoot(int leaveIndex, LoserTree loserTree);
LoserTree loserTreeCreate(int leaveNum);
void loserTreeDestroy(LoserTree loserTree);

#endif
