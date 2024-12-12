#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
    ListItem* head;
    ListItem* tail;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->head = nullptr;
    queue->tail = nullptr;
    return queue;
}

void queue_delete(Queue* queue)
{
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->tail == nullptr) {
        queue->tail = list_insert(queue->list, data);
        queue->head = queue->tail;
    } else {
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    }
}

Data queue_get(const Queue* queue)
{
    return list_item_data(queue->head);
}

void queue_remove(Queue* queue)
{
    queue->head = list_erase_first(queue->list);
    if (queue->head == nullptr) {
        queue->tail = nullptr;
    }
}

bool queue_empty(const Queue* queue)
{
    return queue->head == nullptr;
}
