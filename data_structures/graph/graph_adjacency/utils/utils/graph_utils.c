#include <stdio.h>
#include <stdlib.h>

#include "graph_utils.h"

static bool isCyclicUtil(int v, bool* visited, bool *recStack, Graph graph);
static bool isCyclicUtilForUndirected(int v, int parent, bool* visited, Graph graph);
static void topologicalSortUtil(int v, bool* visited, Stack stack, Graph graph);

// 检测有向图是否有环
bool isCyclic(Graph graph) {
    bool* visited = malloc(sizeof(bool) * graph->vertexNum);
    if (!visited) {
        perror("malloc visited failed");
        exit(EXIT_FAILURE);
    }

    bool* recStack = malloc(sizeof(bool) * graph->vertexNum);
    if (!recStack) {
        perror("malloc recStack failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(i, visited, recStack, graph)) {
                return true;
            }
        }
    }

    free(visited);
    free(recStack);

    return false;
}

static bool isCyclicUtil(int v, bool* visited, bool *recStack, Graph graph) {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        for (AdjNode curNode = graph->adjLists[v]; curNode; curNode = curNode->next) {
            if (!visited[curNode->dest]) {
                if (isCyclicUtil(curNode->dest, visited, recStack, graph)) {
                    return true;
                }
            } else if (recStack[curNode->dest]) {
                return true;
            }
        }
    }
    recStack[v] = false;
    return false;
}

// 检测无向图是否有环。
// 无向图检测环的方法。不能用于有向图，因为有向图两个顶点可以成环，所以检测 parent 不起作用。
bool isCyclicForUnDirected(Graph graph) {
    bool* visited = malloc(sizeof(bool) * graph->vertexNum);
    if (!visited) {
        perror("malloc visited failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        if (!visited[i]) {
            if (isCyclicUtilForUndirected(i, -1, visited, graph)) {
                return true;
            }
        }
    }

    free(visited);
    return false;
}

static bool isCyclicUtilForUndirected(int v, int parent, bool* visited, Graph graph) {
    visited[v] = true;

    for (AdjNode curNode = graph->adjLists[v]; curNode; curNode = curNode->next) {
        if (!visited[curNode->dest]) {
            if (isCyclicUtilForUndirected(curNode->dest, v, visited, graph)) {
                return true;
            }
        } else if (curNode->dest != parent) {
            return true;
        }
    }
    return false;
}

// 拓扑排序
int topologicalSort(int* topoSort, Graph graph) {
    if (isCyclic(graph)) {
        return -1;
    }

    bool* visited = malloc(sizeof(bool) * graph->vertexNum);
    if (!visited) {
        perror("malloc visited failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < graph->vertexNum; i++) {
        visited[i] = false;
    }

    Stack stack = stackCreate();

    for (int i = 0; i < graph->vertexNum; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack, graph);
        }
    }

    int idx = 0;
    while (!stackIsEmpty(stack)) {
        topoSort[idx++] = stackTop(stack);
        stackPop(stack);
    }

    stackDestroy(stack);
    free(visited);

    return 0;
}

static void topologicalSortUtil(int v, bool* visited, Stack stack, Graph graph) {
    visited[v] = true;

    for (AdjNode curNode = graph->adjLists[v]; curNode; curNode = curNode->next) {
        if (!visited[curNode->dest]) {
            topologicalSortUtil(curNode->dest, visited, stack, graph);
        }
    }

    stackPush(v, stack);
}
