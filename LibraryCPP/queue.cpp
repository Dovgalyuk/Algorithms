#include "queue.h"
#include "list.h"
#include <cstddef>

struct Queue
{
    List* list;
};

Queue *queue_create()
{
    Queue* q = new Queue();
    q->list = list_create();
    return q;
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
        list_insert_after(queue->list, list_last(queue->list), data);
    }
}

Data queue_get(const Queue *queue)
{
    if (!queue || !list_first(queue->list)) return (Data)0;
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue)
{
    if (queue) {
        list_erase_first(queue->list);
    }
}

bool queue_empty(const Queue *queue)
{
    return !queue || list_first(queue->list) == NULL;
}