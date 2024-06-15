#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"

static Position bstFindMin(BinSearchTree binSearchTree);
static Position bstFindMax(BinSearchTree binSearchTree);

// 不插入相同的值
BinSearchTree bstInsert(Element element, BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        Position newNode = malloc(sizeof(struct TreeNode));
        if (!newNode) {
            fprintf(stderr, "No space for newNode!\n");
            exit(EXIT_FAILURE);
        }
        newNode->element = element;
        newNode->leftChild = newNode->rightChild = NULL;

        binSearchTree = newNode;
    } else if (element < binSearchTree->element) {
        binSearchTree->leftChild = bstInsert(element, binSearchTree->leftChild);
    } else if (element > binSearchTree->element) {
        binSearchTree->rightChild = bstInsert(element, binSearchTree->rightChild);
    } else {    // 相同值
        ;
    }

    return binSearchTree;
}

BinSearchTree bstDelete(Element element, BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        return NULL;
    }

    if (element < binSearchTree->element) {
        binSearchTree->leftChild = bstDelete(element, binSearchTree->leftChild);
    } else if (element > binSearchTree->element) {
        binSearchTree->rightChild = bstDelete(element, binSearchTree->rightChild);
    } else {    // element == binSearchTree->element
        Position tmpPos;
        if (binSearchTree->leftChild && binSearchTree->rightChild) {    // 有两个儿子
            tmpPos = bstFindMax(binSearchTree->leftChild);
            binSearchTree->element = tmpPos->element;

            binSearchTree->leftChild = bstDelete(tmpPos->element, binSearchTree->leftChild);
        } else {                                                        // 只有一个儿子或没有儿子
            tmpPos = binSearchTree;
            if (!binSearchTree->rightChild) {                       // 没有左儿子或没有儿子
                binSearchTree = binSearchTree->leftChild;
            } else if (!binSearchTree->leftChild) {                 // 没有右儿子或没有左儿子
                binSearchTree = binSearchTree->rightChild;
            } else {                                                // 没有儿子
                ;
            }
            free(tmpPos);
        }
    }

    return binSearchTree;
}

Position bstFind(Element element, BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        return NULL;
    }

    Position pos;
    if (element < binSearchTree->element) {
        pos = bstFind(element, binSearchTree->leftChild);
    } else if (element > binSearchTree->element) {
        pos = bstFind(element, binSearchTree->rightChild);
    } else {    // element == binSearchTree->element
        pos = binSearchTree;
    }

    return pos;
}

static Position bstFindMin(BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        return NULL;
    }

    Position curPos = binSearchTree;
    while (curPos->leftChild) {
        curPos = curPos->leftChild;
    }

    return curPos;
}

static Position bstFindMax(BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        return NULL;
    }

    Position curPos = binSearchTree;
    while (curPos->rightChild) {
        curPos = curPos->rightChild;
    }

    return curPos;
}

BinSearchTree bstMakeEmpty(BinSearchTree binSearchTree) {
    if (!binSearchTree) {
        return NULL;
    }

    bstMakeEmpty(binSearchTree->leftChild);
    bstMakeEmpty(binSearchTree->rightChild);
    free(binSearchTree);
    return NULL;
}
