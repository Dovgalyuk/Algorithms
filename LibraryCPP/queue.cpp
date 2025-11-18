#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue *queue)
{
    if (!queue) return;
    
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;
    if (list_first(queue->list)) 
    {
        ListItem* last = list_item_prev(list_first(queue->list));
        list_insert_after(queue->list, last, data);
    } 
    else
    {
        list_insert(queue->list, data);
    }
}

Data queue_get(const Queue *queue)
{
    if (!queue) return 0;
    ListItem* first = list_first(queue->list);
    if (!first) return 0;
    
    return list_item_data(first);
}

void queue_remove(Queue *queue)
{
    if (!queue) return;
    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    if (!queue) return true;
    return list_first(queue->list) == nullptr;
}