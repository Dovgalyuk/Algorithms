#include <iostream>
#include "priorityQueue.h"
#include "huffmanTree.h"

void testPriorityQueue() {
    // ������� ������� � �����������
    PriorityQueue* queue = priorityQueue_create(10);

    // ���������, ����� �� ������� ����� ����� ��������
    std::cout << "����: ������� ������ ���� ������ ����� �������� - " << (priorityQueue_empty(queue) ? "�����" : "������") << std::endl;

    // ������� ��������� ����� Huffman
    HuffmanNode* node1 = huffman_createLeafNode('a', 5);
    HuffmanNode* node2 = huffman_createLeafNode('b', 3);
    HuffmanNode* node3 = huffman_createLeafNode('c', 8);

    // ��������� ���� � �������
    priorityQueue_insert(queue, node1);
    priorityQueue_insert(queue, node2);
    priorityQueue_insert(queue, node3);
    // ��������� ������ ������� ����� ������� �����
    std::cout << "����: ������ ������� ����� ���������� 3 ����� ������ ���� 3 - " << (priorityQueue_getSize(queue) == 3 ? "�����" : "������") << std::endl;

    // ��������� � ��������� ���� � ���������� ������� (������� node2, ����� node1, ����� node3)
    HuffmanNode* extractedNode = priorityQueue_getNode(queue);
    std::cout << "����: ������ ����������� ���� ������ ����� ������ 'b' � ��� 3 - " << (huffman_getNodeChar(extractedNode) == 'b' && huffman_getNodeWeight(extractedNode) == 3 ? "�����" : "������") << std::endl;
    priorityQueue_remove(queue);

    extractedNode = priorityQueue_getNode(queue);
    std::cout << "����: ������ ����������� ���� ������ ����� ������ 'a' � ��� 5 - " << (huffman_getNodeChar(extractedNode) == 'a' && huffman_getNodeWeight(extractedNode) == 5 ? "�����" : "������") << std::endl;
    priorityQueue_remove(queue);

    extractedNode = priorityQueue_getNode(queue);
    std::cout << "����: ������ ����������� ���� ������ ����� ������ 'c' � ��� 8 - " << (huffman_getNodeChar(extractedNode) == 'c' && huffman_getNodeWeight(extractedNode) == 8 ? "�����" : "������") << std::endl;
    priorityQueue_remove(queue);

    // ���������, ����� �� ������� ����� ���������� ���� �����
    std::cout << "����: ������� ������ ���� ������ ����� ���������� ���� ����� - " << (priorityQueue_empty(queue) ? "�����" : "������") << std::endl;

    // ������� �������
    priorityQueue_delete(queue);
}

int main() {
    testPriorityQueue();
    return 0;
}