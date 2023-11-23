#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <stdlib.h>
#include <iostream>

struct HuffmanNode;

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
void huffman_printTree(HuffmanNode* node, unsigned int height);

// Дополнительные функции для использования с BinaryHeap
int huffmanNodeComparator(const void* nodeA, const void* nodeB);
void huffmanNodeDestructor(void* node);

#endif