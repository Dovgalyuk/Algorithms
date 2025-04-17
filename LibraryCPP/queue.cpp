#include "list.h"
#include "queue.h"

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
        q->tail = list_insert(q->list, data);
    }
    else 
    {
        q->tail = list_insert_after(q->list, q->tail, data);
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

    if (list_first(q->list) == q->tail) 
    {
        q->tail = nullptr;
    }

    list_erase_first(q->list);
}

bool queue_empty(const Queue* q) 
{
    return q == nullptr || list_first(q->list) == nullptr;
}