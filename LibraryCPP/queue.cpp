#include "queue.h"
#include "list.h"
#include <stdexcept>

struct Queue {
    List* list;
    ListItem* tail;

    Queue() : list(nullptr), tail(nullptr) {}
    ~Queue() {
        if (list) list_delete(list);
    }
};

Queue* queue_create() {
    Queue* queue = new Queue();
    queue->list = list_create();
    queue->tail = nullptr;
    return queue;
}

void queue_delete(Queue* queue) {
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    if (!queue) throw std::invalid_argument("Null queue in queue_insert");

    if (queue->tail == nullptr) {
        queue->tail = list_insert(queue->list, data);
    } else {
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    }
}

Data queue_get(const Queue* queue) {
    if (!queue) throw std::invalid_argument("Null queue in queue_get");
    if (queue_empty(queue)) throw std::out_of_range("queue_get from empty queue");

    ListItem* first = list_first(queue->list);
    if (!first) throw std::out_of_range("queue_get: no first item");

    return list_item_data(first);
}

void queue_remove(Queue* queue) {
    if (!queue) throw std::invalid_argument("Null queue in queue_remove");
    if (queue_empty(queue)) return;

    ListItem* first = list_first(queue->list);
    if (!first) return;

    if (first == queue->tail) {
        queue->tail = nullptr;
    }

    list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue) {
    if (!queue) return true;
    return list_first(queue->list) == nullptr;
}
