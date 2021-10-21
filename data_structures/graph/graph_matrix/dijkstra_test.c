#include <stdio.h>

#include "dijkstra.h"

static void testdijkstra();

static void testDijkstra() {
    Graph digraph = graphCreate(4);
    Edge edge;

    edge.src = 0;
    edge.dest = 1;
    edge.weight = 11;
    graphAddDirectedEdge(edge, digraph);

    edge.src = 0;
    edge.dest = 2;
    edge.weight = 10;
    graphAddDirectedEdge(edge, digraph);

    edge.src = 1;
    edge.dest = 3;
    edge.weight = 5;
    graphAddDirectedEdge(edge, digraph);

    edge.src = 2;
    edge.dest = 3;
    edge.weight = 12;
    graphAddDirectedEdge(edge, digraph);

    edge.src = 1;
    edge.dest = 2;
    edge.weight = 8;
    graphAddDirectedEdge(edge, digraph);

    printGraph(digraph);

    printf("### dijkstra\n");
    dijkstra(0, digraph);

    graphDestroy(digraph);
}

int main() {
    testDijkstra();
    return 0;
}
