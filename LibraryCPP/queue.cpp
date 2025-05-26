#include "queue.h"
#include "list.h"

struct Queue {
    List* list;
};

Queue* queue_create() {
    Queue* q = new Queue;
    q->list = list_create();
    return q;
}

void queue_delete(Queue* queue) {
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    list_insert(queue->list, data);
}

Data queue_get(const Queue* queue) {
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue* queue) {
    list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue) {
    return list_first(queue->list) == nullptr;
}
