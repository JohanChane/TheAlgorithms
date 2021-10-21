#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

typedef int BinHeapElement;

typedef struct BinHeapStruct {
    int capacity;
    int size;
    BinHeapElement *elements;
} *BinHeap;

void binHeapPush(BinHeapElement element, BinHeap binHeap);
void binHeapPop(BinHeap binHeap);
BinHeapElement binHeapTop(BinHeap binHeap);
BinHeap binHeapCreate(int capacity);
void binHeapDestroy(BinHeap binHeap);
void binHeapClear(BinHeap binHeap);

static inline bool binHeapIsEmpty(BinHeap binHeap) {
    return !binHeap->size;
}

static inline bool binHeapIsFull(BinHeap binHeap) {
    return binHeap->size + 1 == binHeap->capacity;
}

static inline int binHeapSize(BinHeap binHeap) {
    return binHeap->size;
}

// 返回负数时，e1 在堆的上层。返回正数时，e2 在堆的上层。返回 0 时，是不确定的。
// `return e1 - e2` 为最小堆，`return e2 - e1` 为最大堆
int binHeapCmp(BinHeapElement e1, BinHeapElement e2);

#endif
