#include <iostream>
#include "binaryHeap.h"
#include "huffmanTree.h"

int main() {
    // Создаем кучу
    BinaryHeap* heap = binaryHeap_create(10, huffmanNodeComparator, huffmanNodeDestructor);

    // Тест 1: Вставка элементов и проверка минимального элемента
    HuffmanNode* nodeA = huffman_createLeafNode('a', 5);
    HuffmanNode* nodeB = huffman_createLeafNode('b', 3);
    HuffmanNode* nodeC = huffman_createLeafNode('c', 8);

    binaryHeap_insert(heap, nodeA);
    binaryHeap_insert(heap, nodeB);
    binaryHeap_insert(heap, nodeC);

    std::cout << "Тест 1: Минимальный элемент после вставки - ";
    HuffmanNode* minNode = (HuffmanNode*)binaryHeap_getMin(heap);
    if (huffman_getNodeChar(minNode) == 'b' && huffman_getNodeWeight(minNode) == 3) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }

    // Тест 2: Извлечение минимального элемента и его удаление
    minNode = (HuffmanNode*)binaryHeap_extractMin(heap);
    std::cout << "Тест 2: Минимальный элемент после извлечения - ";
    if (huffman_getNodeChar(minNode) == 'b' && huffman_getNodeWeight(minNode) == 3) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }
    huffman_deleteTree(minNode); // Удаление извлеченного узла

    // Тест 3: Проверка следующего минимального элемента
    minNode = (HuffmanNode*)binaryHeap_getMin(heap);
    std::cout << "Тест 3: Следующий минимальный элемент - ";
    if (huffman_getNodeChar(minNode) == 'a' && huffman_getNodeWeight(minNode) == 5) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }

    // Тест 4: Размер кучи после извлечения одного элемента
    std::cout << "Тест 4: Размер кучи после извлечения одного элемента - ";
    if (binaryHeap_getSize(heap) == 2) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }

    // Очищаем кучу
    binaryHeap_delete(heap);

    return 0;
}