Data Structrues
===

Content
---

<!-- vim-markdown-toc GFM -->

* [References](#references)
* [时间复杂度](#时间复杂度)
    * [References](#references-1)
    * [分治算法的时间复杂度](#分治算法的时间复杂度)
    * [Others](#others)
* [排序算法](#排序算法)
    * [Insertion Sort](#insertion-sort)
    * [Selection Sort](#selection-sort)
    * [Bubble Sort](#bubble-sort)
    * [Merge Sort（归并排序）](#merge-sort归并排序)
    * [Quick Sort（快速排序）](#quick-sort快速排序)
    * [Shell Sort（希尔排序）](#shell-sort希尔排序)
    * [Heap Sort（堆排序）](#heap-sort堆排序)
    * [External Sort（外部排序）](#external-sort外部排序)
        * [用胜者树合并的外部排序](#用胜者树合并的外部排序)
        * [用败者树合并的外部排序](#用败者树合并的外部排序)
    * [Counting Sort（计数排序）](#counting-sort计数排序)
    * [Bucket Sort（桶排序）](#bucket-sort桶排序)
    * [Radix Sort（基数排序）](#radix-sort基数排序)
* [List](#list)
    * [Linked List](#linked-list)
        * [Single Linked List](#single-linked-list)
        * [Double Linked List](#double-linked-list)
        * [Circular Linked List](#circular-linked-list)
* [Tree](#tree)
    * [BinSearchTree（二叉查找树）](#binsearchtree二叉查找树)
    * [AVL Tree（自平衡二叉查找树）](#avl-tree自平衡二叉查找树)
    * [Splay Tree（伸展树）](#splay-tree伸展树)
    * [BTree（多路搜索树）](#btree多路搜索树)
        * [References](#references-2)
        * [Btree 性质](#btree-性质)
            * [Knuth's Definition](#knuths-definition)
            * [CLRS（算法导论）](#clrs算法导论)
        * [操作](#操作)
            * [三个基本的操作](#三个基本的操作)
            * [插入的递归操作](#插入的递归操作)
            * [删除的递归操作：](#删除的递归操作)
                * [填充操作：](#填充操作)
        * [说明](#说明)
    * [Huffman Tree（哈夫曼树）](#huffman-tree哈夫曼树)
        * [refer:](#refer)
        * [说明](#说明-1)
    * [Red-black tree](#red-black-tree)
        * [References](#references-3)
        * [红黑树的定义](#红黑树的定义)
        * [二叉搜索树与红黑树的插入与删除](#二叉搜索树与红黑树的插入与删除)
        * [定义](#定义)
        * [红黑树的插入](#红黑树的插入)
        * [红黑树的删除](#红黑树的删除)
        * [红黑树的常用的旋转操作](#红黑树的常用的旋转操作)
* [Heap](#heap)
    * [Binary Heap（二叉堆）](#binary-heap二叉堆)
    * [Leftist Heap（左式堆）](#leftist-heap左式堆)
        * [说明](#说明-2)
    * [Skew Heap（斜堆）](#skew-heap斜堆)
    * [Binomial Queue（二项队列）](#binomial-queue二项队列)
        * [说明](#说明-3)
* [Hash Table](#hash-table)
    * [SeparateChaining](#separatechaining)
    * [OpenAddressing](#openaddressing)
* [Stack, Queue](#stack-queue)
    * [Stack](#stack)
        * [用数组实现](#用数组实现)
        * [用链表实现](#用链表实现)
    * [Queue](#queue)
        * [用数组实现](#用数组实现-1)
        * [用链表实现](#用链表实现-1)
* [图](#图)
    * [概念](#概念)
    * [图的存储方式](#图的存储方式)
        * [邻接表](#邻接表)
        * [邻接表](#邻接表-1)
        * [边集](#边集)
        * [链式前向星](#链式前向星)
    * [边和点的松弛](#边和点的松弛)
        * [边的松弛](#边的松弛)
        * [点的松弛](#点的松弛)
    * [图的算法](#图的算法)
        * [广度优先搜索](#广度优先搜索)
        * [深度优先搜索](#深度优先搜索)
        * [拓扑排序](#拓扑排序)
        * [检测图是否有环或有负值环](#检测图是否有环或有负值环)
            * [无向图的检测环的方法](#无向图的检测环的方法)
            * [有向图的检测环的方法](#有向图的检测环的方法)
            * [有/无向图检测负环](#有无向图检测负环)
        * [最短路径算法](#最短路径算法)
            * [Dijkstra](#dijkstra)
            * [Bellman-Ford](#bellman-ford)
            * [Floyd-Warshall](#floyd-warshall)
            * [无环有向图的最短路径和最长路径](#无环有向图的最短路径和最长路径)
            * [无权有/无向图的单源的最短路径](#无权有无向图的单源的最短路径)
        * [最小生成树](#最小生成树)
            * [Prim 算法](#prim-算法)
            * [Kruskal 算法](#kruskal-算法)

<!-- vim-markdown-toc -->

References
---

-   《数据结构与算法分析：C 语言描述》

时间复杂度
---

### References

-   <https://www.bigocheatsheet.com/>
-   <https://mp.weixin.qq.com/s/VQN5pQAAwi3Zwn-vcsu-3w>

### 分治算法的时间复杂度

方程 $ T(N) = aT(N / b) + \Theta(N^{k}) $ 的解为

$$
T(N) =
\begin{cases}
O(N^{\log_{b} a}), & a > b^{k} \\
O(N^{k}\log N), & a = b^{k} \\
O(N^{k}), & a < b^{k} \\
\end{cases}
$$

其中 $ a \geq 1, b > 1 $。

常见的情况

快速排序、归并排序、堆排序的平均时间复杂度是，$ O(N^{1}\log N) = O(N\log N), a = 2, b = 2, k = 1 $。

二叉搜索树、AVL 树、红黑树、伸展树、B 树的搜索、插入、删除的平均时间复杂度是, $ O(N^{0}\log N) = O(\log N), a = 1, b = 2, k = 0 $。

### Others

希尔排序的计算比较复杂。至于最坏情形的时间复杂度，[有的资料](https://www.bigocheatsheet.com/)说是 $ (N\log (N))^{2} $，而《数据结构与算法分析：C 语言描述》说是 $ N^{2} $。

堆排序的平均时间复杂度是，$ \log_{2} N + \log_{2} (N - 1), + \cdots + log_{2} 1 = \Theta(\log_{2} (N!)) = O(N\log N) $。

二叉堆的建堆的时间复杂度是，$ O(N) $。

排序算法
---

[source code](../data_structures/sorting)

### Insertion Sort

### Selection Sort

### Bubble Sort

### Merge Sort（归并排序）

### Quick Sort（快速排序）

### Shell Sort（希尔排序）

### Heap Sort（堆排序）

### External Sort（外部排序）

[ref](https://www.cnblogs.com/qianye/archive/2012/11/25/2787923.html)

#### 用胜者树合并的外部排序

胜者树

> 规律：树或子树的根结点是整棵树的最小的数。
>
> 左子树与右子树的胜者（小者胜）比较，胜者放入父结点。

#### 用败者树合并的外部排序

败者树

> 规律：树或子树的根结点是整棵树的第二小的数。
>
> 左子树与右子树的胜者（小者胜）比较，败者放入父结点。

### Counting Sort（计数排序）

[ref](https://www.cnblogs.com/xiaochuan94/p/11198610.html)

### Bucket Sort（桶排序）

将一定范围的数放入桶内，然后将桶内的数排序，再将数从桶内拿出。

### Radix Sort（基数排序）

List
---

[source code](../data_structures/linked_list)

### Linked List

#### Single Linked List

#### Double Linked List

#### Circular Linked List

Tree
---

[source code](../data_structures/tree)

### BinSearchTree（二叉查找树）

### AVL Tree（自平衡二叉查找树）

### Splay Tree（伸展树）

### BTree（多路搜索树）

`B` 是 balance 的简称。

#### References

-   <https://www.geeksforgeeks.org/introduction-of-b-tree-2/>
-   <https://www.geeksforgeeks.org/insert-operation-in-b-tree/>
-   <https://www.geeksforgeeks.org/delete-operation-in-b-tree/>

#### Btree 性质

[两种流行的定义](https://stackoverflow.com/a/45826413)
[多种定义](https://www.zhihu.com/question/19836260)
[wiki](https://en.wikipedia.org/wiki/B-tree#Definition)

> 一个用阶来描述 `min <= children <= max` 而另一个用最小度数。<br>
> 它们的区别是，`CLRS Degree (Degree)` 对应的阶只能是偶数。

*internal node（内部结点）：非叶子结点。*

##### Knuth's Definition

设 Btree 的阶（Order）为 M。

叶子结点：指向叶子结点的指针为 NULL。

1. 树中每一个结点至多有 M 棵子树；
2. 若根结点不是叶子结点，则至少有两棵子树；
3. 除根结点之外的所有非终端结点（内部结点）至少有 `ceil(M/2)` 棵子树；
4. 左儿子的 key < key < 右儿子的 key。
5. 所有的叶子结点都出现在同一层次上，并且不带信息。

##### CLRS（算法导论）

*对 Knuth 的改进。*

设 BTree 的最小度数（minimum Degree）为 t (t >= 2)。

叶子结点：指向儿子的指针都为 NULL 的结点。

1. 每个结点（除了 root）有 [t - 1, 2t - 1] 个 keys；
2. 每个内部结点（除了根结点）有 [t, 2t] 个儿子。
3. 当 BTree 不为空时，根结点至少有 1 个 key。至多有 2t 儿子。
4. 左儿子的 key <= key <= 右儿子的 key。
5. 所有的叶子结点都有同样的深度，与树的高度相同。

#### 操作

如何保持叶子结点在同一深度:<br>
> 插入满时，分裂。 删除时，key < t 时，合并。所以不会造成左右儿子深度不一。

##### 三个基本的操作

-   分裂

    如果本结点不满而有一个儿子满时，可分裂儿子。将儿子的 keys[t - 1] 拿出，则儿子刚好平分。将儿子的 keys[t - 1] 插入到本结点，再将儿子的右半部分作为 keys[t - 1] 的右儿子即可。

-   合并

    如果本结点 keyCount >= t 且 keys[idx] 的左右儿子的 keyCount = t - 1 时，可将 keys[idx] 及其左右儿子合并为一个满的结点，再将作为 keys[idx] 的左儿子, 删除 keys[idx] 及其右儿子即可。

-   向兄弟借一个 key 和 child

    如果兄弟的 keyCount >= t 可向兄弟借一个 key 和 child。

    分为两个情况：

    -   向左兄弟借

        设 curChild = childs[idx], 则 prevChild = childs[idx - 1]。所以有 prevChild <= keys[idx - 1] <= curChild。<br>
        curChild 右移空出 childs[0], keys[0]。 keys[idx - 1] 和 prevChild 最右的儿子补入。再将 prevChild 最右的 key 插入到 keys[idx - 1]。

    -   向右兄弟借

        与`向左兄弟借`同理。

##### 插入的递归操作

前提本结点不满。<br>
如果本结点是叶子结点，则插入。如果不是叶子则向儿子插入。如果儿子是满的则分裂儿子再插入。所以最终结果是优先向儿子插入（最终插入到叶子）。

*如果本结点为 root 时，先分裂 root 再插入。*

##### 删除的递归操作：

前提是，如果本结点不是根结点则 `keyCount >= t`，如果是根结点则 `keyCount >= 1`。

如果要删除的 key 在本结点：<br>
> 如果本结点是叶子结点则直接删除。<br>
> 如果不是叶子结点，且左右儿子的 `keyCount >= t`，则将左儿子的最大 key 或右儿子的最小 key 复制到本结点，再删除左或右儿子复制的 key。这过程类似二叉查找树的删除。

*如果本结点是 root, 则 keyCount 为 0 时，将第一个儿子作为 root。*

如果要删除的 key 不在本结点：<br>
> 找到 key 可能所在的 child。如果儿子结点的 `keyCount == t - 1` 则填充儿子，再删除儿子。

###### 填充操作：

前提是，本结点 `keyCount == t - 1`。

如果兄弟 `keyCount >=t`，则向其借一个 key。<br>
如果兄弟 `keyCount == t - 1`，则与兄弟合并。

#### 说明

以下的例子是 CLRS（算法导论）的 BTree

1. 叶子结点的 childs 不初始化为 NULL。
2. 左儿子的 key <= key <= 右儿子的 key。

[source code](../data_structures/tree/btree.h)

### Huffman Tree（哈夫曼树）

#### refer:

-   <https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/>

#### 说明

构造 huffman 树的步骤：

> 建立一个堆，其结点是一个一棵树。初始时，用每个数建立一棵树，所以每棵树只有一个结点，然后将每个棵的插入堆中。<br>
> 在堆中弹出两个最小频率的根结点的树，合并两棵树，并产生一个新的根结点，然后将合并后的树的根结点插入堆中。直到堆中只有一个堆结点。剩下的堆结点就是 huffman tree。

### Red-black tree

#### References

-   [彻底理解红黑树](https://www.jianshu.com/p/a9c064d38a92)
-   <https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/?ref=rp>
-   <https://en.wikipedia.org/wiki/Red%E2%80%93black_tree>

#### 红黑树的定义

[ref](https://zh.wikipedia.org/zh-hans/%E7%BA%A2%E9%BB%91%E6%A0%91)

红黑树是每个结点都带有颜色属性的二叉搜索树，颜色为红色或黑色。在二叉搜索树强制一般要求以外，对于任何有效的红黑树我们增加了如下的额外要求：

1.  结点是红色或黑色。
2.  根是黑色。
3.  所有叶子都是黑色（叶子是NIL结点）。
4.  每个红色结点必须有两个黑色的子结点。（从每个叶子到根的所有路径上不能有两个连续的红色结点。）
5.  从任一结点到其每个叶子的所有简单路径都包含相同数目的黑色结点。

总结:

> 如果父结点是红色则其两个儿子一定是黑色。因此，不能有连续的两个红色结点。<br>
> 如果父结点是黑色则其儿子的颜色可能任意色。比如：红红，黑黑，红黑。

#### 二叉搜索树与红黑树的插入与删除

红黑树的插入与删除与二叉搜索树一样，不过是多了平衡调整。

#### 定义

*为了方便描述，有了这些定义*

1.  Nil（NULL）结点为黑色结点
2.  当前平衡点 N, N 的兄弟 S, SL, SR 为 S 的左右树。P 为 N 的父结点，GP 为祖父结点。
3.  h(A -> B -> Nil): 为路径 A -> B -> Nil 的黑色结点数量。
4.  h(树)：表示 h(root -> Nil)。
5.  D 为删除的结点。

#### 红黑树的插入

新插入的结点都是红色的

> 因为红色结点不会破坏树（包含所有子树）的平衡（从任一结点到其每个叶子的所有简单路径都包含相同数目的黑色结点），而插入黑色结点会破坏树（包含所有子树）的平衡。遇到“红红结点”的情况时，只是局部（一部分子树）调整即可。
>
> 插入结点与其父结点为红色时，才要调整红黑树。

[情形3. 父红-叔红](https://www.jianshu.com/p/96e652ccf720)根结点是否会变为红色？

> 递归时，当 N 为根结点时会调用“情形1. N为根结点（父结点为NULL）”的调整方法。所以会将根结点涂黑。

#### 红黑树的删除

和平衡二叉搜索树一样，删除的结点一定子树中，最大或最小的一个结点是一个叶子结点。所以该结点最多只有一个儿子。<br>
只有一个子结点时，删除结点只能是黑色，其子结点为红色，否则无法满足红黑树的性质了。反之，删除的结点是红色时，则该结点一定是一个叶子结点。

1.  如果删除的结点是红色的，则直接删除即可，因为补上的结点（Nil）黑色的。
2.  如果删除的结点是黑色时，才需要平衡调整。

    1.  当删除的结点有一个儿子时，则儿子一定是红色的，所以将补上的红色儿子涂黑即可达到平衡。
    2.  当删除的结点是一个叶子结点时，补上的结点是一个 Nil 结点。这时树就不平衡了，所以补上的结点成为当前平衡点（N）。平衡的方向是，方法一：因为删除之后，会有 `h(N) -= 1, h(P) -= 1, h(GP) -= 1, h(GGP) -= 1, ...`，将它们其一个加 1 即可。方法二：使 `h(S) -= 1`，且 D 的 P 为黑色，然后 P 成为新的平衡点 N，此时 N 相当上删除之后补上的点，符合递归的条件。（因为递归的原因，在调整阶段，当 N 结点为黑色时，N 结点的儿子是任意的。）

#### 红黑树的常用的旋转操作

*旋转能使树保持二叉搜索树的特性。*

Root' 表示旋转后的树的根结点。

1.  当 X(B), XL(B), XR(R)。X 左旋，X 与 XR 互换颜色。XL, XR 的子树的父结点不会由从黑变红。且 h(X' 的左子树) == h(X' 的右子树), h(XR' 左子树) = h(XR' 的右子树), h(Root') 不变。Root' 颜色不变。
2.  当 N(B), P, S(B), SL(R), N 是 P 的右儿子。P 右旋，P 和 S 交换颜色，SL 变黑。N, S, SL 的子树的父结点颜色不会从黑变红。h(P' 的左子树) == h(P' 的右子树)，h(S' 的左子树) = h(S' 的右子树)，h(Root') 不变。Root' 的颜色不变。

[source code](../data_structures/tree/red_black_tree/red_black_tree.h)

Heap
---

[source code](../data_structures/heap)

### Binary Heap（二叉堆）

### Leftist Heap（左式堆）

#### 说明

左式堆：对于堆中的每一个结点，其左儿子的零路径长至少与右儿子的零路径长一样大。具有堆的性质。

零路径长：具有 2 个儿子，Npl(2) = 1; 0 个或 1 个儿子的结点的 Npl(0 | 1) = 0; Npl(NULL) = -1 。 leftistHeap->Npl = leftistHeap->Right->Npl + 1 。

两个左式堆合并的操作：堆顶最小的堆的右子树与另一个堆合并。

插入：即两个堆合并

删除Min：即一个堆的左右子树合并

### Skew Heap（斜堆）

对左式堆的改进，没有零和路径长的信息，合并之后每个有右儿子的结点的交换是无条件的。如果没有右儿子则不交换，因为交换没有意义。

### Binomial Queue（二项队列）

#### 说明

二项队列由多个二项树组成

二项树的上一层小于等于下一层。即父结点小于等于其所有后裔。二项树的结点数：B0 = 1， B1 = 2, B3 = 4, ... , Bn = 2 * Bn-1 。

插入和删除都用合并实现

Hash Table
---

[source code](../data_structures/hash_table)

### SeparateChaining

解决冲突的方法是分离链接法，是将散列到同一值的所有元素保留到一个链表中。

### OpenAddressing

解决冲突的方法是开放定址法。有一个冲突解决方程，自变量是冲突次数，`(散列值 + 因变量) mod TableSize` 是将要插入的位置。

Stack, Queue
---

[source code](../data_structures/stack_queue)

### Stack

#### 用数组实现

#### 用链表实现

### Queue

#### 用数组实现

#### 用链表实现

图
---

[source code](../data_structures/graph)

### 概念

    graph, digraph: 无向图，有向图
    arc, edge: 弧（有向图的“边”）, 边（无向图的边）。
    vertex: 点
    adj: adjacent. 邻接。
    matrix: 矩阵
    weight, unweight: 有权的, 无权的
    directed, undirected: ...

    the single-source shortest paths: 单源最短路径
    the all-pairs shortest paths: 多源最短路径
    Acyclic Graph: 无环图
    Minimum Spanning Tree（mst）: 最小生成树

### 图的存储方式

ref: [图的顺序存储结构及C语言实现](http://data.biancheng.net/view/37.html)

> ArcNode: 弧结点
> VNode: Vertex Node. 顶点结点。

ref: [邻接表、邻接多重表、十字链表及C语言实现](http://data.biancheng.net/view/38.html)

> 在实际应用中，图最常用的是链式存储结构。

#### 邻接表

```c
typedef struct EdgeStruct Edge;

typedef struct GraphStruct {
    int** edges;
    int vertexNum;
} *Graph;

struct EdgeStruct {
    int src, dest, weight;
};

void graphAddDirectedEdge(Edge edge, Graph graph) {
    graph->edges[edge.src][edge.dest] = edge.weight;
}

void graphAddUndirectedEdge(Edge edge, Graph graph) {
    graph->edges[edge.src][edge.dest] = edge.weight;
    graph->edges[edge.dest][edge.src] = edge.weight;
}
```

#### 邻接表

```c
typedef struct AdjNodeStruct* AdjList;

typedef struct EdgeStruct Edge;

typedef struct GraphStruct {
    int vertexNum;
    AdjList* adjLists;
} *Graph;

typedef struct AdjNodeStruct {
    int dest;
    int weight;
    struct AdjNodeStruct* next;
} *AdjNode;

typedef struct EdgeStruct {
    int src, dest;
    int weight;
} Edge;

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
```

#### 边集

有些无向图的算法只需求用到边集，而不需要用到点集，所以只存储边集即可。比如：bellman ford, Kruskal。

```c
typedef struct EdgeStruct Edge;

typedef struct GraphStruct {
    int vertexNum;
    int edgeNum;
    Edge* edges;
} *Graph;

struct EdgeStruct {
    int src, dest, weight;
};

void graphAddEdge(Edge edge, Graph graph) {
    static int edgeIndex;
    graph->edges[edgeIndex++] = edge;
}
```

#### 链式前向星

为了防止使用指针，用数组建立链表，类似于拉链法。实质上是邻接表。

[链式前向星的发明者是谁？](https://www.zhihu.com/question/306076815)

[链式前向星](https://baike.baidu.com/item/%E9%93%BE%E5%BC%8F%E5%89%8D%E5%90%91%E6%98%9F/5970605)

> 如果说邻接表是不好写但效率好，邻接矩阵是好写但效率低的话，前向星就是一个相对中庸的数据结构。前向星固然好些，但效率并不高。而在优化为链式前向星后，效率也得到了较大的提升。虽然说，世界上对链式前向星的使用并不是很广泛，但在不愿意写复杂的邻接表的情况下，链式前向星也是一个很优秀的数据结构。

```c
#define V (10)

struct Edge {
	int to;     // 这条边的终点
	int w;      // 权值
    // 注意：这里不是下一条边的指针。类似拉链法。
    int next;   // 下一条边的存储下标(默认0)
};

struct Edge e[100];

// head[i]存以i为起点的第一条边(在edge中的下标)
int head[V];

// cnt为边的计数，从1开始计
int cnt = 1;

void addEdge(int u, int v, int w) {
    e[cnt].to = v;
    e[cnt].w = w;
    // 插入链表头
    e[cnt].next = head[u];
    // 更新链表头
    head[u] = cnt;
    cnt++;
}
```

### 边和点的松弛

松弛的定义

> 松弛这个术语来自于用一根橡皮筋沿着连接两个顶点的路径紧紧展开的比喻放松一条边就类似于将橡皮筋转移到一条更短的路径上，从而缓解了橡皮筋的压力。

#### 边的松弛

比如：Bellman-Ford。

```c
void relex(Edge e) {
    if (distance[e.src] + e.weight < distance[e.dest]) {
        distance[e.dest] = distance[e.src] + e.weight;
    }
}
```

#### 点的松弛

比如：Dijkstra。

```c
void relax(int src, Graph graph) {
    for (src 的邻接结点 dest) {
        if (distance[src] + `src->dest 的权 weight` < distance[dest]) {
            distance[dest] = distance[src] + weight;
        }
    }
}
```

### 图的算法

#### 广度优先搜索

ref: [Breadth First Search or BFS for a Graph](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)

广度优先搜索

> 访问自身向再依次访问完所有没有被访问过的邻接结点。

伪代码

```
void bfs(int src) {
    访问 src 结点，将其加入队列
    while (队列不为空) {
        从队列中弹出结点 v
        for (v 的所有没有被访问过的邻接结点 dest) {
            访问 dest，并将其加入队列
        }
    }
}
```

#### 深度优先搜索

ref: [Depth First Search or DFS for a Graph](https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/)

深度优先搜索

> 访问自身 src 向再访问其中一个没有被访问过的邻接结点。<br>
> 当一个点没有可访问的邻接结点时，则返回上一步（弹出函数栈帧），访问下一个没有被访问过结点。直到自身 src 和邻接结点都被深度优先搜索的方式访问。

伪代码

```
// 函数功能：用深度优先搜索的访问访问 src 结点。
void dfs(int src) {
    访问 src 结点
    for (src 的所有邻接结点 v) {
        v 没有被访问过
        dfs(v)
    }
}
```

#### 拓扑排序

ref: [Topological Sorting](https://www.geeksforgeeks.org/topological-sorting/)

当有向图无环时，则图一定存在拓扑排序。

定义

> 当一个的图的拓扑排序是 v1, v2, v3, .... 时，前面的点到后面的点一定存在路径，而不后面的点到前面的点是没有路径的。

有两种方法

-   [将入度为 0 的点取出，移除其出度的边，之后的图会存在一个入度为 0 的点。重复该步骤即可。](https://www.jianshu.com/p/3347f54a3187)<br>

-   [反之亦可。拓扑排序最后一个点的出度一定为 0，取出该点并移除其出度的边。重复该步骤即可。这个可与深度优先搜索结合。](https://www.geeksforgeeks.org/topological-sorting/)

#### 检测图是否有环或有负值环

##### 无向图的检测环的方法

ref

-   [Detect cycle in an undirected graph](https://www.geeksforgeeks.org/detect-cycle-undirected-graph/?ref=leftbar-rightbar)
-   [kruskal 算法检测环的方法](https://www.geeksforgeeks.org/union-find/)

首先无向图的两个点只能有一条边，所以只有两个点是构成不成环的。<br>
使用深度优先搜索的方法。当当前结点 u 的一个邻接结点 v 已经访问过且 v 不是 u 的 parent 时，则图有环。<br>
分析：parent 和 v 之间会存在一个不经过 u 的路径，且 v 是先被访问，再到 parent 的。

##### 有向图的检测环的方法

ref: [Detect Cycle in a Directed Graph](https://www.geeksforgeeks.org/?p=18516)

首先无向图的两个点可以有一条边，所以只有两个点是可以构成环的。用无向图的检测方法是行不通的。<br>
还是可以使用深度优先搜索的方法。当一个图存在一个环时，用深度优先搜索的方法时，当环的点没有被访问完时，则已访问的点会存在于栈（函数调用栈）中。当当前结点 u 的邻接结点 v 在栈中（在栈中则一定被访问过了）时，则图有环。

##### 有/无向图检测负环

-   Bellman Ford. [Detect a negative cycle in a Graph | (Bellman Ford)](https://www.geeksforgeeks.org/detect-negative-cycle-graph-bellman-ford/)
-   Floyd Warshall. [Detecting negative cycle using Floyd Warshall](https://www.geeksforgeeks.org/detecting-negative-cycle-using-floyd-warshall/)

Bellman-Ford 与 Floyd-Warshall 检测负环的区别

> 因为 Bellman–Ford 是单源的，而 Floyd-Warshall 是多源的，所以 Bellman-Ford 只能检测从源点出发是否存在负环，而 Floyd-Warshll 则可以检测从所有点出发，是否存在负环。

#### 最短路径算法

##### Dijkstra

ref: [Dijkstra’s shortest path algorithm | Greedy Algo-7](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/)

用于计算正权边（没有无负值圈）的有/无向图的单源最短路径。将无向边当成两条有向边即可。

dijkstra算法为什么不能有负边？

> 因为Dijkstra算法在计算最短路径时，不会因为负边的出现而更新已经在最短路径的顶点的距离。

Dijkstra 的思路

1.  将顶点分成两类，一类是已经知道源点到该顶点的最短路径，其他的顶点则为另一类。将第一类顶点加入最短路径顶点集。
2.  找出非最短路径顶点集中距离最小的点 v，然后将该顶点加入最短路径集。再然后松弛 v 邻接结点的最短距离。
3.  重复上一步，直到将所有顶点加入最短路径集。

##### Bellman-Ford

ref: [Bellman–Ford Algorithm | DP-23](https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/)

Bellman-Ford 算法用于计算有权边的有/无向图的单源最短路径。图中边的权重可为负数即负权边，但不可以出现负权环。

*与 Dijkstra 相比的优点是，也适合存在负权的图。*

Bellman-Ford 的思路

1.  源结点到自身的距离为 0。
2.  松弛所有边 `顶点数 - 1` 次，则到其他结点的距离就是最短距离。
3.  再松弛所有边一次。如果还有更短的距离，则图存在负环。

为什么松弛 `顶点数 - 1` 次时，到其他结点的距离就是最短距离？

> 任意选一条源点到其他结点的最短路径，因为不存在负环，所以该路径不会成环，所以只能是一条线。该最短路径最多是包含所有点。<br>
> 所以每松弛一次所有边（松弛的顺序是任意的），至少会计算出路径上一个点的最短距离。源点的最短距离已知，算出 `顶点数 - 1` 个顶点的最短距离即可。

##### Floyd-Warshall

ref: [Floyd Warshall Algorithm | DP-16。该程序没有检测负环。](https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/)

Floyd-Warshall 算法用于计算有权边的有/无向图的任意两点间（多源）的最短路径。图中边的权重可为负数即负权边，但不可以出现负权环。

*与 Bellman-Ford 相比，Bellman-Ford 是计算单源的最短路径，而 Floyd-Warshall 是计算多源的。*

[Floyd-Warshall 的证明](https://blog.csdn.net/qq_43824791/article/details/103834690)

1.  任意两个结点 i, j。因为没有负环，所以它们的最短路径会是一条线。i, j 之间会有 k 的结点，它们的编号为 `1, 2, ..., k`。
2.  然后 `min(distance[i][k] + distance[k][j], distance[i][j])。k 的范围是 [1, 2, ..., k]` 就是 i, j 结点的最短距离。

##### 无环有向图的最短路径和最长路径

ref

-   [Shortest Path in Directed Acyclic Graph](https://www.geeksforgeeks.org/shortest-path-for-directed-acyclic-graphs/)
-   [Longest Path in a Directed Acyclic Graph](https://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/)

要用到拓扑排序

##### 无权有/无向图的单源的最短路径

unweight single source shortest paths.

将边的权看作是 1，然后用广度优先搜索的方法即可。

[*无权无向图多源的最短路径*](https://math.stackexchange.com/questions/58198/all-pairs-shortest-path-in-undirected-and-unweighted-graphs)

#### 最小生成树

图是无向的，有权的。

最小生成树的定义

> 删除部分边，使图变成树。边的权之和最小的树就是最小生成树。

##### Prim 算法

ref

-   [prim算法（普里姆算法）详解](http://c.biancheng.net/algorithm/prim.html)
-   [Prim’s Minimum Spanning Tree (MST) | Greedy Algo-5](https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/)

从点的角度出发。

Prim 的思路

1.  将连通网中的所有顶点分为两类（假设为 A 类和 B 类）。初始状态下，所有顶点位于 B 类；
2.  选择任意一个顶点，将其从 B 类移动到 A 类；
3.  从 B 类的所有顶点出发，找出一条连接着 A 类中的某个顶点且权值最小的边，将此边连接着的 A 类中的顶点移动到 B 类；（这样不会构成环）
4.  重复执行第 3  步，直至 B 类中的所有顶点全部移动到 A 类，恰好可以找到 N-1 条边。

##### Kruskal 算法

ref

-   [kruskal算法（克鲁斯卡尔算法）详解](http://c.biancheng.net/algorithm/kruskal.html)
-   [Kruskal’s Minimum Spanning Tree Algorithm | Greedy Algo-2](https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/)

从边的角度出发。

Kruskal 的思路

1.  将连通网中所有的边按照权值大小做升序排序，从权值最小的边开始选择，只要此边不和已选择的边一起构成环路，就可以选择它组成最小生成树。
2.  对于 N 个顶点的连通网，挑选出 N-1 条符合条件的边，这些边组成的生成树就是最小生成树。

Kruskal 检测环的思路

1.  当选择一条条当前的最小边时，会构成一个个子树。
2.  当一条当前的最小边连接两个子树时，则选择该边不会构成环。但是一条边连接同一个子树的结点时，则该边会构成环。因为`树的顶点数 - 树的边数 = 1`。

Kruskal 检测环的实现

1.  方法一

    记录每个结点所在的子树的 ID, 当 ID 不同时，可选择该边。反之，则否。<br>
    当边连接两个不同的子树之后，更新新的子树的结点的子树 ID。

2.  方法二

    为每个结点建立一个父结点的数据，这样就构成了新的树的结构。该树的边是从儿子指向父母，这样就能从儿子结点找到根结点。<br>
    当边连接两个不同的子树时，则合并两棵子树（将一棵子树的根结点作为另一棵树的根结点的儿子即可）。

    *这个方法比上个方法好在不用更新过多的数据。*

    [kruskal 算法检测环的方法](https://www.geeksforgeeks.org/union-find/)
