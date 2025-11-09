#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
    ListItem* tail;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->tail = nullptr;
    return queue; 
}

void queue_delete(Queue *queue)
{
    if(!queue) return;

    if(queue->list){
        list_delete(queue->list);
        queue->list = nullptr;
    }    

    queue->tail = nullptr;
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if(!queue) return;

    if(!queue->tail){
        queue->tail = list_insert(queue->list, data);
    }
    else {
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    }
}

Data queue_get(const Queue *queue)
{
    if(!queue || !queue->list) return "";

    ListItem* first = list_first(queue->list);
    if(!first) return "";

    return list_item_data(first);
}

void queue_remove(Queue *queue)
{
    if(!queue || !queue->list) return;

    ListItem* next = list_erase_first(queue->list);

    if(!next){
        queue->tail = nullptr;
    }
}

bool queue_empty(const Queue *queue)
{
    return !queue || !queue->list || list_first(queue->list) == nullptr;
}
