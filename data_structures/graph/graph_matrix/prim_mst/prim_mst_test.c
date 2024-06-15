#include <stdio.h>

#include "prim_mst.h"

static void testPrimMst();

static void testPrimMst() {
	/* Let us create the following graph
		2    3
	(0)--(1)--(2)
	|    / \    |
	6  8/   \5  |7
	|  /     \  |
	(3)-------(4)
          9
    */
    Graph graph = graphCreate(5);
    Edge e;

    e.src = 0;
    e.dest = 1;
    e.weight = 2;
    graphAddUndirectedEdge(e, graph);

    e.src = 1;
    e.dest = 2;
    e.weight = 3;
    graphAddUndirectedEdge(e, graph);

    e.src = 0;
    e.dest = 3;
    e.weight = 6;
    graphAddUndirectedEdge(e, graph);

    e.src = 2;
    e.dest = 4;
    e.weight = 7;
    graphAddUndirectedEdge(e, graph);

    e.src = 3;
    e.dest = 4;
    e.weight = 9;
    graphAddUndirectedEdge(e, graph);

    e.src = 1;
    e.dest = 3;
    e.weight = 8;
    graphAddUndirectedEdge(e, graph);

    e.src = 1;
    e.dest = 4;
    e.weight = 5;
    graphAddUndirectedEdge(e, graph);

    printGraph(graph);

    printf("### primMst\n");
	primMst(graph);

    graphDestroy(graph);
}

int main() {
    testPrimMst();
}
