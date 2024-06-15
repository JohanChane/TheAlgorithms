#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "bellman_ford.h"
// debug
#include "test_utils/utils.h"

#define INFINITY INT_MAX

void bellmanFord(int src, Graph graph) {
    int* distance = malloc(sizeof(int) * graph->vertexNum);
    if (!distance) {
        perror("malloc distance failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        distance[i] = INFINITY;
    }
    distance[src] = 0;

    int i = 0, edgeIndex = 0;
    Edge edge;
    int newDistance;
    for (int i = 0; i < graph->vertexNum - 1; i++) {
        // ### 松弛所有边
        for (int j = 0; j < graph->edgeNum; j++) {
            edge = graph->edges[j];
            newDistance = distance[edge.src] + edge.weight;
            if (distance[edge.src] != INFINITY && newDistance < distance[edge.dest]) {
                distance[edge.dest] = newDistance;
            }
        }
    }

    for (int j = 0; j < graph->edgeNum; j++) {
        edge = graph->edges[j];
        if (distance[edge.src] != INFINITY && distance[edge.src] + edge.weight < distance[edge.dest]) {
            fprintf(stderr, "Graph contains negative weight cycle.\n");
            return;
        }
    }

    // debug
    printArray(distance, graph->vertexNum);

    free(distance);
}
