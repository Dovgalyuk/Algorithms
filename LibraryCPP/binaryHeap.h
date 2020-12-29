#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <stdlib.h>
#include <iostream>

struct HuffmanNode;

struct BinaryHeap;

HuffmanNode* huffman_createLeafNode(unsigned char symbol, unsigned long long int weight);

HuffmanNode* huffman_createInternalNode(HuffmanNode* leftNode, HuffmanNode* rightNode);

HuffmanNode* huffman_getLeftNode(HuffmanNode* node);

HuffmanNode* huffman_getRightNode(HuffmanNode* node);

void huffman_setLeftNode(HuffmanNode* node, HuffmanNode* newNode);

void huffman_setRightNode(HuffmanNode* node, HuffmanNode* newNode);

bool huffman_nodeIsLeaf(HuffmanNode* node);

unsigned char huffman_getNodeChar(HuffmanNode* node);

unsigned long long int huffman_getNodeWeight(HuffmanNode* node);

HuffmanNode* huffman_deleteTree(HuffmanNode* node);

BinaryHeap* binaryHeap_create(const size_t size);

void binaryHeap_swapData(BinaryHeap* heap, const size_t firstIndex, const size_t secondIndex);

void binaryHeap_heapify(BinaryHeap* heap, int i);

void binaryHeap_insert(BinaryHeap* heap, HuffmanNode* node);

void binaryHeap_extractMin(BinaryHeap* heap);

HuffmanNode* BinaryHeap_getNode(BinaryHeap* heap);

bool binaryHeap_nodeIsLeaf(BinaryHeap* heap);

unsigned long long int binaryHeap_getNodeWeight(BinaryHeap* heap);

unsigned char binaryHeap_getNodeSymbol(BinaryHeap* heap);

size_t binaryHeap_getSize(BinaryHeap* heap);

void binaryHeap_delete(BinaryHeap* heap);

void binaryHeap_printTree(HuffmanNode* node, unsigned int height);

#endif
