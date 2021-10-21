#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "double_linked_list.h"

#define ARRAY_SIZE (10000 * 1)

static void testDoubleLinkedList();
static void printLinkedList(DoubleLinkedList list);

static void printLinkedList(DoubleLinkedList list) {
    DoubleLinkedListPosition curPos = list->theList->next;
    while (curPos) {
        printf("%d\t", curPos->element);
        curPos = curPos->next;
    }
    printf("\n");
}

static void testDoubleLinkedList() {
    DoubleLinkedListElement array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end;
    DoubleLinkedList list = doubleLinkedListCreate();
    start = getTime();
    // ### pushback popfront
    for (int i = 0; i < ARRAY_SIZE; i++) {
        doubleLinkedListPushBack(array[i], list);
    }
    printf("size of list: %d\n", doubleLinkedListSize(list));

    int outArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        outArray[i] = doubleLinkedListFront(list); doubleLinkedListPopFront(list);
    }
    printf("size of list: %d\n", doubleLinkedListSize(list));

    if (!areArraysSame(array, outArray, ARRAY_SIZE)) {
        fprintf(stderr, "Arrays aren't same.\n");
        exit(EXIT_FAILURE);
    }

    // ### pushfront popback
    for (int i = 0; i < ARRAY_SIZE; i++) {
        doubleLinkedListPushFront(array[i], list);
    }
    printf("size of list: %d\n", doubleLinkedListSize(list));

    for (int i = 0; i < ARRAY_SIZE; i++) {
        outArray[i] = doubleLinkedListBack(list); doubleLinkedListPopBack(list);
    }
    printf("size of list: %d\n", doubleLinkedListSize(list));

    if (!areArraysSame(array, outArray, ARRAY_SIZE)) {
        fprintf(stderr, "Arrays aren't same.\n");
        exit(EXIT_FAILURE);
    }

    // ### insert erase
    doubleLinkedListPushBack(0, list);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        doubleLinkedListInsert(doubleLinkedListBegin(list), array[i], list);
    }
    doubleLinkedListPopBack(list);
    printf("size of list: %d\n", doubleLinkedListSize(list));

    for (int i = 0; i < ARRAY_SIZE; i++) {
        outArray[i] = doubleLinkedListBack(list); doubleLinkedListErase(doubleLinkedListEnd(list), list);
    }
    printf("size of list: %d\n", doubleLinkedListSize(list));

    if (!areArraysSame(array, outArray, ARRAY_SIZE)) {
        fprintf(stderr, "Arrays aren't same.\n");
        exit(EXIT_FAILURE);
    }

    end = getTime();
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    doubleLinkedListDestroy(list);
}

int main() {
    testDoubleLinkedList();

    return 0;
}
