#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"

Graph graphCreate(int vertexNum) {
    Graph graph = malloc(sizeof(struct GraphStruct));
    if (!graph) {
        perror("malloc graph failed");
        exit(EXIT_FAILURE);
    }
    graph->vertexNum = vertexNum;

    // ### 为 edge 分配内存
    graph->edges = malloc(sizeof(int*) * graph->vertexNum);
    if (!graph->edges) {
        perror("malloc edges failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        graph->edges[i] = malloc(sizeof(int) * graph->vertexNum);
        if (!graph->edges[i]) {
            perror("malloc edge[i] failed");
            exit(EXIT_FAILURE);
        }
    }

    // ### 初始化 edges。到自身也是 INFINITY。
    for (int i = 0; i < graph->vertexNum; i++) {
        for (int j = 0; j < graph->vertexNum; j++) {
            graph->edges[i][j] = INFINITY;
        }
    }

    return graph;
}

void graphDestroy(Graph graph) {
    // ### 回收边的内存
    for (int i = 0; i < graph->vertexNum; i++) {
        free(graph->edges[i]);
    }
    free(graph->edges);

    free(graph);
}

void graphAddDirectedEdge(Edge edge, Graph graph) {
    graph->edges[edge.src][edge.dest] = edge.weight;
}

void graphAddUndirectedEdge(Edge edge, Graph graph) {
    graph->edges[edge.src][edge.dest] = edge.weight;
    graph->edges[edge.dest][edge.src] = edge.weight;
}

void printGraph(Graph graph) {
    for (int i = 0; i < graph->vertexNum; i++) {
        for (int j = 0; j < graph->vertexNum; j++) {
            if (graph->edges[i][j] != INFINITY) {
                printf("%d -> %d: %d\n", i, j, graph->edges[i][j]);
            }
        }
    }
}
