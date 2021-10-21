#include <stdio.h>

#include "kruskal_mst.h"

static void testKruskalMst();

static void testKruskalMst() {
    /* Let us create following weighted graph
            10
        0-------1
        | \     |
       6|  5\   |15
        |     \ |
        2-------3
            4
    */
    int V = 4; // Number of vertices in graph
    int E = 5; // Number of edges in graph
    Graph graph = graphCreate(V, E);

    // add edge 0-1
    graph->edges[0].src = 0;
    graph->edges[0].dest = 1;
    graph->edges[0].weight = 10;

    // add edge 0-2
    graph->edges[1].src = 0;
    graph->edges[1].dest = 2;
    graph->edges[1].weight = 6;

    // add edge 0-3
    graph->edges[2].src = 0;
    graph->edges[2].dest = 3;
    graph->edges[2].weight = 5;

    // add edge 1-3
    graph->edges[3].src = 1;
    graph->edges[3].dest = 3;
    graph->edges[3].weight = 15;

    // add edge 2-3
    graph->edges[4].src = 2;
    graph->edges[4].dest = 3;
    graph->edges[4].weight = 4;

    printGraph(graph);

    printf("### kruskalMst\n");
    kruskalMst(graph);

    graphDestroy(graph);
}

int main() {
    testKruskalMst();
}
