#include "queue.h"
#include "list.h"
#include <stdexcept>

struct Queue {
    List* list;
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue* queue) {
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    list_insert(queue->list, data);
}

Data queue_get(const Queue* queue) {
    ListItem* item = list_first(queue->list);
    if (!item) {
        throw std::out_of_range("Queue is empty");
    }
    return list_item_data(item);
}

void queue_remove(Queue* queue) {
    if (queue_empty(queue)) {
        throw std::out_of_range("Queue is empty");
    }
    list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue) {
    return list_first(queue->list) == nullptr;
}
