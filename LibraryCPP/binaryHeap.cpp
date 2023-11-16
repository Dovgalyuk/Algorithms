#include "binaryHeap.h"

struct BinaryHeap
{
   HuffmanNode** heapData;
   size_t heapSize;
   size_t dataCount;
};

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

      if (left <= (int)heap->dataCount && huffman_getNodeWeight(heap->heapData[left - 1]) < huffman_getNodeWeight(heap->heapData[smallest - 1]))
         smallest = left;
      if (right <= (int)heap->dataCount && huffman_getNodeWeight(heap->heapData[left - 1]) < huffman_getNodeWeight(heap->heapData[smallest - 1]))
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

      while (i > 1 && huffman_getNodeWeight(heap->heapData[(i / 2) - 1]) >= huffman_getNodeWeight(node))
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
   return huffman_nodeIsLeaf(heap->heapData[0]);
}

unsigned long long int binaryHeap_getNodeWeight(BinaryHeap* heap)
{
   return huffman_getNodeWeight(heap->heapData[0]);
}

unsigned char binaryHeap_getNodeSymbol(BinaryHeap* heap)
{
   return huffman_getNodeChar(heap->heapData[0]);
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
