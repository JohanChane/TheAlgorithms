#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

void selectionSort(int* array, int n);

static inline void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

#endif
