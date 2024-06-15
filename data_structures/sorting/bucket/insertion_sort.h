#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

typedef enum InsertionSortOrderEnum {
    INSERTION_SORT_ASC,
    INSERTION_SORT_DESC
} InsertionSortOrder;

void insertionSort(int* array, int n, InsertionSortOrder order);

#endif
