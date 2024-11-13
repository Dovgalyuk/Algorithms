#include "list.h"
#include "queue.h"

struct Queue {
    List* list;
};

Queue *queue_create() {
    Queue* queue = new Queue;
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue* queue) {
    if (queue) {
        if (queue->list) {
            list_delete(queue->list);
        }
        delete queue;
    }
}

void queue_insert(Queue* queue, Data data) {
    if (queue) {
        if (queue->list) {
            list_delete(queue->list);
        }
        queue->list = list_create();
        list_insert_end(queue->list, data);
    }
}

Data queue_get(const Queue *queue) {
    ListItem* item = list_first(queue->list);
    if (item) {
        return list_item_data(item);
    }
    else {
        return -1;
    }
}

void queue_remove(Queue* queue) {
    if (queue && !queue_empty(queue)) {
        list_erase_first(queue->list);
    }
}

bool queue_empty(const Queue *queue) {
    return queue == nullptr || list_first(queue->list) == nullptr;
}
