#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "btree.h"

void btreeInsert(Key key, BTree btree) {
    if (!btree->root) {
        btree->root = btreeNodeCreateNode(true, btree->t);
        btree->root->keys[0] = key;
        btree->root->keyCount++;
        return;
    }

    if (!btreeNodeIsFull(btree->root)) {     // 本结点不满
        btreeNodeInsertNonFull(key, btree->root);
    } else {    // 本结点已满
        BTreeNode newRoot = btreeNodeCreateNode(false, btree->t);
        newRoot->childs[0]= btree->root;
        btreeNodeSplitChild(0, newRoot);
        btree->root = newRoot;
        btreeNodeInsertNonFull(key, btree->root);
    }
}

void btreeDelete(Key key, BTree btree) {
    if (!btree->root) {
        fprintf(stderr, "root is Empty!\n");
        exit(EXIT_FAILURE);
    }

    btreeNodeDelete(key, btree->root);

    if (!btree->root->keyCount) {
        BTreeNode tmpRoot = btree->root;
        if (btree->root->isLeaf) {
            btree->root = NULL;
        } else {
            // btreeNodeDelete 后，已合并 childs[0], childs[1]
            btree->root = btree->root->childs[0];
        }
        free(tmpRoot);
    }
}

BTree btreeInitialize(int t) {
    BTree btree = malloc(sizeof(struct BTreeStruct));
    if (!btree) {
        fprintf(stderr, "No space for creating btree!\n");
        exit(EXIT_FAILURE);
    }
    btree->t = t;
    btree->root = NULL;

    return btree;
}

void btreeDestroy(BTree btree) {
    btreeNodeDestroy(btree->root);
    free(btree);
}

// 前提：本结点不满
// 要优先向叶子插入
void btreeNodeInsertNonFull(Key key, BTreeNode btreeNode) {
    if (btreeNode->isLeaf) {
        int idx = 0;
        while (idx < btreeNode->keyCount && key >= btreeNode->keys[idx]) {
            idx++;
        }

        // 将 keys[idx] 右边的东西（包含 keys[idx]）右移
        for (int i = btreeNode->keyCount; i > idx; i--) {
            btreeNode->keys[i] = btreeNode->keys[i - 1];
        }
        btreeNode->keys[idx] = key;
        btreeNode->keyCount++;
    } else {
        int idx = btreeNodeFindIdx(key, btreeNode);
        if (btreeNodeIsFull(btreeNode->childs[idx])) {
            btreeNodeSplitChild(idx, btreeNode);

            // 分裂会使本结点新增一个 key 和 child。 keys[idx] 为新增的 key。
            if (key > btreeNode->keys[idx]) {
                idx++;
            }
        }
        btreeNodeInsertNonFull(key, btreeNode->childs[idx]);
    }
}

// 前提：btreeNode 的 keyCount 比允许的最少值至少多 1（根节点最少可有 0 个 key(btree 为空时), 非根节点最少有 t - 1 个 key）。
// 如果只有一个 key 时，root 要更新，这要在外边处理。
void btreeNodeDelete(Key key, BTreeNode btreeNode) {
    int idx = btreeNodeFindIdx(key, btreeNode);

    // ### key 在本结点
    if (idx < btreeNode->keyCount && btreeNode->keys[idx] == key) {
        if (btreeNode->isLeaf) {
            btreeNodeDeleteFromLeaf(idx, btreeNode);
        } else {
            btreeNodeDeleteFromNonLeaf(idx, btreeNode);
        }
        return;
    }

    // ### key 不在本结点
    if (btreeNode->isLeaf) {
        return;
    }

    // #### 向儿子节点的 BTree 删除 key
    bool isLastChild = (idx == btreeNode->keyCount);
    if (btreeNode->childs[idx]->keyCount < btreeNode->t) {
        btreeNodeFillChild(idx, btreeNode);
    }
    // 如果是最后一个儿子且被合并了
    if (isLastChild && idx > btreeNode->keyCount) {
        btreeNodeDelete(key, btreeNode->childs[idx - 1]);
    } else {
        btreeNodeDelete(key, btreeNode->childs[idx]);
    }
}

void btreeNodeDestroy(BTreeNode btreeNode) {
    if (!btreeNode) {
        return;
    }

    for (int i = 0; i <= btreeNode->keyCount; i++) {
        btreeNodeDestroy(btreeNode->childs[i]);
    }
    free(btreeNode->keys);
    free(btreeNode->childs);
    free(btreeNode);
}

// 前提：keyCount >= t
static void btreeNodeDeleteFromLeaf(int idx, BTreeNode btreeNode) {
    for (int i = idx + 1; i < btreeNode->keyCount; i++) {
        btreeNode->keys[i - 1] = btreeNode->keys[i];
    }
    btreeNode->keyCount--;
}

