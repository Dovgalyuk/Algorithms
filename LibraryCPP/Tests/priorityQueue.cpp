#include <iostream>
#include "priorityQueue.h"
#include "huffmanTree.h"

void testPriorityQueue() {
    // Создаем очередь с приоритетом
    PriorityQueue* queue = priorityQueue_create(10);

    // Создаем несколько узлов Huffman
    HuffmanNode* node1 = huffman_createLeafNode('a', 5);
    HuffmanNode* node2 = huffman_createLeafNode('b', 3);
    HuffmanNode* node3 = huffman_createLeafNode('c', 8);

    // Вставляем узлы в очередь
    priorityQueue_insert(queue, node1);
    priorityQueue_insert(queue, node2);
    priorityQueue_insert(queue, node3);

    // Извлекаем и проверяем узлы в правильном порядке, затем удаляем их
    HuffmanNode* extractedNode = priorityQueue_extractMin(queue);
    std::cout << "Тест: Первый извлеченный узел должен иметь символ 'b' и вес 3 - ";
    std::cout << (huffman_getNodeChar(extractedNode) == 'b' && huffman_getNodeWeight(extractedNode) == 3 ? "Успех" : "Ошибка") << std::endl;
    huffman_deleteTree(extractedNode);

    extractedNode = priorityQueue_extractMin(queue);
    std::cout << "Тест: Второй извлеченный узел должен иметь символ 'a' и вес 5 - ";
    std::cout << (huffman_getNodeChar(extractedNode) == 'a' && huffman_getNodeWeight(extractedNode) == 5 ? "Успех" : "Ошибка") << std::endl;
    huffman_deleteTree(extractedNode);

    extractedNode = priorityQueue_extractMin(queue);
    std::cout << "Тест: Третий извлеченный узел должен иметь символ 'c' и вес 8 - ";
    std::cout << (huffman_getNodeChar(extractedNode) == 'c' && huffman_getNodeWeight(extractedNode) == 8 ? "Успех" : "Ошибка") << std::endl;
    huffman_deleteTree(extractedNode);

    // Проверяем, пуста ли очередь после извлечения всех узлов
    std::cout << "Тест: Очередь должна быть пустой после извлечения всех узлов - ";
    std::cout << (priorityQueue_empty(queue) ? "Успех" : "Ошибка") << std::endl;

    // Удаляем очередь
    priorityQueue_delete(queue);
}

int main() {
    testPriorityQueue();
    return 0;
}