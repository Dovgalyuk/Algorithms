#include "queue.h"
#include "list.h"
#include <stdexcept>
#include <iostream>

struct Queue {
    List* list;
    ListItem* tail;
    size_t size;

    Queue() : list(nullptr), tail(nullptr), size(0) {
        try {
            list = list_create();
            if (!list) throw std::bad_alloc();
        } catch (...) {
            std::cerr << "Queue creation failed" << std::endl;
            throw;
        }
    }
    
    ~Queue() {
        if (list) {
            list_delete(list);
        }
    }
};

Queue* queue_create() {
    try {
        return new Queue();
    } catch (const std::bad_alloc&) {
        std::cerr << "Memory allocation failed in queue_create()" << std::endl;
        return nullptr;
    }
}

void queue_delete(Queue* queue) {
    if (queue) {
        delete queue;
    }
}

void queue_insert(Queue* queue, Data data) {
    if (!queue || !queue->list) {
        throw std::invalid_argument("Null queue in queue_insert");
    }

    try {
        if (!queue->tail) {
            queue->tail = list_insert(queue->list, data);
        } else {
            queue->tail = list_insert_after(queue->list, queue->tail, data);
        }
        queue->size++;
    } catch (const std::exception& e) {
        std::cerr << "queue_insert failed: " << e.what() << std::endl;
        throw;
    }
}

Data queue_get(const Queue* queue) {
    if (!queue || !queue->list) {
        throw std::invalid_argument("Null queue in queue_get");
    }
    
    ListItem* first = list_first(queue->list);
    if (!first) {
        throw std::out_of_range("Empty queue in queue_get");
    }
    
    return list_item_data(first);
}

void queue_remove(Queue* queue) {
    if (!queue || !queue->list || queue_empty(queue)) {
        return;
    }

    if (queue->tail == list_first(queue->list)) {
        queue->tail = nullptr;
    }

    list_erase_first(queue->list);
    queue->size--;
}

bool queue_empty(const Queue* queue) {
    return !queue || !queue->list || queue->size == 0;
}