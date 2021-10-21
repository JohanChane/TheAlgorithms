// ### 说明
// 保留头结点

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "double_linked_list.h"

static int doubleLinkedListNodeCmp(DoubleLinkedListElement e1, DoubleLinkedListElement e2);

void doubleLinkedListPushFront(DoubleLinkedListElement element, DoubleLinkedList list) {
    DoubleLinkedListNode newNode = doubleLinkedListNodeCreate(element);
    newNode->next = list->theList->next;
    newNode->prev = list->theList;

    list->theList->next = newNode;
    if (newNode->next) {
        newNode->next->prev = newNode;
    }

    list->size++;
}

void doubleLinkedListPushBack(DoubleLinkedListElement element, DoubleLinkedList list) {
    DoubleLinkedListNode newNode = doubleLinkedListNodeCreate(element);
    newNode->next = NULL;

    DoubleLinkedListNode endNode = doubleLinkedListEnd(list);
    // size == 0
    if (!endNode) {
        endNode = list->theList;
    }

    endNode->next = newNode;
    newNode->prev = endNode;

    list->size++;
}

void doubleLinkedListPopFront(DoubleLinkedList list) {
    if (doubleLinkedListIsEmpty(list)) {
        fprintf(stderr, "List is empty.\n");
        exit(EXIT_FAILURE);
    }

    DoubleLinkedListNode frontNode = list->theList->next;
    list->theList->next = frontNode->next;

    if (frontNode->next) {
        frontNode->next->prev = list->theList;
    }

    doubleLinkedListNodeDestroy(frontNode);
    list->size--;
}

void doubleLinkedListPopBack(DoubleLinkedList list) {
    DoubleLinkedListNode endNode = doubleLinkedListEnd(list);
    // ## size == 0
    if (!endNode) {
        fprintf(stderr, "List is empty.\n");
        exit(EXIT_FAILURE);
    }

    // ## size > 0
    endNode->prev->next = NULL;

    doubleLinkedListNodeDestroy(endNode);
    list->size--;
}

void doubleLinkedListInsert(DoubleLinkedListPosition pos, DoubleLinkedListElement element, DoubleLinkedList list) {
    if (!pos) {
        fprintf(stderr, "pos is NULL.\n");
        exit(EXIT_FAILURE);
    }

    DoubleLinkedListNode newNode = doubleLinkedListNodeCreate(element);
    newNode->next = pos;
    newNode->prev = pos->prev;

    pos->prev->next = newNode;
    pos->prev = newNode;

    list->size++;
}

void doubleLinkedListErase(DoubleLinkedListPosition pos, DoubleLinkedList list) {
    if (!pos || doubleLinkedListIsEmpty(list)) {
        fprintf(stderr, "pos is NULL OR list is empty.\n");
        exit(EXIT_FAILURE);
    }

    pos->prev->next = pos->next;
    if (pos->next) {
        pos->next->prev = pos->prev;
    }

    doubleLinkedListNodeDestroy(pos);
    list->size--;
}

DoubleLinkedListElement doubleLinkedListFront(DoubleLinkedList list) {
    if (doubleLinkedListIsEmpty(list)) {
        fprintf(stderr, "List is empty.\n");
        exit(EXIT_FAILURE);
    }

    return list->theList->next->element;
}

DoubleLinkedListElement doubleLinkedListBack(DoubleLinkedList list) {
    DoubleLinkedListNode endNode = doubleLinkedListEnd(list);
    if (!endNode) {
        fprintf(stderr, "List is empty.\n");
        exit(EXIT_FAILURE);
    }

    return endNode->element;
}

void doubleLinkedListClear(DoubleLinkedList list) {
    DoubleLinkedListPosition curPos = doubleLinkedListBegin(list);
    if (!curPos) {
        return;
    }

    DoubleLinkedListNode tmpPos;
    while (curPos) {
        tmpPos = curPos;
        curPos = curPos->next;
        doubleLinkedListNodeDestroy(tmpPos);
    }
    list->size = 0;
}

DoubleLinkedList doubleLinkedListCreate() {
    DoubleLinkedList list = malloc(sizeof(struct DoubleLinkedListStruct));
    if (!list) {
        perror("malloc list failed");
        exit(EXIT_FAILURE);
    }

    list->theList = malloc(sizeof(struct DoubleLinkedListNodeStruct));
    if (!list->theList) {
        perror("malloc list->theList failed");
        exit(EXIT_FAILURE);
    }
    list->theList->next = NULL;
    list->theList->prev = NULL;

    list->size = 0;

    return list;
}

void doubleLinkedListDestroy(DoubleLinkedList list) {
    DoubleLinkedListPosition curPos = list->theList;
    DoubleLinkedListNode tmpPos;
    while (curPos) {
        tmpPos = curPos;
        curPos = curPos->next;
        doubleLinkedListNodeDestroy(tmpPos);
    }

    free(list);
}

DoubleLinkedListPosition doubleLinkedListBegin(DoubleLinkedList list) {
    return list->theList->next;
}

DoubleLinkedListPosition doubleLinkedListEnd(DoubleLinkedList list) {
    if (doubleLinkedListIsEmpty(list)) {
        return NULL;
    }

    DoubleLinkedListPosition curPos = list->theList->next;
    while (curPos->next) {
        curPos = curPos->next;
    }

    return curPos;
}

// 注意 prev, next 悬挂
DoubleLinkedListNode doubleLinkedListNodeCreate(DoubleLinkedListElement element) {
    DoubleLinkedListNode newNode = malloc(sizeof(struct DoubleLinkedListNodeStruct));
    if (!newNode) {
        perror("malloc newNode failed");
        exit(EXIT_FAILURE);
    }

    newNode->element = element;

    return newNode;
}

void doubleLinkedListNodeDestroy(DoubleLinkedListNode node) {
    free(node);
}

DoubleLinkedListPosition doubleLinkedListFind(DoubleLinkedListElement element, DoubleLinkedList list) {
    for (DoubleLinkedListPosition curPos = doubleLinkedListBegin(list); curPos; curPos = curPos->next) {
        if (doubleLinkedListNodeCmp(curPos->element, element) == 0) {
            return curPos;
        }
    }

    return NULL;
}

// 0 表示相等，小于 0 表示 e1 < e2, 大小 0 表示 e1 > e2。
static int doubleLinkedListNodeCmp(DoubleLinkedListElement e1, DoubleLinkedListElement e2) {
    return e1 - e2;
}
