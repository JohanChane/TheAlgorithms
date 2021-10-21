#ifndef SUCCESS_TREE_H
#define SUCCESS_TREE_H

typedef int Element;

typedef struct SuccessTreeStruct {
    // (leaveNum - 1) 个非叶子结点, nonleaves[1, leaveNum - 1]。nonleaves[0] 不使用。nonleaves 的长度是 leaveNum。
    int* nonLeaves;
    // leaves[0, leaveNum - 1]。leaves 的长度是 leaveNum。
    Element* leaves;
    int leaveNum;
} *SuccessTree;

void successTreeAdjustToRoot(int leaveIndex, SuccessTree successTree);
SuccessTree successTreeCreate(int leaveNum);
void successTreeDestroy(SuccessTree successTree);

#endif
