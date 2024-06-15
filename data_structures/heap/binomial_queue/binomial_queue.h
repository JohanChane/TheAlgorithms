#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

typedef int Element;

struct BinomialTreeNode;
struct BinomialQueue;
typedef struct BinomialTreeNode* PtrToBinTreeNode;
typedef PtrToBinTreeNode BinTree;
typedef PtrToBinTreeNode Position;
typedef struct BinomialQueue* BinQueue;

struct BinomialTreeNode {
    Element element;
    PtrToBinTreeNode leftChild;
    PtrToBinTreeNode nextSibling;
};

struct BinomialQueue {
    int capacity;
    int size;
    BinTree* theTrees;
};

BinQueue binQueueMerge(BinQueue binQueue1, BinQueue binQueue2);
BinQueue binQueueInsert(Element element, BinQueue binQueue);
Element binQueueDeleteMin(BinQueue binQueue);
BinQueue binQueueInitialize(int capacity);
void binQueueDestroy(BinQueue binQueue);
void binQueueRecapacity(int capacity, BinQueue binQueue);

// ### debug
int checkBinQueue(BinQueue binQueue);
void printBinQueue(BinQueue binQueue);

#endif
