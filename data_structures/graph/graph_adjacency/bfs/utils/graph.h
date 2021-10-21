#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct AdjNodeStruct* AdjList;

typedef struct EdgeStruct Edge;

typedef struct GraphStruct {
    int vertexNum;
    AdjList* adjLists;
} *Graph;

typedef struct AdjNodeStruct {
    int dest;
    int weight;
    struct AdjNodeStruct* next;
} *AdjNode;

typedef struct EdgeStruct {
    int src, dest;
    int weight;
} Edge;

Graph graphCreate(int vertexNum);
void graphDestroy(Graph graph);
void graphAddDirectedEdge(Edge edge, Graph graph);
void graphAddUndirectedEdge(Edge edge, Graph graph);
AdjList graphAdjacency(int v, Graph graph);

// debug
void printGraph(Graph graph);

#endif
