#include "queue.h"
#include "list.h"
#include <cstddef>
struct Queue
{
    List* list;
    size_t head;
    size_t tail;

    ~Queue() {
        list_delete(list);
    }
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->tail = -1;
    return queue;
}

void queue_delete(Queue *queue)
{
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    list_insert(queue->list, data);
    queue->tail++;
}

Data queue_get(const Queue *queue)
{
    if (!queue_empty(queue))
    {
        return list_item_data(list_item_next(list_first(queue->list)));
    }
    else
    {
        return Data();
    }
}

void queue_remove(Queue* queue)
{
    if (!queue_empty(queue))
    {
        list_erase(queue->list, list_item_next(list_first(queue->list)));
        queue->tail--;
    }
}

bool queue_empty(const Queue *queue)
{
  return queue->tail == -1;
}

