#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;         
    ListItem* tail;     
};

Queue* queue_create()
{
    Queue* q = new Queue;
    q->list = list_create();
    q->tail = nullptr;
    return q;
}

void queue_delete(Queue* queue)
{
    list_delete(queue->list);
    delete queue;
}


void queue_insert(Queue* queue, Data data)
{
    if (queue->tail == nullptr)
    {
        
        queue->tail = list_insert(queue->list, data);
    }
    else
    {
        
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    }
}


Data queue_get(const Queue* queue)
{
    ListItem* first = list_first(queue->list);
    if (first == nullptr)
        return (Data)0; 

    return list_item_data(first);
}


void queue_remove(Queue* queue)
{
    ListItem* first = list_first(queue->list);
    if (first == nullptr)
        return;

    ListItem* new_first = list_erase_first(queue->list);

  
    if (new_first == nullptr)
    {
        queue->tail = nullptr;
    }
}


bool queue_empty(const Queue* queue)
{
    return list_first(queue->list) == nullptr;
}
