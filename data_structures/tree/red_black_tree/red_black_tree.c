#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "red_black_tree.h"

static void rbtreeFixInsertion(RBTreeNode newNode, RBTree rbtree);
static void rbtreeFixDeletion(RBTreeNode parent, enum Side side, RBTree rbtree);

static void rbtreeDeleteNode(RBTreeNode node, RBTree rbtree);
static void rbtreeFixDeletionBlackBlack(RBTreeNode parent, enum Side side, RBTree rbtree);
static void rbtreeLeftRotate(RBTreeNode node, RBTree rbtree);
static void rbtreeRightRotate(RBTreeNode node, RBTree rbtree);
static RBTreeNode rbtreeSearch(Element element, RBTree rbtree);
static RBTreeNode rbtreeFindRepalcingNode(RBTreeNode node, RBTree rbtree);
static void rbtreeDestroyNodes(RBTreeNode node);
static RBTreeNode rbtreeFindMin(RBTreeNode node);
static RBTreeNode rbtreeFindMax(RBTreeNode node);

static RBTreeNode rbtreeNodeCreate(Element element);
static void rbtreeNodeDestroy(RBTreeNode node);
static inline bool rbtreeNodeIsBlack(RBTreeNode node);
static inline bool rbTreeNodeIsRed(RBTreeNode node);
static inline bool rbtreeNodeIsRoot(RBTreeNode node);
static inline bool rbtreeNodeIsOnLeft(RBTreeNode node);
static inline bool rbtreeNodeIsOnRight(RBTreeNode node);
static inline void rbtreeNodeSwapColor(RBTreeNode node1, RBTreeNode node2);
static inline RBTreeNode rbtreeNodeSibling(RBTreeNode node);
static inline RBTreeNode rbtreeNodeGrandparent(RBTreeNode node);
static inline RBTreeNode rbtreeNodeUncle(RBTreeNode node);
static inline enum Side rbtreeNodeSide(RBTreeNode node);

// ## bebug
#include "utils/queue.h"

// ### 为了打印红黑树
# define NIL_ELEMENT (0)
# define LEVEL_SEPARATOR_ELEMENT (-1)

# define ARRAY_SIZE (10000 * 10)
// # define ARRAY_SIZE (12)

static int checkRBTreeSubTree(RBTreeNode node);
static int hOfRBTree(RBTreeNode node);
static void printNode(RBTreeNode node);

RBTree rbtreeCreate() {
    RBTree rbtree = malloc(sizeof(RBTreeNode));
    if (!rbtree) {
        fprintf(stderr, "No space for rbtree!\n");
        exit(EXIT_FAILURE);
    }
    rbtree->root = NULL;

    return rbtree;
}

void rbtreeDestroy(RBTree rbtree) {
    if (!rbtree || !rbtree->root) {
        return;
    }

    rbtreeDestroyNodes(rbtree->root);

    free(rbtree);
}

static void rbtreeDestroyNodes(RBTreeNode node) {
    if (!node) {
        return;
    }

    rbtreeDestroyNodes(node->leftChild);
    rbtreeDestroyNodes(node->rightChild);
    free(node);
}

void rbtreeInsert(Element element, RBTree rbtree) {
    // ### 插入值
    RBTreeNode newNode = rbtreeNodeCreate(element);

    if (!rbtree->root) {
        rbtree->root = newNode;
        newNode->color = BLACK;
        return;
    }

    RBTreeNode tmpNode = rbtreeSearch(element, rbtree);
    // 不允许插入相同的值
    if (tmpNode->element == element) {
        rbtreeNodeDestroy(newNode);
        return;
    }

    // ### 插入结点
    newNode->parent = tmpNode;
    if (newNode->element < tmpNode->element) {
        tmpNode->leftChild = newNode;
    } else {
        tmpNode->rightChild = newNode;
    }

    // ### 调整插入后的树
    rbtreeFixInsertion(newNode, rbtree);
}

void rbtreeDelete(Element element, RBTree rbtree) {
    RBTreeNode tmpNode = rbtreeSearch(element, rbtree);
    if (tmpNode && (tmpNode->element == element)) {
        rbtreeDeleteNode(tmpNode, rbtree);
    }
}

