#include "queue.h"
#include <iostream>
#include <vector>

using namespace std;

struct Queue {
    vector<int> data;  // Используем стандартный вектор для хранения элементов
};

Queue* queue_create() {
    return new Queue;
}

void queue_delete(Queue* queue) {
    delete queue;
}

void queue_insert(Queue* queue, int data) {
    queue->data.push_back(data);  // Добавляем элемент в конец очереди
}

int queue_get(const Queue* queue) {
    if (queue->data.empty()) {
        cerr << "Ошибка: очередь пуста!" << endl;
        return -1;  // Ошибка
    }
    return queue->data.front();  // Возвращаем первый элемент очереди
}

void queue_remove(Queue* queue) {
    if (!queue->data.empty()) {
        queue->data.erase(queue->data.begin());  // Удаляем первый элемент
    }
}

bool queue_empty(const Queue* queue) {
    return queue->data.empty();  // Проверка, пуста ли очередь
}
