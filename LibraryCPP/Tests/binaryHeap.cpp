#include <iostream>
#include "binaryHeap.h"
#include "huffmanTree.h"

// �������-���������� � ���������� ��� ������������
int testHuffmanNodeComparator(const void* a, const void* b) {
    HuffmanNode* nodeA = (HuffmanNode*)a;
    HuffmanNode* nodeB = (HuffmanNode*)b;
    return (int)(huffman_getNodeWeight(nodeA) - huffman_getNodeWeight(nodeB));
}

void testHuffmanNodeDestructor(void* node) {
    huffman_deleteTree((HuffmanNode*)node);
}

void testBinaryHeap() {
    // ������� ����
    BinaryHeap* heap = binaryHeap_create(10, testHuffmanNodeComparator, testHuffmanNodeDestructor);

    // ���� 1: ������� ��������� � �������� ������������ ��������
    binaryHeap_insert(heap, huffman_createLeafNode('a', 5));
    binaryHeap_insert(heap, huffman_createLeafNode('b', 3));
    binaryHeap_insert(heap, huffman_createLeafNode('c', 8));

    std::cout << "���� 1: ����������� ������� ����� ������� - ";
    HuffmanNode* minNode = (HuffmanNode*)binaryHeap_getMin(heap);
    if (huffman_getNodeChar(minNode) == 'b' && huffman_getNodeWeight(minNode) == 3) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }

    // ���� 2: ���������� ������������ ��������
    binaryHeap_extractMin(heap);
    minNode = (HuffmanNode*)binaryHeap_getMin(heap);
    std::cout << "���� 2: ����������� ������� ����� ���������� - ";
    if (huffman_getNodeChar(minNode) == 'a' && huffman_getNodeWeight(minNode) == 5) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }

    // ���� 3: ������ ����
    std::cout << "���� 3: ������ ���� - ";
    if (binaryHeap_getSize(heap) == 2) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }

    // ������� ����
    huffman_deleteTree(minNode);
    binaryHeap_delete(heap);
}

int main() {
    testBinaryHeap();
    return 0;
}