// 前提：keyCount >= t
static void btreeNodeDeleteFromNonLeaf(int idx, BTreeNode btreeNode) {
    if (btreeNode->childs[idx]->keyCount >= btreeNode->t) {
        Key maxKey = btreeNodeGetMax(btreeNode->childs[idx]);
        btreeNode->keys[idx] = maxKey;
        btreeNodeDelete(maxKey, btreeNode->childs[idx]);
    } else if (btreeNode->childs[idx + 1]->keyCount >= btreeNode->t) {
        Key minKey = btreeNodeGetMin(btreeNode->childs[idx + 1]);
        btreeNode->keys[idx] = minKey;
        btreeNodeDelete(minKey, btreeNode->childs[idx + 1]);
    } else {
        int key = btreeNode->keys[idx];
        btreeNodeMergeChild(idx, btreeNode);
        btreeNodeDelete(key, btreeNode->childs[idx]);
    }
}

// 前提：本结点不满，childs[idx] 是满的
// keys: [0, t - 1), [t - 1], [t, 2t - 1). 将 keys[t - 1] 抽出，则刚好平分。将本结点的 keys[idx], childs[idx + 1] 空出，再将 keys[t - 1], newRightNode 插入即可。
static void btreeNodeSplitChild(int idx, BTreeNode btreeNode) {
    BTreeNode splitedChild = btreeNode->childs[idx];

    // ### 将 childs[idx] 右半部分放入 newRightChild
    BTreeNode newRightNode = btreeNodeCreateNode(splitedChild->isLeaf, btreeNode->t);
    for (int i = 0; i < splitedChild->t - 1; i++) {
        newRightNode->keys[i] = splitedChild->keys[i + splitedChild->t];
    }
    if (!splitedChild->isLeaf) {
        for (int j = 0; j < splitedChild->t; j++) {
            newRightNode->childs[j] = splitedChild->childs[j + splitedChild->t];
        }
    }
    // 更新 newRightNode->keyCount
    newRightNode->keyCount = btreeNode->t - 1;

    // ### 空出 keys[idx], childs[idx + 1]
    btreeNodeRightShift(idx, false, btreeNode);

    // ### 本结点插入 keys[t - 1], newRightNode
    btreeNode->keys[idx] = splitedChild->keys[splitedChild->t - 1];
    btreeNode->childs[idx + 1] = newRightNode;

    // 更新本结点与 childs[idx] 的 keyCount
    btreeNode->keyCount++;
    splitedChild->keyCount = splitedChild->t - 1;
}

// 填充 childs[idx]
// 前提：child[idx]->keyCount == t - 1
static void btreeNodeFillChild(int idx, BTreeNode btreeNode) {
    if (idx != 0 && btreeNode->childs[idx - 1]->keyCount >= btreeNode->t) {
        btreeNodeBorrowFromPrev(idx, btreeNode);
    } else if (idx != btreeNode->keyCount && btreeNode->childs[idx + 1]->keyCount >= btreeNode->t) {
        btreeNodeBorrowFromNext(idx, btreeNode);
    } else {    // (idx == 0 || childs[idx - 1]->keyCount < t) && (idx == keyCount || childs[idx + 1] < t)
        if (idx != btreeNode->keyCount) {   // childs[idx + 1]->keyCount < t
            btreeNodeMergeChild(idx, btreeNode);
        } else {    // childs[idx - 1]->keyCount < t
            btreeNodeMergeChild(idx- 1, btreeNode);
        }
    }
}

// 合并 keys[idx] 的左右儿子
// 前提：childs[idx], childs[idx + 1] 的 keyCount == t - 1; 本结点 keyCount >= t
static void btreeNodeMergeChild(int idx, BTreeNode btreeNode) {
    Position leftChild = btreeNode->childs[idx];
    Position rightChild = btreeNode->childs[idx + 1];

    // ### keys[idx] 加入 leftChild
    leftChild->keys[btreeNode->t - 1] = btreeNode->keys[idx];

    // ### rightChild 加入 leftchild
    for (int i = 0; i < btreeNode->t - 1; i++) {
        leftChild->keys[i + btreeNode->t] = rightChild->keys[i];
        leftChild->childs[i + btreeNode->t] = rightChild->childs[i];
    }
    leftChild->childs[2 * btreeNode->t - 1] = rightChild->childs[rightChild->keyCount];

    // ### 本结点左移
    for (int i = idx + 1; i < btreeNode->keyCount; i++) {
        btreeNode->keys[i - 1] = btreeNode->keys[i];
        btreeNode->childs[i] = btreeNode->childs[i + 1];
    }

    // ### 更新
    btreeNode->keyCount--;
    leftChild->keyCount += rightChild->keyCount + 1;
    free(rightChild);
}

