#include "queue.h"
#include "list.h"

struct Queue {
    List* list;
    ListItem* tail;
};

Queue* queue_create() 
{
    Queue* queue = new Queue; 
    queue->list = list_create();
    queue->tail = nullptr;
    return queue;
}

void queue_delete(Queue* queue) 
{
    if (!queue) return;

    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    if (!queue) return;

    if (!queue->tail) 
    {
        queue->tail = list_insert(queue->list, data);
    } 
    else 
    {
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    }
}

Data queue_get(const Queue *queue)
{
    if (queue != nullptr && list_first(queue->list) != nullptr) 
    {
        return list_item_data(list_first(queue->list));
    }
    return Data();
}

void queue_remove(Queue* queue) 
{
    if (!queue || queue_empty(queue)) return;

    if (list_first(queue->list) == queue->tail) 
    {
        queue->tail = nullptr;
    }

    list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue) 
{
    return !queue || list_first(queue->list) == nullptr;
}
