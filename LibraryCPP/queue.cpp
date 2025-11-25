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
    list_delete(queue->list);
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    ListItem* first = list_first(queue->list);
    if (first) {
        ListItem* last = list_item_prev(first);
        list_insert_after(queue->list, last, data);
    }
    else {
        list_insert(queue->list, data);
    }
}

Data queue_get(const Queue *queue)
{
    ListItem* first = list_first(queue->list);
    return list_item_data(first);
}

void queue_remove(Queue *queue)
{
        list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    return list_first(queue->list) == nullptr;
}
