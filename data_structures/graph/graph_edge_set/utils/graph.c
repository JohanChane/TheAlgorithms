#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"

Graph graphCreate(int vertexNum, int edgeNum) {
    Graph graph = malloc(sizeof(struct GraphStruct));
    if (!graph) {
        perror("malloc graph failed");
        exit(EXIT_FAILURE);
    }
    graph->vertexNum = vertexNum;
    graph->edgeNum = edgeNum;

    graph->edges = malloc(sizeof(struct EdgeStruct) * edgeNum);
    if (!graph->edges) {
        perror("malloc edges failed");
        exit(EXIT_FAILURE);
    }

    return graph;
}

void graphDestroy(Graph graph) {
    free(graph->edges);
    free(graph);
}

void graphAddEdge(Edge edge, Graph graph) {
    static int edgeIndex;
    graph->edges[edgeIndex++] = edge;
}

void printGraph(Graph graph) {
    Edge* edge;
    for (int i = 0; i < graph->edgeNum; i++) {
        edge = &(graph->edges[i]);
        printf("%d - %d: %d\n", edge->src, edge->dest, edge->weight);
    }
}
