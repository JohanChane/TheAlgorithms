#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "binary_heap.h"

void binHeapPush(BinHeapElement element, BinHeap binHeap) {
    if (binHeapIsFull(binHeap)) {
        fprintf(stderr, "BinHeap is full!\n");
        exit(EXIT_FAILURE);
    }

    // ### 从新的空位节点开始，下移动父结点, 直至有空位，然后插入
    int curPos = ++binHeap->size;
    int parent = curPos / 2;
    // 如果 element 可以在 binHeap->elements[parent] 之上时，则继续下移父结点
    while (parent >= 1 && binHeapCmp(element, binHeap->elements[parent]) < 0) {
        binHeap->elements[curPos] = binHeap->elements[parent];

        curPos = parent;
        parent = curPos / 2;
    }
    binHeap->elements[curPos] = element;
}

void binHeapPop(BinHeap binHeap) {
    if (binHeapIsEmpty(binHeap)) {
        fprintf(stderr, "BinHeap is empty!\n");
        exit(EXIT_FAILURE);
    }

    // ### 因为删除了堆顶，所以用最后一个结点补上
    BinHeapElement lastElement = binHeap->elements[binHeap->size--];

    // ### 从根结点开始，上移的应该在堆的上层的儿子，直至找到合适的结点或叶子结点
    int curPos = 1;
    // upChild 默认是 leftChild
    int upChild = curPos * 2;
    while (upChild <= binHeap->size) {
        // 如果 upChild 是右儿子
        if (upChild < binHeap->size && \
                binHeapCmp(binHeap->elements[upChild], binHeap->elements[upChild + 1]) > 0) {
            upChild++;
        }

        // 如果 upChild 应该在 lastElement 之上，否则将 lastElement 插入
        if (binHeapCmp(lastElement, binHeap->elements[upChild]) > 0) {
            // 上移 upChild
            binHeap->elements[curPos] = binHeap->elements[upChild];
        } else {
            break;
        }

        curPos = upChild;
        upChild = curPos * 2;
    }
    // ### 插入 lastElement
    binHeap->elements[curPos] = lastElement;
}

BinHeap binHeapCreate(int capacity) {
    BinHeap binHeap = malloc(sizeof(struct BinHeapStruct));
    if (!binHeap) {
        fprintf(stderr, "No space for creating binHeap!\n");
        exit(EXIT_FAILURE);
    }

    binHeap->elements = malloc(sizeof(BinHeapElement) * capacity);
    if (!binHeap->elements) {
        fprintf(stderr, "No space for creating binHeap->elements!\n");
        exit(EXIT_FAILURE);
    }

    binHeap->capacity = capacity;
    binHeap->size = 0;

    return binHeap;
}

void binHeapDestroy(BinHeap binHeap) {
    free(binHeap->elements);
    free(binHeap);
}

void binHeapClear(BinHeap binHeap) {
    binHeap->size = 0;
}

BinHeapElement binHeapTop(BinHeap binHeap) {
    if (binHeapIsEmpty(binHeap)) {
        fprintf(stderr, "BinHeap is empty!\n");
        exit(EXIT_FAILURE);
    }
    return binHeap->elements[1];
}
