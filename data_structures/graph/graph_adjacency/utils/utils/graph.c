#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "graph.h"

static AdjNode adjNodeCreate(int dest, int weight);
static void adjNodeDestroy(AdjNode adjListNode);

// ### debug
static void printAdjList(AdjList adjList, int src);

Graph graphCreate(int vertexNum) {
    Graph graph = malloc(sizeof(struct GraphStruct));
    if (!graph) {
        perror("malloc graph failed");
        exit(EXIT_FAILURE);
    }
    graph->vertexNum = vertexNum;

    // ### 为 adjlists 分配内存, 并初始化 adjLists。
    graph->adjLists = malloc(sizeof(AdjList) * vertexNum);
    if (!graph->adjLists) {
        perror("malloc adjLists failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < vertexNum; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void graphDestroy(Graph graph) {
    // ### 回收 adjLists 的内存
    AdjNode curNode, tmpNode;
    for (int i = 0; i < graph->vertexNum; i++) {
        curNode = graph->adjLists[i];
        while (curNode) {
            tmpNode = curNode;
            curNode = curNode->next;
            adjNodeDestroy(tmpNode);
        }
    }
    free(graph->adjLists);

    free(graph);
}

void graphAddDirectedEdge(Edge edge, Graph graph) {
    AdjNode newNode = adjNodeCreate(edge.dest, edge.weight);
    // ### 将 newNode 插入到表头
    newNode->next = graph->adjLists[edge.src];
    graph->adjLists[edge.src] = newNode;
}

void graphAddUndirectedEdge(Edge edge, Graph graph) {
    // ### 添加 `src -> dest`
    AdjNode newNode = adjNodeCreate(edge.dest, edge.weight);
    // 将 `src -> dest` 插入到表头
    newNode->next = graph->adjLists[edge.src];
    graph->adjLists[edge.src] = newNode;

    // ### 添加 `dest -> src`
    AdjNode newNode2 = adjNodeCreate(edge.src, edge.weight);
    newNode2->next = graph->adjLists[edge.dest];
    graph->adjLists[edge.dest] = newNode2;
}

AdjList graphAdjacency(int v, Graph graph) {
    return graph->adjLists[v];
}

static AdjNode adjNodeCreate(int dest, int weight) {
    AdjNode adjListNode = malloc(sizeof(struct AdjNodeStruct));
    if (!adjListNode) {
        perror("malloc adjListNode failed");
        exit(EXIT_FAILURE);
    }
    adjListNode->dest = dest;
    adjListNode->weight = weight;

    return adjListNode;
}

static void adjNodeDestroy(AdjNode adjListNode) {
    free(adjListNode);
}

void printGraph(Graph graph) {
    for (int i = 0; i < graph->vertexNum; i++) {
        printAdjList(graph->adjLists[i], i);
    }
}

static void printAdjList(AdjList adjList, int src) {
    for (AdjNode curNode = adjList; curNode; curNode = curNode->next) {
        printf("%d -> %d: %d\n", src, curNode->dest, curNode->weight);
    }
}
