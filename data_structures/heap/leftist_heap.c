#include <stdio.h>
#include <stdlib.h>

#include "leftist_heap.h"

static LeftistHeap leftistHeapMerge(LeftistHeap leftistHeap1, LeftistHeap leftistHeap2);
static LeftistHeap leftistHeapMergeUtil(LeftistHeap leftistHeap1, LeftistHeap leftistHeap2);
static void leftistHeapSwapChildren(LeftistHeap leftistHeap);

LeftistHeap leftistHeapInsert(Element element, LeftistHeap leftistHeap) {
    PtrToNode newNode = malloc(sizeof(struct TreeNode));
    if (!newNode) {
        fprintf(stderr, "No space for creating newNode!\n");
        exit(EXIT_FAILURE);
    }
    newNode->element = element;
    newNode->leftChild = newNode->rightChild = NULL;
    newNode->npl = 0;

    return leftistHeap = leftistHeapMerge(newNode, leftistHeap);
}

LeftistHeap leftistHeapDeleteMin(LeftistHeap leftistHeap) {
    if (leftistHeapIsEmpty(leftistHeap)) {
        fprintf(stderr, "leftistHeap is empty!\n");
        exit(EXIT_FAILURE);
    }

    Position tmpNode = leftistHeap;
    leftistHeap = leftistHeapMerge(leftistHeap->leftChild, leftistHeap->rightChild);
    free(tmpNode);
    return leftistHeap;
}

LeftistHeap leftistHeapInitialize() {
    return NULL;
}

void leftistHeapDestroy(LeftistHeap leftistHeap) {
    if (!leftistHeap) {
        return;
    }

    leftistHeapDestroy(leftistHeap->leftChild);
    leftistHeapDestroy(leftistHeap->rightChild);
    free(leftistHeap);
}

static LeftistHeap leftistHeapMerge(LeftistHeap leftistHeap1, LeftistHeap leftistHeap2) {
    if (!leftistHeap1) {
        return leftistHeap2;
    }

    if (!leftistHeap2) {
        return leftistHeap1;
    }

    if (leftistHeap1->element < leftistHeap2->element) {
        return leftistHeapMergeUtil(leftistHeap1, leftistHeap2);
    } else {
        return leftistHeapMergeUtil(leftistHeap2, leftistHeap1);
    }
}

// leftistHeap1->element < leftistHeap2->element
// leftistHeap1, leftistHeap2 不为空。
static LeftistHeap leftistHeapMergeUtil(LeftistHeap leftistHeap1, LeftistHeap leftistHeap2) {
    if (!leftistHeap1->leftChild) {
        leftistHeap1->leftChild = leftistHeap2;
    } else {
        leftistHeap1->rightChild = leftistHeapMerge(leftistHeap1->rightChild, leftistHeap2);
        if (leftistHeap1->leftChild->npl < leftistHeap1->rightChild->npl) {
            leftistHeapSwapChildren(leftistHeap1);
        }

        leftistHeap1->npl = leftistHeap1->rightChild->npl + 1;
    }

    return leftistHeap1;
}

// leftistHeap 不为空
static void leftistHeapSwapChildren(LeftistHeap leftistHeap) {
    Position tmpPos = leftistHeap->leftChild;
    leftistHeap->leftChild = leftistHeap->rightChild;
    leftistHeap->rightChild = tmpPos;
}
