#include "queue.h"
#include "list.h"
struct Queue
{
public:
    List* list_base;
    ListItem* last = nullptr;
    Queue()
    {
        list_base = list_create();
    }
    ~Queue()
    {
        list_delete(list_base);
    }
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->last)
    {
        queue->last = list_insert_after(queue->list_base, queue->last, data);
    }
    else
    {
        queue->last = list_insert(queue->list_base, data);
    }
}

Data queue_get(const Queue* queue)
{
    if (queue_empty(queue))
    {
        return (Data)0;
    }
    else
    {
        return list_item_data((list_first(queue->list_base)));
    }


}

void queue_remove(Queue* queue)
{
    if (!queue_empty(queue))
    {
        list_erase_first(queue->list_base);
        if (queue_empty(queue))
        {
            queue->last = nullptr;
        }
    }


}

bool queue_empty(const Queue* queue)
{
    return list_first(queue->list_base) == nullptr;
}
