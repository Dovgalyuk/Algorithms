#include "binaryHeap.h"

#include <iostream>
struct HuffmanNode
{
   bool isLeaf;
   unsigned long long int weight;
   unsigned char symbol;

   HuffmanNode* leftNode;
   HuffmanNode* rightNode;
};

struct BinaryHeap
{
   HuffmanNode** heapData;
   size_t heapSize;
   size_t dataCount;
};

HuffmanNode* huffman_createLeafNode(unsigned char symbol, unsigned long long int weight)
{
   HuffmanNode* node = new HuffmanNode;
   node->isLeaf = true;
   node->symbol = symbol;
   node->weight = weight;
   node->leftNode = NULL;
   node->rightNode = NULL;
   return node;
}

HuffmanNode* huffman_createInternalNode(HuffmanNode* leftNode, HuffmanNode* rightNode)
{
   HuffmanNode* node = new HuffmanNode;
   node->isLeaf = false;
   node->leftNode = leftNode;
   node->rightNode = rightNode;
   node->weight = (leftNode && rightNode) ? leftNode->weight + rightNode->weight : 0;
   return node;
}

HuffmanNode* huffman_getLeftNode(HuffmanNode* node)
{
   return node ? node->leftNode : NULL;
}

HuffmanNode* huffman_getRightNode(HuffmanNode* node)
{
   return node ? node->rightNode : NULL;
}

void huffman_setLeftNode(HuffmanNode* node, HuffmanNode* newNode)
{
   node->leftNode = node->leftNode ? node->leftNode : newNode;
}

void huffman_setRightNode(HuffmanNode* node, HuffmanNode* newNode)
{
   node->rightNode = node->rightNode ? node->rightNode : newNode;
}

bool huffman_nodeIsLeaf(HuffmanNode* node)
{
   return node->isLeaf;
}

unsigned char huffman_getNodeChar(HuffmanNode* node)
{
   return node->symbol;
}

unsigned long long int huffman_getNodeWeight(HuffmanNode* node)
{
   return node->weight;
}

HuffmanNode* huffman_deleteTree(HuffmanNode* node)
{
   if (!node)
   {
      huffman_deleteTree(node->leftNode);
      huffman_deleteTree(node->rightNode);
      delete node;
   }
   return NULL;
}

BinaryHeap* binaryHeap_create(const size_t size)
{
   BinaryHeap* heap = new BinaryHeap;
   heap->heapData = new HuffmanNode*[size];
   heap->heapSize = size;
   heap->dataCount = 0;
   return heap;
}

void binaryHeap_swapData(BinaryHeap* heap, const size_t firstIndex, const size_t secondIndex)
{
   HuffmanNode* temp = heap->heapData[firstIndex];
   heap->heapData[firstIndex] = heap->heapData[secondIndex];
   heap->heapData[secondIndex] = temp;
}

void binaryHeap_heapify(BinaryHeap* heap, int i)
{
   while (true)
   {
      int left = i * 2;
      int right = i * 2 + 1;
      int smallest = i;
      
      if (left <= heap->dataCount && heap->heapData[left - 1]->weight < heap->heapData[smallest - 1]->weight)
         smallest = left;
      if (right <= heap->dataCount && heap->heapData[right - 1]->weight < heap->heapData[smallest - 1]->weight)
         smallest = right;
      if (i == smallest)
         break;

      binaryHeap_swapData(heap, i - 1, smallest - 1);
      i = smallest;
   }
}

void binaryHeap_insert(BinaryHeap* heap, HuffmanNode* node)
{
   if (heap->dataCount < heap->heapSize)
   {
      heap->dataCount++;
      size_t i = heap->dataCount;
      
      while (i > 1 && heap->heapData[(i / 2) - 1]->weight >= node->weight)
      {
         heap->heapData[i - 1] = heap->heapData[i / 2 - 1];
         i = i / 2;
      }
      heap->heapData[i - 1] = node; 
   }
}

void binaryHeap_extractMin(BinaryHeap* heap)
{
   if (heap->dataCount)
   {
      heap->heapData[0] = heap->heapData[heap->dataCount - 1];
      heap->dataCount--;
      binaryHeap_heapify(heap, 1);
   }
}

HuffmanNode* BinaryHeap_getNode(BinaryHeap* heap)
{
   return heap->heapData[0];
}

bool binaryHeap_nodeIsLeaf(BinaryHeap* heap)
{
   return heap->heapData[0]->isLeaf;
}

unsigned long long int binaryHeap_getNodeWeight(BinaryHeap* heap)
{
   return heap->heapData[0]->weight;
}

unsigned char binaryHeap_getNodeSymbol(BinaryHeap* heap)
{
   return heap->heapData[0]->symbol;
}

size_t binaryHeap_getSize(BinaryHeap* heap)
{
   return heap->dataCount;
}

void binaryHeap_delete(BinaryHeap* heap)
{
   delete[] heap->heapData;
   delete heap;
}

void binaryHeap_printTree(HuffmanNode* node, unsigned int height)
{
   if (node)
   {
      binaryHeap_printTree(node->rightNode, height + 1);
      for (int i = 0; i < height; i++)
         std::cout << "  ";
      if (node->isLeaf)
         std::cout << (unsigned char) node->symbol;
      else
         std::cout << node->weight;
      binaryHeap_printTree(node->leftNode, height + 1);
   }
   else
      std::cout << std::endl;
}
