#include <stdlib.h>
#include "queue.h"
#include "list.h"
#include <iostream>

struct Queue
{
    List* lst;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->lst = list_create();
    return queue;
}

void queue_delete(Queue *queue)
{
    list_delete(queue->lst);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    list_insert(queue->lst, data);
}

Data queue_get(const Queue *queue)
{
    ListItem* currect = list_first(queue->lst);
    while (list_item_next(currect))
    {
        currect = list_item_next(currect);
    }
    return list_item_data(currect);
}

void queue_remove(Queue *queue)
{
    ListItem* currect = list_first(queue->lst);
    ListItem* last = currect;
    while (list_item_next(currect))
    {
        last = currect;
        currect = list_item_next(currect);
    }

    list_erase_next(queue->lst, last);
}

bool queue_empty(const Queue* queue)
{
    return (list_first(queue->lst)!= NULL) ? false : true;
}
