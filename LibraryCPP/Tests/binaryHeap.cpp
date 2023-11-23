#include <iostream>
#include "binaryHeap.h"
#include "huffmanTree.h"

// Функция-компаратор и деструктор для тестирования
int testHuffmanNodeComparator(const void* a, const void* b) {
    HuffmanNode* nodeA = (HuffmanNode*)a;
    HuffmanNode* nodeB = (HuffmanNode*)b;
    return (int)(huffman_getNodeWeight(nodeA) - huffman_getNodeWeight(nodeB));
}

void testHuffmanNodeDestructor(void* node) {
    huffman_deleteTree((HuffmanNode*)node);
}

void testBinaryHeap() {
    // Создаем кучу
    BinaryHeap* heap = binaryHeap_create(10, testHuffmanNodeComparator, testHuffmanNodeDestructor);

    // Тест 1: Вставка элементов и проверка минимального элемента
    binaryHeap_insert(heap, huffman_createLeafNode('a', 5));
    binaryHeap_insert(heap, huffman_createLeafNode('b', 3));
    binaryHeap_insert(heap, huffman_createLeafNode('c', 8));

    std::cout << "Тест 1: Минимальный элемент после вставки - ";
    HuffmanNode* minNode = (HuffmanNode*)binaryHeap_getMin(heap);
    if (huffman_getNodeChar(minNode) == 'b' && huffman_getNodeWeight(minNode) == 3) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }

    // Тест 2: Извлечение минимального элемента
    binaryHeap_extractMin(heap);
    minNode = (HuffmanNode*)binaryHeap_getMin(heap);
    std::cout << "Тест 2: Минимальный элемент после извлечения - ";
    if (huffman_getNodeChar(minNode) == 'a' && huffman_getNodeWeight(minNode) == 5) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }

    // Тест 3: Размер кучи
    std::cout << "Тест 3: Размер кучи - ";
    if (binaryHeap_getSize(heap) == 2) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }

    // Очищаем кучу
    huffman_deleteTree(minNode);
    binaryHeap_delete(heap);
}

int main() {
    testBinaryHeap();
    return 0;
}