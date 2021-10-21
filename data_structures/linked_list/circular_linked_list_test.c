#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "circular_linked_list.h"

#define ARRAY_SIZE (10000 * 10)

static void testCirLinkedList();
static size_t cirLinkedListSize(List list);
static void printLinkedList(List list);

static void testCirLinkedList() {
    Element array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end;
    List list = cirLinkedListCreate();
    start = getTime();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cirLinkedListInsertAfter(array[i], list, list);
    }
    printf("size of list: %lu\n", cirLinkedListSize(list));

    int increment = (ARRAY_SIZE - 1) / 2 + 1;
    for (int k = 0; k < increment; k++) {
        for (int j = k; j < ARRAY_SIZE; j += increment) {
            cirLinkedListDelete(array[j], list);
        }
    }
    end = getTime();
    printf("size of list: %lu\n", cirLinkedListSize(list));
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    cirLinkedListDestroy(list);
}

static size_t cirLinkedListSize(List list) {
    size_t size = 0;
    Position curPos = list->next;
    while (curPos != list) {
        size++;
        curPos = curPos->next;
    }

    return size;
}

static void printLinkedList(List list) {
    Position curPos = list->next;
    while (curPos != list) {
        printf("%d\t", curPos->element);
        curPos = curPos->next;
    }
    printf("\n");
}

int main() {
    testCirLinkedList();

    return 0;
}
