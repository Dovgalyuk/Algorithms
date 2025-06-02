#include "queue.h"
#include "list.h"

struct Queue {
    List *list;
    ListItem *back;
};

Queue *queue_create() {
    Queue *queue = new Queue;
    queue->list = list_create();
    queue->back = nullptr;
    return queue;
}

void queue_delete(Queue *queue) {
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data) {
    ListItem *node = nullptr;
    if (queue->back)
        node = list_insert_after(queue->list, queue->back, data);
    else
        node = list_insert_after(queue->list, nullptr, data);
    queue->back = node;
}

Data queue_get(const Queue *queue) {
    ListItem *first = list_first(queue->list);
    return list_item_data(first);
}

void queue_remove(Queue *queue) {
    ListItem *next = list_erase_first(queue->list);
    if (!next) {
        queue->back = nullptr;
    }
}

bool queue_empty(const Queue *queue) {
    return (list_first(queue->list) == nullptr);
}