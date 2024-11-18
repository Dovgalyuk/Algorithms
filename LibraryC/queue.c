#include <stdlib.h>

#include "queue.h"

typedef struct Queue
{
    List* list;
    ListItem* last;
    FFree* destructor;
} Queue;

Queue *queue_create(FFree f)
{
    Queue* new_queue = malloc(sizeof(Queue));
    new_queue->list = list_create(f);
    new_queue->last = NULL;
    new_queue->destructor = f;
    return new_queue;
}

void queue_delete(Queue *queue)
{
    list_delete(queue->list);
    free(queue);
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue->last)
       queue->last = list_insert(queue->list, data);
    else
        queue->last = list_insert_after(queue->list, queue->last, data);
}

Data queue_get(const Queue *queue)
{
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue)
{
    list_erase_first(queue->list);
    if (!list_first(queue->list))
        queue->last = NULL;
}

bool queue_empty(const Queue *queue)
{
    return queue->last ? false : true;
}
