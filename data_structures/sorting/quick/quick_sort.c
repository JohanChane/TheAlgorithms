#include "quick_sort.h"

static void qSort(int* array, int left, int right);
static int median3(int* array, int left, int right);
static void insertionSort(int* array, int n);

void quickSort(int* array, int n) {
    qSort(array, 0, n - 1);
}

void qSort(int* array, int left, int right) {
    int elementNum = right - left + 1;
    if (elementNum <= 3) {
        // 插入排序
        insertionSort(array + left, elementNum);
        return;
    }

    int pivot = median3(array, left, right);

    int i = left, j = right - 1;
    while (1) {
        // 找到 array[i] >= pivot
        // 这种方式下，如果所有数是 pivot（极小概率的情况）, 要检查 i 是否越界，所以不采用。
        // while (array[++i] <= pivot) { }
        while (array[++i] < pivot) { }
        // 找到 array[j] <= pivot
        while (array[--j] > pivot) { }
        // `i == j` 的情况是 `array[i] == pivot`。将 elementValue == pivot 的数放在左右都没有影响排序结果。
        if (i < j) {
            swap(&array[i], &array[j]);
        } else {
            break;
        }
    }

    // i 之前的数是小于 pivot 的，j 之后的数是大于 pivot 的。i 可能等于 j。

    // restore pivot
    swap(&array[i], &array[right - 1]);

    qSort(array, left, i - 1);
    qSort(array, i + 1, right);
}

int median3(int* array, int left, int right) {
    int center = (right + left) / 2;

    // 冒泡排序
    if (array[right] < array[center]) {
        swap(&array[right], &array[center]);
    }

    if (array[center] < array[left]) {
        swap(&array[center], &array[left]);
    }

    if (array[right] < array[center]) {
        swap(&array[right], &array[center]);
    }

    // hide pivot
    swap(&array[center], &array[right - 1]);
    return array[right - 1];
}

static void insertionSort(int* array, int n) {
    int temp;
    for (int i = 1; i < n; i++) {
        // j 表示将要插入的位置
        int j = i;
        // 防止覆盖，取出将要插入的数
        temp = array[j];
        // 移动。遇到 <= temp 的数停止，或到 j == 0
        while (j > 0 && array[j - 1] > temp) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = temp;
    }
}
