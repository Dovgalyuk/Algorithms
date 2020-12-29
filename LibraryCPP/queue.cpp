#include <stdlib.h>
#include "queue.h"
#include "list.h"
#include <iostream>

struct Queue
{
    List* lst;
    ListItem* last;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->lst = list_create();
    queue->last = NULL;
    return queue;
}

void queue_delete(Queue* queue)
{
    list_delete(queue->lst);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (!queue->last) {
        queue->last = list_insert(queue->lst, data);
    }
    else
    {
        queue->last = list_insert_after(queue->lst, queue->last, data);
    }
}

Data queue_get(const Queue* queue)
{
    return list_item_data(list_first(queue->lst));
}

void queue_remove(Queue* queue)
{
    list_erase(queue->lst, list_first(queue->lst));
    if (queue_empty(queue))
        queue->last = NULL;
}

bool queue_empty(const Queue* queue)
{
    return (list_first(queue->lst) != NULL) ? false : true;
}