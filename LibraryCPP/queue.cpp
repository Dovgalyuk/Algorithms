#include <stdlib.h>
#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
    ListItem* front;
    size_t length;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->front = nullptr;
    queue->length = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    ListItem* elem = list_insert(queue->list, data);
    if (queue->length == 0)
    {
        queue->front = elem;
    }
    
    queue->length++;
}

Data queue_get(const Queue *queue)
{
    return list_item_data(queue->front);
}

void queue_remove(Queue *queue)
{
    ListItem* new_front = list_item_prev(queue->front);
    list_erase(queue->list, queue->front);
    queue->front = new_front;
    queue->length--;
}

bool queue_empty(const Queue *queue)
{
    return queue->length == 0;
}
