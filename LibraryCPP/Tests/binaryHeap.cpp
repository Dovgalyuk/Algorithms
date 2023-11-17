#include <iostream>
#include "binaryHeap.h"
#include "huffmanTree.h"

void testBinaryHeap() {
    // Создаем кучу
    BinaryHeap* heap = binaryHeap_create(10);

    // Тест 1: Вставка элементов и проверка минимального элемента
    binaryHeap_insert(heap, huffman_createLeafNode('a', 5));
    binaryHeap_insert(heap, huffman_createLeafNode('b', 3));
    binaryHeap_insert(heap, huffman_createLeafNode('c', 8));

    std::cout << "Тест 1: Минимальный элемент после вставки - ";
    if (binaryHeap_getNodeSymbol(heap) == 'b' && binaryHeap_getNodeWeight(heap) == 3) {
        std::cout << "Успех" << std::endl;
    }
    else {
        std::cout << "Ошибка" << std::endl;
    }

    // Тест 2: Извлечение минимального элемента
    binaryHeap_extractMin(heap);
    std::cout << "Тест 2: Минимальный элемент после извлечения - ";
    if (binaryHeap_getNodeSymbol(heap) == 'a' && binaryHeap_getNodeWeight(heap) == 5) {
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
    binaryHeap_delete(heap);
}

int main() {
    testBinaryHeap();
    return 0;
}