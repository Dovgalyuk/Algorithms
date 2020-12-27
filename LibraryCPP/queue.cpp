#include <stdlib.h>
#include "queue.h"
#include "list.h"
#include <iostream>

struct Queue
{
    List* lst;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->lst = list_create();
    return queue;
}

void queue_delete(Queue* queue)
{
    list_delete(queue->lst);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    ListItem* current = list_first(queue->lst);
    while (list_item_next(current))
        current = list_item_next(current);
    if (current)
        list_insert_after(queue->lst, current, data);
    else
        list_insert(queue->lst, data);
}

Data queue_get(const Queue* queue)
{
    return list_item_data(list_first(queue->lst));
}

void queue_remove(Queue* queue)
{
    list_erase(queue->lst, list_first(queue->lst));
}

bool queue_empty(const Queue* queue)
{
    return (list_first(queue->lst) != NULL) ? false : true;
}