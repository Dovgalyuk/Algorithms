#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
    ListItem* tail;

    Queue() {
        list = list_create();
        tail = nullptr;
    }

    ~Queue() {
        list_delete(list);
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue){
        return;
    }

    queue->tail = list_insert_after(
        queue->list,
        queue->tail,
        data
    );
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue)) return -1;
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue)
{
    if (queue == nullptr || queue_empty(queue)) return;
    list_erase_first(queue->list);

    if (queue_empty(queue)) {
        queue->tail = nullptr;
    }
}

bool queue_empty(const Queue *queue)
{
    if (!queue){
        return true;
    }
    
    if (list_first(queue->list) == nullptr){
        return true;
    } else {
        return false;
    }
}
