#include "queue.h"
#include "list.h"

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
    list_delete(queue->list);
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->tail == nullptr) {
        list_insert(queue->list, data);
        queue->tail = list_first(queue->list);
    }
    else {
        list_insert_after(queue->list, queue->tail, data);
        queue->tail = list_item_next(queue->tail);
    }
}

Data queue_get(const Queue *queue)
{
    ListItem* first = list_first(queue->list);
    return list_item_data(first);
}

void queue_remove(Queue *queue)
{
    list_erase_first(queue->list);
    if (list_first(queue->list) == nullptr) {
        queue->tail = nullptr;
    }
}

bool queue_empty(const Queue *queue)
{
    return list_first(queue->list) == nullptr;
}
