#include "selection_sort.h"

void selectionSort(int* array, int n) {
    int minIndex;
    for (int i = 0; i < n; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }

        // swap min to sorted list
        swap(&array[i], &array[minIndex]);
    }
}
