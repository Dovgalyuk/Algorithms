#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <stdlib.h>
#include <iostream>

// Предварительное объявление структуры HuffmanNode
struct HuffmanNode;

struct BinaryHeap;

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

#endif