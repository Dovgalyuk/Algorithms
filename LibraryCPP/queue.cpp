#include "queue.h"
#include "list.h"

struct Queue
{
    List* _list = list_create();
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    list_delete(queue->_list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    list_insert_after(queue->_list, list_last(queue->_list), data);
}

Data queue_get(const Queue *queue)
{
    return list_item_data(list_first(queue->_list));
}

void queue_remove(Queue *queue)
{
    list_erase(queue->_list, list_first(queue->_list));
}

bool queue_empty(const Queue *queue)
{
    return list_first(queue->_list) == nullptr;
}
