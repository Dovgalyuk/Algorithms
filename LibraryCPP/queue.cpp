#include "queue.h"
#include "list.h"
#include <stdexcept>

struct Queue {
    List* list;
    ListItem* tail;

    Queue() : list(list_create()), tail(nullptr) {}
    ~Queue() { list_delete(list); }
};

Queue* queue_create() {
    return new Queue();
}

void queue_delete(Queue* queue) {
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    if (!queue) throw std::invalid_argument("Null queue");

    if (!queue->tail) {
        queue->tail = list_insert(queue->list, data);
    } else {
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    }
}

Data queue_get(const Queue* queue) {
    if (!queue) throw std::invalid_argument("Null queue");
    if (queue_empty(queue)) throw std::out_of_range("Empty queue");

    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue* queue) {
    if (!queue || queue_empty(queue)) return;

    if (queue->tail == list_first(queue->list)) {
        queue->tail = nullptr;
    }

    list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue) {
    return !queue || !list_first(queue->list);
}