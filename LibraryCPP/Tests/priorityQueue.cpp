#include <iostream>
#include "priorityQueue.h"
#include "huffmanTree.h"

void testPriorityQueue() {
    // Создаем очередь с приоритетом
    PriorityQueue* queue = priorityQueue_create(10);

    // Проверяем, пуста ли очередь сразу после создания
    std::cout << "Тест: Очередь должна быть пустой после создания - " << (priorityQueue_empty(queue) ? "Успех" : "Ошибка") << std::endl;

    // Создаем несколько узлов Huffman
    HuffmanNode* node1 = huffman_createLeafNode('a', 5);
    HuffmanNode* node2 = huffman_createLeafNode('b', 3);
    HuffmanNode* node3 = huffman_createLeafNode('c', 8);

    // Вставляем узлы в очередь
    priorityQueue_insert(queue, node1);
    priorityQueue_insert(queue, node2);
    priorityQueue_insert(queue, node3);
    // Проверяем размер очереди после вставки узлов
    std::cout << "Тест: Размер очереди после добавления 3 узлов должен быть 3 - " << (priorityQueue_getSize(queue) == 3 ? "Успех" : "Ошибка") << std::endl;

    // Извлекаем и проверяем узлы в правильном порядке (сначала node2, затем node1, потом node3)
    HuffmanNode* extractedNode = priorityQueue_getNode(queue);
    std::cout << "Тест: Первый извлеченный узел должен иметь символ 'b' и вес 3 - " << (huffman_getNodeChar(extractedNode) == 'b' && huffman_getNodeWeight(extractedNode) == 3 ? "Успех" : "Ошибка") << std::endl;
    priorityQueue_remove(queue);

    extractedNode = priorityQueue_getNode(queue);
    std::cout << "Тест: Второй извлеченный узел должен иметь символ 'a' и вес 5 - " << (huffman_getNodeChar(extractedNode) == 'a' && huffman_getNodeWeight(extractedNode) == 5 ? "Успех" : "Ошибка") << std::endl;
    priorityQueue_remove(queue);

    extractedNode = priorityQueue_getNode(queue);
    std::cout << "Тест: Третий извлеченный узел должен иметь символ 'c' и вес 8 - " << (huffman_getNodeChar(extractedNode) == 'c' && huffman_getNodeWeight(extractedNode) == 8 ? "Успех" : "Ошибка") << std::endl;
    priorityQueue_remove(queue);

    // Проверяем, пуста ли очередь после извлечения всех узлов
    std::cout << "Тест: Очередь должна быть пустой после извлечения всех узлов - " << (priorityQueue_empty(queue) ? "Успех" : "Ошибка") << std::endl;

    // Удаляем очередь
    priorityQueue_delete(queue);
}

int main() {
    testPriorityQueue();
    return 0;
}