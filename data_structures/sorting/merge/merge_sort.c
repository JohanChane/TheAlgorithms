#include <stdio.h>
#include <stdlib.h>

#include "merge_sort.h"

static void mSort(int* array, int* tmpArray, int left, int right);
static void merge(int* array, int* tmpArray, int leftPos, int rightPos, int rightEnd);

void mergeSort(int* array, int n) {
    int* tmpArray = malloc(n * sizeof(int));
    if (!tmpArray) {
        fprintf(stderr, "No space for tmpArray!\n");
        exit(EXIT_FAILURE);
    }

    mSort(array, tmpArray, 0, n - 1);

    free(tmpArray);
}

// 将已排序的数列 [leftPos, rightPos), [rightPos, rightEnd] 合并
static void merge(int* array, int* tmpArray, int leftPos, int rightPos, int rightEnd) {
    // ### 比较两个数列，每个数列拿出最小的数比较，最小者就两个数列中最小的数
    // #### 保存信息, 因为之后修改参数
    int elementNum = rightEnd - leftPos + 1;
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (array[leftPos] < array[rightPos]) {
            tmpArray[tmpPos++] = array[leftPos++];
        } else {
            tmpArray[tmpPos++] = array[rightPos++];
        }
    }

    // ### 将剩余的数放入 tmpArray 中
    while (leftPos <= leftEnd) {
        tmpArray[tmpPos++] = array[leftPos++];
    }

    while (rightPos <= rightEnd) {
        tmpArray[tmpPos++] = array[rightPos++];
    }

    // ### 排序结果放入 array 的 [leftPos, rightEnd] 中
    for (int i = 0; i < elementNum; i++) {
        array[rightEnd] = tmpArray[rightEnd];
        rightEnd--;
    }
}

static void mSort(int* array, int* tmpArray, int left, int right) {
    // ### base case
    // 少于一个数
    if (right - left + 1 <= 1) {
        return;
    }

    int center = (left + right) / 2;
    mSort(array, tmpArray, left, center);
    mSort(array, tmpArray, center + 1, right);
    merge(array, tmpArray, left, center + 1, right);
}
