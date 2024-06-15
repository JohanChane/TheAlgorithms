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
    // [0, i - 1] 是已排序的序列, [i, n] 是未排序的序列。
    for (int i = 1; i < n; i++) {
        // array[j] 表示将要插入的数
        int j = i;
        // 防止覆盖，取出将要插入的数
        temp = array[j];
        // 从右到左比较已排序的数，然后右移已排序的右边的数。直到要插入的数找到合适的位置，或至首位。
        while (j > 0 && cmp(temp, array[j - 1], order) < 0) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = temp;
    }
}
