#include <stdlib.h>
#include <string.h>

#include "counting_sort.h"

// array: [0, ~)
void countingSort(int* array, int n) {
    // ### 分配内存
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

    int elementNum = max - min + 1;
    int* countingArray = malloc(sizeof(int) * elementNum);
    memset(countingArray, 0, elementNum * sizeof(int));

    // ### 计数
    for (int j = 0; j < n; j++) {
        countingArray[array[j] - min] += 1;
    }

    // ### 复制结果
    int m = 0;
    for (int k = 0; k < elementNum; k++) {
        while (countingArray[k] > 0) {
            array[m++] = min + k;
            countingArray[k]--;
        }
    }

    // ### 回收内存
    free(countingArray);
}
