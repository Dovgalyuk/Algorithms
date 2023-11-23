#include "binaryHeap.h"

struct BinaryHeap
{
    void** heapData;
    size_t heapSize;
    size_t dataCount;
    Comparator compare;
    Destructor destroy;
};

BinaryHeap* binaryHeap_create(const size_t size, Comparator comp, Destructor dest)
{
    BinaryHeap* heap = new BinaryHeap;
    heap->heapData = new void* [size];
    heap->heapSize = size;
    heap->dataCount = 0;
    heap->compare = comp;
    heap->destroy = dest;
    return heap;
}

void binaryHeap_swapData(BinaryHeap* heap, const size_t firstIndex, const size_t secondIndex)
{
    void* temp = heap->heapData[firstIndex];
    heap->heapData[firstIndex] = heap->heapData[secondIndex];
    heap->heapData[secondIndex] = temp;
}

void binaryHeap_heapify(BinaryHeap* heap, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < heap->dataCount && heap->compare(heap->heapData[left], heap->heapData[smallest]) < 0)
        smallest = left;
    if (right < heap->dataCount && heap->compare(heap->heapData[right], heap->heapData[smallest]) < 0)
        smallest = right;
    if (smallest != i)
    {
        binaryHeap_swapData(heap, i, smallest);
        binaryHeap_heapify(heap, smallest);
    }
}

void binaryHeap_insert(BinaryHeap* heap, void* node)
{
    if (heap->dataCount == heap->heapSize)
        return;

    heap->dataCount++;
    size_t i = heap->dataCount - 1;
    heap->heapData[i] = node;

    while (i != 0 && heap->compare(heap->heapData[(i - 1) / 2], heap->heapData[i]) > 0)
    {
        binaryHeap_swapData(heap, (i - 1) / 2, i);
        i = (i - 1) / 2;
    }
}

void* binaryHeap_extractMin(BinaryHeap* heap)
{
    if (heap->dataCount <= 0)
        return NULL;
    if (heap->dataCount == 1)
    {
        heap->dataCount--;
        return heap->heapData[0];
    }

    void* root = heap->heapData[0];
    heap->heapData[0] = heap->heapData[heap->dataCount - 1];
    heap->dataCount--;
    binaryHeap_heapify(heap, 0);

    return root;
}

void* binaryHeap_getMin(BinaryHeap* heap)
{
    if (heap->dataCount == 0)
        return NULL;
    return heap->heapData[0];
}

size_t binaryHeap_getSize(BinaryHeap* heap)
{
    return heap->dataCount;
}

void binaryHeap_delete(BinaryHeap* heap)
{
    for (size_t i = 0; i < heap->dataCount; i++)
        heap->destroy(heap->heapData[i]);
    delete[] heap->heapData;
    delete heap;
}