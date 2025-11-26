#include "queue.h"
#include "list.h"

struct Queue {
    List* list;
    ListItem* tail; 
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->tail = nullptr;
    return queue;
}

void queue_delete(Queue* queue) {
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    if (queue->tail)
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    else
        queue->tail = list_insert(queue->list, data);
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) return (Data)0;
    ListItem* first = list_first(queue->list);
    return list_item_data(first);
}

void queue_remove(Queue* queue) {
    ListItem* first = list_first(queue->list);
    if (!first) return;
    list_erase_first(queue->list);
    if (first == queue->tail) queue->tail = nullptr;
}

bool queue_empty(const Queue* queue) {
    return list_first(queue->list) == nullptr;
}
