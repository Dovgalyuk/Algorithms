#include "list.h"
#include "queue.h"
#include <stdexcept>
struct Queue {
    List* list;
};

Queue* queue_create() {
    Queue* queue = new Queue();
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue* queue) {
    if (queue) {
        list_delete(queue->list);
        delete queue;
    }
    else {
        throw std::runtime_error("Cannot delete a null queue");
    }
}

void queue_insert(Queue* queue, Data data) {
    if (queue) {
        list_insert_end(queue->list, data);
    }
    else {
        throw std::runtime_error("Cannot insert into a null queue");
    }
}

Data queue_get(const Queue* queue) {
    if (queue && queue->list) {
        if (!list_empty(queue->list)) {
            return list_item_data(list_first(queue->list));
        }
        else {
            throw std::runtime_error("Queue is empty");
        }
    }
    throw std::runtime_error("Cannot get data from a null queue");
}

void queue_remove_one(Queue* queue) {
    if (queue) {
        if (!list_empty(queue->list)) {
            list_erase_first(queue->list);
        }
        else {
            throw std::runtime_error("Cannot remove from an empty queue");
        }
    }
    else {
        throw std::runtime_error("Cannot remove from a null queue");
    }
}

bool queue_empty(const Queue* queue) {
    if (queue) {
        return list_empty(queue->list);
    }
    throw std::runtime_error("Cannot check if a null queue is empty");
}
