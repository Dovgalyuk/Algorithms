#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;

    Queue() {
        this->list = list_create();
    }

    ~Queue(){
        list_delete(this->list);
    }
};

Queue* queue_create()
{
    return new Queue();
}

void queue_delete(Queue* queue)
{
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue_empty(queue)) list_insert(queue->list, data);
    else list_insert_after(queue->list, list_last(queue->list), data);
}

Data queue_get(const Queue* queue)
{
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue* queue)
{
    list_erase(queue->list ,list_first(queue->list));
}

bool queue_empty(const Queue* queue)
{
    return !list_first(queue->list);
}
