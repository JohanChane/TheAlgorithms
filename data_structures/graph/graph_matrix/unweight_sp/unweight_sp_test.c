#include "unweight_sp.h"

static void testUnweightSP();

static void testUnweightSP() {
    Graph graph = graphCreate(4);

    // 不使用 weight
    Edge e;

    e.src = 0;
    e.dest = 1;
    graphAddDirectedEdge(e, graph);
    e.src = 1;
    e.dest = 0;
    graphAddDirectedEdge(e, graph);
    e.src = 1;
    e.dest = 2;
    graphAddDirectedEdge(e, graph);
    e.src = 2;
    e.dest = 1;
    graphAddDirectedEdge(e, graph);
    e.src = 3;
    e.dest = 1;
    graphAddDirectedEdge(e, graph);

    unweightSP(0, graph);
    unweightSP(1, graph);
    unweightSP(2, graph);
    unweightSP(3, graph);
}

int main() {
    testUnweightSP();
    return 0;
}

