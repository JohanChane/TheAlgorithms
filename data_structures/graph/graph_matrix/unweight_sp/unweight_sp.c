#include <limits.h>

#include "utils/queue.h"
#include "unweight_sp.h"
#include "test_utils/utils.h"

// unweight single source shortest paths
// 用广度优先搜索的方法解决
void unweightSP(int src, Graph graph) {
    // ### 创建并初始化 visited 和 distance。
    int* visited = malloc(sizeof(int) * graph->vertexNum);
    if (!visited) {
        perror("malloc visited failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < graph->vertexNum; i++) {
        visited[i] = 0;
    }

    int* distance = malloc(sizeof(int) * graph->vertexNum);
    if (!distance) {
        perror("malloc visited failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < graph->vertexNum; i++) {
        distance[i] = INFINITY;
    }
    distance[src] = 0;

    // ### 访问第一个点
    visited[src] = 1;
    Queue queue = queueCreate(graph->vertexNum * graph->vertexNum);
    queuePush(src, queue);

    int curV;
    int curDistance = 1;
    while(!queueIsEmpty(queue)) {
        curV = queueFront(queue);
        queuePop(queue);

        // ### 访问当前结点的邻近结点
        for (int i = 0; i < graph->vertexNum; i++) {
            if (!visited[i] && graph->edges[curV][i]) {
                visited[i] = 1;
                distance[i] = curDistance;
                queuePush(i, queue);
            }
        }
        curDistance++;
    }

    queueDestroy(queue);

    // debug
    printArray(distance, graph->vertexNum);

    free(visited);
    free(distance);
}
