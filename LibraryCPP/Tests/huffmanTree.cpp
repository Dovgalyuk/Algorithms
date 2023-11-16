#include "huffmanTree.h"
#include <cassert>
#include <iostream>

void test_createAndDeleteNodes() {
    // �������� �������� �����
    HuffmanNode* leafA = huffman_createLeafNode('A', 3);
    HuffmanNode* leafB = huffman_createLeafNode('B', 2);

    // �������� ������� �������� �����
    assert(huffman_nodeIsLeaf(leafA));
    assert(huffman_getNodeChar(leafA) == 'A');
    assert(huffman_getNodeWeight(leafA) == 3);

    assert(huffman_nodeIsLeaf(leafB));
    assert(huffman_getNodeChar(leafB) == 'B');
    assert(huffman_getNodeWeight(leafB) == 2);

    // �������� ����������� ����
    HuffmanNode* internalNode = huffman_createInternalNode(leafA, leafB);

    // �������� ������� ����������� ����
    assert(!huffman_nodeIsLeaf(internalNode));
    assert(huffman_getLeftNode(internalNode) == leafA);
    assert(huffman_getRightNode(internalNode) == leafB);
    assert(huffman_getNodeWeight(internalNode) == 5);

    // �������� ������
    huffman_deleteTree(internalNode);
}

int main() {
    test_createAndDeleteNodes();
    std::cout << "Test completed!" << std::endl;
    return 0;
}