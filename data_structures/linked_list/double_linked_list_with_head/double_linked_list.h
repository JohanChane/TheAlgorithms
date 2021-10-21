#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef int DoubleLinkedListElement;

typedef struct DoubleLinkedListNodeStruct* DoubleLinkedListNode;
typedef struct DoubleLinkedListNodeStruct* DoubleLinkedListPosition;

typedef struct DoubleLinkedListStruct {
    struct DoubleLinkedListNodeStruct* theList;
    int size;
} *DoubleLinkedList;

struct DoubleLinkedListNodeStruct {
    DoubleLinkedListElement element;
    struct DoubleLinkedListNodeStruct* prev;
    struct DoubleLinkedListNodeStruct* next;
};

// ### DoubleLinkedList 接口
void doubleLinkedListPushFront(DoubleLinkedListElement element, DoubleLinkedList list);
void doubleLinkedListPushBack(DoubleLinkedListElement element, DoubleLinkedList list);
void doubleLinkedListPopFront(DoubleLinkedList list);
void doubleLinkedListPopBack(DoubleLinkedList list);
void doubleLinkedListInsert(DoubleLinkedListPosition pos, DoubleLinkedListElement element, DoubleLinkedList list);
void doubleLinkedListErase(DoubleLinkedListPosition pos, DoubleLinkedList list);

DoubleLinkedListElement doubleLinkedListFront(DoubleLinkedList list);
DoubleLinkedListElement doubleLinkedListBack(DoubleLinkedList list);

void doubleLinkedListClear(DoubleLinkedList list);

DoubleLinkedList doubleLinkedListCreate();
void doubleLinkedListDestroy(DoubleLinkedList list);

DoubleLinkedListPosition doubleLinkedListFind(DoubleLinkedListElement element, DoubleLinkedList list);

// ### Iterator
DoubleLinkedListPosition doubleLinkedListBegin(DoubleLinkedList list);
// 指向最后一个元素
DoubleLinkedListPosition doubleLinkedListEnd(DoubleLinkedList list);

// ### DoubleLinkedNode
DoubleLinkedListNode doubleLinkedListNodeCreate(DoubleLinkedListElement element);
void doubleLinkedListNodeDestroy(DoubleLinkedListNode node);

static inline bool doubleLinkedListIsEmpty(DoubleLinkedList list) {
    return !list->size;
}

static inline int doubleLinkedListSize(DoubleLinkedList list) {
    return list->size;
}

#endif
