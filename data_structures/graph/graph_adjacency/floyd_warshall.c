#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "floyd_warshall.h"

// 条件：边权值之和 + FLOY_WARSHALL_INFINITY <= INT_MAX
#define FLOY_WARSHALL_INFINITY (INT_MAX / 2)

void floydWarshall(Graph graph);

void floydWarshall(Graph graph) {
    int** distance = malloc(sizeof(int*) * graph->vertexNum);
    if (!distance) {
        perror("malloc distance failed");
        exit(EXIT_FAILURE);
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
            distance[i][j] = FLOY_WARSHALL_INFINITY;
        }
        // 到自身的距离为 0。
        distance[i][i] = 0;
    }

    for (int v = 0; v < graph->vertexNum; v++) {
        for (AdjNode curNode = graph->adjLists[v]; curNode; curNode = curNode->next) {
            distance[v][curNode->dest] = curNode->weight;
        }
    }

    int newDistance;
    for (int k = 0; k < graph->vertexNum; k++) {
        for (int i = 0; i < graph->vertexNum; i++) {
            for (int j = 0; j < graph->vertexNum; j++) {
                // k 为中间结点
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

    for (int i = 0; i < graph->vertexNum; i++) {
        for (int j = 0; j < graph->vertexNum; j++) {
            printf("%d\t", distance[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        free(distance[i]);
    }
    free(distance);
}
