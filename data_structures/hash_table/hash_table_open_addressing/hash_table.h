#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define KEY_SIZE (4 + 1)

typedef char* Key;

typedef int Index;
typedef Index TableSize;
typedef Index Position;

typedef enum EntryStatusEnum {
    empty,
    legitimate,
    deleted
} EntryStatus;

typedef struct HashEntryStruct {
    Key key;
    EntryStatus status;
} Cell;

typedef struct HashTableStruct {
    TableSize capacity;
    TableSize size;
    Cell *theCellArray;
} *HashTable;

void hashTableInsert(Key key, HashTable hashTable);
void hashTableDelete(Key key, HashTable hashTable);
Position hashTableFind(Key key, HashTable hashTable);
HashTable hashTableCreate(TableSize capacity);
void hashTableDestroy(HashTable hashTable);
Key hashTableRetrieve(Position position, HashTable hashTable);

#endif
