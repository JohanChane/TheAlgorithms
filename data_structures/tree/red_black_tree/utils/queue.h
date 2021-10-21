#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct RBTreeNodeStruct* QueueElement;

typedef struct QueueNodeStruct* QueueNode;

typedef struct QueueStruct {
    QueueNode front;
    QueueNode rear;
    int size;
} *Queue;

struct QueueNodeStruct {
    QueueElement element;
    QueueNode next;
};

void queuePush(QueueElement element, Queue queue);
void queuePop(Queue queue);
Queue queueCreate();
void queueDestroy(Queue queue);
void queueClear(Queue queue);

static inline bool queueIsEmpty(Queue queue) {
    return queue->size == 0;
}

static inline QueueElement queueFront(Queue queue) {
    if (queueIsEmpty(queue)) {
        fprintf(stderr, "The queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    return queue->front->element;
}

static inline QueueElement queueBack(Queue queue) {
    if (queueIsEmpty(queue)) {
        fprintf(stderr, "The queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    return queue->rear->element;
}

static int queueSize(Queue queue) {
    return queue->size;
}

#endif
