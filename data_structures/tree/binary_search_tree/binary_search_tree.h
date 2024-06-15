#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef int Element;

struct TreeNode;
typedef struct TreeNode *PtrToNode;
typedef PtrToNode BinSearchTree;
typedef PtrToNode Position;

struct TreeNode {
    Element element;
    PtrToNode leftChild;
    PtrToNode rightChild;
};

BinSearchTree bstInsert(Element element, BinSearchTree binSearchTree);
BinSearchTree bstDelete(Element element, BinSearchTree binSearchTree);
Position bstFind(Element element, BinSearchTree binSearchTree);
BinSearchTree bstMakeEmpty(BinSearchTree binSearchTree);

#endif
