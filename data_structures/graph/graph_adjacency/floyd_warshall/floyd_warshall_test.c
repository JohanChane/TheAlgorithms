#include <stdio.h>

#include "floyd_warshall.h"

static void testFloydWarshall();

static void testFloydWarshall() {
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

    edge.src = 3;
    edge.dest = 2;
    edge.weight = 12;
    graphAddDirectedEdge(edge, digraph);

    edge.src = 2;
    edge.dest = 1;
    edge.weight = -17;
    // edge.weight = -18;
    graphAddDirectedEdge(edge, digraph);

    printGraph(digraph);

    printf("### floydWarshall\n");
    floydWarshall(digraph);

    graphDestroy(digraph);
}

int main() {
    testFloydWarshall();
}
