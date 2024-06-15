#ifndef SKEW_HEAP_H
#define SKEW_HEAP_H

#include <stdbool.h>

typedef int Element;

struct TreeNode;
typedef struct TreeNode* PtrToNode;
typedef PtrToNode SkewHeap;
typedef PtrToNode Position;

struct TreeNode {
    Element element;
    PtrToNode leftChild;
    PtrToNode rightChild;
};

SkewHeap skewHeapInsert(Element element, SkewHeap skewHeap);
SkewHeap skewHeapDeleteMin(SkewHeap skewHeap);
SkewHeap skewHeapInitialize();
void skewHeapDestroy(SkewHeap skewHeap);

static inline Element skewHeapFindMin(SkewHeap skewHeap) {
    return skewHeap->element;
}

static inline bool skewHeapIsEmpty(SkewHeap skewHeap) {
    return !skewHeap ? true : false;
}

#endif
