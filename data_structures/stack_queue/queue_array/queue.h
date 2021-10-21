#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int QueueElement;

struct QueueStruct {
    int capacity;
    int size;
    int front;
    int rear;
    QueueElement* data;
};

typedef struct QueueStruct* Queue;

void queueEnqueue(QueueElement element, Queue queue);
QueueElement queueDequeue(Queue queue);
Queue queueCreate(int capacity);
void queueDestroy(Queue queue);
void queueEmpty(Queue queue);

static inline bool queueIsEmpty(Queue queue) {
    return queue->size == 0;
}

static inline QueueElement queueFront(Queue queue) {
    if (queueIsEmpty(queue)) {
        fprintf(stderr, "The queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    return queue->data[queue->front];
}

static inline QueueElement queueBack(Queue queue) {
    if (queueIsEmpty(queue)) {
        fprintf(stderr, "The queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    return queue->data[queue->rear];
}

static inline int queueSize(Queue queue) {
    return queue->size;
}

#endif