static void rbtreeFixInsertion(RBTreeNode newNode, RBTree rbtree) {
    // ### newNode 是根结点
    if (rbtreeNodeIsRoot(newNode)) {
        newNode->color = BLACK;
        return;
    }

    RBTreeNode parent = newNode->parent;

    // ## 父结点是黑色的
    if (rbtreeNodeIsBlack(parent)) {
        return;
    }

    // ## 父结点是红色的
    RBTreeNode grandparent = rbtreeNodeGrandparent(newNode);
    RBTreeNode uncle = rbtreeNodeUncle(newNode);

    if (rbTreeNodeIsRed(uncle)) {
        // ### 父红叔红
        grandparent->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        rbtreeFixInsertion(grandparent, rbtree);
    } else {
        // ### 父红叔黑
        if (rbtreeNodeIsOnLeft(parent)) {
            if (rbtreeNodeIsOnLeft(newNode)) {
                // #### 父左 N 左
                rbtreeRightRotate(grandparent, rbtree);
                rbtreeNodeSwapColor(grandparent, parent);
            } else {
                // #### 父左 N 左
                rbtreeLeftRotate(parent, rbtree);
                rbtreeFixInsertion(parent, rbtree);
            }
        } else {
            if (rbtreeNodeIsOnLeft(newNode)) {
                // #### 父右 N 左
                rbtreeRightRotate(parent, rbtree);
                rbtreeFixInsertion(parent, rbtree);
            } else {
                // #### 父右 N 右
                rbtreeLeftRotate(grandparent, rbtree);
                rbtreeNodeSwapColor(grandparent, parent);
            }
        }
    }
}

// 二叉搜索树的删除是可以用递归实现的，但根据分析，红黑树的 delete 很难用递归实现，所以用非递归实现。
static void rbtreeDeleteNode(RBTreeNode node, RBTree rbtree) {
    if (!node) {
        return;
    }

    RBTreeNode replacingNode = rbtreeFindRepalcingNode(node, rbtree);

    // 只有一个根结点的情况，否则不可能是 `replacingNode == rbtree->root`
    if (replacingNode == rbtree->root) {
        rbtreeNodeDestroy(replacingNode);
        rbtree->root = NULL;
        return;
    }

    /* 以下，replacingNode 不是根结点 */

    // ### 删除结点前，先保存 replacingNode 的 parent, side 和 color，以便进行删除和删除调整。
    RBTreeNode parent = replacingNode->parent;
    enum Side side;
    if (rbtreeNodeIsOnLeft(replacingNode)) {
        side = LEFT;
    } else {
        side = RIGHT;
    }

    enum Color color = replacingNode->color;

    // ### replacingNode element 替换 node element
    node->element = replacingNode->element;

    // ## 先以平衡二叉树的方法删除 replacingNode, 再判断是否要平衡调整
    if (!replacingNode->leftChild && !replacingNode->rightChild) {
        // ### replaceNode 是叶子结点
        if (side == LEFT) {
            parent->leftChild = NULL;
        } else {
            parent->rightChild = NULL;
        }

        rbtreeNodeDestroy(replacingNode);
    } else {
        // ### 只有一个儿子。直接删除 replacingNode。
        if (replacingNode->rightChild) {
            replacingNode->rightChild->parent = parent;
            if (side == LEFT) {
                parent->leftChild = replacingNode->rightChild;
            } else {
                parent->rightChild = replacingNode->rightChild;
            }
        } else {
            replacingNode->leftChild->parent = parent;
            if (side == LEFT) {
                parent->leftChild = replacingNode->leftChild;
            } else {
                parent->rightChild = replacingNode->leftChild;
            }
        }

        rbtreeNodeDestroy(replacingNode);
    }

    // ## 进行删除调整
    if (color == BLACK) {
        rbtreeFixDeletion(parent, side, rbtree);
    }
}

// parent 为当前平衡点 N 的 parent, side 表示平衡点在 parent 的左边还是右边
static void rbtreeFixDeletion(RBTreeNode parent, enum Side side, RBTree rbtree) {
    if (!parent) {
        return;
    }

    RBTreeNode node;
    RBTreeNode sibling;
    if (side == LEFT) {
        node = parent->leftChild;
        sibling = parent->rightChild;
    } else {
        node = parent->rightChild;
        sibling = parent->leftChild;
    }

    // ### 被删除的结点只有一个儿子的, 则其子结点必是红色的, 将其置为黑即可。
    if (node) {
        node->color = BLACK;
        return;
    }

    // ### 被删除的结点是叶子结点。
    rbtreeFixDeletionBlackBlack(parent, side, rbtree);
}

