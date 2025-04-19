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

void queue_delete(Queue* q) 
{
    if (q == nullptr) return;
    
    list_delete(q->list);
    delete q;
}

void queue_insert(Queue* q, Data data) 
{
    if (q->tail == nullptr) q->tail = list_insert(q->list, data);
    else q->tail = list_insert_after(q->list, q->tail, data);
}

Data queue_get(const Queue* q) 
{
    if (q == nullptr || queue_empty(q)) return Data();

    return list_item_data(list_first(q->list));
}

void queue_remove(Queue* q) 
{
    ListItem* first = list_first(q->list);
    if (first == q->tail) q->tail = nullptr;

    list_erase_first(q->list);
}

bool queue_empty(const Queue* q) 
{
    return list_first(q->list) == nullptr;
}
