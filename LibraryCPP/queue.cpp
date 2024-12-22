#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
};

// Создание новой очереди
Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    return queue;
}

// Удаление очереди и всех её элементов
void queue_delete(Queue *queue)
{
    if (queue) {
        list_delete(queue->list);
        delete queue;
    }
}

// Вставка нового элемента в очередь
void queue_insert(Queue *queue, Data data)
{
    if (queue) {
        list_insert(queue->list, data);  // Вставка в конец списка
    }
}

// Получение первого элемента из очереди
Data queue_get(const Queue *queue)
{
    if (!queue || !list_first(queue->list)) {
        // Если очередь пуста, возвращаем "пустой" объект Data
        return Data();
    }
    return list_item_data(list_first(queue->list));
}

// Удаление первого элемента из очереди
void queue_remove(Queue *queue)
{
    if (queue) {
        list_erase_first(queue->list);
    }
}

// Проверка, пуста ли очередь
bool queue_empty(const Queue *queue)
{
    return queue ? list_first(queue->list) == nullptr : true;
}
