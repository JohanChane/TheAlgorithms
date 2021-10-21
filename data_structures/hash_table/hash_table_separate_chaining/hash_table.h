#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

#include "utils/double_linked_list.h"

#define HASH_TABLE_KEY_SIZE (4 + 1)

typedef DoubleLinkedListPosition HashTablePosition;
typedef DoubleLinkedList HashTableList;

typedef char* HashTableKey;
typedef int HashTableIndex;

typedef struct HashTableStruct {
    HashTableIndex tableSize;
    HashTableList* theListArray;

} *HashTable;

void hashTableInsert(HashTableKey key, HashTable hashTable);
void hashTableErase(HashTableKey key, HashTable hashTable);
HashTable hashTableCreate(HashTableIndex tableSize);
void hashTableDestroy(HashTable hashTable);
HashTablePosition hashTableFind(HashTableKey key, HashTable hashTable);
HashTableKey hashTableRetrieve(HashTablePosition position, HashTable hashTable);

HashTableKey hashTableKeyCreate(HashTableKey key);
void hashTableKeyDestroy(HashTableKey key);

#endif
