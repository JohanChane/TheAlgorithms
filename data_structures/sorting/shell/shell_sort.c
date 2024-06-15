#include "shell_sort.h"

void shellSort(int* array, int n) {
    for (int increment = n / 2; increment > 0; increment /= 2) {
        // ## 所有增量序列一起排序, 而不是先排序一个增量序列一再排序另一个。
        for (int i = increment; i < n; i++) {
            int temp = array[i];
            int j = i;

            // ### 采用插入排序
            // 移位，直至遇到合适的位置，或数列的首位
            while (j - increment >= 0 && array[j - increment] > temp) {
                array[j] = array[j - increment];
                j -= increment;
            }

            // 插入
            array[j] = temp;
        }
    }
}
