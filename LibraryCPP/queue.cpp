#include "queue.h"
#include "list.h"

using namespace std;

struct Queue
{
    List *values;
};

Queue *queue_create()
{
    return new Queue{list_create()};
}

void queue_delete(Queue *queue)
{
    if (queue == nullptr)
        return;

    list_delete(queue->values);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue != nullptr)
        list_insert_after(queue->values, list_last(queue->values), data);
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue))
        return 0;

    return list_item_data(list_first(queue->values));
}

void queue_remove(Queue *queue)
{
    if (queue != nullptr)
        list_erase_first(queue->values);
}

bool queue_empty(const Queue *queue)
{
    return queue == nullptr || list_first(queue->values) == nullptr;
}
