#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "hash_table.h"

static inline bool areEqual(Key keyA, Key keyB) {
    return !strncmp(keyA, keyB, KEY_SIZE - 1);
}

static inline Position hashTableDetect(TableSize collisionNum) {
    return collisionNum * collisionNum;
}

static Position hashTableHash(Key key, TableSize capacity);
static void hashTableReHash(HashTable hashTable);

void hashTableInsert(Key key, HashTable hashTable) {
    Position pos = hashTableFind(key, hashTable);
    if (hashTable->theCellArray[pos].status != legitimate) {
        Key newkey = malloc(KEY_SIZE);
        if (!newkey) {
            fprintf(stderr, "No space for newkey!\n");
            exit(EXIT_FAILURE);
        }
        strncpy(newkey, key, KEY_SIZE - 1);
        newkey[KEY_SIZE - 1] = '\0';
        hashTable->theCellArray[pos].key = newkey;

        hashTable->theCellArray[pos].status = legitimate;
        hashTable->size++;
    }
}

void hashTableDelete(Key key, HashTable hashTable) {
    Position pos = hashTableFind(key, hashTable);
    if (hashTable->theCellArray[pos].status == legitimate) {
        hashTable->theCellArray[pos].status = deleted;
        hashTable->size--;
    }
}

Position hashTableFind(Key key, HashTable hashTable) {
    Position curPos = hashTableHash(key, hashTable->capacity);
    TableSize collisionNum = 0;

    Position firstPos = curPos;
    int firstPosCount = 0;
    while (hashTable->theCellArray[curPos].status != empty \
            && !areEqual(hashTable->theCellArray[curPos].key, key)) {
        collisionNum++;
        curPos = (firstPos + hashTableDetect(collisionNum)) % hashTable->capacity;
        if (curPos == firstPos) {
            firstPosCount++;
        }
        if (firstPosCount > 1) {
            hashTableReHash(hashTable);

            // 继续 find
            curPos = hashTableFind(key, hashTable);
            break;
        }
    }

    return curPos;
}

HashTable hashTableCreate(TableSize capacity) {
    HashTable hashTable = malloc(sizeof(struct HashTableStruct));
    if (!hashTable) {
        fprintf(stderr, "No space for creating hashTable!\n");
        exit(EXIT_FAILURE);
    }
    hashTable->theCellArray = malloc(sizeof(struct HashEntryStruct) * capacity);
    if (!hashTable->theCellArray) {
        fprintf(stderr, "No space for creating hashTable->theCellArray!\n");
        exit(EXIT_FAILURE);
    }

    hashTable->capacity = capacity;
    hashTable->size = 0;
    for (Position i = 0; i < capacity; i++) {
        hashTable->theCellArray[i].status = empty;
    }

    return hashTable;
}

void hashTableDestroy(HashTable hashTable) {
    for (Position i = 0; i < hashTable->capacity; i++) {
        if (hashTable->theCellArray[i].status != empty) {
            free(hashTable->theCellArray[i].key);
        }
    }
    free(hashTable->theCellArray);
    free(hashTable);
}

Key hashTableRetrieve(Position position, HashTable hashTable) {
    return hashTable->theCellArray[position].key;
}

static Position hashTableHash(Key key, TableSize capacity) {
    TableSize hashVal = 0;

    TableSize dataIndex = 0;
    while (key[dataIndex] != '\0') {
        hashVal += (hashVal << 5) + key[dataIndex++];
    }
    return hashVal % capacity;
}

static void hashTableReHash(HashTable hashTable) {
    Cell* oldCellArray = hashTable->theCellArray;
    TableSize oldCapacity = hashTable->capacity;

    TableSize newCapacity = hashTable->capacity * 2;
    Cell* newCellArray = malloc(sizeof(struct HashEntryStruct) * newCapacity);
    if (!newCellArray) {
        fprintf(stderr, "No space for newCellArray!\n");
        exit(EXIT_FAILURE);
    }
    for (Position i; i < newCapacity; i++) {
        newCellArray->status = empty;
    }
    hashTable->capacity = newCapacity;
    hashTable->size = 0;
    hashTable->theCellArray = newCellArray;

    for (Position i = 0; i < oldCapacity; i++) {
        // 不保留 deleted
        if (oldCellArray[i].status == legitimate) {
            hashTableInsert(oldCellArray[i].key, hashTable);
        }

        if (oldCellArray[i].status != empty) {
            free(oldCellArray[i].key);
        }
    }
    free(oldCellArray);
}
