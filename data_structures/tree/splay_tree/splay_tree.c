// ### 说明
// 父子之间的大小：LeftChild < Parent < RightChild
// 每次执行 Splay(X, H) ，则含 X 的结点被旋转为根结点。
// zig-zag, zag-zig 的旋转的方法与 AVL Tree 相同，而 zig-zig, zag-zag 类似但不同于 AVL Tree。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "splay_tree.h"

static inline Position splayTreeSingleRotateWithLeft(Position k2);
static inline Position splayTreeSingleRotateWithRight(Position k2);
static Position splayTreeFindMin(SplayTree splayTree);
static Position splayTreeFindMax(SplayTree splayTree);

Position splayTreeSplay(Element element, SplayTree splayTree) {
    if (!splayTree || element == splayTree->element) {
        return splayTree;
    }

    if (element < splayTree->element) {
        if (!splayTree->leftChild) {
            return splayTree;
        }

        if (element < splayTree->leftChild->element) {      // Zig-Zig (Left Left)
            splayTree->leftChild->leftChild = splayTreeSplay(element, splayTree->leftChild->leftChild);
            splayTree = splayTreeSingleRotateWithLeft(splayTree);
        } else if (element > splayTree->leftChild->element) {       // Zig-Zag (Left Right)
            splayTree->leftChild->rightChild = splayTreeSplay(element, splayTree->leftChild->rightChild);
            if (splayTree->leftChild->rightChild) {
                splayTree->leftChild = splayTreeSingleRotateWithRight(splayTree->leftChild);
            }
        } else {
            ;
        }

        return splayTree->leftChild ? splayTreeSingleRotateWithLeft(splayTree) : splayTree;
    } else {    // element > splayTree->element
        if (!splayTree->rightChild) {
            return splayTree;
        }

        if (element > splayTree->rightChild->element) {     // Zag-Zag (Right Right)
            splayTree->rightChild->rightChild = splayTreeSplay(element, splayTree->rightChild->rightChild);
            splayTree = splayTreeSingleRotateWithRight(splayTree);
        } else if (element < splayTree->rightChild->element) {     // Zag-Zig (Right Left)
            splayTree->rightChild->leftChild = splayTreeSplay(element, splayTree->rightChild->leftChild);
            if (splayTree->rightChild->leftChild) {
                splayTree->rightChild = splayTreeSingleRotateWithLeft(splayTree->rightChild);
            }
        } else {
            ;
        }

        return splayTree->rightChild ? splayTreeSingleRotateWithRight(splayTree) : splayTree;
    }

    return splayTree;
}

SplayTree splayTreeInsert(Element element, SplayTree splayTree) {
    if (!splayTree) {
        Position newNode = malloc(sizeof(struct TreeNode));
        if (!newNode) {
            fprintf(stderr, "No space for newNode!\n");
            exit(EXIT_FAILURE);
        }
        newNode->element = element;
        newNode->leftChild = newNode->rightChild = NULL;

        splayTree = newNode;
    } else if (element < splayTree->element) {
        splayTree->leftChild = splayTreeInsert(element, splayTree->leftChild);
    } else if (element > splayTree->element) {
        splayTree->rightChild = splayTreeInsert(element, splayTree->rightChild);
    } else {    // 相同值
        ;
    }

    return splayTree;
}

SplayTree splayTreeDelete(Element element, SplayTree splayTree) {
    if (!splayTree) {
        return NULL;
    }

    if (element < splayTree->element) {
        splayTree->leftChild = splayTreeDelete(element, splayTree->leftChild);
    } else if (element > splayTree->element) {
        splayTree->rightChild = splayTreeDelete(element, splayTree->rightChild);
    } else {    // element == splayTree->element
        Position tmpPos;
        if (splayTree->leftChild && splayTree->rightChild) {    // 有两个儿子
            tmpPos = splayTreeFindMax(splayTree->leftChild);
            splayTree->element = tmpPos->element;

            splayTree->leftChild = splayTreeDelete(tmpPos->element, splayTree->leftChild);
        } else {    // 只有一个儿子或没有儿子
            tmpPos = splayTree;
            if (!splayTree->rightChild) {                       // 没有左儿子或没有儿子
                splayTree = splayTree->leftChild;
            } else if (!splayTree->leftChild) {                 // 没有右儿子或没有左儿子
                splayTree = splayTree->rightChild;
            } else {                                                // 没有儿子
                ;
            }
            free(tmpPos);
        }
    }

    return splayTree;
}

// 右旋
// 标号：最底的结点为 k1, 往上是 k2, k3...
// k1 不为空
static inline Position splayTreeSingleRotateWithLeft(Position k2) {
    Position k1 = k2->leftChild;
    k2->leftChild = k1->rightChild;
    k1->rightChild = k2;

    return k1;
}

// 左旋
static inline Position splayTreeSingleRotateWithRight(Position k2) {
    Position k1 = k2->rightChild;
    k2->rightChild = k1->leftChild;
    k1->leftChild = k2;

    return k1;
}

SplayTree splayTreeMakeEmpty(SplayTree splayTree) {
    if (!splayTree) {
        return NULL;
    }

    splayTreeMakeEmpty(splayTree->leftChild);
    splayTreeMakeEmpty(splayTree->rightChild);
    free(splayTree);
    return NULL;
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
