#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#include <stdbool.h>

typedef int Element;

struct TreeNode;
typedef struct TreeNode* PtrToNode;
typedef PtrToNode LeftistHeap;
typedef PtrToNode Position;

struct TreeNode {
    Element element;
    PtrToNode leftChild;
    PtrToNode rightChild;
    int npl;
};

LeftistHeap leftistHeapInsert(Element element, LeftistHeap leftistHeap);
LeftistHeap leftistHeapDeleteMin(LeftistHeap leftistHeap);
LeftistHeap leftistHeapInitialize();
void leftistHeapDestroy(LeftistHeap leftistHeap);

static inline Element leftistHeapFindMin(LeftistHeap leftistHeap) {
    return leftistHeap->element;
}

static inline bool leftistHeapIsEmpty(LeftistHeap leftistHeap) {
    return !leftistHeap ? true : false;
}

#endif