static BTreeNode btreeNodeCreateNode(bool isLeaf, int t) {
    BTreeNode btreeNode = malloc(sizeof(struct BTreeNodeStruct));
    if (!btreeNode) {
        fprintf(stderr, "No space for creating btreeNode!\n");
        exit(EXIT_FAILURE);
    }
    btreeNode->keys = malloc(sizeof(Key) * (2 * t - 1));
    if (!btreeNode->keys) {
        fprintf(stderr, "No space for creating btreeNode->keys!\n");
        exit(EXIT_FAILURE);
    }
    btreeNode->childs = malloc(sizeof(btreeNode) * (2 * t));
    if (!btreeNode->childs) {
        fprintf(stderr, "No space for creating btreeNode->childs!\n");
        exit(EXIT_FAILURE);
    }
    btreeNode->keyCount = 0;
    btreeNode->isLeaf = isLeaf;
    btreeNode->t = t;

    return btreeNode;
}

// 前提：本结点不满
// 基于 keys[idx] 或 childs[idx], 将其右边（包含自身）的 keys, childs 右移。
// isBaseOnChild 表示基于 childs[idx], 否则基于 keys[idx]
static void btreeNodeRightShift(int idx, bool isBaseOnChild, BTreeNode btreeNode) {
    // 将 keys[idx] 右边的东西右移
    for (int i = btreeNode->keyCount; i > idx; i--) {
        btreeNode->keys[i] = btreeNode->keys[i - 1];
        btreeNode->childs[i + 1] = btreeNode->childs[i];
    }

    if (isBaseOnChild) {
        btreeNode->childs[idx + 1] = btreeNode->childs[idx];
    }
}

// 如果 btreeNode 有相同的 key, 则返回其 key 的 idx, 否则返回 key 所在的 child 的 idx
static int btreeNodeFindIdx(Key key, BTreeNode btreeNode) {
    int idx = 0;
    while (idx < btreeNode->keyCount && key > btreeNode->keys[idx]) {
        idx++;
    }
    return idx;
}

static bool btreeNodeIsFull(BTreeNode btreeNode) {
    return btreeNode->keyCount == 2 * btreeNode->t - 1;
}

static Key btreeNodeGetMax(BTreeNode btreeNode) {
    Position cur = btreeNode;
    while (!cur->isLeaf) {
        cur = cur->childs[cur->keyCount];
    }

    return cur->keys[cur->keyCount - 1];
}

static Key btreeNodeGetMin(BTreeNode btreeNode) {
    Position cur = btreeNode;
    while (!cur->isLeaf) {
        cur = cur->childs[0];
    }

    return cur->keys[0];
}

// 前提: idx 不为 0; childs[idx - 1]->keyCount >= t
// prevSibling->keys[keyCount - 1] <= prevSibling->childs[keyCount] <= keys[idx - 1] <= childs[idx]。prevSibling->childs[keyCount] 和 key[idx - 1] 加入 childs[idx], prevSibling->keys[keyCount - 1] 加入 keys[idx] 即可。
static void btreeNodeBorrowFromPrev(int idx, BTreeNode btreeNode) {
    Position prevSibling = btreeNode->childs[idx - 1];
    Position curChild = btreeNode->childs[idx];

    btreeNodeRightShift(0, true, curChild);

    // ### keys
    curChild->keys[0] = btreeNode->keys[idx - 1];
    btreeNode->keys[idx - 1] = prevSibling->keys[prevSibling->keyCount - 1];

    // ### the child
    curChild->childs[0] = prevSibling->childs[prevSibling->keyCount];

    // ### 更新 keyCount
    prevSibling->keyCount--;
    curChild->keyCount++;
}

// 前提: idx 不为 keyCount; childs[idx + 1]->keyCount >= t
static void btreeNodeBorrowFromNext(int idx, BTreeNode btreeNode) {
    Position nextSibling = btreeNode->childs[idx + 1];
    Position curChild = btreeNode->childs[idx];

    // ### keys
    curChild->keys[curChild->keyCount] = btreeNode->keys[idx];
    btreeNode->keys[idx] = nextSibling->keys[0];

    // ### the child
    curChild->childs[curChild->keyCount + 1] = nextSibling->childs[0];

    // ### nextSibling 左移
    for (int i = 1; i < nextSibling->keyCount; i++) {
        nextSibling->keys[i - 1] = nextSibling->keys[i];
    }

    if (!nextSibling->isLeaf) {
        for (int j = 0; j < nextSibling->keyCount; j++) {
            nextSibling->childs[j] = nextSibling->childs[j + 1];
        }
    }

    // ### 更新
    nextSibling->keyCount--;
    curChild->keyCount++;
}
