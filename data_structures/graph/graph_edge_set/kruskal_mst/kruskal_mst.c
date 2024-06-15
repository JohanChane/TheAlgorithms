#include <stdio.h>
#include <stdlib.h>

#include "kruskal_mst.h"

// 子树结点的数据
typedef struct SubsetStruct {
    // 记录子树的父结点
    int parent;
    // 用于估算树的子结点。越大则越多。联合子树时，使子结点多的子树的根结点作为合并后的根结点，这样多数结点的深度不增加，根据结点查看根结点会更加的快。
    int rank;
} *Subset;

static int findRoot(Subset subset, int v);
static void unionSets(Subset subset, int u, int v);
static int edgeCmp(const void* a, const void* b);

void kruskalMst(Graph graph) {
    // ## 按升序的方式排序边
    qsort(graph->edges, graph->edgeNum, sizeof(graph->edges[0]), edgeCmp);

    // ## 创建需要的数据并初始化。
    Subset subsets = malloc(sizeof(struct SubsetStruct) * graph->vertexNum);
    if (!subsets) {
        perror("malloc subset failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->vertexNum; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    const int maxCountOfMstEdge = graph->vertexNum - 1;
    // mstSet 记录最小生成树的边
    Edge* mstSet = malloc(sizeof(struct EdgeStruct) * maxCountOfMstEdge);
    int countOfMstEdge = 0;

    // ## 生成最小生成树
    // graph->edge 的索引
    int edgeIndex = 0;
    Edge* curEdge;
    int uroot, vroot;
    while (countOfMstEdge < maxCountOfMstEdge && edgeIndex < graph->edgeNum) {
        curEdge = &(graph->edges[edgeIndex++]);

        // 查找 u,v 各自的子树的根结点（相当于子树的 ID）
        uroot = findRoot(subsets, curEdge->src);
        vroot = findRoot(subsets, curEdge->dest);

        // 如果边的源点和终点属于不同的子树，则将联合两棵子树。并将该边加入 mstSet。
        if (uroot != vroot) {
            unionSets(subsets, uroot, vroot);
            mstSet[countOfMstEdge++] = *curEdge;
        }
        // Else discard the curEdge
    }

    // ## print mstSet
    int minimumCost = 0;
    for (int i = 0; i < countOfMstEdge; i++) {
        printf("%d - %d: %d\n", mstSet[i].src, mstSet[i].dest, mstSet[i].weight);
        minimumCost += mstSet[i].weight;
    }
    printf("Minimum Cost Spanning tree: %d\n",minimumCost);

    // ## 回收内存
    free(mstSet);
    free(subsets);
}

// 查找子树的根结点
static int findRoot(Subset subset, int v) {
    if (subset[v].parent != v) {
        // 顺便更新 subset[v].parent。下次寻找会更加快。
        subset[v].parent = findRoot(subset, subset[v].parent);
    }

    return subset[v].parent;
}

// 函数功能：联合 u，v 结点所在子树
static void unionSets(Subset subset, int u, int v) {
    int uroot = findRoot(subset, u);
    int vroot = findRoot(subset, v);

    if (subset[uroot].rank == subset[vroot].rank) {
        subset[vroot].parent = uroot;
        subset[uroot].rank++;
    } else if (subset[uroot].rank > subset[vroot].rank) {
        subset[vroot].parent = uroot;
        subset[uroot].rank++;
    } else {
        subset[uroot].parent = vroot;
        subset[vroot].rank++;
    }
}

static int edgeCmp(const void* a, const void* b) {
    int wa = ((Edge*) a)->weight;
    int wb = ((Edge*) b)->weight;
    return wa - wb;
}
