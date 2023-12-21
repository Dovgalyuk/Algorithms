#include "list.h"
#include "queue.h"

struct Queue
{
    List* data;
    ListItem* tail;
};

Queue *queue_create()
{
    Queue* temp = new Queue;
    temp->data = list_create();
    temp->tail = nullptr;
    return temp;
}

void queue_delete(Queue *queue)
{
    list_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->tail) {
        queue->tail = list_insert_after(queue->data, queue->tail, data);
    } else {
        queue->tail = list_insert(queue->data, data);
    }
}

Data queue_get(const Queue *queue)
{
    return list_item_data(list_first(queue->data));
}

void queue_remove(Queue *queue)
{
    if (!queue_empty(queue)) {
        list_erase_first(queue->data);

        if (queue_empty(queue)) {
            queue->tail = nullptr;
        }
    }
}

bool queue_empty(const Queue *queue)
{
    return (list_first(queue->data) == nullptr);
}
