#include "queue.h"
#include "list.h"

#include <stdexcept>

struct Queue
{
    List *items = list_create();

    ~Queue()
    {
        list_delete(items);
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    list_insert_after(queue->items, list_last(queue->items), data);
}

Data queue_get(const Queue *queue)
{
    ListItem *first = list_first(queue->items);
    if (!first)
        throw std::out_of_range("Queue is empty");

    return list_item_data(first);
}

void queue_remove(Queue *queue)
{
    list_erase_first(queue->items);
}

bool queue_empty(const Queue *queue)
{
    return list_first(queue->items) == nullptr;
}
