#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue* queue)
{
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    ListItem* tail = queue->list->tail;
    if (tail == nullptr) {
        queue->list->tail = list_insert(queue->list, data);
    } else {
        queue->list->tail = list_insert_after(queue->list, tail, data);
    }
    if (queue->list->head == nullptr) {
        queue->list->head = queue->list->tail;
    }
}

Data queue_get(const Queue* queue)
{
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue* queue)
{
    list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue)
{
    return list_first(queue->list) == nullptr;
}
