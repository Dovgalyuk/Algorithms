#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
    ListItem* last;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->last = nullptr;
    return queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    if (!queue) return;
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;

    queue->last = list_insert_after(queue->list, queue->last, data);
}

Data queue_get(const Queue *queue)
{
    if (!queue) return (Data)0;
    ListItem* first = list_first(queue->list);
    if (!first) return (Data)0;
    return list_item_data(first);
}

void queue_remove(Queue *queue)
{
    if (!queue) return;

    ListItem* first = list_first(queue->list);
    if (!first) return;

    if (first == queue->last)
    {
        queue->last = nullptr;
    }
    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    if (!queue) return true;
    return list_first(queue->list) == nullptr;
}
