#include "floy_warshall.h"

static void testfloydWarshall();

static void testFloydWarshall() {
    /* Let us create the following weighted graph
                10
           (0)------->(3)
            |         /|\
          5 |          |
            |          | 1
           \|/         |
           (1)------->(2)
                3           */
    Graph digraph = graphCreate(4);

    Edge e;

    e.src = 0;
    e.dest = 1;
    e.weight = 5;
    graphAddDirectedEdge(e, digraph);

    e.src = 0;
    e.dest = 3;
    e.weight = 10;
    graphAddDirectedEdge(e, digraph);

    e.src = 1;
    e.dest = 2;
    e.weight = 3;
    graphAddDirectedEdge(e, digraph);

    e.src = 2;
    e.dest = 3;
    e.weight = 1;
    graphAddDirectedEdge(e, digraph);

    floydWarshall(0, digraph);

    graphDestroy(digraph);
}

int main() {
    testFloydWarshall();
    return 0;
}
