#include "queue.h"
#include "list.h"

struct Queue
{
    List* list = list_create();
    ListItem* last = nullptr;
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
}

Data queue_get(const Queue *queue)
{
    return (Data)0;
}

void queue_remove(Queue *queue)
{
}

bool queue_empty(const Queue *queue)
{
    return true;
}
