// ### 说明
// 链表保留头结点

#include <stdio.h>

#include "linked_list.h"

static int linkedListElementCmp(LinkedListElement e1, LinkedListElement e2);

void linkedListInsertAfter(LinkedListPosition position, LinkedListElement element, LinkedList list) {
    if (!position) {
        fprintf(stderr, "(!position)\n");
        exit(EXIT_FAILURE);
    }

    LinkedListNode newNode = LinkedListNodeCreate(element);
    newNode->next = position->next;
    position->next = newNode;
    list->size++;
}

void linkedListEraseAfter(LinkedListPosition position, LinkedList list) {
    if (!position || !position->next) {
        fprintf(stderr, "(!position || !position->next)\n");
        exit(EXIT_FAILURE);
    }

    LinkedListNode tmpNode = position->next;
    position->next = tmpNode->next;
    LinkedListNodeDestroy(tmpNode);
    list->size--;
}

void linkedListPushFront(LinkedListElement element, LinkedList list) {
    LinkedListNode newNode = LinkedListNodeCreate(element);
    newNode->next = list->theList->next;
    list->theList->next = newNode;
    list->size++;
}

void linkedListPopFront(LinkedList list) {
    if (linkedListIsEmpty(list)) {
        fprintf(stderr, "List is empty.\n");
        exit(EXIT_FAILURE);
    }

    LinkedListNode frontNode = list->theList->next;
    list->theList->next = frontNode->next;
    LinkedListNodeDestroy(frontNode);
    list->size--;
}

LinkedListElement linkedListFront(LinkedList list) {
    if (linkedListIsEmpty(list)) {
        fprintf(stderr, "List is empty.\n");
        exit(EXIT_FAILURE);
    }

    return list->theList->next->element;
}

LinkedList linkedListCreate() {
    LinkedList list = malloc(sizeof(struct LinkedListStruct));
    if (!list) {
        perror("malloc list failed");
        exit(EXIT_FAILURE);
    }

    list->theList = malloc(sizeof(struct LinkedListNodeStruct));
    if (!list->theList) {
        perror("malloc list->theList failed");
        exit(EXIT_FAILURE);
    }
    list->theList->next = NULL;

    list->size = 0;

    return list;
}

void linkedListDestroy(LinkedList list) {
    LinkedListPosition curPos = list->theList, tmpPos;
    while (curPos) {
        tmpPos = curPos;
        curPos = curPos->next;
        LinkedListNodeDestroy(tmpPos);
    }
    free(list);
}

void linkedListClear(LinkedList list) {
    LinkedListPosition curPos = list->theList->next, tmpPos;
    while (curPos) {
        tmpPos = curPos;
        curPos = curPos->next;
        LinkedListNodeDestroy(tmpPos);
    }
    list->size = 0;
}

static int linkedListElementCmp(LinkedListElement e1, LinkedListElement e2) {
    return e1 - e2;
}

LinkedListPosition linkedListBegin(LinkedList list) {
    return list->theList->next;
}

LinkedListPosition linkedListEnd(LinkedList list) {
    if (!linkedListIsEmpty(list)) {
        return NULL;
    }

    LinkedListPosition curPos = list->theList;
    while (curPos->next) {
        curPos = curPos->next;
    }
    return curPos;
}

LinkedListPosition linkedListFind(LinkedListElement element, LinkedList list) {
    LinkedListPosition curPos = list->theList->next;
    while (curPos) {
        if (linkedListElementCmp(curPos->element, element) == 0) {
            return curPos;
        }
        curPos = curPos->next;
    }

    return curPos;
}

// 如果找不到则返回 NULL
LinkedListPosition linkedListFindPrevious(LinkedListElement element, LinkedList list) {
    LinkedListPosition prePos = list->theList;
    while (prePos->next) {
        if (linkedListElementCmp(prePos->next->element, element) == 0) {
            return prePos;
        }

        prePos = prePos->next;
    }

    return prePos->next;
}

// 注意结点的 next 是悬挂的
LinkedListNode LinkedListNodeCreate(LinkedListElement element) {
    LinkedListNode newNode = malloc(sizeof(struct LinkedListNodeStruct));
    if (!newNode) {
        perror("malloc newNode failed");
        exit(EXIT_FAILURE);
    }
    newNode->element = element;

    return newNode;
}

void LinkedListNodeDestroy(LinkedListNode node) {
    free(node);
}
