#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "prim_mst.h"

static int minKey(int* key, bool* mstSet, int vertexNum);
static void printMst(int* parent, Graph graph);

// Prim’s Minimum Spanning Tree（prim 最小生成树）
void primMst(Graph graph) {
    // ## 创建需要的数据并初始化。
    // 记录顶点是否在最小生成树内
    bool* mstSet = malloc(sizeof(bool) * graph->vertexNum);
    if (!mstSet) {
        perror("malloc mstSet failed");
        exit(EXIT_FAILURE);
    }
    // key[i] 表示最小生成树的顶点到非最小生成树的顶点 i 的所有直接相连的边的最小权值。
    int* key = malloc(sizeof(int) * graph->vertexNum);
    if (!key) {
        perror("malloc key failed");
        exit(EXIT_FAILURE);
    }
    // 用于回溯。parent[i] 表示 i 顶点的父结点。第一个顶点的父顶点为 `-1`, 表示 root of mst。
    int* parent = malloc(sizeof(int) * graph->vertexNum);
    if (!parent) {
        perror("malloc parent failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        mstSet[i] = false;
        key[i] = INFINITY;
    }

    // 从顶点 0 开始
    key[0] = 0;
    parent[0] = -1;

    // ## 开始生成最小生成树
    int u;
    for (int i = 0; i < graph->vertexNum; i++) {
        u = minKey(key, mstSet, graph->vertexNum);

        mstSet[u] = true;

        // ### 更新 u 顶点到非最小生成树顶点的 key 和 非最小生成树的顶点的 parent
        for (int v = 0; v < graph->vertexNum; v++) {
            if (graph->edges[u][v] != INFINITY && !mstSet[v] && graph->edges[u][v] < key[v]) {
                key[v] = graph->edges[u][v];
                parent[v] = u;
            }
        }
    }

    // ## 打印最小生成树
    printMst(parent, graph);

    free(mstSet);
    free(key);
    free(parent);
}

static int minKey(int* key, bool* mstSet, int vertexNum) {
    int min = INFINITY, minIndex;
    for (int i = 0; i < vertexNum; i++) {
        if (!mstSet[i] && key[i] < min) {
            min = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

static void printMst(int* parent, Graph graph) {
    int u;
    for (int v = 1; v < graph->vertexNum; v++) {
        u = parent[v];
        printf("%d -> %d: %d\n", u, v, graph->edges[u][v]);
    }
}

