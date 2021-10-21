#include <stdbool.h>
#include "insertion_sort.h"

// 负数则 a 在 b 的前面, 否则反之。
static int cmp(int a, int b, InsertionSortOrder order) {
    if (order == INSERTION_SORT_ASC) {
        return a - b;
    } else {
        return b - a;
    }
}

void insertionSort(int* array, int n, InsertionSortOrder order) {
    int temp;
    for (int i = 1; i < n; i++) {
        // j 表示将要插入的位置
        int j = i;
        // 防止覆盖，取出将要插入的数
        temp = array[j];
        // 从右到左比较已排序的数，然后右移已排序的右边的数。遇到在 temp 左边的数停止，或到 j == 0
        while (j > 0 && cmp(temp, array[j - 1], order) < 0) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = temp;
    }
}
