#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils/binary_heap.h"
#include "huffman_tree.h"

#define NONLEAF_DATA '$'

// 构建最小堆
int binHeapCmp(HuffmanTree tree1, HuffmanTree tree2) {
    return tree1->freq - tree2->freq;
}

static HuffmanTree huffmanTreeMerge(HuffmanTree huffmanTree1, HuffmanTree huffmanTree2);

// ### 这些函数都是为了生成 huffmanCode
static void genHuffmanTreeCodesUtil(HuffmanCode huffmanCode, int* prefix, int index, HuffmanTree huffmanTree);
static bool huffmanTreeIsLeaf(HuffmanTree huffmanTree);
static int huffmanTreeHeight(HuffmanTree huffmanTree);
static inline int max(int a, int b);
static int huffmanTreeLeaveNum(HuffmanTree huffmanTree);

HuffmanTree huffmanTreeCreate(char* datas, Freq* freqs, int n) {
    if (n < 0) {
        fprintf(stderr, "n < 0!\n");
        exit(EXIT_FAILURE);
    }

    BinHeap binHeap = binHeapCreate(n + 1);
    HuffmanTree newNode;
    for (int i = 0; i < n; i++) {
        newNode = malloc(sizeof(struct HuffmanTreeNodeStruct));
        if (!newNode) {
            fprintf(stderr, "No space for creating newNode!\n");
            exit(EXIT_FAILURE);
        }
        newNode->data = datas[i];
        newNode->freq = freqs[i];
        newNode->leftChild = newNode->rightChild = NULL;

        binHeapPush(newNode, binHeap);
    }

    if (n == 1) {
        return binHeapTop(binHeap);
    }

    // ## n > 1
    HuffmanTree mergedHuffmanTree, huffmanTree1, huffmanTree2;
    for (int j = 0; j < n - 1; j++) {
        huffmanTree1 = binHeapTop(binHeap); binHeapPop(binHeap);
        huffmanTree2 = binHeapTop(binHeap); binHeapPop(binHeap);

        mergedHuffmanTree = huffmanTreeMerge(huffmanTree1, huffmanTree2);
        binHeapPush(mergedHuffmanTree, binHeap);
    }

    return binHeapTop(binHeap);
}

void huffmanTreeDestroy(HuffmanTree huffmanTree) {
    if (!huffmanTree) {
        return;
    }

    huffmanTreeDestroy(huffmanTree->leftChild);
    huffmanTreeDestroy(huffmanTree->rightChild);
    free(huffmanTree);
}

static HuffmanTree huffmanTreeMerge(HuffmanTree huffmanTree1, HuffmanTree huffmanTree2) {
    HuffmanTreeNode newNode = malloc(sizeof(struct HuffmanTreeNodeStruct));
    if (!newNode) {
        fprintf(stderr, "No space for creating newNode!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = NONLEAF_DATA;
    newNode->freq = huffmanTree1->freq + huffmanTree2->freq;
    newNode->leftChild = huffmanTree1;
    newNode->rightChild = huffmanTree2;

    return newNode;
}

HuffmanCode huffmanCodeCreate(HuffmanTree huffmanTree) {
    HuffmanCode huffmanCode = malloc(sizeof(struct HuffmanCodeStruct));
    if (!huffmanCode) {
        perror("malloc huffmanCodes failed");
        exit(EXIT_FAILURE);
    }

    int leaveNum = huffmanTreeLeaveNum(huffmanTree);
    huffmanCode->elements = malloc(sizeof(huffmanCode->elements[0]) * leaveNum);
    if (!huffmanCode->elements) {
        perror("malloc huffmanCode->elements failed");
        exit(EXIT_FAILURE);
    }
    huffmanCode->count = 0;

    int treeHeight = huffmanTreeHeight(huffmanTree);
    for (int i = 0; i < leaveNum; i++) {
        huffmanCode->elements[i].code = malloc(sizeof(int) * treeHeight);
        if (!huffmanCode->elements[i].code) {
            perror("malloc elements->code failed");
            exit(EXIT_FAILURE);
        }
        huffmanCode->elements[i].count = 0;
    }

    return huffmanCode;
}

void huffmanCodeDestroy(HuffmanCode huffmanCode) {
    for (int i = 0; i < huffmanCode->count; i++) {
        free(huffmanCode->elements[i].code);
    }
    free(huffmanCode->elements);
    free(huffmanCode);
}

void genHuffmanTreeCode(HuffmanCode huffmanCode, HuffmanTree huffmanTree) {
    int* prefix = malloc(sizeof(int) * huffmanTreeHeight(huffmanTree));
    genHuffmanTreeCodesUtil(huffmanCode, prefix, 0, huffmanTree);
    free(prefix);
}

static void genHuffmanTreeCodesUtil(HuffmanCode huffmanCode, int* prefix, int index, HuffmanTree huffmanTree) {
    if (!huffmanTree) {
        return;
    }

    if (!huffmanTreeIsLeaf(huffmanTree)) {
        // 向左则为 0
        if (huffmanTree->leftChild) {
            prefix[index] = 0;
            genHuffmanTreeCodesUtil(huffmanCode, prefix, index + 1, huffmanTree->leftChild);
        }

        if (huffmanTree->rightChild) {
            prefix[index] = 1;
            genHuffmanTreeCodesUtil(huffmanCode, prefix, index + 1, huffmanTree->rightChild);
        }
    } else {
        huffmanCode->elements[huffmanCode->count].c = huffmanTree->data;
        for (int i = 0; i <= index; i++) {
            huffmanCode->elements[huffmanCode->count].code[i] = prefix[i];
            huffmanCode->elements[huffmanCode->count].count++;
        }
        huffmanCode->count++;
    }
}

bool huffmanTreeIsLeaf(HuffmanTree huffmanTree) {
    return !huffmanTree->leftChild && !huffmanTree->rightChild;
}

static int huffmanTreeHeight(HuffmanTree huffmanTree) {
    if (!huffmanTree) {
        return 0;
    }

    return max(huffmanTreeHeight(huffmanTree->leftChild), huffmanTreeHeight(huffmanTree->rightChild)) + 1;
}

static inline int max(int a, int b) {
    return a > b ? a : b;
}

static int huffmanTreeLeaveNum(HuffmanTree huffmanTree) {
    if (!huffmanTree) {
        return 0;
    }

    if (!huffmanTree->leftChild && !huffmanTree->rightChild) {
        return 1;
    }

    return huffmanTreeLeaveNum(huffmanTree->leftChild) + huffmanTreeLeaveNum(huffmanTree->rightChild);
}
