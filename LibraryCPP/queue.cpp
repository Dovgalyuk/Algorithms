#include "queue.h"

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue* queue)
{
    if (queue) {
        list_delete(queue->list);
        delete queue;
    }
}

void queue_insert(Queue* queue, Data data)
{
    if (queue) {
        
        if (list_first(queue->list)) {
            ListItem* last = list_item_prev(list_first(queue->list));
            list_insert_after(queue->list, last, data);
        }
        else {
            list_insert(queue->list, data);
        }
    }
}

Data queue_get(const Queue* queue)
{
    if (queue && queue->list && list_first(queue->list)) {
        return list_item_data(list_first(queue->list));
    }
    return (Data)0;
}

void queue_remove(Queue* queue)
{
    if (queue && queue->list) {
        list_erase_first(queue->list);
    }
}

bool queue_empty(const Queue* queue)
{
    return !queue || !queue->list || !list_first(queue->list);
}