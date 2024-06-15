#include <stdbool.h>

#include "bucket_array.h"

static inline bool bucketIsFull(Bucket bucket);

BucketArray bucketArrayCreate(int arraySize, int bucketCapacity) {
    BucketArray bucketArray = malloc(sizeof(struct BucketArrayStruct));
    if (!bucketArray) {
        perror("malloc bucketArray failed");
        exit(EXIT_FAILURE);
    }

    bucketArray->size = arraySize;

    bucketArray->theBuckets = malloc(sizeof(Bucket) * arraySize);
    if (!bucketArray->theBuckets) {
        perror("malloc bucketArray->theBuckets failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < arraySize; i++) {
        bucketArray->theBuckets[i] = bucketCreate(bucketCapacity);
    }

    return bucketArray;
}

void bucketArrayDestroy(BucketArray bucketArray) {
    for (int i = 0; i < bucketArray->size; i++) {
        bucketDestroy(bucketArray->theBuckets[i]);
    }

    free(bucketArray);
}

void bucketPush(BucketElement element, Bucket bucket) {
    if (bucketIsFull(bucket)) {
        fprintf(stderr, "The Bucket is full.\n");
        exit(EXIT_FAILURE);
    }

    bucket->data[bucket->size++] = element;
}

Bucket bucketCreate(int capacity) {
    Bucket bucket = malloc(sizeof(struct BucketStruct));
    if (!bucket) {
        perror("malloc bucket failed");
        exit(EXIT_FAILURE);
    }

    bucket->data = malloc(sizeof(BucketElement) * capacity);
    if (!bucket->data) {
        perror("malloc bucket->data failed");
        exit(EXIT_FAILURE);
    }

    bucket->capacity = capacity;
    bucket->size = 0;
    return bucket;
}

void bucketDestroy(Bucket bucket) {
    free(bucket);
}

static inline bool bucketIsFull(Bucket bucket) {
    return bucket->size == bucket->capacity;
}

