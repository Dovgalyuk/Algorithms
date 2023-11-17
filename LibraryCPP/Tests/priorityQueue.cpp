#include <iostream>
#include <cassert>
#include "priorityQueue.h"
#include "huffmanTree.h"

void testPriorityQueue() {
    std::cout << "Starting priority queue tests..." << std::endl;

    // ���� �������� � �������� �������
    PriorityQueue* queue = priorityQueue_create(10);
    assert(queue != nullptr);
    std::cout << "Test create: passed" << std::endl;

    // ���� ������� � �������
    HuffmanNode* node1 = huffman_createLeafNode('a', 1);
    priorityQueue_insert(queue, node1);
    assert(priorityQueue_getSize(queue) == 1);
    huffman_deleteTree(node1);
    std::cout << "Test insert and size: passed" << std::endl;

    // ���� ������������� �������� � ��������
    assert(huffman_getNodeChar(priorityQueue_getNode(queue)) == 'a' && huffman_getNodeWeight(priorityQueue_getNode(queue)) == 1);
    priorityQueue_remove(queue);
    assert(priorityQueue_getSize(queue) == 0);
    std::cout << "Test get and remove: passed" << std::endl;

    // ���� �� ������� �������
    assert(priorityQueue_empty(queue));
    std::cout << "Test empty: passed" << std::endl;

    priorityQueue_delete(queue);
    std::cout << "Priority queue tests completed successfully." << std::endl;
}

int main() {
    testPriorityQueue();
    return 0;
}