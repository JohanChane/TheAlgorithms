#ifndef BUCKET_ARRAY_H
#define BUCKET_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

typedef int BucketElement;

typedef struct BucketStruct* Bucket;
typedef struct BucketArrayStruct {
    Bucket* theBuckets;
    int size;
} *BucketArray;

struct BucketStruct {
    BucketElement* data;
    int size;
    int capacity;
};

// ## BucketArray 的接口
BucketArray bucketArrayCreate(int arraySize, int bucketCapacity);
void bucketArrayDestroy(BucketArray bucketArray);

// ## Bucket 的接口
Bucket bucketCreate(int capacity);
void bucketDestroy(Bucket bucket);

void bucketPush(BucketElement element, Bucket bucket);

static inline BucketElement bucketPop(Bucket bucket) {
    if (!bucket->size) {
        fprintf(stderr, "Bucket is empty.\n");
        exit(EXIT_FAILURE);
    }
    return bucket->data[--bucket->size];
}

static inline void bucketClear(Bucket bucket) {
    bucket->size = 0;
}

static inline bool bucketIsEmpty(Bucket bucket) {
    return !bucket->size;
}

static inline int bucketSize(Bucket bucket) {
    return bucket->size;
}

#endif
