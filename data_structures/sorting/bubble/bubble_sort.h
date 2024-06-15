#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

void bubbleSort(int* array, int n);

static inline void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

#endif
