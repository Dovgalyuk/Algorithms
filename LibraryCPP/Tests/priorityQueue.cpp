#include <iostream>
#include "priorityQueue.h"
#include "huffmanTree.h"

void testPriorityQueue() {
    // ������� ������� � �����������
    PriorityQueue* queue = priorityQueue_create(10);

    // ������� ��������� ����� Huffman
    HuffmanNode* node1 = huffman_createLeafNode('a', 5);
    HuffmanNode* node2 = huffman_createLeafNode('b', 3);
    HuffmanNode* node3 = huffman_createLeafNode('c', 8);

    // ��������� ���� � �������
    priorityQueue_insert(queue, node1);
    priorityQueue_insert(queue, node2);
    priorityQueue_insert(queue, node3);

    // ��������� � ��������� ���� � ���������� �������, ����� ������� ��
    HuffmanNode* extractedNode = priorityQueue_extractMin(queue);
    std::cout << "����: ������ ����������� ���� ������ ����� ������ 'b' � ��� 3 - ";
    std::cout << (huffman_getNodeChar(extractedNode) == 'b' && huffman_getNodeWeight(extractedNode) == 3 ? "�����" : "������") << std::endl;
    huffman_deleteTree(extractedNode);

    extractedNode = priorityQueue_extractMin(queue);
    std::cout << "����: ������ ����������� ���� ������ ����� ������ 'a' � ��� 5 - ";
    std::cout << (huffman_getNodeChar(extractedNode) == 'a' && huffman_getNodeWeight(extractedNode) == 5 ? "�����" : "������") << std::endl;
    huffman_deleteTree(extractedNode);

    extractedNode = priorityQueue_extractMin(queue);
    std::cout << "����: ������ ����������� ���� ������ ����� ������ 'c' � ��� 8 - ";
    std::cout << (huffman_getNodeChar(extractedNode) == 'c' && huffman_getNodeWeight(extractedNode) == 8 ? "�����" : "������") << std::endl;
    huffman_deleteTree(extractedNode);

    // ���������, ����� �� ������� ����� ���������� ���� �����
    std::cout << "����: ������� ������ ���� ������ ����� ���������� ���� ����� - ";
    std::cout << (priorityQueue_empty(queue) ? "�����" : "������") << std::endl;

    // ������� �������
    priorityQueue_delete(queue);
}

int main() {
    testPriorityQueue();
    return 0;
}