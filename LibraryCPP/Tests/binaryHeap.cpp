#include <iostream>
#include "binaryHeap.h"
#include "huffmanTree.h"

void testBinaryHeap() {
    // ������� ����
    BinaryHeap* heap = binaryHeap_create(10);

    // ���� 1: ������� ��������� � �������� ������������ ��������
    binaryHeap_insert(heap, huffman_createLeafNode('a', 5));
    binaryHeap_insert(heap, huffman_createLeafNode('b', 3));
    binaryHeap_insert(heap, huffman_createLeafNode('c', 8));

    std::cout << "���� 1: ����������� ������� ����� ������� - ";
    if (binaryHeap_getNodeSymbol(heap) == 'b' && binaryHeap_getNodeWeight(heap) == 3) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }

    // ���� 2: ���������� ������������ ��������
    binaryHeap_extractMin(heap);
    std::cout << "���� 2: ����������� ������� ����� ���������� - ";
    if (binaryHeap_getNodeSymbol(heap) == 'a' && binaryHeap_getNodeWeight(heap) == 5) {
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
    binaryHeap_delete(heap);
}

int main() {
    testBinaryHeap();
    return 0;
}