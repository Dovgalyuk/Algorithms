#include "huffmanTree.h"
#include <cassert>
#include <iostream>

void test_createAndDeleteNodes() {
    // Создание листовых узлов
    HuffmanNode* leafA = huffman_createLeafNode('A', 3);
    HuffmanNode* leafB = huffman_createLeafNode('B', 2);

    // Проверка свойств листовых узлов
    assert(huffman_nodeIsLeaf(leafA));
    assert(huffman_getNodeChar(leafA) == 'A');
    assert(huffman_getNodeWeight(leafA) == 3);

    assert(huffman_nodeIsLeaf(leafB));
    assert(huffman_getNodeChar(leafB) == 'B');
    assert(huffman_getNodeWeight(leafB) == 2);

    // Создание внутреннего узла
    HuffmanNode* internalNode = huffman_createInternalNode(leafA, leafB);

    // Проверка свойств внутреннего узла
    assert(!huffman_nodeIsLeaf(internalNode));
    assert(huffman_getLeftNode(internalNode) == leafA);
    assert(huffman_getRightNode(internalNode) == leafB);
    assert(huffman_getNodeWeight(internalNode) == 5);

    // Удаление дерева
    huffman_deleteTree(internalNode);
}

int main() {
    test_createAndDeleteNodes();
    std::cout << "Test completed!" << std::endl;
    return 0;
}