// 前提：当前平衡点 node 是黑的。
static void rbtreeFixDeletionBlackBlack(RBTreeNode parent, enum Side side, RBTree rbtree) {
    // ### base case
    // node 为根结点, 无需操作
    if(!parent) {
        return;
    }

    /* 以下，node 不为根结点 */

    // ### 找到 sibling
    RBTreeNode sibling;
    if (side == LEFT) {
        sibling = parent->rightChild;
    } else {
        sibling = parent->leftChild;
    }

    // 因为 h(S) - h(N) = 1，node 是黑的，parent 不空，所以 sibling 不为空。
    if (rbTreeNodeIsRed(sibling)) {
        // ## 兄红
        if (rbtreeNodeIsOnLeft(sibling)) {
            // ### 兄红-兄左
            rbtreeRightRotate(parent, rbtree);
            rbtreeNodeSwapColor(parent, sibling);
            rbtreeFixDeletionBlackBlack(parent, RIGHT, rbtree);
        } else {
            // ### 兄红-兄右
            rbtreeLeftRotate(parent, rbtree);
            rbtreeNodeSwapColor(parent, sibling);
            rbtreeFixDeletionBlackBlack(parent, LEFT, rbtree);
        }
    } else {
        // ## 兄黑
        if (rbtreeNodeIsBlack(sibling->leftChild) && rbtreeNodeIsBlack(sibling->rightChild)) {
            if (rbTreeNodeIsRed(parent)) {
                // ### 兄黑-兄的儿子全黑-父红
                rbtreeNodeSwapColor(parent, sibling);
            } else {
                // ### 兄黑-兄的儿子全黑-父黑
                sibling->color = RED;
                rbtreeFixDeletionBlackBlack(parent->parent, rbtreeNodeSide(parent), rbtree);
            }
        } else {
            if (rbtreeNodeIsOnLeft(sibling)) {
                if (rbTreeNodeIsRed(sibling->leftChild)) {
                    // ### 兄黑-兄的儿子结点不全黑，兄左，SL 红
                    rbtreeRightRotate(parent, rbtree);
                    rbtreeNodeSwapColor(parent, sibling);
                    sibling->leftChild->color = BLACK;
                } else {
                    // ### 兄黑-兄的儿子结点不全黑，兄左，SL 黑
                    RBTreeNode siblingRightChild = sibling->rightChild;
                    rbtreeLeftRotate(sibling, rbtree);
                    rbtreeNodeSwapColor(sibling, siblingRightChild);
                    rbtreeFixDeletionBlackBlack(parent, side, rbtree);
                }
            } else {
                if (rbTreeNodeIsRed(sibling->rightChild)) {
                    // ### 兄黑-兄的儿子结点不全黑，兄右，SR 红
                    rbtreeLeftRotate(parent, rbtree);
                    rbtreeNodeSwapColor(parent, sibling);
                    sibling->rightChild->color = BLACK;
                } else {
                    // ### 兄黑-兄的儿子结点不全黑，兄右，SR 黑
                    RBTreeNode siblingLeftChild = sibling->leftChild;
                    rbtreeRightRotate(sibling, rbtree);
                    rbtreeNodeSwapColor(sibling, siblingLeftChild);
                    rbtreeFixDeletionBlackBlack(parent, side, rbtree);
                }
            }
        }
    }
}

// 右儿子不能为空。如果 node 是 root 时，会更新 root。
static void rbtreeLeftRotate(RBTreeNode node, RBTree rbtree) {
    RBTreeNode parent = node->parent;
    RBTreeNode rightChild = node->rightChild;

    // ### 更新父结点的连接
    if (node == rbtree->root) {
        rbtree->root = rightChild;
    }

    // ### 重定位 node 和 rightChild 的 leftChild 之间的指针
    node->rightChild = rightChild->leftChild;
    if (rightChild->leftChild) {
        rightChild->leftChild->parent = node;
    }
    // ### 重定位 node 和 rightChild 之间的指针
    rightChild->leftChild = node;
    node->parent = rightChild;

    // ### 重定位 parent 和 right 之间的指针
    rightChild->parent = parent;
    if (parent) {
        if (node == parent->leftChild) {
            parent->leftChild = rightChild;
        } else {
            parent->rightChild = rightChild;
        }
    }
}

