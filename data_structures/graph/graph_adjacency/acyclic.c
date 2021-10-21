#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "utils/graph_utils.h"
#include "acyclic.h"

#define INFINITY INT_MAX
#define NEGATIVE_INFINITY INT_MIN

// Acyclic graph shortest paths
void acyclicSP(int src, Graph graph) {
    int* topoSort = malloc(sizeof(int) * graph->vertexNum);
    if (!topoSort) {
        perror("malloc topoSort failed");
        exit(EXIT_FAILURE);
    }
    if (topologicalSort(topoSort, graph) < 0) {
        fprintf(stderr, "The graph is cyclic.\n");
        return;
    }

    int* distance = malloc(sizeof(int) * graph->vertexNum);
    if (!distance) {
        perror("malloc distance failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < graph->vertexNum; i++) {
        distance[i] = INFINITY;
    }
    distance[src] = 0;

    int v;
    int newDistance;
    for (int i = 0; i < graph->vertexNum; i++) {
        v = topoSort[i];
        if (distance[v] == INFINITY) {
            continue;
        }

        for (AdjNode curNode = graph->adjLists[v]; curNode; curNode = curNode->next) {
            newDistance = distance[v] + curNode->weight;
            if (newDistance < distance[curNode->dest]) {
                distance[curNode->dest] = newDistance;
            }
        }
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        printf("%d\t", distance[i]);
    }
    printf("\n");

    free(topoSort);
    free(distance);
}

// Acyclic graph longest paths
void acyclicLP(int src, Graph graph) {
    int* topoSort = malloc(sizeof(int) * graph->vertexNum);
    if (!topoSort) {
        perror("malloc topoSort failed");
        exit(EXIT_FAILURE);
    }
    if (topologicalSort(topoSort, graph) < 0) {
        fprintf(stderr, "The graph is cyclic.\n");
        return;
    }

    int* distance = malloc(sizeof(int) * graph->vertexNum);
    if (!distance) {
        perror("malloc distance failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < graph->vertexNum; i++) {
        distance[i] = NEGATIVE_INFINITY;
    }
    distance[src] = 0;

    int v;
    int newDistance;
    for (int i = 0; i < graph->vertexNum; i++) {
        v = topoSort[i];
        if (distance[v] == NEGATIVE_INFINITY) {
            continue;
        }

        for (AdjNode curNode = graph->adjLists[v]; curNode; curNode = curNode->next) {
            newDistance = distance[v] + curNode->weight;
            if (newDistance > distance[curNode->dest]) {
                distance[curNode->dest] = newDistance;
            }
        }
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        printf("%d\t", distance[i]);
    }
    printf("\n");

    free(topoSort);
    free(distance);
}
