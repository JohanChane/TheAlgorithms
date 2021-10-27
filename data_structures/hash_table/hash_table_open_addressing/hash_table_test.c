#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test_utils/utils.h"
#include "hash_table.h"

#define KEY_COUNT (10000 * 10)
// 如果用平方探测，当表大小是素数，那么当表至少有一半为空时，总能插入一个新的元素。
#define TABLE_SIZE (KEY_COUNT * 2)

static void testHashTable();
static void printHashTable(HashTable hashTable);

static void testHashTable() {
    char keyArray[KEY_COUNT][KEY_SIZE];
    genRandomStrings(keyArray, KEY_COUNT, KEY_SIZE, 'A', 'Z');

    // HashTable hashTable = hashTableCreate(TABLE_SIZE);
    HashTable hashTable = hashTableCreate(2);

    clock_t start, end;
    start = getTime();
    for (Index i = 0; i < KEY_COUNT; i++) {
        hashTableInsert(keyArray[i], hashTable);
    }
    printf("hashTable:\n");
    printHashTable(hashTable);

    bool isContain = true;
    Position pos;
    for (Index j = 0; j < KEY_COUNT; j++) {
        if (!(pos = hashTableFind(keyArray[j], hashTable))) {
            isContain = false;
            break;
        }
    }
    printf("isContain: %d\n", isContain);

    for (Index k = 0; k < KEY_COUNT; k++) {
        hashTableDelete(keyArray[k], hashTable);
    }
    end = getTime();
    printf("hashTable:\n");
    printHashTable(hashTable);
    printf("duration = %lfs\n", calcDuration(start, end));

    hashTableDestroy(hashTable);
}

static void printHashTable(HashTable hashTable) {
    printf("Num\t\t\tElement\t\t\tInfo\n");
    for (Position i = 0; i < hashTable->capacity; i++) {
        if (hashTable->theCellArray[i].status == legitimate) {
            printf("%d\t\t\t%s\t\t\t%s\n", i, hashTable->theCellArray[i].key, "legitimate");
        } else if (hashTable->theCellArray[i].status == deleted) {
            printf("%d\t\t\t%s\t\t\t%s\n", i, hashTable->theCellArray[i].key, "deleted");
        } else {    // empty
        }
    }
}

int main() {
    testHashTable();
    return 0;
}
