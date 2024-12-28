#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

struct Queue {
    List* list;
};

// Создает новую очередь
Queue* queue_create();

// Удаляет очередь
void queue_delete(Queue* queue);

// Добавляет элемент в конец очереди
void queue_insert(Queue* queue, int data);

// Возвращает первый элемент очереди
int queue_get(const Queue* queue);

// Удаляет первый элемент очереди
void queue_remove(Queue* queue);

// Проверяет, пуста ли очередь
bool queue_empty(const Queue* queue);

#endif // QUEUE_H
