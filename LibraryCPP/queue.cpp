#include "queue.h"
#include "list.h"

struct Queue {
    List* list;
    ListItem* last;
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->last = nullptr;
    return queue;
}

void queue_delete(Queue* queue) {
    list_delete(queue->list);
    delete queue;
}


void queue_insert(Queue* queue, Data data) {
    if (queue->last != nullptr) {
        queue->last = list_insert_after(queue->list, queue->last, data);
    }
    else {
        list_insert(queue->list, data);
        queue->last = list_first(queue->list);
    }
}

Data queue_get(const Queue* queue) {
    ListItem* item = list_first(queue->list);
    if (item) {
        return list_item_data(item);
    }
    return -1;
}


void queue_remove(Queue* queue) {
    if (queue->last && queue->last == list_first(queue->list)) {
        queue->last = nullptr;
    }
    list_erase_first(queue->list);
}


bool queue_empty(const Queue* queue) {
    return list_first(queue->list) == nullptr;
}
