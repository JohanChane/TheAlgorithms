#include "bubble_sort.h"

void bubbleSort(int* array, int n) {
    // 从后向前冒泡
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (array[j] < array[j - 1]) {
                swap(&array[j], &array[j - 1]);
            }
        }
    }
}