// 左儿子不能为空。如果 node 是 root 时，会更新 root。
static void rbtreeRightRotate(RBTreeNode node, RBTree rbtree) {
    RBTreeNode parent = node->parent;
    RBTreeNode leftChild = node->leftChild;

    // ### 更新父结点的连接
    if (node == rbtree->root) {
        rbtree->root = leftChild;
    }

    // ### 重位 node 和 leftChild 的 rightChild 之间的指针
    node->leftChild = leftChild->rightChild;
    if (leftChild->rightChild) {
        leftChild->rightChild->parent = node;
    }
    // ### 重位 node 和 leftChild 之间的指针
    leftChild->rightChild = node;
    node->parent = leftChild;

    // ### 重位 parent 和 leftChild 之间的指针
    leftChild->parent = parent;
    if (parent) {
        if (node == parent->leftChild) {
            parent->leftChild = leftChild;
        } else {
            parent->rightChild = leftChild;
        }
    }
}

 // 如果 element 相等则返回该结点。如果找不到则返回能作为插入的结点的父亲的结点。如果 root 为空则返回 NULL。
static RBTreeNode rbtreeSearch(Element element, RBTree rbtree) {
    RBTreeNode cur = rbtree->root;
    while (cur) {
        if (element < cur->element) {
            if (cur->leftChild) {
                cur = cur->leftChild;
            } else {
                break;
            }
        } else if (element > cur->element) {
            if (cur->rightChild) {
                cur = cur->rightChild;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    return cur;
}

// node 不为空。返回的结点不为空。有可能返回 node 自己。
static RBTreeNode rbtreeFindRepalcingNode(RBTreeNode node, RBTree rbtree) {
    // ### 是叶子
    if (!node->leftChild && !node->rightChild) {
        return node;
    }

    // ### 有两个儿子时，返回右边子树的最小结点
    if (node->leftChild && node->rightChild) {
        RBTreeNode cur = node->rightChild;
        while (cur->leftChild) {
            cur = cur->leftChild;
        }
        return cur;
    }

    // ### 只有一个儿子
    if (node->leftChild) {
        return node->leftChild;
    } else {
        return node->rightChild;
    }
}

static RBTreeNode rbtreeFindMin(RBTreeNode node) {
    RBTreeNode cur = node;
    while (cur->leftChild) {
        cur = cur->leftChild;
    }

    return cur;
}

static RBTreeNode rbtreeFindMax(RBTreeNode node) {
    RBTreeNode cur = node;
    while (cur->rightChild) {
        cur = cur->rightChild;
    }

    return cur;
}

static RBTreeNode rbtreeNodeCreate(Element element) {
    RBTreeNode newNode = malloc(sizeof(struct RBTreeNodeStruct));
    if (!newNode) {
        fprintf(stderr, "No space for newNode!\n");
        exit(EXIT_FAILURE);
    }
    newNode->element = element;
    // 默认颜色为红色
    newNode->color = RED;
    newNode->leftChild = newNode->rightChild = newNode->parent = NULL;

    return newNode;
}

static void rbtreeNodeDestroy(RBTreeNode node) {
    free(node);
}

static inline bool rbTreeNodeIsRed(RBTreeNode node) {
    return node && node->color == RED;
}

static inline bool rbtreeNodeIsBlack(RBTreeNode node) {
    // return !node || node->color == BLACK;
    return !rbTreeNodeIsRed(node);
}

static inline bool rbtreeNodeIsRoot(RBTreeNode node) {
    return node->parent == NULL;
}

// 判断 node 是否在其父亲的左边
static inline bool rbtreeNodeIsOnLeft(RBTreeNode node) {
    return node == node->parent->leftChild;
}

static inline bool rbtreeNodeIsOnRight(RBTreeNode node) {
    return node == node->parent->rightChild;
}

static inline void rbtreeNodeSwapColor(RBTreeNode node1, RBTreeNode node2) {
    enum Color tmpColor = node1->color;
    node1->color = node2->color;
    node2->color = tmpColor;
}

static inline RBTreeNode rbtreeNodeSibling(RBTreeNode node) {
    if (rbtreeNodeIsOnLeft(node)) {
        return node->parent->rightChild;
    } else {
        return node->parent->leftChild;
    }
}

static inline RBTreeNode rbtreeNodeGrandparent(RBTreeNode node) {
    return node->parent->parent;
}

static inline RBTreeNode rbtreeNodeUncle(RBTreeNode node) {
    RBTreeNode grandparent = node->parent->parent;

    if (rbtreeNodeIsOnLeft(node->parent)) {
        return grandparent->rightChild;
    } else {
        return grandparent->leftChild;
    }
}

// 为了使 node 为 root 时也能运行，root 结点是在父亲左边的（随便定一个位置）。
static inline enum Side rbtreeNodeSide(RBTreeNode node) {
    if (!node->parent) {
        return LEFT;
    }

    if (rbtreeNodeIsOnLeft(node)) {
        return LEFT;
    } else {
        return RIGHT;
    }
}

int checkRBTree(RBTree rbtree) {
    if (!rbtree->root) {
        return -1;
    }

    // 根结点是黑色的
    if (rbtree->root->color != BLACK) {
        return -2;
    }

    int ret = checkRBTreeSubTree(rbtree->root);

    return ret;
}

// node 可以作为红黑树的子树。所以 node（子树根结点） 为红黑无所谓。
int checkRBTreeSubTree(RBTreeNode node) {
    // Nil 结点
    if (!node) {
        return 0;
    }

    // ## 二叉搜索树的条件
    if (node->leftChild) {
        if (node->element < rbtreeFindMax(node->leftChild)->element) {
            return -3;
        }
    }

    if (node->rightChild) {
        if (node->element > rbtreeFindMin(node->rightChild)->element) {
            return -4;
        }
    }

    // ## 红黑树的条件
    // 不能是“红红”
    if (rbTreeNodeIsRed(node)) {
        if (rbTreeNodeIsRed(node->leftChild)) {
            return -5;
        }
        if (rbTreeNodeIsRed(node->rightChild)) {
            return -6;
        }
    }

    // 左右子树的 h 相同
    if (hOfRBTree(node->leftChild) != hOfRBTree(node->rightChild)) {
        return -7;
    }

    // 左右子树是红黑树
    int ret = checkRBTreeSubTree(node->leftChild);
    if (ret) {
        return -8;
    }
    ret = checkRBTreeSubTree(node->rightChild);
    if (ret) {
        return -9;
    }

    return 0;
}

// 层序遍历红黑树
// LEVEL_SEPARATOR_ELEMENT 是树的层分隔符。
void traverseBTree(RBTree rbtree) {
    if (!rbtree || !rbtree->root) {
        return;
    }

    Queue queue = queueCreate(ARRAY_SIZE);
    queuePush(rbtree->root, queue);
    RBTreeNode levelSeparatorNode = rbtreeNodeCreate(LEVEL_SEPARATOR_ELEMENT);
    queuePush(levelSeparatorNode, queue);

    RBTreeNode cur;
    while (!queueIsEmpty(queue)) {
        cur = queueFront(queue); queuePop(queue);

        printNode(cur);
        printf("\t");

        if (cur) {
            if (cur->element != LEVEL_SEPARATOR_ELEMENT) {
                queuePush(cur->leftChild, queue);
                queuePush(cur->rightChild, queue);
            } else {
                printf("\n");

                // 如果 cur 是层分隔符结点，且还有结点有 queue 中，则插入层分隔符（防止死循环）
                if (queueSize(queue)) {
                    queuePush(levelSeparatorNode, queue);
                }
            }
        }
    }

    rbtreeNodeDestroy(levelSeparatorNode);
}

// 为了方便打印，测试时不会加入 `LEVEL_SEPARATOR_ELEMENT`, `NIL_ELEMENT`
static void printNode(RBTreeNode node) {
    if (node) {
        // 不打印 LEVEL_SEPARATOR_ELEMENT 结点
        if (node->element == LEVEL_SEPARATOR_ELEMENT) {
            return;
        }

        printf("%d:", node->element);
        if (rbtreeNodeIsBlack(node)) {
            printf("B:");
        } else {
            printf("R:");
        }
        printf("[%d, %d]", node->leftChild ? node->leftChild->element : NIL_ELEMENT, node->rightChild ? node->rightChild->element : NIL_ELEMENT);
    } else {
        printf("%d", NIL_ELEMENT);
    }
}

// node 不一定是根结点。返回 node 到叶子结点的路径的黑色结点数
static int hOfRBTree(RBTreeNode node) {
    if (!node) {
        return 1;
    }

    if (!node->leftChild) {
        if (rbTreeNodeIsRed(node)) {
            return 1;
        } else {
            return 2;
        }
    } else {
        if (node->color == BLACK) {
            return 1 + hOfRBTree(node->leftChild);
        } else {
            return hOfRBTree(node->leftChild);
        }

    }
}
