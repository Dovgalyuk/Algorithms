#include "queue.h"
#include "list.h"

struct Queue
{
    List *items;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->items = list_create();
    return queue;
    // return new Queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    list_delete(queue->items);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    list_insert_after(queue->items, list_last(queue->items), data);
}

Data queue_get(const Queue *queue)
{
    return list_item_data(list_first(queue->items));
    // return (Data)0;
}

void queue_remove(Queue *queue)
{
    list_erase_first(queue->items);
}

bool queue_empty(const Queue *queue)
{
    return list_first(queue->items) == nullptr;
    // return true;
}
