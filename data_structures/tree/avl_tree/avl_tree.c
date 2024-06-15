// ### 说明
// 父子之间的大小：LeftChild < Parent < RightChild
// |Height(LeftChild) - Height(RightChild)| 小于等于 1

#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

static inline Position avlTreeSingleRotateWithLeft(Position node);
static inline Position avlTreeSingleRotateWithRight(Position node);
static inline Position avlTreeDoubleRotateWithLeft(Position node);
static inline Position avlTreeDoubleRotateWithRight(Position node);
static inline int max(int a, int b);

AvlTree avlTreeInsert(Element element, AvlTree avlTree) {
    if (!avlTree) {
        avlTree = malloc(sizeof(struct AvlNode));
        if (!avlTree) {
            fprintf(stderr, "No space for newNode!\n");
            exit(EXIT_FAILURE);
        }
        avlTree->element = element;
        avlTree->height = 0;
        avlTree->leftChild = avlTree->rightChild = NULL;
        return avlTree;
    }

    if (element < avlTree->element) {
        avlTree->leftChild = avlTreeInsert(element, avlTree->leftChild);
    } else if (element > avlTree->element) {
        avlTree->rightChild = avlTreeInsert(element, avlTree->rightChild);
    } else {
        return avlTree;
    }
    avlTree->height = max(avlTreeHeight(avlTree->leftChild), avlTreeHeight(avlTree->rightChild)) + 1;

    // ### 旋转调整
    int diff = avlTreeHeight(avlTree->leftChild) - avlTreeHeight(avlTree->rightChild);
    if (diff == 2) {
        if (element < avlTree->leftChild->element) {        // 左子树一定不为空，因为高度差为 2。
            avlTree = avlTreeSingleRotateWithLeft(avlTree);
        } else {    // 不可能是相等的情况，因为相等则表示左子树为空或左子树旋转了，而不会出现高度差为 2，所以不可能是相等的。
            avlTree = avlTreeDoubleRotateWithLeft(avlTree);
        }
    } else if (diff == -2) {
        if (element > avlTree->rightChild->element) {
            avlTree = avlTreeSingleRotateWithRight(avlTree);
        } else {
            avlTree = avlTreeDoubleRotateWithRight(avlTree);
        }
    } else {
        ;
    }

    return avlTree;
}

// 与 `insert` 同理
AvlTree avlTreeDelete(Element element, AvlTree avlTree) {
    if (!avlTree) {
        return NULL;
    }

    if (element < avlTree->element) {
        avlTree->leftChild = avlTreeDelete(element, avlTree->leftChild);
    } else if (element > avlTree->element) {
        avlTree->rightChild = avlTreeDelete(element, avlTree->rightChild);
    } else {
        Position tmpPos;
        if (avlTree->leftChild && avlTree->rightChild) {    // 有两个儿子
            tmpPos = avlTreeFindMax(avlTree->leftChild);
            avlTree->element = tmpPos->element;
            avlTree->leftChild = avlTreeDelete(tmpPos->element, avlTree->leftChild);
        } else {    // 只有一个儿子或没有儿子
            tmpPos = avlTree;
            if (avlTree->leftChild) {
                avlTree = avlTree->leftChild;
                avlTree->height -= 1;
            } else if (avlTree->rightChild) {
                avlTree = avlTree->rightChild;
                avlTree->height -= 1;
            } else {    // 没有儿子
                avlTree = NULL;
            }
            free(tmpPos);
            return avlTree;
        }
    }
    avlTree->height = max(avlTreeHeight(avlTree->leftChild), avlTreeHeight(avlTree->rightChild)) + 1;

    // ### 旋转调整
    // #### 计算 diff（保留四个底层的 diff，为了不重复计算高度）
    int diff, diffLeft, diffRight, diffLeftLeft, diffLeftRight, diffRightLeft, diffRightRight;
    if (avlTree->leftChild) {
        diffLeftLeft = avlTreeHeight(avlTree->leftChild->leftChild);
        diffLeftRight = avlTreeHeight(avlTree->leftChild->rightChild);
    } else {
        diffLeftLeft = -2;
        diffLeftRight = -2;
    }
    diffLeft = max(diffLeftLeft, diffLeftRight) + 1;

    if (avlTree->rightChild) {
        diffRightLeft = avlTreeHeight(avlTree->rightChild->leftChild);
        diffRightRight = avlTreeHeight(avlTree->rightChild->rightChild);
    } else {
        diffRightLeft = -2;
        diffRightRight = -2;
    }
    diffRight = max(diffRightLeft, diffRightRight) + 1;

    // #### 高度超 1 则旋转调整
    diff = diffLeft - diffRight;
    if (diff == 2) {
        if (diffLeftLeft >= diffLeftRight) {    // 如果相等则单双旋转都可以
            avlTree = avlTreeSingleRotateWithLeft(avlTree);
        } else {
            avlTree = avlTreeDoubleRotateWithLeft(avlTree);
        }
    } else if (diff == -2) {
        if (diffRightLeft <= diffRightRight) {
            avlTree = avlTreeSingleRotateWithRight(avlTree);
        } else {
            avlTree = avlTreeDoubleRotateWithRight(avlTree);
        }
    } else {
        ;
    }

    return avlTree;
}

