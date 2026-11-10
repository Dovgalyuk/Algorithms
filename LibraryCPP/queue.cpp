#include <stdexcept>
#include "queue.h"
#include "list.h"

struct Queue {
    List* list;
};

Queue* queue_create() {
    return new Queue{list_create()};
}

void queue_delete(Queue* queue) {
    if (!queue) return;
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    list_append(queue->list, data);
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) throw std::out_of_range("Queue is empty");
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue* queue) {
    list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue) {
    return list_first(queue->list) == nullptr;
}
