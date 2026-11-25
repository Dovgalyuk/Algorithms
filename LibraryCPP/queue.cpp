#include "queue.h"
#include "list.h"
#include <stdexcept>

struct Queue
{
    List *list;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    try {
        queue->list = list_create();
    } catch (...) {
        delete queue;
        throw;
    }
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
    if (!queue) throw std::invalid_argument("Queue is null");
    list_insert_after(queue->list, list_last(queue->list), data);
}

Data queue_get(const Queue *queue)
{
    if (!queue) throw std::invalid_argument("Queue is null");
    ListItem* first = list_first(queue->list);
    if (!first) throw std::out_of_range("Queue is empty");
    return list_item_data(first);
}

void queue_remove(Queue *queue)
{
    if (!queue) throw std::invalid_argument("Queue is null");
    if (queue_empty(queue)) throw std::out_of_range("Queue is empty");
    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    if (!queue) throw std::invalid_argument("Queue is null");
    return list_first(queue->list) == nullptr;
}
