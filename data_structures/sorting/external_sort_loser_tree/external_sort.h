#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H

#include "utils/queue.h"

typedef Queue Run;

void extSortSort(Run mergedRun, Run* sortedRuns, int runNum);

Run* runsCreate(int n, int capacity);
void runsDestroy(Run* runs, int n);

#endif
