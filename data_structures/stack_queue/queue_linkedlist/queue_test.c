#include <stdbool.h>
#include <time.h>

#include "queue.h"
#include "test_utils/utils.h"

#define ARRAY_SIZE (10000 * 10)

static void testQueue() {
    QueueElement array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end;
    Queue queue = queueCreate();
    start = getTime();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        queuePush(array[i], queue);
    }
    printf("size of queue: %d\n", queueSize(queue));

    QueueElement tmpArray[ARRAY_SIZE];
    for (int j = 0; j < ARRAY_SIZE; j++) {
        tmpArray[j] = queueFront(queue); queuePop(queue);
    }
    end = getTime();

    printf("size of queue: %d\n", queueSize(queue));
    printf("duration = %lfs\n", (double) calcDuration(start, end));

    if (!areArraysSame(array, tmpArray, ARRAY_SIZE)) {
        fprintf(stderr, "Arrays aren't same\n");
        return;
    }

    queueDestroy(queue);
}

int main() {
    testQueue();
    return 0;
}
