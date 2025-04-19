#include "list.h"

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
    ListItem* current = list_first(q->list);
    if (!current)
    {
        list_insert(q->list, data); 
        return;
    }
    
    while (list_item_next(current))
    {
        current = list_item_next(current);
    }
    
    list_insert_after(q->list, current, data);
}

bool queue_empty(const Queue* q) 
{
    return q == nullptr || list_first(q->list) == nullptr;
}

Data queue_get(const Queue* q) 
{
    if (q == nullptr || queue_empty(q)) return Data();
    return list_item_data(list_first(q->list));
}

void queue_remove(Queue* q) 
{
    if (q == nullptr || queue_empty(q)) return;
    list_erase_first(q->list);
}