#ifndef GRAPH_H
#define GRAPH_H

#define INFINITY INT_MAX

typedef struct EdgeStruct Edge;

typedef struct GraphStruct {
    int** edges;
    int vertexNum;
} *Graph;

struct EdgeStruct {
    int src, dest, weight;
};

Graph graphCreate(int vertexNum);
void graphDestroy(Graph graph);
void graphAddDirectedEdge(Edge edge, Graph graph);
void graphAddUndirectedEdge(Edge edge, Graph graph);

// debug
void printGraph();

#endif
