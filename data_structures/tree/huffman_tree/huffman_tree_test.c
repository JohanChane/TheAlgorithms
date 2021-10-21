#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "huffman_tree.h"
#include "test_utils/utils.h"

#define ARRAY_SIZE (26 + 26)

static void printHuffmanCode(HuffmanCode huffmanCode);

static void printHuffmanCode(HuffmanCode huffmanCode) {
    for (int i = 0; i < huffmanCode->count; i++) {
        printf("%c: ", huffmanCode->elements[i].c);
        for (int j = 0; j < huffmanCode->elements[i].count; j++) {
            printf("%d", huffmanCode->elements[i].code[j]);
        }
        printf("\n");
    }
}

static void testHuffmanTree() {
    char datas[ARRAY_SIZE];
    for (int i = 0; i < 26; i++) {
        datas[i] = 'A' + i;
        datas[26 + i] = 'a' + i;
    }
    Freq freqs[ARRAY_SIZE];
    genRandomNums(freqs, ARRAY_SIZE, 100, ARRAY_SIZE + 999);

    HuffmanTree huffmanTree = huffmanTreeCreate(datas, freqs, ARRAY_SIZE);

    HuffmanCode huffmanCode = huffmanCodeCreate(huffmanTree);
    genHuffmanTreeCode(huffmanCode, huffmanTree);
    printHuffmanCode(huffmanCode);
    huffmanCodeDestroy(huffmanCode);
}

int main() {
    testHuffmanTree();
    return 0;
}
