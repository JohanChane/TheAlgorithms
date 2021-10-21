#include <stdio.h>

#include "test_utils/utils.h"
#include "linked_list.h"

#define ARRAY_SIZE (10000 * 10)

static void testLinkedList();

static void testLinkedList() {
    LinkedListElement array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE * 100);

    clock_t start, end;
    LinkedList list = linkedListCreate();
    start = getTime();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        linkedListPushFront(array[i], list);
    }
    printf("size of list: %d\n", linkedListSize(list));

    int outArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        outArray[i] = linkedListFront(list); linkedListPopFront(list);
    }
    reverseArray(outArray, ARRAY_SIZE);
    if (!areArraysSame(array, outArray, ARRAY_SIZE)) {
        fprintf(stderr, "Arrays aren't Same.\n");
        return;
    }

    linkedListPushFront(0, list);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        linkedListInsertAfter(linkedListBegin(list), array[i], list);
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        linkedListEraseAfter(linkedListBegin(list), list);
    }
    printf("size of list: %d\n", linkedListSize(list));

    end = getTime();
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    linkedListDestroy(list);
}

int main() {
    testLinkedList();
    return 0;
}
