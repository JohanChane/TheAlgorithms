#include "test_utils/utils.h"
#include "queue.h"

#define ARRAY_SIZE (10000 * 10)

static void testQueue();

static void testQueue() {
    QueueElement array[ARRAY_SIZE];
    genRandomNums(array, ARRAY_SIZE, 1, ARRAY_SIZE);

    clock_t start, end;
    Queue queue = queueCreate(2);
    start = getTime();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        queueEnqueue(array[i], queue);
    }
    printf("size of queue: %d\n", queueSize(queue));

    QueueElement tmpArray[ARRAY_SIZE];
    for (int j = 0; j < ARRAY_SIZE; j++) {
        tmpArray[j] = queueDequeue(queue);
    }
    end = getTime();
    printf("size of queue: %d\n", queueSize(queue));
    printf("duration = %lfs\n", calcDuration(start, end));

    if (!areArraysSame(tmpArray, array, ARRAY_SIZE)) {
        fprintf(stderr, "Array aren't same.\n");
        return;
    }

    queueDestroy(queue);
}

int main() {
    testQueue();

    return 0;
}
