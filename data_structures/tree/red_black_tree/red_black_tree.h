#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

typedef int Element;

enum Color {RED, BLACK};
enum Side {LEFT, RIGHT};

typedef struct RBTreeNodeStruct* PtrToRBTreeNode;
typedef PtrToRBTreeNode RBTreeNode;
typedef PtrToRBTreeNode Position;

typedef struct RBTreeStruct {
    RBTreeNode root;
} *RBTree;

struct RBTreeNodeStruct {
    Element element;
    enum Color color;
    RBTreeNode parent, leftChild, rightChild;
};

RBTree rbtreeCreate();
void rbtreeDestroy(RBTree rbtree);
void rbtreeInsert(Element element, RBTree rbtree);
void rbtreeDelete(Element element, RBTree rbtree);

// debug
int checkRBTree(RBTree rbtree);
void traverseBTree(RBTree rbtree);

#endif
