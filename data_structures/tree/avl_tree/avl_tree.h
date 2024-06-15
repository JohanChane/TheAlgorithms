#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef int Element;

struct AvlNode;
typedef struct AvlNode* PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode AvlTree;

struct AvlNode {
    Element element;
    PtrToNode leftChild;
    PtrToNode rightChild;
    int height;
};

AvlTree avlTreeInsert(Element element, AvlTree avlTree);
AvlTree avlTreeDelete(Element element, AvlTree avlTree);
Position avlTreeFind(Element element, AvlTree avlTree);
Position avlTreeFindMin(AvlTree avlTree);
Position avlTreeFindMax(AvlTree avlTree);
int avlTreeHeight(AvlTree avlTree);
AvlTree avlTreeMakeEmpty(AvlTree avlTree);

#endif
