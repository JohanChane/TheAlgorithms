#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "dijkstra.h"
// debug
#include "test_utils/utils.h"

#define INFINITY INT_MAX

static int minDistance(int* distance, bool* sptSet, int vertexNum);

void dijkstra(int src, Graph graph) {
    // src 到其他点的最短距离
    int* distance = malloc(sizeof(int) * graph->vertexNum);
    if (!distance) {
        perror("malloc distance failed");
        exit(EXIT_FAILURE);
    }
    // the set of shortest path tree
    bool* sptSet = malloc(sizeof(bool) * graph->vertexNum);
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

    int v;
    int newDistance;
    for (int i = 0; i < graph->vertexNum; i++) {
        // ### 在非最短路径集合中找出最近的点，并将其加入最短路径集合。
        v = minDistance(distance, sptSet, graph->vertexNum);
        // 加入最短路径集合
        sptSet[v] = true;

        // ### 更新还没有加入最短路径集合的点的距离
        for (AdjNode curNode = graph->adjLists[v]; curNode; curNode = curNode->next) {
            if (!sptSet[curNode->dest]) {
                // newDistance: src -> curV -> k
                // oldDistance: src -> k
                newDistance = distance[v] + curNode->weight;
                if (newDistance < distance[curNode->dest]) {
                    distance[curNode->dest] = newDistance;
                }
            }
        }
    }

    // debug
    printArray(distance, graph->vertexNum);

    free(distance);
    free(sptSet);
}

static int minDistance(int* distance, bool* sptSet, int vertexNum) {
    int minDistance = INFINITY, minIndex;
    for (int i = 0; i < vertexNum; i++) {
        if (!sptSet[i] && distance[i] < minDistance) {
            minIndex = i;
            minDistance = distance[i];
        }
    }

    return minIndex;
}
