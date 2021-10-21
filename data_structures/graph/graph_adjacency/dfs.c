#include <stdio.h>
#include <stdlib.h>

#include "dfs.h"

static void dfsUtil(int v, bool* visited, Graph graph);

void dfs(int src, Graph graph) {
    bool* visited = malloc(sizeof(bool) * graph->vertexNum);
    if (!visited) {
        perror("malloc visited failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        visited[i] = false;
    }

    dfsUtil(src, visited, graph);
    // debug
    printf("\n");

    free(visited);
}

static void dfsUtil(int v, bool* visited, Graph graph) {
    visited[v] = true;
    // debug
    printf("%d\t", v);

    // ### 用 dfsUtil 的方式访问 v 的邻接结点
    for (AdjNode curNode = graph->adjLists[v]; curNode; curNode = curNode->next) {
        if (!visited[curNode->dest]) {
            dfsUtil(curNode->dest, visited, graph);
        }
    }
}
