#include <stdio.h>
#include <stdlib.h>

#include "heap_sort.h"

static void adjustDown(int nonLeafNodeNum, int* heap, int heapSize);

// ### debug
static int checkMaxHeap(int* array, int n);

// 从小到大排序
void heapSort(int* array, int n) {
    // ### 构造最大堆
    int* heap = malloc(sizeof(int) * (n + 1));
    if (!heap) {
        fprintf(stderr, "No space for heap!\n");
        exit(EXIT_FAILURE);
    }
    int heapSize = n;

    for (int i = 0; i < n; i++) {
        heap[i + 1] = array[i];
    }

    int nonLeafCount = n / 2 - 1;
    for (int j = nonLeafCount; j > 0; j--) {
        adjustDown(j, heap, heapSize);
    }

    // ### 排序
    for (int m = 0; m < n; m++) {
        swap(&heap[1], &heap[heapSize]);
        heapSize--;
        adjustDown(1, heap, heapSize);

        // ### debug
        /* int checkRet = checkMaxHeap(heap, heapSize); */
        /* if (checkRet < 0) { */
        /*     fprintf(stderr, "checkRet = %d\n", checkRet); */
        /*     exit(EXIT_FAILURE); */
        /* } */
    }

    // ### 将结果放入 array
    for (int k = 0; k < n; k++) {
        array[k] = heap[k + 1];
    }

    // ### 回收内存
    free(heap);
}

void adjustDown(int nonLeafNodeNum, int* heap, int heapSize) {
    int leftChildNum;
    int rightChildNum;
    int maxNodeNum;
    int theNodeNum = nonLeafNodeNum;
    int nonLeafCount = heapSize / 2;
    while (theNodeNum <= nonLeafCount) {
        leftChildNum = theNodeNum * 2;
        rightChildNum = leftChildNum + 1;

        maxNodeNum = theNodeNum;
        if (heap[leftChildNum] > heap[maxNodeNum]) {
            maxNodeNum = leftChildNum;
        }
        if (rightChildNum <= heapSize && heap[rightChildNum] > heap[maxNodeNum]) {
            maxNodeNum = rightChildNum;
        }

        if (maxNodeNum != theNodeNum) {
            swap(&heap[maxNodeNum], &heap[theNodeNum]);
            theNodeNum = maxNodeNum;
        } else {
            break;
        }
    }
}

static int checkMaxHeap(int* array, int n) {
    int curPos = 1;
    int leftChildPos = 2 * curPos;
    int rightChildPos;
    while (leftChildPos < n) {
        if (array[leftChildPos] > array[curPos]) {
            return -1;
        }

        rightChildPos = leftChildPos + 1;
        if (rightChildPos < n) {
            if (array[rightChildPos] > array[curPos]) {
                return -2;
            }
        }

        curPos++;
        leftChildPos = 2 * curPos;
        rightChildPos = leftChildPos + 1;
    }

    return 0;
}
