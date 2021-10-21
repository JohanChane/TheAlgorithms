#include <stdio.h>
#include <stdlib.h>

#include "skew_heap.h"

static SkewHeap skewHeapMerge(SkewHeap skewHeap1, SkewHeap skewHeap2);
static SkewHeap skewHeapMerge1(SkewHeap skewHeap1, SkewHeap skewHeap2);
static void skewHeapSwapChildren(SkewHeap skewHeap);

SkewHeap skewHeapInsert(Element element, SkewHeap skewHeap) {
    PtrToNode newNode = malloc(sizeof(struct TreeNode));
    if (!newNode) {
        fprintf(stderr, "No space for creating newNode!\n");
        exit(EXIT_FAILURE);
    }
    newNode->element = element;
    newNode->leftChild = newNode->rightChild = NULL;

    return skewHeap = skewHeapMerge(newNode, skewHeap);
}

SkewHeap skewHeapDeleteMin(SkewHeap skewHeap) {
    if (skewHeapIsEmpty(skewHeap)) {
        fprintf(stderr, "skewHeap is empty!\n");
        exit(EXIT_FAILURE);
    }

    Position tmpNode = skewHeap;
    skewHeap = skewHeapMerge(skewHeap->leftChild, skewHeap->rightChild);
    free(tmpNode);
    return skewHeap;
}

SkewHeap skewHeapInitialize() {
    return NULL;
}

void skewHeapDestroy(SkewHeap skewHeap) {
    if (!skewHeap) {
        return;
    }

    skewHeapDestroy(skewHeap->leftChild);
    skewHeapDestroy(skewHeap->rightChild);
    free(skewHeap);
}

static SkewHeap skewHeapMerge(SkewHeap skewHeap1, SkewHeap skewHeap2) {
    if (!skewHeap1) {
        return skewHeap2;
    }

    if (!skewHeap2) {
        return skewHeap1;
    }

    if (skewHeap1->element < skewHeap2->element) {
        return skewHeapMerge1(skewHeap1, skewHeap2);
    } else {
        return skewHeapMerge1(skewHeap2, skewHeap1);
    }
}

// skewHeap1->element < skewHeap2->element
// skewHeap1, skewHeap2 不为空。
static SkewHeap skewHeapMerge1(SkewHeap skewHeap1, SkewHeap skewHeap2) {
    skewHeap1->rightChild = skewHeapMerge(skewHeap1->rightChild, skewHeap2);
    // 合并之后旋转
    skewHeapSwapChildren(skewHeap1);

    return skewHeap1;
}

// skewHeap 不为空
static void skewHeapSwapChildren(SkewHeap skewHeap) {
    Position tmpPos = skewHeap->leftChild;
    skewHeap->leftChild = skewHeap->rightChild;
    skewHeap->rightChild = tmpPos;
}
