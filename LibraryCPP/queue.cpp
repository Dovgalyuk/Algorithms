#include "queue.h"
#include "list.h"
#include <cstddef>

struct Queue
{
    List *list;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue *queue)
{
    if (queue != NULL) {
        list_delete(queue->list);
        delete queue;
    }
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;
    ListItem* last = list_last(queue->list);
    if (last == NULL) {
        list_insert(queue->list, data);
    } else {
        list_insert_after(queue->list, last, data);
    }
}

Data queue_get(const Queue *queue)
{
    if (!queue || queue_empty(queue))
        return 0;
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue)
{
    if (!queue || queue_empty(queue))
        return;
    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    return !queue || list_first(queue->list) == NULL;
}

Data queue_size(const Queue* queue)
{
    if (!queue) return 0;
    Data count = 0;
    ListItem* item = list_first(queue->list);
    ListItem* end = list_end(queue->list);
    while (item != NULL && item != end) {
        count++;
        item = list_item_next(item);
    }
    return count;
}