#include <limits.h>

#include "loser_tree.h"
#include "external_sort.h"

typedef struct ExternalSortStruct {
    Run* runs;
    int runCount;
    LoserTree loserTree;
} *ExtSort;

typedef int Element;

#define ELEMENT_MIN INT_MIN
#define ELEMENT_MAX INT_MAX

static Element extSortSortUtil(ExtSort extSort);
static void extSortInitLoserTree(ExtSort extSort);
static ExtSort extSortCreate(Run* sortedRuns, int runCount);
static void extSortDestroy(ExtSort extSort);

void extSortSort(Run mergedRun, Run* sortedRuns, int runNum) {
    ExtSort extSort = extSortCreate(sortedRuns, runNum);
    extSortInitLoserTree(extSort);
    while (extSort->runCount > 0) {
        queuePush(extSortSortUtil(extSort), mergedRun);
    }
    extSortDestroy(extSort);
}

static Element extSortSortUtil(ExtSort extSort) {
    LoserTree loserTree = extSort->loserTree;

    int indexInRoot = loserTree->nonLeaves[0];
    // 找到 loserTree Root 的元素
    Element elementInRoot = loserTree->leaves[indexInRoot];
    Run theRun = extSort->runs[indexInRoot];
    if (!queueIsEmpty(theRun)) {
        // 将 theRun 的数据放进入空位。
        loserTree->leaves[indexInRoot] = queueFront(theRun); queuePop(theRun);
    } else {
        // 将 ELEMENT_MAX 放进入空位。
        loserTree->leaves[indexInRoot] = ELEMENT_MAX;
        extSort->runCount--;
    }

    loserTreeAdjustToRoot(indexInRoot, loserTree);

    return elementInRoot;
}

static void extSortInitLoserTree(ExtSort extSort) {
    LoserTree loserTree = extSort->loserTree;
    int leaveNum = loserTree->leaveNum;

    loserTree->leaves[leaveNum] = ELEMENT_MIN;

    for (int i = 1; i < leaveNum; i++) {
        loserTree->nonLeaves[i] = leaveNum;
    }

    for (int i = 0; i < leaveNum; i++) {
        loserTree->leaves[i] = queueFront(extSort->runs[i]); queuePop(extSort->runs[i]);
    }

    for (int i = leaveNum - 1; i >= 0; i--) {
        loserTreeAdjustToRoot(i, loserTree);
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
    extSort->loserTree = loserTreeCreate(runCount);

    return extSort;
}

static void extSortDestroy(ExtSort extSort) {
    loserTreeDestroy(extSort->loserTree);
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
