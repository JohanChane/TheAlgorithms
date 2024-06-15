#include <stdio.h>

#include "bellman_ford.h"

static void testBellmanFord();

static void testBellmanFord() {
    Graph graph = graphCreate(4, 5);
    Edge e;

    e.src = 0;
    e.dest = 1;
    e.weight = 10;
    graphAddEdge(e, graph);

    e.src = 1;
    e.dest = 2;
    e.weight = 5;
    graphAddEdge(e, graph);

    e.src = 2;
    e.dest = 3;
    e.weight = 9;
    graphAddEdge(e, graph);

    e.src = 3;
    e.dest = 0;
    e.weight = 8;
    graphAddEdge(e, graph);

    e.src = 1;
    e.dest = 3;
    e.weight = -3;
    graphAddEdge(e, graph);

    printGraph(graph);

    printf("### BellmanFord\n");
    bellmanFord(0, graph);

    graphDestroy(graph);
}

int main() {
    testBellmanFord();
}
