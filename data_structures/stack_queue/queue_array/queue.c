#include "queue.h"

static inline bool queueIsFull(Queue queue);
static inline int queueSucc(int index, Queue queue);

// ## debug
#include <time.h>

#define ARRAY_SIZE (10000 * 10)
// #define ARRAY_SIZE (10)

void queueEnqueue(QueueElement element, Queue queue) {
    if (queueIsFull(queue)) {
        int newCapacity = queue->capacity * 2;
        QueueElement* newData = malloc(sizeof(QueueElement) * newCapacity);
        if (!newData) {
            fprintf(stderr, "No space for newData!\n");
            exit(EXIT_FAILURE);
        }

        int qsize = queueSize(queue);
        for (int i = 0; i < qsize; i++) {
            newData[i] = queueDequeue(queue);
        }
        free(queue->data);
        queue->data = newData;
        queue->capacity = newCapacity;
        queue->front = 0;
        queue->size = qsize;
        queue->rear = queue->size - 1;
    }

    queue->rear = queueSucc(queue->rear, queue);
    queue->data[queue->rear] = element;
    queue->size++;
}

QueueElement queueDequeue(Queue queue) {
    if (queueIsEmpty(queue)) {
        fprintf(stderr, "The queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    QueueElement frontElement = queueFront(queue);
    queue->front = queueSucc(queue->front, queue);
    queue->size--;
    return frontElement;
}

void queueEmpty(Queue queue) {
    queue->size = 0;
    queue->rear = 0;
    queue->front = 1;
}

Queue queueCreate(int capacity) {
    Queue queue = malloc(sizeof(struct QueueStruct));
    if (!queue) {
        fprintf(stderr, "No space for creating queue!\n");
        exit(EXIT_FAILURE);
    }

    queue->data = malloc(sizeof(QueueElement) * capacity);
    if (!queue->data) {
        fprintf(stderr, "No space for queue data!\n");
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;

    queueEmpty(queue);
    return queue;
}

void queueDestroy(Queue queue) {
    free(queue->data);
    free(queue);
}

static inline bool queueIsFull(Queue queue) {
    return queue->size == queue->capacity;
}

static inline int queueSucc(int index, Queue queue) {
    if (++index == queue->capacity) {
        index = 0;
    }
    return index;
}
