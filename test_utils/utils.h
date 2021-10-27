#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <time.h>
#include <stdbool.h>

typedef enum ORDER { ASC, DESC } Order;

void printArray(int* array, int n);
void printArrays(int** arrays, int m, int n);
void printTwoDimensArray(void* data, int row, int col);
void printStrArrays(void* data, int row, int col);

int checkArrayOrder(int* array, int n, Order order);
bool areArraysSame(int* a, int* b, int n);

void genRandomNums(int* outArray, int n, int lower, int upper);
void genRandomChars(char* outArray, size_t n, char lower, char upper);
void genRandomNumsNotSame(int* outArray, int n, int lower, int upper);
void genRandomStrings(void* data, int row, int col, char lower, char upper);

void reverseArray(int* array, int n);

double calcDuration(clock_t start, clock_t end);
clock_t getTime();

#endif
