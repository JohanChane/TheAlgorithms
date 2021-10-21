#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef int LinkedListElement;

typedef struct LinkedListNodeStruct* LinkedListNode;
typedef struct LinkedListNodeStruct* LinkedListPosition;

typedef struct LinkedListStruct {
    struct LinkedListNodeStruct* theList;
    int size;
} *LinkedList;

struct LinkedListNodeStruct {
    LinkedListElement element;
    struct LinkedListNodeStruct* next;
};

// ### LinkedList 接口
void linkedListInsertAfter(LinkedListPosition position, LinkedListElement element, LinkedList list);
void linkedListEraseAfter(LinkedListPosition position, LinkedList list);
void linkedListPushFront(LinkedListElement element, LinkedList list);
void linkedListPopFront(LinkedList list);
LinkedListElement linkedListFront(LinkedList list);

LinkedList linkedListCreate();
void linkedListDestroy(LinkedList list);
void linkedListClear(LinkedList list);

// ### Iterator
LinkedListPosition linkedListBegin(LinkedList list);
// 这里的 end 是指向最后一个结点
LinkedListPosition linkedListEnd(LinkedList list);

LinkedListPosition linkedListFind(LinkedListElement element, LinkedList list);
LinkedListPosition linkedListFindPrevious(LinkedListElement element, LinkedList list);

// ### Node
LinkedListNode LinkedListNodeCreate(LinkedListElement element);
void LinkedListNodeDestroy(LinkedListNode node);

static inline bool linkedListIsEmpty(LinkedList list) {
    return !list->size;
}

static int linkedListSize(LinkedList list) {
    return list->size;
}

#endif
