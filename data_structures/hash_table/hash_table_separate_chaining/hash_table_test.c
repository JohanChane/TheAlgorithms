#include <stdio.h>
#include <stdlib.h>

#include "test_utils/utils.h"
#include "hash_table.h"

#define KEY_COUNT (10000 * 10)

#define TABLE_SIZE (KEY_COUNT)

static void testHashTable();

static void printHashTable(HashTable hashTable);
static void printLinkedList(HashTableList list);

static void testHashTable() {
    char keyArray[KEY_COUNT][HASH_TABLE_KEY_SIZE];
    genRandomStrings(keyArray, KEY_COUNT, HASH_TABLE_KEY_SIZE, 'A', 'Z');

    HashTable hashTable = hashTableCreate(TABLE_SIZE);

    clock_t start, end;
    start = getTime();
    for (HashTableIndex i = 0; i < KEY_COUNT; i++) {
        hashTableInsert(keyArray[i], hashTable);
    }
    printf("hashTable:\n");
    printHashTable(hashTable);

    bool isContain = true;
    HashTablePosition pos;
    for (HashTableIndex j = 0; j < KEY_COUNT; j++) {
        if (!(pos = hashTableFind(keyArray[j], hashTable))) {
            isContain = false;
            break;
        }
    }
    printf("isContain: %d\n", isContain);

    for (HashTableIndex k = 0; k < KEY_COUNT; k++) {
        hashTableErase(keyArray[k], hashTable);
    }
    end = getTime();
    printf("hashTable:\n");
    printHashTable(hashTable);
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    hashTableDestroy(hashTable);
}

static void printHashTable(HashTable hashTable) {
    if (!hashTable) {
        fprintf(stderr, "hashTable is NULL!\n");
        exit(EXIT_FAILURE);
    }

    for (HashTableIndex i = 0; i < hashTable->tableSize; i++) {
        if (doubleLinkedListSize(hashTable->theListArray[i]) > 0) {
            printf("theListArray[%d]: ", i);
            printLinkedList(hashTable->theListArray[i]);
        }
    }
}

static void printLinkedList(HashTableList list) {
    if (!list) {
        fprintf(stderr, "list is NULL!\n");
        exit(EXIT_FAILURE);
    }

    HashTablePosition curPos = doubleLinkedListBegin(list);
    while (curPos) {
        printf("%s\t", curPos->element);
        curPos = curPos->next;
    }
    printf("\n");
}

int main() {
    testHashTable();
    return 0;
}
