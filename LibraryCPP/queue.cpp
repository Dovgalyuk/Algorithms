#include "queue.h"
#include "list.h"

struct Queue
{
    List *list;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->list = list_create();

    return queue;
}

void queue_delete(Queue *queue)
{
    if (queue == nullptr)
        return;

    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue == nullptr)
        return;

    list_insert_after(queue->list, list_last(queue->list), data);
}

Data queue_get(const Queue *queue)
{
    if (queue == nullptr || queue_empty(queue))
        return 0;

    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue)
{
    if (queue == nullptr || queue_empty(queue))
        return;

    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    if (queue == nullptr)
        return true;

    return list_first(queue->list) == nullptr;
}
