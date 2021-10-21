#include <stdio.h>
#include <stdlib.h>

#include "floy_warshall.h"
#include "test_utils/utils.h"

void floydWarshall(int src, Graph graph) {
    int** distance = malloc(sizeof(int*) * graph->vertexNum);
    if (!distance) {
        perror("malloc distance failed");
    }
    for (int i = 0; i < graph->vertexNum; i++) {
        distance[i] = malloc(sizeof(int) * graph->vertexNum);
        if (!distance[i]) {
            perror("malloc distance[i] failed");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        for (int j = 0; j < graph->vertexNum; j++) {
            distance[i][j] = graph->edges[i][j];
        }
        // 到自身的距离为 0。
        distance[i][i] = 0;
    }

    // k 为中间结点
    int newDistance;
    for (int k = 0; k < graph->vertexNum; k++) {
        for (int i = 0; i < graph->vertexNum; i++) {
            for (int j = 0; j < graph->vertexNum; j++) {
                newDistance = distance[i][k] + distance[k][j];
                if (newDistance < distance[i][j]) {
                    distance[i][j] = newDistance;
                }
            }
        }
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        if (distance[i][i] < 0) {
            fprintf(stderr, "Graph contains negative weight cycle.\n");
            return;
        }
    }

    // debug
    printArrays(distance, graph->vertexNum, graph->vertexNum);

    for (int i = 0; i < graph->vertexNum; i++) {
        free(distance[i]);
    }
    free(distance);
}
