#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils/double_linked_list.h"
#include "hash_table.h"

static inline bool hashTableAreKeyEqual(HashTableKey keyA, HashTableKey keyB) {
    return !strncmp(keyA, keyB, HASH_TABLE_KEY_SIZE - 1);
}

static HashTableIndex hashTableHash(HashTableKey key, HashTableIndex tableSize);
static HashTableList hashTableGetList(HashTableKey key, HashTable hashTable);
static HashTablePosition hashTableFindList(HashTableKey key, HashTableList list);

static HashTableIndex hashTableHash(HashTableKey key, HashTableIndex tableSize) {
    int hashVal = 0;

    int i = 0;
    while (key[i] != '\0') {
        hashVal += (hashVal << 5) + key[i++];
    }
    return hashVal % tableSize;
}

static HashTableList hashTableGetList(HashTableKey key, HashTable hashTable) {
    return hashTable->theListArray[hashTableHash(key, hashTable->tableSize)];
}

// 不存放相同的 key
void hashTableInsert(HashTableKey key, HashTable hashTable) {
    HashTablePosition pos = hashTableFind(key, hashTable);
    if (pos) {
        return;
    }

    // ### copy key
    HashTableKey newkey = hashTableKeyCreate(key);

    // ### insert key to LinkedList
    HashTableList list = hashTableGetList(newkey, hashTable);
    // 插入到链表头
    doubleLinkedListPushFront(newkey, list);
}

void hashTableErase(HashTableKey key, HashTable hashTable) {
    HashTableList list = hashTableGetList(key, hashTable);
    HashTablePosition pos = hashTableFindList(key, list);
    if (pos) {
        // 回收 key 的内存
        hashTableKeyDestroy(pos->element);
        // 回收 list 的内存
        doubleLinkedListErase(pos, list);
    }
}

HashTable hashTableCreate(HashTableIndex tableSize) {
    HashTable hashTable = malloc(sizeof(struct HashTableStruct));
    if (!hashTable) {
        fprintf(stderr, "No space for hashTable!\n");
        exit(EXIT_FAILURE);
    }
    hashTable->tableSize = tableSize;

    // ### 创建 theListArray
    // #### 创建指向 HashTableList 的数组
    hashTable->theListArray = malloc(sizeof(HashTableList) * hashTable->tableSize);
    if (!hashTable->theListArray) {
        fprintf(stderr, "No space for hashTable->theListArray!\n");
        exit(EXIT_FAILURE);
    }

    // #### 为 theListArray 数组中的 HashTableList 创建链表头
    for (HashTableIndex i = 0; i < hashTable->tableSize; i++) {
        hashTable->theListArray[i] = doubleLinkedListCreate();
    }

    return hashTable;
}

void hashTableDestroy(HashTable hashTable) {
    if (!hashTable || !hashTable->theListArray) {
        fprintf(stderr, "hashTable is NULL!\n");
        exit(EXIT_FAILURE);
    }

    HashTableList list;
    HashTablePosition curPos;
    for (HashTableIndex i = 0; i < hashTable->tableSize; i++) {
        list = hashTable->theListArray[i];
        // ### 销毁链表的数据
        curPos = doubleLinkedListBegin(list);
        while (curPos) {
            // #### 销毁元素
            hashTableKeyDestroy(curPos->element);
        }
        // ### 销毁链表
        doubleLinkedListDestroy(list);
    }
    // ### 销毁 hashTable
    free(hashTable);
}

HashTablePosition hashTableFind(HashTableKey key, HashTable hashTable) {
    HashTableList list = hashTableGetList(key, hashTable);

    // ### 查找 key 在链表中的位置
    return hashTableFindList(key, list);
}

// 可以用 doubleLinkedList 的查找，不过要定义它的比较函数。这里新定义一个查找 list 函数。
static HashTablePosition hashTableFindList(HashTableKey key, HashTableList list) {
    HashTablePosition cur = doubleLinkedListBegin(list);
    while (cur) {
        if (hashTableAreKeyEqual(key, cur->element)) {
            break;
        } else {
            cur = cur->next;
        }
    }

    return cur;
}

HashTableKey hashTableRetrieve(HashTablePosition position, HashTable hashTable) {
    return position->element;
}

HashTableKey hashTableKeyCreate(HashTableKey key) {
    HashTableKey newkey = malloc(HASH_TABLE_KEY_SIZE);
    if (!newkey) {
        fprintf(stderr, "No space for newkey!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(newkey, key, HASH_TABLE_KEY_SIZE - 1);
    newkey[HASH_TABLE_KEY_SIZE - 1] = '\0';

    return newkey;
}

void hashTableKeyDestroy(HashTableKey key) {
    free(key);
}
