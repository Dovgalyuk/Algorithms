#include <iostream>
#include "binaryHeap.h"
#include "huffmanTree.h"

int main() {
    // ������� ����
    BinaryHeap* heap = binaryHeap_create(10, huffmanNodeComparator, huffmanNodeDestructor);

    // ���� 1: ������� ��������� � �������� ������������ ��������
    HuffmanNode* nodeA = huffman_createLeafNode('a', 5);
    HuffmanNode* nodeB = huffman_createLeafNode('b', 3);
    HuffmanNode* nodeC = huffman_createLeafNode('c', 8);

    binaryHeap_insert(heap, nodeA);
    binaryHeap_insert(heap, nodeB);
    binaryHeap_insert(heap, nodeC);

    std::cout << "���� 1: ����������� ������� ����� ������� - ";
    HuffmanNode* minNode = (HuffmanNode*)binaryHeap_getMin(heap);
    if (huffman_getNodeChar(minNode) == 'b' && huffman_getNodeWeight(minNode) == 3) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }

    // ���� 2: ���������� ������������ �������� � ��� ��������
    minNode = (HuffmanNode*)binaryHeap_extractMin(heap);
    std::cout << "���� 2: ����������� ������� ����� ���������� - ";
    if (huffman_getNodeChar(minNode) == 'b' && huffman_getNodeWeight(minNode) == 3) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }
    huffman_deleteTree(minNode); // �������� ������������ ����

    // ���� 3: �������� ���������� ������������ ��������
    minNode = (HuffmanNode*)binaryHeap_getMin(heap);
    std::cout << "���� 3: ��������� ����������� ������� - ";
    if (huffman_getNodeChar(minNode) == 'a' && huffman_getNodeWeight(minNode) == 5) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }

    // ���� 4: ������ ���� ����� ���������� ������ ��������
    std::cout << "���� 4: ������ ���� ����� ���������� ������ �������� - ";
    if (binaryHeap_getSize(heap) == 2) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }

    // ������� ����
    binaryHeap_delete(heap);

    return 0;
}