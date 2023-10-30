#include "queue.h"
#include "list.h"

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
    ListItem* item = list_first(queue->list);
    if (item) {
        while (list_item_next(item) != nullptr) {
            item = list_item_next(item);
        }
        list_insert_after(queue->list, item, data);
    }
    else {
        list_insert(queue->list, data);
    }
}

Data queue_get(const Queue* queue) {
    ListItem* item = list_first(queue->list);
    if (item) {
        return list_item_data(item);
    }
    // Assuming that Data is an integer and using -1 as an error code.
    // Ideally, we should have a more robust error handling mechanism.
    return -1;
}

void queue_remove(Queue* queue) {
    list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue) {
    return list_first(queue->list) == nullptr;
}
