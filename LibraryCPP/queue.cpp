#include "queue.h"
#include "list.h"

struct Queue
{
    List* list = list_create();
    ListItem* last = nullptr; //указатель на последний
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
    if (queue->last)
    {
        queue->last = list_insert_after(queue->list, queue->last, data);
    }
    else
    {
        queue->last = list_insert(queue->list, data);
    }
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue))
    {
        return (Data)0;
    }
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue)
{
    if(!queue_empty(queue))
    {
        list_erase_first(queue->list);
        if (queue_empty(queue))
        {
            queue->last = nullptr;
        }
    }
}

bool queue_empty(const Queue *queue)
{
    return list_first(queue->list) == nullptr;
}
