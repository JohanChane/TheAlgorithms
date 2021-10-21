#ifndef GRAPH_H
#define GRAPH_H

typedef struct EdgeStruct Edge;

typedef struct GraphStruct {
    int vertexNum;
    int edgeNum;
    Edge* edges;
} *Graph;

struct EdgeStruct {
    int src, dest, weight;
};

Graph graphCreate(int vertexNum, int edgeNum);
void graphDestroy(Graph graph);
void graphAddEdge(Edge edge, Graph graph);

// debug
void printGraph(Graph graph);

#endif
