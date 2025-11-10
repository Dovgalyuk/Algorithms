#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
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
    if (queue) {
        // Для очереди вставляем в конец
        if (list_first(queue->list) == nullptr) {
            list_insert(queue->list, data);
        } else {
            // Находим последний элемент
            ListItem* last = list_first(queue->list);
            while (list_item_next(last)) {
                last = list_item_next(last);
            }
            list_insert_after(queue->list, last, data);
        }
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
    if (queue) {
        list_erase_first(queue->list);
    }
}

bool queue_empty(const Queue *queue)
{
    return !queue || list_first(queue->list) == nullptr;
}