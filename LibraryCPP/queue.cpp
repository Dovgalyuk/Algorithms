#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
};

Queue *queue_create()
{
    Queue* q = new Queue;
    q->list = list_create();
    return q;
}

void queue_delete(Queue *queue)
{
    if (queue == nullptr) return;
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue == nullptr) return;
    ListItem* last = list_last(queue->list);
    list_insert_after(queue->list, last, data);
}

Data queue_get(const Queue *queue)
{
    if (queue == nullptr) return Data();
    ListItem* first = list_first(const_cast<List*>(queue->list));
    return list_item_data(first);
}

void queue_remove(Queue *queue)
{
    if (queue == nullptr) return;
    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    if (queue == nullptr) return true;
    return list_first(const_cast<List*>(queue->list)) == nullptr;
}
