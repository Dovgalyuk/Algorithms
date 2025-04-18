#include "list.h"
#include "queue.h"

struct Queue 
{
    List* list;
};

Queue* queue_create() 
{
    Queue* q = new Queue;
    q->list = list_create();
    return q;
}

void queue_delete(Queue* q) 
{
    if (q == nullptr) return;

    list_delete(q->list);
    delete q;
}

void queue_insert(Queue* q, Data data) 
{
    if (q == nullptr) return;

    if (queue_empty(q))
    {
        list_insert(q->list, data);
    }
    else
    {
        ListItem* last = list_first(q->list);
        while (list_item_next(last) != nullptr)
        {
            last = list_item_next(last);
        }
        list_insert_after(q->list, last, data);
    }
}

Data queue_get(const Queue* q) 
{
    if (q == nullptr || queue_empty(q))
    {
        return Data();
    }
    return list_item_data(list_first(q->list));
}

void queue_remove(Queue* q) 
{
    if (q == nullptr || queue_empty(q)) return;
    list_erase_first(q->list);
}

bool queue_empty(const Queue* q) 
{
    return q == nullptr || list_first(q->list) == nullptr;
}