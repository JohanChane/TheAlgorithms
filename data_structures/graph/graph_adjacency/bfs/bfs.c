#include <stdio.h>
#include <stdlib.h>

#include "utils/queue.h"
#include "bfs.h"

void bfs(int src, Graph graph) {
    bool* visited = malloc(sizeof(bool) * graph->vertexNum);
    if (!visited) {
        perror("malloc visited failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        visited[i] = false;
    }

    Queue queue = queueCreate(graph->vertexNum);

    // ### 访问 src 结点，并将它加入队列
    visited[src] = true;
    queuePush(src, queue);

    int s;
    while (!queueIsEmpty(queue)) {
        s = queueFront(queue); queuePop(queue);
        // debug
        printf("%d\t", s);

        // ### 访问 s 的邻接结点并将它们加入邻接队列
        for (AdjNode curNode = graph->adjLists[s]; curNode; curNode = curNode->next) {
            if (!visited[curNode->dest]) {
                visited[curNode->dest] = true;
                queuePush(curNode->dest, queue);
            }
        }
    }
    // debug
    printf("\n");

    queueDestroy(queue);
    free(visited);
}
