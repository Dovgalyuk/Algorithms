#include "queue.h"
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct Queue
{
    List* list;
    ListItem* tail;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->tail = nullptr;
    return queue;
}

void queue_delete(Queue *queue)
{
    if (queue) {
        list_delete(queue->list);
        delete queue;
    }
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;
    
    if (queue->tail) {
        // Добавляем в конец
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    } else {
        // Очередь пуста
        ListItem* new_item = list_insert(queue->list, data);
        queue->tail = new_item;
    }
    
    // Если после вставки tail указывает на элемент без следующего, значит это конец
    if (queue->tail) {
        ListItem* current = queue->tail;
        while (current && current->next) {
            current = current->next;
        }
        queue->tail = current;
    }
}

Data queue_get(const Queue *queue)
{
    if (queue && list_first(queue->list)) {
        return list_item_data(list_first(queue->list));
    }
    return Data(0);
}

void queue_remove(Queue *queue)
{
    if (!queue) return;
    
    ListItem* first = list_first(queue->list);
    if (!first) return;
    
    // Если удаляем единственный элемент
    if (first == queue->tail) {
        queue->tail = nullptr;
    }
    
    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    return !queue || list_first(queue->list) == nullptr;
}