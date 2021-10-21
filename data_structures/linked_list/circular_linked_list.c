// ### 说明
// 保留头结点

#include <stdio.h>
#include <stdlib.h>

#include "circular_linked_list.h"

void cirLinkedListInsertAfter(Element element, Position position, List list) {
    Position newNode = malloc(sizeof(struct Node));
    if (!newNode) {
        fprintf(stderr, "No space for creating a node");
        exit(EXIT_FAILURE);
    }
    newNode->element = element;

    newNode->next = position->next;
    position->next->prev = newNode;
    position->next = newNode;
    newNode->prev = position;
}

void cirLinkedListInsertPrev(Element element, Position position, List list) {
    if (!position->prev) {
        fprintf(stderr, "position is header!\n");
        exit(EXIT_FAILURE);
    }

    Position newNode = malloc(sizeof(struct Node));
    if (!newNode) {
        fprintf(stderr, "No space for creating a node");
        exit(EXIT_FAILURE);
    }
    newNode->element = element;

    newNode->prev = position->prev;
    position->prev->next = newNode;
    newNode->next = position;
    position->prev = newNode;
}

void cirLinkedListDelete(Element element, List list) {
    Position curPos = cirLinkedListFind(element, list);
    // 找到了
    if (curPos) {
        Position prePos = curPos->prev;

        prePos->next = curPos->next;
        curPos->next->prev = prePos;

        free(curPos);
    }
}

Position cirLinkedListFind(Element element, List list) {
    Position curPos = list->next;
    while (curPos != list) {
        if (curPos->element == element) {
            return curPos;
        }
        curPos = curPos->next;
    }

    return curPos;
}

List cirLinkedListCreate() {
    List list = malloc(sizeof(struct Node));
    if (!list) {
        fprintf(stderr, "No space for creating list!\n");
        exit(EXIT_FAILURE);
    }
    list->next = list;
    list->prev = list;

    return list;
}

void cirLinkedListDestroy(List list) {
    Position curPos = list->next;
    Position tmpPos;
    while (curPos != list) {
        tmpPos = curPos->next;
        free(curPos);
        curPos = tmpPos;
    }

    free(list);
}

List cirLinkedListEmpty(List list) {
    Position curPos = list->next;
    Position tmpPos;
    while (curPos != list) {
        tmpPos = curPos->next;
        free(curPos);
        curPos = tmpPos;
    }

    list->next = list;
    list->prev = list;

    return list;
}
