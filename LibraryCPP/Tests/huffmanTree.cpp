#include <iostream>
#include "huffmanTree.h"

void testHuffmanTree() {
    setlocale(LC_ALL, "ru");
    // Тест 1: Создание и проверка листового узла
    HuffmanNode* leafNode = huffman_createLeafNode('a', 5);
    std::cout << "Тест 1: Листовой узел - ";
    if (huffman_getNodeChar(leafNode) == 'a' && huffman_getNodeWeight(leafNode) == 5 && huffman_nodeIsLeaf(leafNode)) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }

    // Тест 2: Создание и проверка внутреннего узла
    HuffmanNode* internalNode = huffman_createInternalNode(leafNode, NULL);
    std::cout << "Тест 2: Внутренний узел - ";
    if (huffman_getNodeWeight(internalNode) == 5 && !huffman_nodeIsLeaf(internalNode)) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }

    // Тест 3: Удаление дерева и проверка на утечку памяти
    huffman_deleteTree(internalNode);
    std::cout << "Тест 3: Удаление дерева (проверьте утечки памяти с помощью инструментов)" << std::endl;
}

int main() {
    testHuffmanTree();
    return 0;
}