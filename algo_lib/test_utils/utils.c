#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "utils.h"

void printArray(int* array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

void printArrays(int** arrays, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", arrays[i][j]);
        }
        printf("\n");
    }
}

// array 的类型是 int (*)[col]
void printTwoDimensArray(void* data, int row, int col) {
    int (*array)[col] = data;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}

// data 的类型是 char (*)[col]
void printStrArrays(void* data, int row, int col) {
    char (*array)[col] = data;
    for (int i = 0; i < row; i++) {
        printf("%s\t", array[i]);
    }
    printf("\n");
}

int checkArrayOrder(int* array, int n, Order order) {
    if (order == ASC) {
        for (int i = 1; i < n; i++) {
            if (array[i - 1] > array[i]) {
                return -1;
            }
        }
    } else {
        for (int i = 1; i < n; i++) {
            if (array[i - 1] < array[i]) {
                return -1;
            }
        }
    }

    return 0;
}

bool areArraysSame(int* a, int* b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

void genRandomNums(int* outArray, int n, int lower, int upper) {
    srand(time(0));
    int tmpUpper = upper - lower + 1;
    for (int i = 0; i < n; i++) {
        outArray[i] = rand() % tmpUpper + lower;
    }
}


void genRandomChars(char* outArray, size_t n, char lower, char upper) {
    srand(time(0));
    int tmpUpper = upper - lower + 1;
    int j;
    for (size_t i = 0; i < n; i++) {
        outArray[i] = (char) (rand() % tmpUpper + lower);
    }
}

void genRandomNumsNotSame(int* outArray, int n, int lower, int upper) {
    srand(time(0));
    int tmpUpper = upper - lower + 1;
    int tmp;
    int i = 0;
    bool isSame = false;
    while (i < n) {
        tmp = rand() % tmpUpper + lower;
        for (int j = 0; j <= i; j++) {
            if (tmp == outArray[j]) {
                isSame = true;
                break;
            }
        }
        if (isSame) {
            isSame = false;
            continue;
        }

        outArray[i] = tmp;
        i++;
    }
}

// data 的类型是 char (*)[col]
void genRandomStrings(void* data, int row, int col, char lower, char upper) {
    char (*outArray)[col] = data;
    srand(time(0));
    int tmpUpper = upper - lower + 1;
    int j;
    for (int i = 0; i < row; i++) {
        for (j = 0; j < col - 1; j++) {
            outArray[i][j] = (char) (rand() % tmpUpper + lower);
        }
        outArray[i][j] = '\0';
    }
}

void reverseArray(int* array, int n) {
    int* tmpArray = malloc(sizeof(int) * n);
    if (!tmpArray) {
        perror("malloc tmpArray failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        tmpArray[i] = array[(n - 1) - i];
    }

    for (int i = 0; i < n; i++) {
        array[i] = tmpArray[i];
    }

    free(tmpArray);
}

double calcDuration(clock_t start, clock_t end) {
    // get cpu time used
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

clock_t getTime() {
    clock_t t = clock();
    if (t == (clock_t)-1) {
        fprintf(stderr, "clock() failed\n");
        exit(EXIT_FAILURE);
    }
    return t;
}
