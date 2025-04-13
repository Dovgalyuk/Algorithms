#include "list.h"
#include "queue.h"

struct Queue {
    List* list;
    ListItem* tail;
};

Queue *queue_create() {
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->tail = nullptr;
    return queue;
}

void queue_delete(Queue *queue) {
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    if (queue_empty(queue)) {
        queue->tail = list_insert(queue->list, data);
    }
    else {
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    }
}

Data queue_get(const Queue *queue) {
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue) {
    if (list_first(queue->list) == queue->tail) {
        queue->tail = nullptr;
    }
    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue) {
    return list_first(queue->list) == nullptr;
}