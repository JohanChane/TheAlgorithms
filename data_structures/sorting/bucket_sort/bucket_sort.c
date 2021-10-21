#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bucket_sort.h"
#include "bucket_array.h"
#include "utils/insertion_sort.h"

// 假设数列均匀分布，每个桶预估放置数字的个数
#define ESTIMATIVE_BUCKET_SIZE 10

static inline void bucketArrayInsertionSort(BucketArray bucketArray);
static inline void bucketInsertionSort(Bucket bucket);

void bucketSort(int* array, int n) {
    // ### 根据数的范围估算桶的数量
    int min, max;
    min = max = array[0];

    for (int i = 1; i < n; i++) {
        if (array[i] < min) {
            min = array[i];
        }

        if (array[i] > max) {
            max = array[i];
        }
    }

    // #### 桶的数量（向上取整）
    int bucketCount = (((max - min) + 1) + (ESTIMATIVE_BUCKET_SIZE - 1)) / ESTIMATIVE_BUCKET_SIZE;
    // #### 每个桶的容量
    int bucketCapacity = n;

    BucketArray bucketArray = bucketArrayCreate(bucketCount, bucketCapacity);

    // ### 将数字放入桶内
    int bucketIndex;
    for (int i = 0; i < n; i++) {
        // [min, min + ESTIMATIVE_BUCKET_SIZE), [min + ESTIMATIVE_BUCKET_SIZE, min + 2 * ESTIMATIVE_BUCKET_SIZE), ...
        bucketIndex = (array[i] - min) / ESTIMATIVE_BUCKET_SIZE;
        bucketPush(array[i], bucketArray->theBuckets[bucketIndex]);
    }

    // ### 排序每个桶
    for (int i = 0; i < bucketCount; i++) {
        bucketInsertionSort(bucketArray->theBuckets[i]);
    }

    // ### 将结果放到数组
    int arrayIndex = 0;;
    for (int i = 0; i < bucketCount; i++) {
        while (!bucketIsEmpty(bucketArray->theBuckets[i])) {
            array[arrayIndex++] = bucketPop(bucketArray->theBuckets[i]);
        }
    }

    bucketArrayDestroy(bucketArray);
}

// 排序后，桶顶的数是最小的
static inline void bucketArrayInsertionSort(BucketArray bucketArray) {
    for (int i = 0; i < bucketArray->size; i++) {
        // 降序排序
        bucketInsertionSort(bucketArray->theBuckets[i]);
    }
}

static inline void bucketInsertionSort(Bucket bucket) {
    insertionSort(bucket->data, bucket->size, INSERTION_SORT_DESC);
}
