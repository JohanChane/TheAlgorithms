#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

typedef int Element;

struct TreeNode;
typedef struct TreeNode *PtrToNode;
typedef PtrToNode SplayTree;
typedef PtrToNode Position;

struct TreeNode {
    Element element;
    PtrToNode leftChild;
    PtrToNode rightChild;
};

Position splayTreeSplay(Element element, SplayTree splayTree);
SplayTree splayTreeInsert(Element element, SplayTree splayTree);
SplayTree splayTreeDelete(Element element, SplayTree splayTree);
SplayTree splayTreeMakeEmpty(SplayTree splayTree);

#endif
