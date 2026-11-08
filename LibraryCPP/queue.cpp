#include <stdexcept>
#include "queue.h"
#include "list.h"

struct Queue {
    List* list;
    ListItem* last;
};

Queue* queue_create() {
    return new Queue{list_create(), nullptr};
}

void queue_delete(Queue* queue) {
    if (!queue) return;
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    queue->last = list_insert_after(queue->list, queue->last, data);
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) throw std::out_of_range("Queue is empty");
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue* queue) {
    list_erase_first(queue->list);
    if (queue_empty(queue)) queue->last = nullptr;
}

bool queue_empty(const Queue* queue) {
    return list_first(queue->list) == nullptr;
}
