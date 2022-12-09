#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef int       PriorityType;

typedef struct tagePQNode
{
    PriorityType Priority;
    void* Data;
} PQNode;

typedef struct tagPriorityQueue
{
    PQNode* Nodes;
    int Capacity;
    int UsedSize;
} PriorityQueue;

PriorityQueue* PQ_Create(int InitialSize);
void           PQ_Destroy(PriorityQueue* PQ);
void           PQ_Enqueue(PriorityQueue* PQ, PQNode NewData);
void           PQ_Dequeue(PriorityQueue* PQ, PQNode* Root);
int            PQ_GetParent(int Index);
int            PQ_GetLeftChild(int Index);
void           PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2);
int            PQ_IsEmpty(PriorityQueue* PQ);

#define MAX_CHAR 256
#define MAX_BIT 8

typedef unsigned int UINT;
typedef unsigned char UCHAR;

typedef struct tagSymbolInfo {
    UCHAR symbol;
    int frequency;
} symbolInfo;

typedef struct tagHuffmanNode {
    symbolInfo data;
    struct tagHuffmanNode* left;
    struct tagHuffmanNode* right;
} huffmanNode;

typedef struct tagBitBuffer {
    UCHAR* buffer;
    UINT size;
} bitBuffer;

typedef struct tagHuffmanCode {
    UCHAR code[MAX_BIT];
    int size;
} huffmanCode;

huffmanNode* createNode(symbolInfo newData) {
    huffmanNode* newNode = (huffmanNode*)malloc(sizeof(huffmanNode));
    newNode->data = newData;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void destroyNode(huffmanNode* node) {
    free(node);
}

void destroyTree(huffmanNode* node) {
    if (node == NULL) { return; }

    destroyTree(node->left);
    destroyTree(node->right);
    destroyNode(node);
}

void addBit(bitBuffer* buffer, char bit) {
    UCHAR  mask = 0x80;

    if (buffer->size % 8 == 0) {
        buffer->buffer = realloc(buffer->buffer, sizeof(UCHAR) * ((buffer->size) / 8) + 1);
        buffer->buffer[buffer->size / 8] = 0x00;
    } 

    mask >>= buffer->size % 8;

    if (bit == 1) { buffer->buffer[buffer->size / 8] |= mask; }
    else { buffer->buffer[buffer->size / 8] &= ~mask; }

    buffer->size++;
}

void buildCodeTable(huffmanNode* tree, huffmanCode codeTable[MAX_CHAR], UCHAR code[MAX_BIT], int size) {
    if (tree == NULL) { return; }

    if (tree->left != NULL) {
        code[size] = 0;
        buildCodeTable(tree->left, codeTable, code, size + 1);
    }
    if (tree->right != NULL) {
        code[size] = 1;
        buildCodeTable(tree->right, codeTable, code, size + 1);
    }

    if (tree->left == NULL && tree->right == NULL) {
        int i;

        for (i = 0; i < size; i++) {
            codeTable[tree->data.symbol].code[i] = code[i];
        }
        codeTable[tree->data.symbol].size = size;
    }
}

void buildPrefizTree(huffmanNode** tree, symbolInfo symbolInfoTable[MAX_CHAR]) {
    int i = 0;
    PQNode result;
    PriorityQueue* PQ = PQ_Create(0);

    for (i = 0; i < MAX_CHAR; i++) {
        if (symbolInfoTable[i].frequency > 0) {
            huffmanNode* bitNode = createNode(symbolInfoTable[i]);
            PQNode newNode;
            newNode.Priority = symbolInfoTable[i].frequency;
            newNode.Data = bitNode;
            PQ_Enqueue(PQ, newNode);
        }
    }

    while (PQ->UsedSize > 1) {
        symbolInfo newData = { 0,0 };
    }
}