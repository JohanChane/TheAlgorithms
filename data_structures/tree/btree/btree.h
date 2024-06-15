#ifndef BTREE_H
#define BTREE_H

typedef int Key;

typedef struct BTreeNodeStruct* PtrToBinTreeNode;
typedef PtrToBinTreeNode BTreeNode;
typedef PtrToBinTreeNode Position;
typedef struct BTreeStruct* PtrToBTree;
typedef PtrToBTree BTree;

struct BTreeNodeStruct {
    Key* keys;
    PtrToBinTreeNode* childs;
    int keyCount;
    int t;
    bool isLeaf;
};

struct BTreeStruct {
    BTreeNode root;
    int t;
};

void btreeInsert(Key key, BTree btree);
void btreeDelete(Key key, BTree btree);
BTree btreeInitialize(int t);
void btreeDestroy(BTree btree);

void btreeNodeInsertNonFull(Key key, BTreeNode btreeNode);
void btreeNodeDelete(Key key, BTreeNode btreeNode);
void btreeNodeDestroy(BTreeNode btreeNode);

static void btreeNodeSplitChild(int idx, BTreeNode btreeNode);
static void btreeNodeMergeChild(int idx, BTreeNode btreeNode);
static void btreeNodeBorrowFromPrev(int idx, BTreeNode btreeNode);
static void btreeNodeBorrowFromNext(int idx, BTreeNode btreeNode);

static void btreeNodeFillChild(int idx, BTreeNode btreeNode);
static void btreeNodeDeleteFromLeaf(int idx, BTreeNode btreeNode);
static void btreeNodeDeleteFromNonLeaf(int idx, BTreeNode btreeNode);

static BTreeNode btreeNodeCreateNode(bool isLeaf, int t);
static void btreeNodeRightShift(int idx, bool isBaseOnChild, BTreeNode btreeNode);
static int btreeNodeFindIdx(Key key, BTreeNode btreeNode);
static bool btreeNodeIsFull(BTreeNode btreeNode);
static Key btreeNodeGetMin(BTreeNode btreeNode);
static Key btreeNodeGetMax(BTreeNode btreeNode);

#endif
