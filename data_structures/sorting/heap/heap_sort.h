#ifndef HEAP_SORT_H
#define HEAP_SORT_H

void heapSort(int* array, int n);

static inline void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

#endif
