#include <iostream>
#include "huffmanTree.h"

void testHuffmanTree() {
    setlocale(LC_ALL, "ru");
    // ���� 1: �������� � �������� ��������� ����
    HuffmanNode* leafNode = huffman_createLeafNode('a', 5);
    std::cout << "���� 1: �������� ���� - ";
    if (huffman_getNodeChar(leafNode) == 'a' && huffman_getNodeWeight(leafNode) == 5 && huffman_nodeIsLeaf(leafNode)) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }

    // ���� 2: �������� � �������� ����������� ����
    HuffmanNode* internalNode = huffman_createInternalNode(leafNode, NULL);
    std::cout << "���� 2: ���������� ���� - ";
    if (huffman_getNodeWeight(internalNode) == 5 && !huffman_nodeIsLeaf(internalNode)) {
        std::cout << "�����" << std::endl;
    }
    else {
        std::cout << "������" << std::endl;
    }

    // ���� 3: �������� ������ � �������� �� ������ ������
    huffman_deleteTree(internalNode);
    std::cout << "���� 3: �������� ������ (��������� ������ ������ � ������� ������������)" << std::endl;
}

int main() {
    testHuffmanTree();
    return 0;
}