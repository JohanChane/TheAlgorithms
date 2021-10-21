#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

typedef struct HuffmanTreeNodeStruct* HuffmanTree;
typedef int Freq;

typedef struct HuffmanTreeNodeStruct {
    char data;
    Freq freq;
    struct HuffmanTreeNodeStruct *leftChild, *rightChild;
} *HuffmanTreeNode;

typedef struct HuffmanCodeStruct {
    struct HuffmanCodeElementStruct {
        char c;
        int* code;
        int count;
    } *elements;

    int count;
} *HuffmanCode;

HuffmanTree huffmanTreeCreate(char* datas, Freq* freqs, int n);
void huffmanTreeDestroy(HuffmanTree huffmanTree);

void genHuffmanTreeCode(HuffmanCode huffmanCode, HuffmanTree huffmanTree);
HuffmanCode huffmanCodeCreate(HuffmanTree huffmanTree);
void huffmanCodeDestroy(HuffmanCode huffmanCode);

#endif
