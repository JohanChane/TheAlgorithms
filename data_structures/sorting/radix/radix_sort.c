#include <stdio.h>
#include <stdlib.h>

#include "radix_sort.h"

// 只能是 10
#define BUCKET_COUNT 10

static void radixSortWithExp(int* array, int n, int exp);
static int getMaxExp(int* array, int n);
static inline int getBucketIndex(int element, int exp);

// 从小到大排序
void radixSort(int* array, int n) {
    int maxExp = getMaxExp(array, n);
    for (int exp = 1; exp <= maxExp; exp *= 10) {
        radixSortWithExp(array, n, exp);
    }
}

static void radixSortWithExp(int* array, int n, int exp) {
    int* bucketData = malloc(sizeof(int) * n);
    if (!bucketData) {
        fprintf(stderr, "No space for bucketData!\n");
        exit(EXIT_FAILURE);
    }
    // ### 计算 bucketTops
    // bucket 在 bucketData 中的桶顶
    int bucketTops[BUCKET_COUNT];
    for (int p = 0; p < BUCKET_COUNT; p++) {
        bucketTops[p] = 0;
    }

    // 记录每个桶包含的数的数量
    for (int i = 0; i < n; i++) {
        bucketTops[getBucketIndex(array[i], exp)]++;
    }

    // 计算 bucketTops（桶底在数组之后，桶顶在数组之前。如果是从小到大排序，则较大的数放入桶底。）
    for (int j = 1; j < BUCKET_COUNT; j++) {
        bucketTops[j] += bucketTops[j - 1];
    }

    // ### 从 9 到 0 桶且从桶底到桶顶遍历。这样就可以将大的数放入桶底。
    int bucketIndex;
    for (int k = n - 1; k >= 0; k--) {
        bucketIndex = getBucketIndex(array[k], exp);
        bucketData[--bucketTops[bucketIndex]] = array[k];
    }

    // ### 将桶的结果放入数组中
    for (int m = 0; m < n; m++) {
        array[m] = bucketData[m];
    }

    // ### 回收内存
    free(bucketData);
}

// ### 获取最大指数
// exp == 1: 表示对个位排序
// exp == 10: 表示对十位排序
// exp == 100: 表示对百位排序
static int getMaxExp(int* array, int n) {
    // ### 找出最大值
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    // ### 计算最大指数
    int exp = 1;
    while(max /= 10) {
        exp *= 10;
    }

    return exp;
}

static inline int getBucketIndex(int element, int exp) {
    return (element / exp) % 10;
}
