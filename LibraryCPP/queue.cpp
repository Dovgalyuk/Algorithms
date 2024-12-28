#include "queue.h"
#include <cstddef> // для NULL

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue* queue) {
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, int data) {
    if (!queue->list) return;

    // Добавляем элемент в конец очереди
    if (list_first(queue->list) == nullptr) {
        list_insert(queue->list, data); // Если очередь пуста, добавляем в начало
    }
    else {
        ListItem* tail = queue->list->tail;
        list_insert_after(queue->list, tail, data);
    }
}

int queue_get(const Queue* queue) {
    if (queue_empty(queue)) return 0;

    // Возвращаем данные первого элемента
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue* queue) {
    if (!queue->list || queue_empty(queue)) return;

    // Удаляем первый элемент списка
    list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue) {
    return list_first(queue->list) == nullptr;
}