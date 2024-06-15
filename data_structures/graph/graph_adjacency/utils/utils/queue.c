#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

void queuePush(QueueElement element, Queue queue) {
    QueueNode node = malloc(sizeof(struct QueueNodeStruct));
    if (!node) {
        fprintf(stderr, "No space for new Node!\n");
        exit(EXIT_FAILURE);
    }
    node->element = element;
    node->next = NULL;

    if (!queue->size) {
        queue->rear = node;
        queue->front = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->size++;
}

void queuePop(Queue queue) {
    if (queueIsEmpty(queue)) {
        fprintf(stderr, "The queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    QueueNode tmpNode = queue->front;
    queue->front = tmpNode->next;
    queue->size--;

    free(tmpNode);
}

Queue queueCreate() {
    Queue queue = malloc(sizeof(struct QueueStruct));
    if (!queue) {
        fprintf(stderr, "No space for creating queue!\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void queueDestroy(Queue queue) {
    QueueNode tmpNode;
    while (queue->front) {
        tmpNode = queue->front;
        queue->front = queue->front->next;
        free(tmpNode);
    }
    free(queue);
}

void queueClear(Queue queue) {
    QueueNode tmpNode;
    while (queue->front) {
        tmpNode = queue->front;
        queue->front = queue->front->next;
        free(tmpNode);
    }
    queue->rear = NULL;
    queue->size = 0;
}
