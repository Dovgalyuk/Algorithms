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
    if (queue != nullptr) { 
        list_delete(queue->list); 
        delete queue; 
    }
}

void queue_insert(Queue *queue, Data data)
{
     if (queue != nullptr) { 
        list_insert_end(queue->list, data); 
    }
}

Data queue_get(const Queue *queue)
{
    if (queue != nullptr && list_first(queue->list) != nullptr) {
        return list_item_data(list_first(queue->list));
    }
    return Data();
}

void queue_remove(Queue *queue)
{
    if (queue != nullptr) { 
        list_erase_first(queue->list); 
    }
}

bool queue_empty(const Queue *queue)
{
    return list_first(queue->list) == nullptr;
}
