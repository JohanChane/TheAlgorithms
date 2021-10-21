#include <limits.h>

#include "external_sort.h"

typedef struct ExternalSortStruct {
    Run* runs;
    int runCount;
    SuccessTree successTree;
} *ExtSort;

typedef int Element;

#define ELEMENT_MAX INT_MAX

static Element extSortSortUtil(ExtSort extSort);
static void extSortInitSuccessTree(ExtSort extSort);
static ExtSort extSortCreate(Run* sortedRuns, int runCount);
static void extSortDestroy(ExtSort extSort);

void extSortSort(Run mergedRun, Run* sortedRuns, int runNum) {
    ExtSort extSort = extSortCreate(sortedRuns, runNum);
    extSortInitSuccessTree(extSort);
    while (extSort->runCount > 0) {
        queuePush(extSortSortUtil(extSort), mergedRun);
    }
    extSortDestroy(extSort);
}

static Element extSortSortUtil(ExtSort extSort) {
    SuccessTree successTree = extSort->successTree;

    int indexInRoot = successTree->nonLeaves[1];
    // 找到 successTree Root 的元素
    Element elementInRoot = successTree->leaves[indexInRoot];
    Run theRun = extSort->runs[indexInRoot];
    if (!queueIsEmpty(theRun)) {
        // 将 theRun 的数据放进入空位。
        successTree->leaves[indexInRoot] = queueFront(theRun); queuePop(theRun);
    } else {
        // 将 ELEMENT_MAX 放进入空位。
        successTree->leaves[indexInRoot] = ELEMENT_MAX;
        extSort->runCount--;
    }

    successTreeAdjustToRoot(indexInRoot, successTree);

    return elementInRoot;
}

static void extSortInitSuccessTree(ExtSort extSort) {
    SuccessTree successTree = extSort->successTree;
    int leaveNum = successTree->leaveNum;

    for (int i = 0; i < leaveNum; i++) {
        successTree->leaves[i] = queueFront(extSort->runs[i]); queuePop(extSort->runs[i]);
    }

    for (int i = leaveNum - 1; i >= 0; i--) {
        successTreeAdjustToRoot(i, successTree);
    }
}

static ExtSort extSortCreate(Run* sortedRuns, int runCount) {
    ExtSort extSort = malloc(sizeof(struct ExternalSortStruct));
    if (!extSort) {
        perror("malloc extSort failed");
        exit(EXIT_FAILURE);
    }

    // 用外部的 runs。这里只是记录指针。因为对外接口会一次排序完所有顺串，所以不会有泄漏内存的情况。
    extSort->runs = sortedRuns;
    extSort->runCount = runCount;
    extSort->successTree = successTreeCreate(runCount);

    return extSort;
}

static void extSortDestroy(ExtSort extSort) {
    successTreeDestroy(extSort->successTree);
    free(extSort);
}

Run* runsCreate(int n, int capacity) {
    Run* runs = malloc(sizeof(Run) * n);
    if (!runs) {
        perror("malloc runs failed.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        runs[i] = queueCreate(capacity);
    }

    return runs;
}

void runsDestroy(Run* runs, int n) {
    for (int i = 0; i < n; i++) {
        queueDestroy(runs[i]);
    }
    free(runs);
}
