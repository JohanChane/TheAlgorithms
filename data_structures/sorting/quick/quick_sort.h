#ifndef QUICK_SORT_H
#define QUICK_SORT_H

void quickSort(int* array, int n);

static inline void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

#endif
