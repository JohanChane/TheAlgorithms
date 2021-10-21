#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "utils/graph.h"
#include "test_utils/utils.h"

static int minDistance(int* distance, bool* sptSet, int n);

void dijkstra(int src, Graph graph) {
    // src 到其他点的最短距离
    int* distance = malloc(sizeof(int) * graph->vertexNum);
    if (!distance) {
        perror("malloc distance failed");
        exit(EXIT_FAILURE);
    }

    // the set of shortest path tree
    bool* sptSet = malloc(sizeof(int) * graph->vertexNum);
    if (!sptSet) {
        perror("malloc sptSet failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        distance[i] = INFINITY;
        sptSet[i] = false;
    }

    // 自己到自己的权为 0
    distance[src] = 0;

    int curV;
    int newDistance;
    for (int j = 0; j < graph->vertexNum; j++) {
        // ### 在非最短路径集合中找出最近的点，并将其加入最短路径集合。
        curV = minDistance(distance, sptSet, graph->vertexNum);
        // 加入最短路径集合
        sptSet[curV] = true;

        // ### 更新还没有加入最短路径集合的点的距离
        for (int k = 0; k < graph->vertexNum; k++) {
            // newDistance: src -> curV -> k
            // oldDistance: src -> k
            newDistance = distance[curV] + graph->edges[curV][k];
            if (!sptSet[k] && graph->edges[curV][k] != INFINITY && newDistance < distance[k]) {
                distance[k] = newDistance;
            }
        }
    }

    // debug
    printArray(distance, graph->vertexNum);

    free(distance);
    free(sptSet);
}

static int minDistance(int* distance, bool* sptSet, int n) {
    int minDistance = INFINITY, minIndex;
    for (int i = 0; i < n; i++) {
        if (!sptSet[i] && distance[i] < minDistance) {
            minIndex = i;
            minDistance = distance[i];
        }
    }

    return minIndex;
}
