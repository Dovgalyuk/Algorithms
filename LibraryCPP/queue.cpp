#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
    ListItem* last;
    Queue(): list(list_create()),last(0) {}

};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue->last){
        queue->last = list_insert(queue->list,data);
    }
    else {
        queue->last = list_insert_after(queue->list,queue->last,data); 
    }
}

Data queue_get(const Queue *queue)
{
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue)
{
    list_erase(queue->list,list_first(queue->list));
}

bool queue_empty(const Queue *queue)
{
    return (list_first(queue->list) == 0); 
}
