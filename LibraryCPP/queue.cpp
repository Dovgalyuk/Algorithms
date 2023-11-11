#include <stdlib.h>
#include "list.h"
#include "queue.h"

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
    list_insert(queue->list, data);
}

Data queue_get(const Queue* queue)
{
    return list_item_data(front);
}

void queue_remove(Queue* queue)
{
    list_erase(queue->list, front);
}

bool queue_empty(const Queue* queue)
{
    return list_get_length(queue->list) == 0;
}
