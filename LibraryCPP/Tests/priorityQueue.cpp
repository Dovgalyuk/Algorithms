#include <iostream>
#include <cassert>
#include "priorityQueue.h"
#include "huffmanTree.h"

void testPriorityQueue() {
    std::cout << "Starting priority queue tests..." << std::endl;

    // Тест создания и удаления очереди
    PriorityQueue* queue = priorityQueue_create(10);
    assert(queue != nullptr);
    std::cout << "Test create: passed" << std::endl;

    // Тест вставки и размера
    HuffmanNode* node1 = huffman_createLeafNode('a', 1);
    priorityQueue_insert(queue, node1);
    assert(priorityQueue_getSize(queue) == 1);
    std::cout << "Test insert and size: passed" << std::endl;

    // Тест возвращаемого значения и удаления
    HuffmanNode* testNode = priorityQueue_getNode(queue);
    assert(huffman_getNodeChar(testNode) == 'a' && huffman_getNodeWeight(testNode) == 1);
    priorityQueue_remove(queue);
    assert(priorityQueue_getSize(queue) == 0);
    std::cout << "Test get and remove: passed" << std::endl;

    // Тест на пустоту очереди
    assert(priorityQueue_empty(queue));
    std::cout << "Test empty: passed" << std::endl;

    priorityQueue_delete(queue);
    std::cout << "Priority queue tests completed successfully." << std::endl;
}

int main() {
    testPriorityQueue();
    return 0;
}