// node 右旋。新插入的结点在左-左边。
static inline Position avlTreeSingleRotateWithLeft(Position node) {
    Position leftChild = node->leftChild;

    // ### 右旋
    node->leftChild = leftChild->rightChild;
    leftChild->rightChild = node;

    // ### 更新 node, leftChild 的 height。
    node->height = max(avlTreeHeight(node->leftChild), avlTreeHeight(node->rightChild)) + 1;
    leftChild->height = max(avlTreeHeight(leftChild->leftChild), avlTreeHeight(leftChild->rightChild)) + 1;
    return leftChild;
}

// node 左旋。新插入的结点在右-右边。
static inline Position avlTreeSingleRotateWithRight(Position node) {
    Position rightChild = node->rightChild;

    // ### 左旋
    node->rightChild = rightChild->leftChild;
    rightChild->leftChild = node;

    // ### 更新 node, rightChild 的 height。
    node->height = max(avlTreeHeight(node->leftChild), avlTreeHeight(node->rightChild)) + 1;
    rightChild->height = max(avlTreeHeight(rightChild->leftChild), avlTreeHeight(rightChild->rightChild)) + 1;

    return rightChild;
}

// 左-右旋。新插入的结点在左-右边。
static inline Position avlTreeDoubleRotateWithLeft(Position node) {
    // 左儿子左旋
    node->leftChild = avlTreeSingleRotateWithRight(node->leftChild);
    // node 右旋
    return avlTreeSingleRotateWithLeft(node);
}

// 右-左旋。新插入的结点在右-左边。
static inline Position avlTreeDoubleRotateWithRight(Position node) {
    // 右儿子右旋
    node->rightChild = avlTreeSingleRotateWithLeft(node->rightChild);
    // node 左旋
    return avlTreeSingleRotateWithRight(node);
}

static inline int max(int a, int b) {
    return a > b ? a : b;
}

Position avlTreeFind(Element element, AvlTree avlTree) {
    if (!avlTree) {
        return NULL;
    }

    Position pos;
    if (element < avlTree->element) {
        pos = avlTreeFind(element, avlTree);
    } else if (element > avlTree->element) {
        pos = avlTreeFind(element, avlTree);
    } else {
        pos = avlTree;
    }

    return pos;
}

Position avlTreeFindMin(AvlTree avlTree) {
    if (!avlTree) {
        return NULL;
    }

    Position curPos = avlTree;
    while (curPos->leftChild) {
        curPos = curPos->leftChild;
    }

    return curPos;
}

Position avlTreeFindMax(AvlTree avlTree) {
    if (!avlTree) {
        return NULL;
    }

    Position curPos = avlTree;
    while (curPos->rightChild) {
        curPos = curPos->rightChild;
    }

    return curPos;
}

int avlTreeHeight(AvlTree avlTree) {
    if (!avlTree) {
        return -1;
    }

    return max(avlTreeHeight(avlTree->leftChild), avlTreeHeight(avlTree->rightChild)) + 1;
}

AvlTree avlTreeMakeEmpty(AvlTree avlTree) {
    avlTreeMakeEmpty(avlTree->leftChild);
    avlTreeMakeEmpty(avlTree->rightChild);
    free(avlTree);

    return NULL;
}
