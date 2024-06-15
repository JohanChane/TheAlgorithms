#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include "stack.h"
#include "graph.h"

bool isCyclic(Graph graph);
bool isCyclicForUnDirected(Graph graph);
int topologicalSort(int* topoSort, Graph graph);

#endif
